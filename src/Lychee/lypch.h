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

#include <math.h>
#include <cmath>

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

// EnTT
#include "entt.hpp"

// * yaml-cpp *
#include "yaml-cpp/yaml.h"

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
    //#define LY_ENABLE_SPLASH_SCREEN

    // #define LY_LOG_EVENTS
#else
    // RELEAS MODE
    #undef LY_DEBUG
    #define LY_RENDER_IMGUI 		//! dont change this
    #define LY_ENABLE_SPLASH_SCREEN
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

// * Colors *
#define LY_COLOR_RED                sf::Color(249, 65, 68, 255)     // #F94144
#define LY_COLOR_ORANGE             sf::Color(243, 114, 44, 255)    // #F3722C
#define LY_COLOR_LIGHT_ORANGE       sf::Color(248, 150, 30, 255)    // #F8961E
#define LY_COLOR_YELLOW             sf::Color(249, 199, 79, 255)    // #F9C74F   
#define LY_COLOR_LIME               sf::Color(144, 190, 109, 255)   // #90BE6D
#define LY_COLOR_LIGHT_BLUE         sf::Color(67, 170, 139, 255)    // #43AA8B
#define LY_COLOR_BLUE               sf::Color(87, 117, 144, 255)    // #577590
#define LY_COLOR_WHITE              sf::Color::White
#define LY_COLOR_BLACK              sf::Color::Black
#define LY_COLOR_GRAY               sf::Color(49, 57, 60, 255)      // #31393C

// * Window *
#define LY_MAIN_CLEAR_COLOR         LY_COLOR_GRAY
#define LY_SCENE_CLEAR_COLOR        LY_COLOR_GRAY
#define LY_SPLASHSCREEN_CLEAR_COLOR LY_COLOR_GRAY

#define LY_WINDOW_SIZE_X            1920
#define LY_WINDOW_SIZE_Y            1080

#define LY_WINDOW_NAME_DEBUG        "Lychee - DEBUG"
#define LY_WINDOW_NAME              "Lychee"
#define LY_VSYNC_DEFAULT            true

