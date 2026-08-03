# Tweeny
<a href="https://repology.org/project/tweeny/versions">
    <img src="https://repology.org/badge/vertical-allrepos/tweeny.svg" alt="Packaging status" align="right" style="padding-left: 20px">
</a>

Tweeny is a modern C++ inbetweening library for creating complex animations in games and other interactive software. It provides a type-safe, fluent API for declaring interpolations of any value that supports arithmetic operations.

The goal of Tweeny is to make it easy to animate position, scale, rotation, color, or any other property: set the starting values, step the tween each frame, and plug the result back into your object.

**It features**:

- A fluent builder API with compile-time safety
- 30+ easing functions, plus support for custom easings
- Multi-point keyframe animations
- Simultaneous tweening of heterogeneous value sets
- Timeline-like control (`seek`, `jump`, backward stepping)
- An event system for step, seek, jump, update, completion, and keyframe enter/leave
- Header-only, zero external dependencies
- C++17

**Obligatory hello world example**:

Linearly interpolate character by character from *hello* to *world* in `50` frames:

```cpp
#include <tweeny/tweeny.h>

auto helloworld = tweeny::from('h', 'e', 'l', 'l', 'o')
                    .to('w', 'o', 'r', 'l', 'd')
                    .during(50U)
                    .build();

for (int i = 0; i < 50; i++) {
    auto [w, o, r, l, d] = helloworld.step(1);
    printf("%c%c%c%c%c\n", w, o, r, l, d);
}
```

A few more patterns:

```cpp
using tweeny::easing;

// Easing
auto smooth = tweeny::from(0.0f)
                  .to(100.0f)
                  .via(easing::quadraticInOut)
                  .during(60U)
                  .build();

// Multi-segment keyframe animation
auto path = tweeny::from(0)
                .to(50).via(easing::linear).during(30U)
                .to(100).via(easing::bounceOut).during(30U)
                .build();

// Events
auto tween = tweeny::from(0).to(100).during(60U).build();
tween.on(tweeny::event::update, [](auto& t) {
    printf("now at %d\n", t.peek());
    return tweeny::event::response::ok;
});
tween.on(tweeny::event::complete, [](auto& t) {
    printf("done at %d\n", t.peek());
    return tweeny::event::response::ok;
});
```

## Migrating from 3.x

Tweeny 4.x introduces breaking API changes. The previous README for version 3.x is kept in [README-3.md](README-3.md).

Key differences:

- `tweeny::from(...)` returns a **builder** — call `.build()` to get a tween
- Durations use `uint32_t` (`60U`), steps use `int32_t` (negative values step backward)
- Callbacks use `on(event::step, ...)` instead of `onStep()` / `onSeek()`
- Multi-value tweens return `std::tuple` (use structured bindings)

Build the Doxygen documentation (`-DTWEENY_BUILD_DOCUMENTATION=ON`) for the full migration guide.

## Installation

**Using your package manager**

There are some packages for tweeny made by some great people. Repology has a list of them and their versions [here](https://repology.org/metapackage/tweeny/versions). Thanks, great people!

**Copying the `include/` folder**

Tweeny is header-only. Copy `include/` into your project and include:

```cpp
#include <tweeny/tweeny.h>
```

**Single-header file**

Tweeny releases include a single-header file with all the necessary code glued together. Simply drop it on your project and/or adjust the include path and then `#include "tweeny-<version>.h"` (eg `#include "tweeny-4.0.0.h"`).

**CMake subproject**

```cmake
add_subdirectory(tweeny)
target_link_libraries(yourtarget PRIVATE tweeny::tweeny)
```

This adds the `include/` directory to your target and requires C++17.

**CMake install + `find_package`**

Install the headers and CMake package config, then consume Tweeny from another project:

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
cmake --install build --prefix /path/to/prefix
```

```cmake
find_package(Tweeny 4 CONFIG REQUIRED)
target_link_libraries(yourtarget PRIVATE tweeny::tweeny)
```

Point CMake at the install prefix if needed (`CMAKE_PREFIX_PATH`). After linking `tweeny::tweeny`, include as usual:

```cpp
#include <tweeny/tweeny.h>
```

## Documentation

The library is documented with Doxygen. Build it with:

```sh
cmake -B build -DTWEENY_BUILD_DOCUMENTATION=ON
cmake --build build --target doc
```

Easing function visualizations: [easings.net](http://easings.net/)

## Contributing

Tweeny is open-source and welcomes contributions. Please follow these guidelines:

- Don't use `PascalCase` nor `snake_case` in names
- Use `camelCase`, but try to avoid multi-word names as hard as possible
- Document code using Doxygen
- Implementation details should go inside the `tweeny::detail` namespace
- Template implementations should go into a `.tcc` file

## License

Tweeny is licensed under the MIT License. See [LICENSE](LICENSE).
