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
#include "Lychee/Core/Core.h"

// *** DEFINE ***

// *** NAMESPACE ***
namespace Lychee {
    Core* Core::s_Instance = nullptr;

    Core::Core() {
        s_Instance = this;

        Lychee::Log::Init();
        LY_CORE_INFO("Initializing Core");

        std::filesystem::current_path(LY_DEFAULT_PATH);
        LY_CORE_INFO("Running in: {0}",std::filesystem::current_path());


        #ifdef LY_PROFILE
            LY_CORE_WARN("Profiler is enabled and may use unnecessary recources");
        #endif
        LY_PROFILE_BEGIN_SESSION("Profile", "LycheeProfile.json");

        #ifdef LY_DEBUG
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
        delete m_Window;
        LY_CORE_INFO("Core is going down for Shutdown NOW!");
    }

    void Core::Run() {
        LY_PROFILE_FUNCTION();

        while (m_isRunning) {

            m_dt.OnUpdate();

            if (!m_isMinimized) {
                // ---------- Update ----------
                m_Window->OnUpdate(m_dt);
                m_ImGuiLayer->OnSfmlUpdate(m_dt);
                for (Layer* layer : m_LayerStack) {
					layer->OnUpdate(m_dt);
                }

                // ---------- Render ----------
                m_Window->Clear();
                for (Layer* layer : m_LayerStack) {
					layer->OnImGuiRender();
                }
                m_ImGuiLayer->OnSfmlRender();
                m_Window->Display();
            }
        }
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
    void Core::OnEvent(sf::Event& e) {
        LY_PROFILE_FUNCTION();

        switch(e.type) {
            case sf::Event::Closed:
                OnWindowClose(e);
                break;
            case sf::Event::Resized:
                OnWindowResize(e);
                break;
            default:
                break;
        }

        for (auto i : m_LayerStack) {
            i->OnEvent(e);
        }

        #ifdef LY_LOG_EVENTS
            LY_CORE_TRACE(e.type);
        #endif
    }

    bool Core::OnWindowClose(sf::Event& e) {
        m_isRunning = false;
        return true;
    }

	bool Core::OnWindowResize(sf::Event& e) {
		if (e.size.width == 0 || e.size.width == 0) {
			m_isMinimized = true;
			return true;
		}
		m_isMinimized = false;
		return false;
	}
    
}