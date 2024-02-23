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

    Core::Core(b8 isSplashScreenEnabled) {
        s_Instance = this;

        Lychee::Log::Init();
        LY_CORE_INFO("Initializing");
        std::filesystem::current_path(LY_DEFAULT_PATH);
        LY_CORE_INFO("\\---- Path: {0}",std::filesystem::current_path());

        #ifdef LY_PROFILE
            LY_CORE_WARN("Profiler is enabled and may use unnecessary recources");
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



        m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
    }

    Core::~Core() {
        delete m_Window;
        LY_CORE_INFO("Terminating");
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

        for (auto& i : m_LayerStack) {
            i->OnEvent(e);
        }

        #ifdef LY_LOG_EVENTS
            LY_CORE_TRACE(e.type);
        #endif
    }

    b8 Core::OnWindowClose(sf::Event& e) {
        m_isRunning = false;
        return true;
    }

	b8 Core::OnWindowResize(sf::Event& e) {
		if (e.size.width == 0 || e.size.width == 0) {
			m_isMinimized = true;
			return true;
		}
		m_isMinimized = false;
		return false;
	}



    void Core::OnSplashScreenDisplay() {
        sf::RenderWindow splashScreen;

        const u32 sizeX = 700;
        const u32 sizeY = 400;

        splashScreen.create(sf::VideoMode(sizeX, sizeY), LY_WINDOW_NAME, sf::Style::None);
        splashScreen.clear(LY_COLOR_BLACK);
        
        sf::Texture tex_MainIcon;
        if (!tex_MainIcon.loadFromFile(LY_ICON_PNG)) {
            LY_CORE_WARN("Could not load window icon at [{0}]", LY_ICON_PNG);
            splashScreen.close();
            return;
        }

        sf::Font main_font;
        if (!main_font.loadFromFile(LY_FONT_REGULAR)) {
            LY_CORE_WARN("Could not load font at [{0}]", LY_FONT_REGULAR);
            splashScreen.close();
            return;
        }
        

        // Main Icon
        sf::Sprite sp_MainIcon;
        sp_MainIcon.setTexture(tex_MainIcon);
        sp_MainIcon.setOrigin(tex_MainIcon.getSize() / 2);
        sp_MainIcon.setPosition(sizeX / 2 - 5, sizeY / 2 - 30); // -5 to center correctly / -30 for vertical offset
        sp_MainIcon.setScale(0.1f, 0.1f);
        splashScreen.draw(sp_MainIcon);

        // Main Text
        sf::Text title(LY_PROJECT_NAME, main_font, 34);
        title.setFillColor(LY_COLOR_RED);
        sf::FloatRect titleBounds = title.getLocalBounds();
        title.setOrigin(titleBounds.left + titleBounds.width / 2.0f, titleBounds.top + titleBounds.height / 2.0f);
        title.setPosition(sizeX / 2, sizeY / 2 + 50); 
        splashScreen.draw(title);

        // Version Text
        sf::Text versionText(LY_VERSION_STR, main_font, 15);
        versionText.setFillColor(LY_COLOR_RED);
        sf::FloatRect versionTextBounds = versionText.getLocalBounds();
        versionText.setOrigin(versionTextBounds.left + versionTextBounds.width / 2.0f, versionTextBounds.top + versionTextBounds.height / 2.0f);
        versionText.setPosition(sizeX / 2, sizeY / 2 + 80); 
        splashScreen.draw(versionText);


        // startup Text
        sf::Text startup("starting...", main_font, 15);
        startup.setFillColor(LY_COLOR_WHITE);
        sf::FloatRect startupBounds = startup.getLocalBounds();
        startup.setOrigin(startupBounds.left + startupBounds.width / 2.0f, startupBounds.top + startupBounds.height / 2.0f);
        startup.setPosition(sizeX / 2, sizeY / 2 + 120); 
        splashScreen.draw(startup);




        splashScreen.display();
        sf::sleep(sf::seconds(5));
        splashScreen.close();
    }

    
}