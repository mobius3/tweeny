# This file is part of the Tweeny library.
#
# Copyright (c) 2016 Leonardo G. Lucena de Freitas
# Copyright (c) 2016 Guilherme R. Costa
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
# the Software, and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
# FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
# IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

# The purpose of this file is to include all examples subdirectories.
macro(add_example)
    set(TARGET ${ARGV0})
    set(SOURCES "${ARGN}")
    list(REMOVE_AT SOURCES 0)
    string(TOUPPER ${TARGET} TARGET_UPPER)
    option(TWEENY_EXAMPLE_${TARGET_UPPER} "Build the ${TARGET} example." ON)
    if (TWEENY_EXAMPLE_${TARGET_UPPER})
        add_executable(${TARGET} ${SOURCES})
        target_link_libraries(${TARGET} PRIVATE tweeny)
    endif()
endmacro()

if (CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ALLOW_MEMORY_GROWTH=1")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

add_example(multitype multitype/multitype.cpp)
add_example(easings easings/easings.cpp)
add_example(loop loop/loop.cpp)

add_example(sprite
    sprite/main.cpp
    sprite/stb_image.h
    sprite/sprite.cpp
    sprite/sprite.h
    sprite/engine.cpp
    sprite/engine.h
    sprite/input.cpp
    sprite/input.h
    sprite/resources.c
)

if (TWEENY_EXAMPLE_SPRITE)
    find_package(SDL2 REQUIRED)
    string(STRIP ${SDL2_LIBRARIES} SDL2_LIBS)
    target_link_libraries(sprite PRIVATE ${SDL2_LIBS})
    target_include_directories(sprite PRIVATE ${SDL2_INCLUDE_DIRS})
endif()

