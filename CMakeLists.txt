cmake_minimum_required(VERSION 3.24.1)

#----------------------------------------------------
#			   	 PROJECT PROPERTIES
#----------------------------------------------------
project(Lychee VERSION 0.0.0)

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
set(CMAKE_CXX_FLAGS_DEBUG "/W1 /W2 /W3 /Zi")
set(CMAKE_CXX_FLAGS_RELEASE "/O3 /g0 /DNLY_DEBUG")


#----------------------------------------------------
#				       RESOURCE
#----------------------------------------------------
set(LYCHEE_APP_ICO "${CMAKE_SOURCE_DIR}/resource/images/Lychee.rc")


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
add_executable(${PROJECT_NAME} ${SRC_FILES} 
							   ${HEADER_FILES}
							   ${LYCHEE_APP_ICO})



#----------------------------------------------------
#				    	LIBS
#----------------------------------------------------

#---------SFML---------
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR ${CMAKE_SOURCE_DIR}/lib/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML 2.5.1 REQUIRED COMPONENTS window system graphics audio network)


#---------BOX2D---------
# FIXME (flex): only debug build possible
set(BOX2D_LIB ${CMAKE_SOURCE_DIR}/lib/box2d/lib/bin/Debug/box2d.lib)


#-----IMGUI-SFML-------
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/lib/vendor/imgui/)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/vendor/imgui-sfml/)

#--------YAML---------
set(YAML_CPP_BUILD_TESTS OFF CACHE BOOL "disable yaml tests")
set(YAML_CPP_BUILD_TOOLS OFF CACHE BOOL "disable yaml tools")
set(YAML_CPP_BUILD_CONTRIB OFF CACHE BOOL "disable yaml contrib")
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/vendor/yaml-cpp/)

#----------------------------------------------------
#				      INCLUDE DIRS
#----------------------------------------------------
include_directories(
	${CMAKE_SOURCE_DIR}/src
	#SFML
	${CMAKE_SOURCE_DIR}/lib/SFML-2.5.1/include
	#EnTT
	${CMAKE_SOURCE_DIR}/lib/entt
	# spdlog
	${CMAKE_SOURCE_DIR}/lib/vendor/spdlog/include
	# Box2D
	${CMAKE_SOURCE_DIR}/lib/box2d/include
	# stb_image
	${CMAKE_SOURCE_DIR}/lib/vendor/stb_image
)



#----------------------------------------------------
#				      LINK & PCH
#----------------------------------------------------

#Put all libraries into a variable
set(LIBS 	sfml-window
			sfml-system
			sfml-graphics
			sfml-audio
			sfml-network
			ImGui-SFML
			yaml-cpp
			${BOX2D_LIB})

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})


### PCH ###
target_precompile_headers(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/Lychee/lypch.h)

	