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

# This file setups CPack to generate packages for Tweeny

# Setup CPack variables
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Tweeny - a modern C++ tweening library.")
set(CPACK_PACKAGE_VERSION_MAJOR "${TWEENY_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${TWEENY_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${TWEENY_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT "leonardo.guilherme@gmail.com")
set(CPACK_MONOLITHIC_INSTALL TRUE)
set(CPACK_GENERATOR ZIP)

# On Windows, also generate a NSIS package
if (WIN32)
    list(APPEND CPACK_GENERATOR NSIS)
endif()

# On Unix-not-apple, generate tgz, deb and rpm packages
if (UNIX AND NOT APPLE)
    list(APPEND CPACK_GENERATOR TGZ)
    list(APPEND CPACK_GENERATOR DEB)
    list(APPEND CPACK_GENERATOR RPM)
endif()

# This will enable the `make package` target.
include(CPack)

