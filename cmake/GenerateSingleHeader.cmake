# This cmake script is used to generate a single header file with all of tweeny
find_program(UVX_EXECUTABLE NAMES uvx REQUIRED)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/single-header)

add_custom_target(single-header
  COMMAND ${UVX_EXECUTABLE} quom
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tweeny/tweeny.h
    ${CMAKE_CURRENT_BINARY_DIR}/single-header/tweeny-${Tweeny_VERSION}.h
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Generating single header file"
)
