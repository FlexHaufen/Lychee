cmake_minimum_required(VERSION 3.24.1)

#----------------------------------------------------
#			   	 PROJECT PROPERTIES
#----------------------------------------------------
project(Lychee VERSION 0.0.1)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

## Requierments ## 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

# Set release and debug folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/release)

# COMPILER FLAGS
#
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
#set(CMAKE_CXX_FLAGS_RELEASE "/O3 /g0")

#----------------------------------------------------
#				  SOURCE & INCLUDE
#----------------------------------------------------
# Header fildes
file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/src/*.h
	                           ${CMAKE_SOURCE_DIR}/src/*.hpp)

# Source files
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*c
                            ${CMAKE_SOURCE_DIR}/src/*.cpp)

### APP ###
add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})



#----------------------------------------------------
#				    	LIBS
#----------------------------------------------------
### GLFW ###
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
#set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORE)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/vendor/glfw)


# GLAD
#add_library(glad 
#			${CMAKE_SOURCE_DIR}/lib/glad/include/glad.h
#			${CMAKE_SOURCE_DIR}/lib/glad/src/glad.c)


#Put all libraries into a variable
set(LIBS glfw)




#----------------------------------------------------
#				      INCLUDE DIRS
#----------------------------------------------------
include_directories(
	"${CMAKE_SOURCE_DIR}/src"

	"${CMAKE_SOURCE_DIR}/lib/vendor/spdlog/include"
	"${CMAKE_SOURCE_DIR}/lib/vendor/glfw"
)



#----------------------------------------------------
#				      LINK & PCH
#----------------------------------------------------
target_link_libraries(${PROJECT_NAME} ${LIBS})

### PCH ###
target_precompile_headers(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/Lychee/lypch.h)

	