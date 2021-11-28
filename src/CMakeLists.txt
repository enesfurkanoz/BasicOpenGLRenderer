cmake_minimum_required(VERSION 3.20)
	


	set(CMAKE_CXX_STANDARD_REQUIRED MSVC17)
	add_executable(main experiment.cpp "OpenGL/GLBuffer.h" "OpenGL/VertexArray.h" "OpenGL/VertexFormat.h" "OpenGL/GLShader.h" "OpenGL/GLShader.cpp" "OpenGL/GLProgram.h" "OpenGL/GLProgram.cpp ")
	set(INCLUDES 
		${GLAD_INCLUDE_DIRECTORY}
		${GLFW_INCLUDE_DIR}

	)

	target_include_directories(main PUBLIC ${INCLUDES})




	set_target_properties(main PROPERTIES 
		LIBRARY_OUTPUT_DIRECTORY ${BINARY_OUTPUT_DIR}
		RUNTIME_OUTPUT_DIRECTORY ${BINARY_OUTPUT_DIR}
		ARCHIVE_OUTPUT_DIRECTORY ${BINARY_OUTPUT_DIR}
		)

	target_link_libraries(main 
	${BINARY_OUTPUT_DIR}/glad/glad.lib 
	${BINARY_OUTPUT_DIR}/glfw/glfw3.lib
	)