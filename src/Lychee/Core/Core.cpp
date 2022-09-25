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

        m_Window = new Window("Lychee", 400, 500);
		m_Window->SetEventCallback(LY_BIND_EVENT_FN(Core::OnEvent));
    }

    void Core::Run() {
        while (m_isRunning) {
            // TODO: "gl" not working at the moment
            /**
            glClearColor(1,0,1,1);
            glClear(GL_COLOR_BUFFER_BIT);
            **/
            m_Window->OnUpdate();
        }   
    }


    void Core::OnEvent(Event& e) {
        LY_CORE_INFO(e);
    }

    Core::~Core() {
        LY_CORE_INFO("Quitting Core");
    }
}