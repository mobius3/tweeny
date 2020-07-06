# This cmake script is used to generate a single header file with all of tweeny
find_package(Python 3.6 QUIET)

if (NOT PYTHON_FOUND)
  message(STATUS "Python 3.6 not found. Single-header include file will NOT be created")
  return()
endif()

find_program(QUOM_EXECUTABLE NAMES quom)
if (QUOM_EXECUTABLE-NOTFOUND)
  message(STATUS "quom program not found. Install it with pip or easy_install")
  return()
endif()

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/single-header)

add_custom_target(single-header
  COMMAND
  ${QUOM_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/include/tweeny.h ${CMAKE_CURRENT_BINARY_DIR}/single-header/tweeny-${Tweeny_VERSION}.h
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Generating single header file"
)