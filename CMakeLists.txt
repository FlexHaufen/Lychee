cmake_minimum_required(VERSION 3.24.1)

### Project ###
project(Lychee VERSION 0.0.1)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

## Requierments ## 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

# Set release and debug folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/release)

# COMPILER FLAGS
#set(CMAKE_CXX_FLAGS_DEBUG "/O0 /g3")
set(CMAKE_CXX_FLAGS_RELEASE "/O3 /g0")


### INCLUDES & SOURCE ###
# Header fildes
file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/src/*.h
	                           ${CMAKE_SOURCE_DIR}/src/*.hpp)

# Source files
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*c
                            ${CMAKE_SOURCE_DIR}/src/*.cpp)

### APP ###
add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})


### LIBS ###
# GLAD
#add_library(glad 
#			${CMAKE_SOURCE_DIR}/lib/glad/include/glad.h
#			${CMAKE_SOURCE_DIR}/lib/glad/src/glad.c)

#Put all libraries into a variable
set(LIBS ${CMAKE_SOURCE_DIR}/lib/glfw/libglfw3dll.a)
			#glad

# Define the include DIRs
include_directories(
	"${CMAKE_SOURCE_DIR}/src"

	"${CMAKE_SOURCE_DIR}/lib/spdlog/include"
	"${CMAKE_SOURCE_DIR}/lib/glfw"
)



# Link libraries
target_link_libraries(${PROJECT_NAME} ${LIBS})

### PCH ###
target_precompile_headers(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/Lychee/lypch.h)

	