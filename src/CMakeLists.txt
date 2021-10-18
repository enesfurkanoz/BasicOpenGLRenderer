cmake_minimum_required(VERSION 3.20)
	


	
	add_executable(main main.cpp)
	set(INCLUDES 
		${GLAD_INCLUDE_DIRECTORY}
		${GLFW_INCLUDE_DIR}
	)
	foreach(INC IN LISTS INCLUDES)
		message("Load :" ${INC})
	endforeach()
	target_include_directories(main PRIVATE ${INCLUDES})
	target_link_libraries(main glad glfw)



	set_target_properties(main PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${BINARY_OUTPUT_DIR})
	set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BINARY_OUTPUT_DIR})
	set_target_properties(main PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${BINARY_OUTPUT_DIR})
