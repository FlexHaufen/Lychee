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
    Core* Core::s_Instance = nullptr;

    Core::Core() {
        s_Instance = this;

        Lychee::Log::Init();
        LY_CORE_INFO("Init Core");

        // TODO: Add define
        std::filesystem::current_path(LY_DEFAULT_PATH);
        LY_CORE_INFO("Current Path: {0}",std::filesystem::current_path());

        #ifdef _DEBUG
            LY_CORE_WARN("Running in DEBUG mode");
            m_Window = new Window(LY_WINDOW_NAME_DEBUG,
                                  LY_WINDOW_SIZE_X,
                                  LY_WINDOW_SIZE_Y);
        #else
            m_Window = new Window(LY_WINDOW_NAME,
                                  LY_WINDOW_SIZE_X,
                                  LY_WINDOW_SIZE_Y);
		#endif
        m_Window->SetEventCallback(LY_BIND_EVENT_FN(Core::OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
    }

    Core::~Core() {
        // delet m_Window -> doesn't matter becose aplication will
        // terminate anyway
        LY_CORE_INFO("Quitting Core");
    }

    void Core::Run() {
        while (m_isRunning) {
            glClearColor(1,1,0,1);
            glClear(GL_COLOR_BUFFER_BIT);

            if (!m_isMinimized) {

                for (Layer* layer : m_LayerStack) {
					layer->OnUpdate();
                }
               
                m_ImGuiLayer->Begin();
                
                for (Layer* layer : m_LayerStack) {
                    layer->OnImGuiRender();
                }
            
                m_ImGuiLayer->End();
            }
            m_Window->OnUpdate();
        }
        LY_CORE_WARN("Core stopped running");
    }

    void Core::Close() {
		m_isRunning = false;
	}

    // ** LAYERS **
    void Core::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Core::PushOverlay(Layer* layer){
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

    // ** EVENTS **
    void Core::OnEvent(Event& e) {

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(LY_BIND_EVENT_FN(Core::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(LY_BIND_EVENT_FN(Core::OnWindowResize));


        for (auto i = m_LayerStack.rbegin(); i != m_LayerStack.rend(); ++i) {
			if (e.m_isHandled) 
				break;
			(*i)->OnEvent(e);
		}
        #ifdef LY_LOG_EVENTS
            LY_CORE_TRACE(e);
        #endif
    }

    bool Core::OnWindowClose(WindowCloseEvent& e) {
        m_isRunning = false;
        return true;
    }

	bool Core::OnWindowResize(WindowResizeEvent& e) {
		if (e.GetWidth() == 0 || e.GetHeight() == 0) {
			m_isMinimized = true;
			return false;
		}
		m_isMinimized = false;
		return false;
	}
}