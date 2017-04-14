# Tweeny Changelog
- Version 3:
  - Implement `peek(float progress)` and `peek(uint32_t time)` to peek
    at arbitrary points
  - Improve README instructions on how to build examples
  - Avoid building the sprite example if SDL2 was not found

- Version 2:
  - Make non-modifying functions `const` (@Balletie)
  - Add `peek()` tween method to get current tween values (@Balletie)
  - Fix build on MSVC by constexpr-instantiating standard easings
  - Add a CHANGELOG :)

- Version 1:
  - Initial Release
