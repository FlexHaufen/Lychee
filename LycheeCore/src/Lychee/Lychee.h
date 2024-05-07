/**
 * @file Lychee.h
 * @author flexhaufen
 * @brief Main Header File
 * @version 0.1
 * @date 2022-09-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

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

// *** INCLUDES ***
// ** Main app **
#include "Lychee/Config.h"
#include "Lychee/Core/Core.h"
#include "Lychee/Scene/Scene.h"
#include "Lychee/Scene/Entity/Entity.h"

#include "Lychee/Core/Input/Input.h"
#include "Lychee/Helper/KeyCodes.h"
#include "Lychee/Helper/MouseCodes.h"
#include "Lychee/Helper/Types.h"

#include "Lychee/Events/Event.h"
#include "Lychee/Events/ApplicationEvent.h"
#include "Lychee/Events/KeyEvent.h"
#include "Lychee/Events/MouseEvent.h"

#include "Lychee/Core/Time/DeltaTime.h"

// ** Logger **
#include "Lychee/Core/Log.h"        