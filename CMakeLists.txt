cmake_minimum_required(VERSION 3.24.1)

#----------------------------------------------------
#			   	 PROJECT PROPERTIES
#----------------------------------------------------
project(Lychee VERSION 0.1.1)

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
### GLFW ###
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
#set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORE)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/vendor/GLFW)


### GLAD ###
add_library(glad 
			${CMAKE_SOURCE_DIR}/lib/glad/include/glad/glad.h
			${CMAKE_SOURCE_DIR}/lib/glad/src/glad.c)


### IMGUI ##
set(IMGUI_PATH ${CMAKE_SOURCE_DIR}/lib/vendor/imgui)
add_library(imgui 
			${IMGUI_PATH}/imconfig.h
			${IMGUI_PATH}/imgui.h
			${IMGUI_PATH}/imgui.cpp
			${IMGUI_PATH}/imgui_draw.cpp
			${IMGUI_PATH}/imgui_internal.h
			${IMGUI_PATH}/imgui_tables.cpp
			${IMGUI_PATH}/imgui_widgets.cpp
			${IMGUI_PATH}/imstb_rectpack.h
			${IMGUI_PATH}/imstb_textedit.h
			${IMGUI_PATH}/imstb_truetype.h
			${IMGUI_PATH}/imgui_demo.cpp
			${IMGUI_PATH}/backends/imgui_impl_glfw.h
			${IMGUI_PATH}/backends/imgui_impl_glfw.cpp
			${IMGUI_PATH}/backends/imgui_impl_opengl3_loader.h 
			${IMGUI_PATH}/backends/imgui_impl_opengl3.h 
			${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp) 


### IMPLOT ###
set(IMPLOT_PATH ${CMAKE_SOURCE_DIR}/lib/vendor/implot)
add_library(implot 
			${IMPLOT_PATH}/implot.h
			${IMPLOT_PATH}/implot_internal.h
			${IMPLOT_PATH}/implot.cpp
			${IMPLOT_PATH}/implot_items.cpp
			${IMPLOT_PATH}/implot_demo.cpp)


#----------------------------------------------------
#				      INCLUDE DIRS
#----------------------------------------------------
include_directories(
	"${CMAKE_SOURCE_DIR}/src"

	
	# TODO: Add imgui to a subfolder "imgui", 
	#       so you can include like <imgui/imgui.h>
	# imgui
	"${CMAKE_SOURCE_DIR}/lib/vendor/imgui"
	# implot
	"${CMAKE_SOURCE_DIR}/lib/vendor/implot"
	# spdlog
	"${CMAKE_SOURCE_DIR}/lib/vendor/spdlog/include"
	# glfw
	"${CMAKE_SOURCE_DIR}/lib/vendor/GLFW/include"
	#glm
	"${CMAKE_SOURCE_DIR}/lib/vendor/glm"
	# glad
	"${CMAKE_SOURCE_DIR}/lib/glad/include"
	# stb_image
	"${CMAKE_SOURCE_DIR}/lib/vendor/stb_image"	
)



#----------------------------------------------------
#				      LINK & PCH
#----------------------------------------------------

#Put all libraries into a variable
set(LIBS glfw
	glad
	imgui
	implot)

target_link_libraries(${PROJECT_NAME} ${LIBS})


### PCH ###
target_precompile_headers(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/Lychee/lypch.h)

	