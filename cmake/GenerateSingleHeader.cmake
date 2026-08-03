# This cmake script is used to generate a single header file with all of tweeny
find_program(UVX_EXECUTABLE NAMES uvx REQUIRED)

set(_single_header_dir "${CMAKE_CURRENT_BINARY_DIR}/single-header")
set(_single_header_file "${_single_header_dir}/tweeny-${Tweeny_VERSION}.h")
set(_single_header_tmp "${_single_header_file}.tmp")

file(MAKE_DIRECTORY "${_single_header_dir}")

add_custom_target(single-header
  COMMAND ${UVX_EXECUTABLE} quom
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tweeny/tweeny.h
    ${_single_header_tmp}
  COMMAND ${CMAKE_COMMAND}
    -DINPUT=${_single_header_tmp}
    -DOUTPUT=${_single_header_file}
    -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/DedupeLicense.cmake
  COMMAND ${CMAKE_COMMAND} -E remove ${_single_header_tmp}
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Generating single header file"
)
