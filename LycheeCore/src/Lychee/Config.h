/**
 * @file Config.h
 * @author flexhaufen
 * @brief Config file
 * @version 0.1
 * @date 2024-05-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once


// *** INCLUDES ***

// *** DEFINES ***

#ifndef NLY_DEBUG
    #define LY_DEBUG
#else
    #undef LY_DEBUG
#endif

#ifdef LY_DEBUG
    #define LY_RENDER_IMGUI 		
    #define LY_IMGUI_SHOW_DEMO      // Demo window    
    #define LY_IMPLOT_SHOW_DEMO     // Demo window
    //#define LY_LOG_EVENTS
    #define LY_DEBUGBREAK() __debugbreak()
	#define LY_ENABLE_ASSERTS
#else
	#define LY_RENDER_IMGUI 		//! dont change this
    #define LY_DEBUGBREAK()
#endif

// ** Config **
// * General *
#define LY_SHOW_WINDOWTITLE_FPS     // FPS counter on window title

#define LY_PROJECT_NAME             "Lychee"
#define LY_VERSION_STR              "v2.1.0a"

#define LY_IMGUI_INSTALL_CALLBACKS  true

// * Rescources *
#define LY_DEFAULT_PATH             "./"
#define LY_DEFAULT_SHADER_PATH      "./LycheeCore/resource/shaders/"
#define LY_ICON_PNG                 "./LycheeCore/resource/images/Lychee.png"
#define LY_FONT_SIZE                15.0f
#define LY_FONT_REGULAR             "./LycheeCore/resource/fonts/Rilu-Regular.ttf"

// * Colors *
// TODO (flex): convert
#define LY_COLOR_RED                ImVec4(249 / 255.f, 65 / 255.f, 68 / 255.f, 255)     // #F94144
#define LY_COLOR_ORANGE             ImVec4(243 / 255.f, 114 / 255.f, 44 / 255.f, 255)    // #F3722C
#define LY_COLOR_LIGHT_ORANGE       ImVec4(248 / 255.f, 150 / 255.f, 30 / 255.f, 255)    // #F8961E
#define LY_COLOR_YELLOW             ImVec4(249 / 255.f, 199 / 255.f, 79 / 255.f, 255)    // #F9C74F   
#define LY_COLOR_LIME               ImVec4(144 / 255.f, 190 / 255.f, 109 / 255.f, 255)   // #90BE6D
#define LY_COLOR_LIGHT_BLUE         ImVec4(67 / 255.f, 170 / 255.f, 139 / 255.f, 255)    // #43AA8B
#define LY_COLOR_BLUE               ImVec4(87 / 255.f, 117 / 255.f, 144 / 255.f, 255)    // #577590
#define LY_COLOR_WHITE              ImVec4(0 / 255.f,0 / 255.f,0 / 255.f,255)
#define LY_COLOR_BLACK              ImVec4(255 / 255.f,255 / 255.f,255 / 255.f,255)
#define LY_COLOR_GRAY               ImVec4(49 / 255.f, 57 / 255.f, 60 / 255.f, 255)      // #31393C

#define LY_WINDOW_SIZE_X            1920
#define LY_WINDOW_SIZE_Y            1080

#define LY_WINDOW_NAME_DEBUG        "Lychee - DEBUG"
#define LY_WINDOW_NAME              "Lychee"
#define LY_VSYNC_DEFAULT            true
