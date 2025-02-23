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

#include "Lychee/Config.h"
#include "Lychee/Renderer/Renderer.h"

// *** DEFINE ***

// *** NAMESPACE ***
namespace Lychee {
    Core* Core::s_Instance = nullptr;

    Core::Core() {
        s_Instance = this;

        Lychee::Log::Init();
        LY_CORE_INFO("Initializing");
        std::filesystem::current_path(LY_DEFAULT_PATH);
        LY_CORE_INFO("\\---- Path: {0}",std::filesystem::current_path());

        #ifdef LY_PROFILE
            LY_CORE_WARN("Profiler is enabled and may use unnecessary resources");
        #endif
        LY_PROFILE_BEGIN_SESSION("Profile", "LycheeProfile.json");

        #ifdef LY_ENABLE_SPLASH_SCREEN
            LY_CORE_INFO("Displaying Splashscreen");
            if (isSplashScreenEnabled) {
                OnSplashScreenDisplay();
            }
        #endif

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

        LY_CORE_INFO("\\---- Allocating Renderer");
        m_Renderer = new Renderer();
        m_Renderer->Init(m_Window->GetNativeGlfwWindow());

        // TODO (flex) implement imgui
        //m_ImGuiLayer = new ImGuiLayer();
		//PushOverlay(m_ImGuiLayer);
    }

    Core::~Core() {
        m_Renderer->Terminate();
        delete m_Renderer;
        delete m_Window;

        LY_CORE_INFO("Terminating");
    }

    void Core::Run() {
        //LY_PROFILE_FUNCTION();

        
        while (m_isRunning) {
            float time = (float)glfwGetTime();
            DeltaTime deltaTime = time - m_lastFrameTime;
            m_lastFrameTime = time;

            if (!m_isMinimized) {
                for (Layer* layer : m_LayerStack) {
					layer->OnUpdate(deltaTime);
                }
                m_Renderer->Render();
                //m_ImGuiLayer->Begin();
                
                //for (Layer* layer : m_LayerStack) {
                //    layer->OnImGuiRender();
                //}
            
                //m_ImGuiLayer->End();
                m_Renderer->WaitIdle();
            }
            m_Window->OnUpdate(deltaTime);

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
    void Core::OnEvent(Event& e) {
        //LY_PROFILE_FUNCTION();

        EventDispatcher dispatcher(e);

        dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& e) {
            m_isRunning = false;
            return true;
        });
        
        dispatcher.Dispatch<WindowResizeEvent>([this](WindowResizeEvent& e) {
            if (m_Renderer != nullptr) {
                m_Renderer->OnResize();
            }
            
            if (e.GetWidth() == 0 || e.GetHeight() == 0) {
                m_isMinimized = true;
                return true;
            }
            m_isMinimized = false;
            return false;
        });

        for (auto i = m_LayerStack.rbegin(); i != m_LayerStack.rend(); ++i) {
			if (e.m_isHandled) 
				break;
			(*i)->OnEvent(e);
		}
        
        #ifdef LY_LOG_EVENTS
            LY_CORE_TRACE(e);
        #endif
    }
}