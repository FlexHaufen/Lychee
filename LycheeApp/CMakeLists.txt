cmake_minimum_required(VERSION 3.24.1)

#----------------------------------------------------
#			   	 PROJECT PROPERTIES
#----------------------------------------------------
project(LycheeApp VERSION 0.0.0)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

## Requierments ## 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)


#----------------------------------------------------
#				       RESOURCE
#----------------------------------------------------
set(LYCHEE_APP_ICO ${CMAKE_CURRENT_SOURCE_DIR}/resource/images/Lychee.rc)


#----------------------------------------------------
#				  SOURCE & INCLUDE
#----------------------------------------------------
# Header fildes
file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
	                           ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)

# Source files
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*c
                            ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

### APP ###
add_executable(${PROJECT_NAME}     ${SRC_FILES} 
							   	   ${HEADER_FILES}
							   	   ${LYCHEE_APP_ICO})


#----------------------------------------------------
#				      INCLUDE DIRS
#----------------------------------------------------
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/src/
)	

#----------------------------------------------------
#				          LINK
#----------------------------------------------------
target_link_libraries(${PROJECT_NAME} PUBLIC LycheeCore)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/LycheeCore/src/)