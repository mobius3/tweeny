# Tweeny

Tweeny is an inbetweening library designed for the creation of complex animations for games and other beautiful interactive software. It leverages features of modern C++ to empower developers with an intuitive API for declaring tweenings of any type of value, as long as they support arithmetic operations.

The goal of Tweeny is to provide means to create fluid interpolations when animating position, scale, rotation, frames or other values of screen objects, by setting their values as the tween starting point and then, after each tween step, plugging back the result.

**It features**:

- A descriptive and (hopefully) intuitive API,
- 30+ easing functions,
- Allows custom easing functions,
- Multi-point tweening,
- Simultaneous tween of heterogeneous value sets,
- Timeline-like usage (allows seeking to any point),
- Header-only
- Zero external dependencies
- Steps forwards or backwards :)
- Accepts lambdas, functors and functions as step and seek callbacks

**Obligatory hello world example**:

```cpp
auto helloworld = tweeny::from('h','e', 'l', 'l', 'o').to('w', 'o', 'r', 'l', 'd').during(50);
for (int i = 0; i < 50; i++) {
    for (char c : helloworld.step(1)) { printf("%c", c); }
    printf("\n");
}
```

There are more complex examples in the `examples` folder.

## Installation methods:

You just need to adjust your include path to point to the `include/` folder.

**Copying the `include` folder:**

Tweeny itself is a header only library. The easiest way to use it is to copy the `include/` folder into your project folder and then include from it: `#include "tweeny/tweeny.h"`

**CMake subproject**

This is useful if you are using CMake already. Copy the whole tweeny project and include it in a top-level `CMakeLists.txt` file and then use `target_link_libraries` to add it to your target:

```
add_subdirectory(tweeny)
target_link_libraries(yourtarget tweeny)
```
This will add the `include/` folder to your search path, and you can `#include "tweeny.h"`.

## Contributing

Tweeny is open-source, meaning that it is open to modifications and contrubutions from the community (you are very much encouraged to do so!). However, we'd appreciate if you follow these guidelines:

- Don't use `PascalCase` nor `snake_case` in names
- Use `camelCase`, but try to avoid multi word names as hard as possible
- Document code using Doxygen
- Implementation details should go inside `tweeny::detail` namespace.
- Template implementations should go into a `.tcc` file
