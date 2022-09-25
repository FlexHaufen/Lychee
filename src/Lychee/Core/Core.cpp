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
            LY_CORE_INFO("Running in DEBUG mode");
        #endif

        m_Window = new Window("Lychee", 400, 500);
		m_Window->SetEventCallback(LY_BIND_EVENT_FN(Core::OnEvent));
    }

    void Core::Run() {
        while (m_isRunning) {
            glClearColor(1,0,1,1);
            glClear(GL_COLOR_BUFFER_BIT);
            m_Window->OnUpdate();
        }
        LY_CORE_INFO("Core stopped running");
    }


    void Core::OnEvent(Event& e) {

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(LY_BIND_EVENT_FN(Core::OnWindowClose));

        LY_CORE_TRACE(e);
    }

    Core::~Core() {
        LY_CORE_INFO("Quitting Core");
    }

    // ** EVENTS **
    bool Core::OnWindowClose(WindowCloseEvent& e) {
        m_isRunning = false;
        return true;
    }
}