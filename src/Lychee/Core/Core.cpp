/**
 * @file Core.cpp
 * @author flexhaufen
 * @brief Core of the engine
 * @version 0.1
 * @date 2022-09-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// *** INCLUDES ***
#include "Lychee/lypch.h"
#include "Lychee/Core/Core.h"

// *** DEFINE ***
#define LY_RUNNING true

// *** NAMESPACE ***
namespace Lychee {
    Core::Core() {
        Lychee::Log::Init();
        LY_CORE_INFO("Init Core");

        #ifdef _DEBUG
            LY_CORE_INFO("Running [DEBUG]");
        #else
            LY_CORE_INFO("Running [RELEASE]");
        #endif
    }

    void Core::Run() {
        while (LY_RUNNING) {
          
        }   
    }

    Core::~Core() {
        LY_CORE_INFO("Quitting Core");
    }
}