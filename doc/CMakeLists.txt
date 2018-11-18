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

find_package(Doxygen)
if (TWEENY_BUILD_DOCUMENTATION)
    set(DOC_ADD_TO_ALL ALL)
else()
    set(DOC_ADD_TO_ALL "")
endif()

if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../README.md DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    file(COPY
            ${CMAKE_CURRENT_SOURCE_DIR}/DoxygenLayout.xml
            ${CMAKE_CURRENT_SOURCE_DIR}/MANUAL.dox
         DESTINATION
            ${CMAKE_CURRENT_BINARY_DIR}
    )
    add_custom_target(doc ${DOC_ADD_TO_ALL}
            ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen" VERBATIM)

    if (TWEENY_BUILD_DOCUMENTATION)
        install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc/Tweeny)
    endif()

endif(DOXYGEN_FOUND)
