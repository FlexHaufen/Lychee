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
		m_EditorCamera = EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f);

		sFramebufferSpecification fbSpec;
		fbSpec.Attachments = { eFramebufferTextureFormat::RGBA8, eFramebufferTextureFormat::RED_INTEGER, eFramebufferTextureFormat::Depth };
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = CreateRef<Framebuffer>(fbSpec);
	}

	void RuntimeLayer::OnAttach() {

	}

	void RuntimeLayer::OnDetach() {
	}

	void RuntimeLayer::OnUpdate(DeltaTime dt) {
		// TODO (flex): in case of scene camera, resize here
		//m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);


		// Resize
		if (sFramebufferSpecification spec = m_Framebuffer->GetSpecification();
			m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
			(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y)) {
			m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_EditorCamera.SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);
		}


		// Render
		m_Framebuffer->Bind();
		Renderer::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Renderer::Clear();
		// Clear our entity ID attachment to -1
		m_Framebuffer->ClearAttachment(1, -1);
		// TODO (flex): Decide here between runtime and editor

		m_EditorCamera.OnUpdate(dt);
		m_ActiveScene->OnEditorUpdate(dt, m_EditorCamera);


		m_Framebuffer->Unbind();
	}

	void RuntimeLayer::OnEvent(Event& e)	{
		m_EditorCamera.OnEvent(e);

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

