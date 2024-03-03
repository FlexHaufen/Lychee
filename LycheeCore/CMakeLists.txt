cmake_minimum_required(VERSION 3.28.0)

#----------------------------------------------------
#			   	 PROJECT PROPERTIES
#----------------------------------------------------
project(LycheeCore VERSION 0.0.0)


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
add_library(${PROJECT_NAME} STATIC	${SRC_FILES} 
							   		${HEADER_FILES})



#--------GLFW----------
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
#set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/vendor/GLFW)

#--------SPDLOG--------
set(SPDLOG_BUILD_WARNINGS OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/vendor/spdlog)

#--------YAML---------
set(YAML_CPP_BUILD_TESTS OFF CACHE BOOL "disable yaml tests")
set(YAML_CPP_BUILD_TOOLS OFF CACHE BOOL "disable yaml tools")
set(YAML_CPP_BUILD_CONTRIB OFF CACHE BOOL "disable yaml contrib")
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/vendor/yaml-cpp/)

#------STBIMAGE-------
set(STBIMAGE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/vendor/stb_image)
add_library(stb_image STATIC
				${STBIMAGE_PATH}/stb_image.h
				${STBIMAGE_PATH}/stb_image.cpp
)
target_include_directories(stb_image PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/lib/vendor/stb_image
)

#--------IMGUI---------
set(IMGUI_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/vendor/imgui)
add_library(imgui STATIC 
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
	${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/lib/vendor/imgui
)
target_link_libraries(imgui glfw)

#--------GLAD---------
set(GLAD_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/glad)
add_library(glad STATIC 
				${GLAD_PATH}/include/glad/glad.h
				${GLAD_PATH}/src/glad.c
) 
target_include_directories(glad PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/lib/glad/include
)

#----------------------------------------------------
#				      INCLUDE DIRS
#----------------------------------------------------
target_include_directories(${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/src/
	${CMAKE_CURRENT_SOURCE_DIR}/lib/vendor/GLFW/include
	${CMAKE_CURRENT_SOURCE_DIR}/lib/vendor/glm
	${CMAKE_CURRENT_SOURCE_DIR}/lib/entt
	${CMAKE_CURRENT_SOURCE_DIR}/lib/vendor/spdlog/include

	${CMAKE_CURRENT_SOURCE_DIR}/lib/glad/include
	${CMAKE_CURRENT_SOURCE_DIR}/lib/vendor/imgui
	${CMAKE_CURRENT_SOURCE_DIR}/lib/vendor/stb_image
	${CMAKE_CURRENT_SOURCE_DIR}/lib/vendor/yaml-cpp/include
)

#----------------------------------------------------
#				      LINK & PCH
#----------------------------------------------------

# Libs
target_link_libraries(${PROJECT_NAME} PRIVATE 	glfw yaml-cpp glad imgui stb_image)
# pch
target_precompile_headers(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/Lychee/lypch.h)