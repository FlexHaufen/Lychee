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

// *** INCLUDES ***
// ** EXTERNAL FILES **
#include <Windows.h>

#include <iostream>
#include <memory>

#include <utility>
#include <algorithm>
#include <functional>
#include <filesystem>

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

// ImGui
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <imgui.h>
#include <imconfig.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

// ImPlot
#include <implot.h>
#pragma warning(pop)


// ** LOCAL FILES **
#include "Lychee/Core/Log.h"
#include "Lychee/Helper/Types.h"

//TODO: Maby move to another file

// *** DEFINES ***
// ** DEBUG **
// #define LY_LOG_EVENTS
#define LY_RENDER_IMGUI 		//! dont change this
#define LY_IMGUI_SHOW_DEMO      // Demo window    
#define LY_IMPLOT_SHOW_DEMO     // Demo window

#define LY_SHOW_WINDOWTITLE_FPS    // FPS counter on window title

// ** CONFIG **
// * General *
#define LY_PROJECT_NAME             "Lychee"
#define LY_VERSION_STR              "v0.1.4b"
#define LY_VERSION_INT              000104      // format: 00.00.00

// * Rescources *
#define LY_DEFAULT_PATH             "./"
#define LY_ICON_PNG                 "./resource/images/Lychee.png"
#define LY_FONT_SIZE                15.0f
#define LY_FONT_REGULAR             "./resource/fonts/Rilu-Regular.ttf"

// * Window *
#define LY_WINDOW_SIZE_X            1500
#define LY_WINDOW_SIZE_Y            1000
#define LY_WINDOW_NAME_DEBUG        "Lychee - DEBUG"
#define LY_WINDOW_NAME              "Lychee"
#define LY_VSYNC_DEFAULT            true


#define LY_OPENGL_VERSION           "#version 410"
#define LY_IMGUI_INSTALL_CALLBACKS  true