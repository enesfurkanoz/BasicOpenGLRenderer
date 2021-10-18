# CMakeList.txt : CMake project for BasicRenderer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.20)

project ("BasicRenderer")




set(SDK_DIR ${CMAKE_CURRENT_LIST_DIR}/SDK)
set(BINARY_OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/BIN)
set(BUILD_LIBS 1)

if(${CMAKE_SYSTEM_NAME}  MATCHES Windows )
	

	add_subdirectory(libs)

	add_subdirectory(src)





elseif()
	message("Targets other than Windows doesn't supported yet!")
endif()


