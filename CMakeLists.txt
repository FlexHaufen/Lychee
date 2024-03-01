cmake_minimum_required(VERSION 3.24.1)

#----------------------------------------------------
#			   	 PROJECT PROPERTIES
#----------------------------------------------------
project(Lychee VERSION 0.0.0)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

## Requierments ## 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

# Set release and debug folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/release)


#----------------------------------------------------
#				      LINK & PCH
#----------------------------------------------------
add_subdirectory(LycheeCore)
add_subdirectory(LycheeApp)