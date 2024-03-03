/**
 * @file RuntimeLayer.cpp
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-03-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */
// *** INCLUDE ***
#include "RuntimeLayer.h"

// *** DEFINES ***

//#define LY_LOG_KEY_EVENT

// *** NAMESPACE ***
namespace Lychee {

	extern const std::filesystem::path g_AssetPath;

	RuntimeLayer::RuntimeLayer()
	: Layer("RuntimeLayer") {

		LY_INFO("Getting Current scene");
		m_ActiveScene = CreateRef<Scene>();

	}

	void RuntimeLayer::OnAttach() {

	}

	void RuntimeLayer::OnDetach() {
	}

	void RuntimeLayer::OnUpdate(DeltaTime dt) {
		// TODO (flex): in case of scene camera, resize here
		//m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);


	}

	void RuntimeLayer::OnEvent(Event& e)	{

		#ifdef LY_LOG_KEY_EVENT
			if (e.GetEventType() == Lychee::eEventType::KeyPressed) {
				Lychee::KeyPressedEvent& eKey = (Lychee::KeyPressedEvent&)e;
				LY_TRACE("KEY PRESSED: {0}", (char)eKey.GetKeyCode());
			}	
		#endif

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(LY_BIND_EVENT_FN(RuntimeLayer::OnKeyPressed));
		dispatcher.Dispatch<MouseButtonPressedEvent>(LY_BIND_EVENT_FN(RuntimeLayer::OnMouseButtonPressed));
	}

	bool RuntimeLayer::OnKeyPressed(KeyPressedEvent& e) {
		// Shortcuts
		if (e.IsRepeat()) {
			return false;

			bool control = Input::IsKeyPressed(Key::LeftControl) || Input::IsKeyPressed(Key::RightControl);
			bool shift = Input::IsKeyPressed(Key::LeftShift) || Input::IsKeyPressed(Key::RightShift);
		}
		return true;
	}

	bool RuntimeLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e) {
		if (e.GetMouseButton() == Mouse::ButtonLeft) {

		}
		return false;
	}
}

