# This file is part of the Tweeny library.
#
# Copyright (c) 2016-2021 Leonardo Guilherme Lucena de Freitas
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

# This file purpose is to setup exports and version files, so that other people using cmake can use the library
# when installed.

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# Setup install of exported targets
install(
    EXPORT TweenyTargets
    NAMESPACE tweeny::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/tweeny
)

# Macro to write config
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/TweenyConfigVersion.cmake"
    VERSION ${Tweeny_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Setup install of version config
install(
    FILES
        cmake/TweenyConfig.cmake
        "${CMAKE_CURRENT_BINARY_DIR}/TweenyConfigVersion.cmake"
    DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/Tweeny
)
