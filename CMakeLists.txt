# This file is part of the Tweeny library.
#
# Copyright (c) 2016-2020 Leonardo Guilherme Lucena de Freitas
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

# This file specifies an INTERFACE library, allowing you to include Tweeny in your CMake project.
# To use Tweeny in your project, put this folder under your source dir and use `add_subdirectory(tweeny)`. For every
# target that uses tweeny, a simple `target_link_libraries(target tweeny)` is sufficient to set up include and link
# instructions.

cmake_minimum_required(VERSION 3.0)
project(Tweeny)

# Setup variables and options
option(TWEENY_BUILD_EXAMPLES "Build examples contained in examples/ folder. It might require additional dependencies." ON)
option(TWEENY_BUILD_DOCUMENTATION "Attempts to build the documentation. You'll need doxygen and graphviz installed" OFF)
option(TWEENY_BUILD_EXTRAS "Attempts to build extra goodies on extras/ folder. It will require additional dependencies" ON)

# Setup version
include(cmake/SetupVersion.cmake)

# The library target
add_library(tweeny INTERFACE)

# Specify the C++ features a compiler should have to use this library.
if(NOT CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    target_compile_features(tweeny
        INTERFACE
        cxx_auto_type
        cxx_variadic_templates
        cxx_lambdas
        cxx_nullptr
        cxx_right_angle_brackets
        cxx_static_assert
        cxx_template_template_parameters
    )
else()
    list(APPEND CMAKE_CXX_FLAGS -std=c++11)
endif()

# Set up include directories
target_include_directories(tweeny INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/tweeny>
)

# Set up install
install(TARGETS tweeny EXPORT TweenyTargets)
install(DIRECTORY include/ DESTINATION include/tweeny)

# Set up export and config
include(cmake/SetupExports.cmake)

if (TWEENY_BUILD_DOCUMENTATION)
    add_subdirectory(doc)
endif()

# This library is a convenience library to force files appear in the IDE properly.
add_library(tweeny-dummy
        include/tweeny.h
        include/tweeny.tcc
        include/tween.h
        include/tween.tcc
        include/tweenone.tcc
        include/tweenpoint.h
        include/tweenpoint.tcc
        include/tweentraits.h
        include/easing.h
        include/easingresolve.h
        include/int2type.h
        include/dispatcher.h)
set_target_properties(tweeny-dummy PROPERTIES LINKER_LANGUAGE CXX EXCLUDE_FROM_ALL TRUE)