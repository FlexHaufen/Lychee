/**
 * @file lyphc.h
 * @author flexhaufen
 * @brief Precompiled header
 * @version 0.1
 * @date 2022-09-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#pragma warning(push, 0)

// ***************************************************************
// ************************ INCLUDES *****************************
// ***************************************************************
// ** EXTERNAL FILES **
#include <Windows.h>

#include <iostream>
#include <memory>

#include <utility>
#include <algorithm>
#include <functional>
#include <filesystem>
#include <fstream>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

// ** LOCAL LIBS **
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// ImGui
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <imgui.h>
#include <imconfig.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

// ImPlot
#include <implot.h>
#pragma warning(pop)

// Stb image
#include <stb_image.h>


// ** LOCAL FILES **
#include "Lychee/Core/Log.h"
#include "Lychee/Helper/Types.h"

// ***************************************************************
// ************************* DEFINES *****************************
// ***************************************************************
// ** DEBUG **
#ifndef NLY_DEBUG
    // DEBUG MODE
    #define LY_DEBUG
    //#define LY_RENDER_IMGUI 		
    #define LY_IMGUI_SHOW_DEMO      // Demo window    
    #define LY_IMPLOT_SHOW_DEMO     // Demo window
    // #define LY_LOG_EVENTS
#else
    // RELEAS MODE
    #undef LY_DEBUG
    #define LY_RENDER_IMGUI 		//! dont change this
#endif


#ifdef LY_DEBUG
    #define LY_DEBUGBREAK() __debugbreak()
	#define LY_ENABLE_ASSERTS
#else
	#define LY_DEBUGBREAK()
#endif

// ** MACROS **
#define LY_EXPAND_MACRO(x) x
#define LY_STRINGIFY_MACRO(x) #x


// ** CONFIG **
//TODO: Maby move to another file
// * General *
#define LY_SHOW_WINDOWTITLE_FPS     // FPS counter on window title

#define LY_PROJECT_NAME             "Lychee"
#define LY_VERSION_STR              "v0.1.5b"
#define LY_VERSION_INT              000105      // format: 00.00.00

// * Rescources *
#define LY_DEFAULT_PATH             "./"
#define LY_ICON_PNG                 "./resource/images/Lychee.png"
#define LY_FONT_SIZE                15.0f
#define LY_FONT_REGULAR             "./resource/fonts/Rilu-Regular.ttf"

// * Window *
#define LY_WINDOW_SIZE_X            1920
#define LY_WINDOW_SIZE_Y            1080

#define LY_CAMERA_SIZE_X            1920.0f
#define LY_CAMERA_SIZE_Y            1080.0f

#define LY_WINDOW_NAME_DEBUG        "Lychee - DEBUG"
#define LY_WINDOW_NAME              "Lychee"
#define LY_VSYNC_DEFAULT            true


#define LY_OPENGL_VERSION           "#version 410"
#define LY_IMGUI_INSTALL_CALLBACKS  true