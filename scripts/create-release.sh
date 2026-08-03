#!/usr/bin/env bash
# create-release.sh — publish a Tweeny GitHub Release from an existing tag.
#
# Usage:
#   ./scripts/create-release.sh X.Y.Z
#
# Prerequisites (must already exist on origin):
#   - Git tag vX.Y.Z
#   - CMakeLists.txt project VERSION equals X.Y.Z
#   - CHANGELOG.md section "- Version X.Y.Z"
#
# Required tools: git, cmake, doxygen, uvx, gh (authenticated)
#
# What it does:
#   1. Clones origin into /tmp, checks out vX.Y.Z
#   2. Builds Doxygen docs + single-header
#   3. Syncs docs into a fresh gh-pages clone and pushes if changed
#   4. Creates GitHub Release vX.Y.Z with changelog notes + tweeny-X.Y.Z.h
#   5. Removes both /tmp clones (also on failure via trap)

set -euo pipefail

usage() {
  echo "Usage: $0 X.Y.Z" >&2
  exit 1
}

if [[ $# -ne 1 ]]; then
  usage
fi

VERSION="$1"
if [[ ! "$VERSION" =~ ^[0-9]+\.[0-9]+\.[0-9]+$ ]]; then
  echo "error: version must be bare semver X.Y.Z (got: $VERSION)" >&2
  exit 1
fi

TAG="v${VERSION}"
PID="$$"
SRC_DIR="/tmp/tweeny-release-${PID}-src"
PAGES_DIR="/tmp/tweeny-release-${PID}-pages"

cleanup() {
  rm -rf "${SRC_DIR}" "${PAGES_DIR}"
}
trap cleanup EXIT

for cmd in git cmake doxygen uvx gh; do
  if ! command -v "$cmd" >/dev/null 2>&1; then
    echo "error: required tool not found: $cmd" >&2
    exit 1
  fi
done

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(git -C "${SCRIPT_DIR}" rev-parse --show-toplevel)"
ORIGIN="$(git -C "${REPO_ROOT}" remote get-url origin)"

echo "==> Cloning ${ORIGIN} → ${SRC_DIR}"
git clone "${ORIGIN}" "${SRC_DIR}"

echo "==> Checking out ${TAG}"
git -C "${SRC_DIR}" checkout "${TAG}"

CMAKE_VERSION="$(
  sed -nE 's/^project\([^)]*[[:space:]]VERSION[[:space:]]+([0-9]+\.[0-9]+\.[0-9]+).*/\1/p' \
    "${SRC_DIR}/CMakeLists.txt" | head -n1
)"
if [[ -z "${CMAKE_VERSION}" ]]; then
  echo "error: could not parse project VERSION from CMakeLists.txt" >&2
  exit 1
fi
if [[ "${CMAKE_VERSION}" != "${VERSION}" ]]; then
  echo "error: CMakeLists.txt VERSION is ${CMAKE_VERSION}, expected ${VERSION}" >&2
  exit 1
fi
echo "==> CMake VERSION matches ${VERSION}"

CHANGELOG="${SRC_DIR}/CHANGELOG.md"
if ! grep -qE "^- Version ${VERSION}(:|[[:space:]]|$)" "${CHANGELOG}"; then
  echo "error: CHANGELOG.md has no '- Version ${VERSION}' section" >&2
  exit 1
fi

NOTES_FILE="${SRC_DIR}/.release-notes.md"
# Extract from "- Version $VERSION" through the line before the next "- Version "
awk -v ver="${VERSION}" '
  BEGIN { printing = 0 }
  $0 ~ ("^- Version " ver "(:|[[:space:]]|$)") { printing = 1 }
  printing && $0 ~ /^- Version / && $0 !~ ("^- Version " ver "(:|[[:space:]]|$)") { exit }
  printing { print }
' "${CHANGELOG}" > "${NOTES_FILE}"

if [[ ! -s "${NOTES_FILE}" ]]; then
  echo "error: failed to extract changelog section for ${VERSION}" >&2
  exit 1
fi
echo "==> Extracted CHANGELOG section for ${VERSION}"

echo "==> Configuring (docs + single-header)"
cmake -S "${SRC_DIR}" -B "${SRC_DIR}/build" \
  -DTWEENY_BUILD_DOCUMENTATION=ON \
  -DTWEENY_BUILD_SINGLE_HEADER=ON

echo "==> Building doc + single-header"
cmake --build "${SRC_DIR}/build" --target doc single-header

HTML_DIR="${SRC_DIR}/build/src/doc/html"
HEADER_ASSET="${SRC_DIR}/build/single-header/tweeny-${VERSION}.h"

if [[ ! -d "${HTML_DIR}" ]]; then
  echo "error: Doxygen output missing: ${HTML_DIR}" >&2
  exit 1
fi
if [[ ! -f "${HEADER_ASSET}" ]]; then
  echo "error: single-header asset missing: ${HEADER_ASSET}" >&2
  exit 1
fi

echo "==> Cloning gh-pages → ${PAGES_DIR}"
git clone --branch gh-pages --single-branch "${ORIGIN}" "${PAGES_DIR}"

echo "==> Syncing Doxygen html/ → doc/"
rm -rf "${PAGES_DIR}/doc"
mkdir -p "${PAGES_DIR}/doc"
cp -a "${HTML_DIR}/." "${PAGES_DIR}/doc/"

git -C "${PAGES_DIR}" add doc/
if git -C "${PAGES_DIR}" diff --cached --quiet; then
  echo "==> No doc/ changes; skipping gh-pages push"
else
  echo "==> Committing and pushing docs for ${TAG}"
  git -C "${PAGES_DIR}" commit -m "docs: publish API docs for ${TAG}"
  git -C "${PAGES_DIR}" push origin gh-pages
fi

if (cd "${SRC_DIR}" && gh release view "${TAG}" >/dev/null 2>&1); then
  echo "error: GitHub release ${TAG} already exists" >&2
  exit 1
fi

echo "==> Creating GitHub release ${TAG}"
# Run from the src clone so gh resolves owner/repo from origin.
(
  cd "${SRC_DIR}"
  gh release create "${TAG}" \
    --title "${TAG}" \
    --notes-file "${NOTES_FILE}" \
    "${HEADER_ASSET}"
)

echo "==> Done: ${TAG} released; cleaning up clones"
# trap cleanup removes SRC_DIR and PAGES_DIR on EXIT
