# Tweeny Changelog
- Version 4.1.0
  - Added `easing::byName` for runtime easing selection by identifier name

- Version 4.0.0
  - **Breaking:** Requires C++17
  - **Breaking:** `tweeny::from()` returns a builder; call `.build()` to create a tween
  - **Breaking:** Tweens are immutable after `build()` (keyframes, durations, and easings cannot be changed)
  - **Breaking:** Durations must be `uint32_t` (`during(60U)`); `step()` accepts `int32_t` frame deltas only (no percentage mode)
  - **Breaking:** `seek()` accepts `uint32_t` absolute frame positions only (no percentage mode)
  - **Breaking:** Multi-value tweens return `std::tuple` instead of `std::array`
  - **Breaking:** Callbacks use `on(event::…)` with `event::response` return values instead of `onStep()` / `onSeek()`
  - **Breaking:** `forward()` / `backward()` removed; use negative `step()` values to move backward
  - **Breaking:** Headers moved to `include/tweeny/`; include as `#include <tweeny/tweeny.h>`
  - **Breaking:** Removed `easing::enumerated` and string-based `via("linear")` easing selection
  - New event types: `complete`, `keyframeEnter`, `keyframeLeave`, `update`
  - New methods: `peek()`, `peek(frame)`, `progress()`, `jump(keyframe)`
  - Restructured internals under `tweeny::detail`; easing split into per-function headers
  - Added Catch2 test suite and Doxygen manual with v3-to-v4 migration guide
  - CMake: C++17 enforcement, `FILE_SET HEADERS`, optional tests and single-header target (via `uvx` + quom)
  - Fixed exponential easing endpoints (`position == 0` / `== 1`) to match Penner behavior
  - Expanded tests: Penner reference samples for bundled easings (direct + `via`); `def`/`stepped` (including multi-keyframe stepped); seek/step/jump vs `peek` consistency
  - GitHub Actions CI (Ubuntu, Catch2, build + ctest)
  - `scripts/create-release.sh` — release from an existing tag (docs sync to `gh-pages`, single-header asset, GitHub Release)
  - README: CMake install + `find_package(Tweeny)`; fixed installed include interface so `#include <tweeny/tweeny.h>` works after install
  - Docs: `event::update`, `progress()`, honest zero-`during()` behavior; Doxygen styling aligned with the site
  - Removed sandbox CMake option/target

- Version 3.2.1
  - Adds `<string>` as dependency

- Version 3.2.0
  -  Fixed installation on other than Ubuntu distributions. (@xvitaly)
  -  Consider interpolation duration in the right place (fix #19)
  -  Fixes compilation error when using the `jump` function (fix #21)
  -  Small code and documentation improvements
  -  **New feature**: allows easing selection (`via()`) using `easing::enumerated` or `std::string`:
  ```
    tweeny::from(0.0f).to(1.0f).during(100).via(easing::enumerated::linear);
    tweeny::from(0.0f).to(1.0f).during(100).via("linear");
  ```

- Version 3.1.1
  - Remove unused CMake options
  - Adds a single header version

- Version 3.1.0:
  - From now on, tweeny will be using a more traditional versioning scheme
  - Remove some extraneous semicolons (@Omegastick)
  - Adds `easing::stepped` and `easing::def` for arithmetic-like values (@ArnCarveris)
  - Fix point progress calculation in multi-duration tweens (#15)
  - Fix deduction of same-type values (#14)
  - Use `auto` to deduce return values of operations inside various easings

- Version 3:
  - Fix point duration calculation in multipoint tweening 
  - Implement `peek(float progress)` and `peek(uint32_t time)` to peek
    at arbitrary points
  - Move examples to [tweeny-demos](http://github.com/mobius3/tweeny-demos) repository
  - Update README and docs

- Version 2:
  - Make non-modifying functions `const` (@Balletie)
  - Add `peek()` tween method to get current tween values (@Balletie)
  - Fix build on MSVC by constexpr-instantiating standard easings
  - Add a CHANGELOG :)

- Version 1:
  - Initial Release
