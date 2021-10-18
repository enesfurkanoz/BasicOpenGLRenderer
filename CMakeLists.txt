# CMakeList.txt : CMake project for BasicRenderer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.20)

project ("BasicRenderer")

#option(BUILD_STARIC_LIBS "")


set(SDK_DIR ${CMAKE_CURRENT_LIST_DIR}/SDK)
set(BINARY_OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/BIN)


if(${CMAKE_SYSTEM_NAME}  MATCHES Windows )
	

	add_subdirectory(libs)

	add_subdirectory(src)





elseif()
	message("Targets other than Windows doesn''t supported yet!")
endif()


