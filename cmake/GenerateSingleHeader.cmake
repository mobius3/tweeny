# This cmake script is used to generate a single header file with all of tweeny
find_package(Python3 3.6 COMPONENTS Interpreter QUIET)

if (NOT Python3_Interpreter_FOUND)
  message(STATUS "Python 3.6+ interpreter not found. Single-header include file will NOT be created")
  return()
endif()

find_program(QUOM_EXECUTABLE NAMES quom)
if (NOT QUOM_EXECUTABLE)
  message(STATUS "quom program not found. Install it with: pip3 install quom")
  return()
endif()

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/single-header)

add_custom_target(single-header
  COMMAND
  ${QUOM_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/include/tweeny.h ${CMAKE_CURRENT_BINARY_DIR}/single-header/tweeny-${Tweeny_VERSION}.h
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Generating single header file"
)