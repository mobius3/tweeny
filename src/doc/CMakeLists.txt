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

# This cmake file creates and builds doxygen documentation. It also sets it in the install list.

find_package(Doxygen REQUIRED)

configure_file(Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

set(DOC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/mainpage.dox"
    "${CMAKE_CURRENT_SOURCE_DIR}/manual.dox"
    "${CMAKE_CURRENT_SOURCE_DIR}/v3_to_v4.dox"
    "${CMAKE_CURRENT_SOURCE_DIR}/DoxygenLayout.xml"
    "${CMAKE_CURRENT_SOURCE_DIR}/tweeny-styling.css"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../README.md"
)

add_custom_target(doc ALL
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../../README.md ${CMAKE_CURRENT_BINARY_DIR}/
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${DOC_FILES} ${CMAKE_CURRENT_BINARY_DIR}/
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/fonts ${CMAKE_CURRENT_BINARY_DIR}/fonts
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_BINARY_DIR}/fonts ${CMAKE_CURRENT_BINARY_DIR}/html/fonts
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${DOC_FILES} Doxyfile.in
    COMMENT "Generating API documentation with Doxygen" VERBATIM
)

include(GNUInstallDirs)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION ${CMAKE_INSTALL_DOCDIR})
