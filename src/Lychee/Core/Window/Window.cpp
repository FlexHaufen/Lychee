/**
 * @file Window.cpp
 * @author flexhaufen
 * @brief Window of app
 * @version 0.1
 * @date 2022-09-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// *** INCLUDES ***
#include "Lychee/Core/Window/Window.h"

// *** DEFINES ***

// *** NAMESPACE ***
namespace Lychee {


	Window::Window(std::string title, u32 width, u32 height)
	: m_EventManager(m_Window) {
		m_sWindowData.title = title;
		m_sWindowData.width = width;
		m_sWindowData.height = height;
        Init();
	}

	Window::~Window() {
		Terminate();
	}

	void Window::Init() {
		LY_CORE_INFO("Initializing window: {0} ({1}, {2})", m_sWindowData.title, m_sWindowData.width, m_sWindowData.height);

		LY_CORE_INFO("Initializing SFML Window");
        m_Window.create(sf::VideoMode(m_sWindowData.width, m_sWindowData.height), m_sWindowData.title);

		// Set window ico
		auto windowIcon = sf::Image();
		if (!windowIcon.loadFromFile(LY_ICON_PNG)) {
			LY_CORE_WARN("Could not load window icon at [{0}]", LY_ICON_PNG);
		}
		else {
			m_Window.setIcon(windowIcon.getSize().x, windowIcon.getSize().y, windowIcon.getPixelsPtr());
		}
		
        LY_CORE_INFO("Setting vsync to {0}", LY_VSYNC_DEFAULT);
		SetVSync(LY_VSYNC_DEFAULT);


		LY_CORE_INFO("Setting up CORE events");
	}

	void Window::Terminate() {
        LY_CORE_INFO("Terminating window");
		m_Window.close();
	}

	void Window::OnUpdate(DeltaTime dt) {

		// ** Event Loop **
		sf::Event event;
		while (m_Window.pollEvent(event)) {
			m_sWindowData.eventCallback(event);
			m_EventManager.processEvents(event, nullptr);
		}

		// NOTE: This function may use unnecessary resources.
		//		 It will not be compiled in releas builds.
		#ifdef LY_SHOW_WINDOWTITLE_FPS
			m_elapsedTimeFps += dt.GetSeconds();
			m_frameCounterFps++;

			if (m_elapsedTimeFps >= 1.0f) {
				std::string title =  m_sWindowData.title + " FPS:  " + std::to_string(m_frameCounterFps);
				m_Window.setTitle(title);
				m_frameCounterFps = 0;
				m_elapsedTimeFps = 0;
			}
		#endif
		m_Window.clear(LY_SCENE_CLEAR_BACKGROUND);
	}

	void Window::SetVSync(bool enabled) {
		m_Window.setVerticalSyncEnabled(enabled);
		m_sWindowData.isVSyncOn = enabled;
	}

	bool Window::IsVSync() const {
		return m_sWindowData.isVSyncOn;
	}

}
