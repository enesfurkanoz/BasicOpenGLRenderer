cmake_minimum_required(VERSION 3.20)

set(GLAD_INCLUDE_DIRECTORY ${SDK_DIR}/glad/include CACHE INTERNAL "")

add_subdirectory(${SDK_DIR}/glad SDK/glad)

set_target_properties(glad PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${BINARY_OUTPUT_DIR}/glad )