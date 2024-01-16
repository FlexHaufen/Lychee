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



// * SFML *
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// ImGui
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui-SFML.h"
#include "imgui.h"

// Stb image
#include <stb_image.h>


// ** LOCAL FILES **
#include "Lychee/Core/Log.h"
#include "Lychee/Core/Debug/Instrumentor.h"
#include "Lychee/Helper/Types.h"

// ***************************************************************
// ************************* DEFINES *****************************
// ***************************************************************
// ** DEBUG **
#ifndef NLY_DEBUG
    // DEBUG MODE
    #define LY_DEBUG
    #define LY_RENDER_IMGUI 		
    #define LY_IMGUI_SHOW_DEMO      // Demo window    
    #define LY_IMPLOT_SHOW_DEMO     // Demo window
    #define LY_LOG_EVENTS
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
#define LY_VERSION_STR              "v1.0.0b"

// * Rescources *
#define LY_DEFAULT_PATH             "./"
#define LY_ICON_PNG                 "./resource/images/Lychee.png"
#define LY_FONT_SIZE                15.0f
#define LY_FONT_REGULAR             "./resource/fonts/Rilu-Regular.ttf"

// * Window *
#define LY_SCENE_CLEAR_BACKGROUND   sf::Color(158, 222, 232, 255)   // light blue

#define LY_WINDOW_SIZE_X            1920
#define LY_WINDOW_SIZE_Y            1080

#define LY_CAMERA_SIZE_X            1920.0f
#define LY_CAMERA_SIZE_Y            1080.0f

#define LY_WINDOW_NAME_DEBUG        "Lychee - DEBUG"
#define LY_WINDOW_NAME              "Lychee"
#define LY_VSYNC_DEFAULT            true

#define LY_IMGUI_INSTALL_CALLBACKS  true