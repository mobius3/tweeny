# This file is part of the Tweeny library.
#
# Copyright (c) 2016-2018 Leonardo G. Lucena de Freitas
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

# This file defines the tweeny-extras-sdl2 target

project(tweeny-extras-sdl)
find_package(SDL2 QUIET)

if (NOT SDL2_FOUND)
  message(STATUS "SDL2 was not found. tweeny-extras-sdl2 will not be built.")
  return()
endif ()


add_library(tweeny-extras-sdl2 STATIC
  engine.cpp
  input.cpp
  sprite.cpp
  color.cpp
  rect.cpp
  point.cpp
  cursor.cpp
  stb_image.c)

if (TARGET SDL2::SDL2)
  target_link_libraries(tweeny-extras-sdl2 PUBLIC SDL2::SDL2)
elseif (SDL2_LIBRARIES)
  string(STRIP ${SDL2_LIBRARIES} SDL2_LIBS)
  target_link_libraries(tweeny-extras-sdl2 PUBLIC ${SDL2_LIBS})
  target_include_directories(tweeny-extras-sdl2 PRIVATE ${SDL2_INCLUDE_DIRS})
endif ()

target_include_directories(tweeny-extras-sdl2 PUBLIC ${CMAKE_SOURCE_DIR}/)

add_library(tweeny::extras::sdl2 ALIAS tweeny-extras-sdl2)


