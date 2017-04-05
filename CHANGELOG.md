# Tweeny Changelog
- Version 3:
  - Implement `peek(float progress)` and `peek(uint32_t time)` to peek
    at arbitrary points

- Version 2:
  - Make non-modifying functions `const` (@Balletie)
  - Add `peek()` tween method to get current tween values (@Balletie)
  - Fix build on MSVC by constexpr-instantiating standard easings
  - Add a CHANGELOG :)

- Version 1:
  - Initial Release
