	cmake_minimum_required(VERSION 3.20)


	set(GLFW_INCLUDE_DIR ${SDK_DIR}/glfw-3.3.4/include CACHE INTERNAL "")

#if(${BUILD_LIBS})
	set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

	add_subdirectory(${SDK_DIR}/glfw-3.3.4 SDK/glfw)

	set_target_properties(glfw PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${BINARY_OUTPUT_DIR}/glfw)
#endif()

	
	