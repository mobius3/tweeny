# Tweeny Changelog
- Version 4:
  - Fix point progress calculation in multi-duration tweens (#15)
- Version 3:
  - Fix point duration calculation in multipoint tweening 
  - Implement `peek(float progress)` and `peek(uint32_t time)` to peek
    at arbitrary points
  - Move examples to [tweeny-demos](github.com/mobius3/tweeny-demos) repository
  - Update README and docs

- Version 2:
  - Make non-modifying functions `const` (@Balletie)
  - Add `peek()` tween method to get current tween values (@Balletie)
  - Fix build on MSVC by constexpr-instantiating standard easings
  - Add a CHANGELOG :)

- Version 1:
  - Initial Release
