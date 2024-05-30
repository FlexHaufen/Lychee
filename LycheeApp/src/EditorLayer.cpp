/**
 * @file EditorLayer.cpp
 * @author flexhaufen
 * @brief ImGui Main
 * @version 0.1
 * @date 2022-09-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// *** INCLUDE ***
#include "EditorLayer.h"

// *** DEFINES ***

//#define LY_LOG_KEY_EVENT

// *** NAMESPACE ***
namespace Lychee {

	extern const std::filesystem::path g_AssetPath;

	EditorLayer::EditorLayer()
	: Layer("EditorLayer") {

		LY_INFO("Initializing Editor");

		LY_INFO("Getting Current scene");
		m_ActiveScene = CreateRef<Scene>();
		//m_EditorCamera = EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f);

		m_ContentBrowserPanel.SetContext(m_ActiveScene);
	}

	void EditorLayer::OnAttach() {
		m_ActiveScene->OnRuntimeStart();
	}

	void EditorLayer::OnDetach() {
	}

	void EditorLayer::OnUpdate(DeltaTime dt) {
		// TODO (flex): in case of scene camera, resize here
		//m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);



		switch (m_SceneState) {

			case SceneState::Edit:
				//m_EditorCamera.OnUpdate(dt);
				m_ActiveScene->OnRuntimeUpdate(dt);
				break;

			case SceneState::Play:
				break;

			default:
				LY_ERROR("EditorLayer: SceneState was {0}. Revert to default", (uint8_t)m_SceneState);		
				m_SceneState = SceneState::Edit;		
				break;
		}
		//m_Framebuffer->Unbind();
	}

	void EditorLayer::OnImGuiRender() {
	#ifdef LY_RENDER_IMGUI
		#ifdef LY_IMGUI_SHOW_DEMO
			ImGui::ShowDemoWindow();
		#endif

		#ifdef LY_IMPLOT_SHOW_DEMO
			//ImPlot::ShowDemoWindow();
		#endif
		// ** Panels **
		m_ContentBrowserPanel.OnImGuiRender();
	#endif
	}

	void EditorLayer::OnEvent(Event& e)	{
		if (m_ViewportFocused) {

			if (m_SceneState == SceneState::Edit) {
				//Sm_EditorCamera.OnEvent(e);
			}

			#ifdef LY_LOG_KEY_EVENT
				if (e.GetEventType() == Lychee::eEventType::KeyPressed) {
					Lychee::KeyPressedEvent& eKey = (Lychee::KeyPressedEvent&)e;
					LY_TRACE("KEY PRESSED: {0}", (char)eKey.GetKeyCode());
				}	
			#endif

			EventDispatcher dispatcher(e);
			dispatcher.Dispatch<KeyPressedEvent>(LY_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
			dispatcher.Dispatch<MouseButtonPressedEvent>(LY_BIND_EVENT_FN(EditorLayer::OnMouseButtonPressed));
		}
	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e) {
		// Shortcuts
		if (e.IsRepeat()) {
			return false;

		bool control = Input::IsKeyPressed(Key::LeftControl) || Input::IsKeyPressed(Key::RightControl);
		bool shift = Input::IsKeyPressed(Key::LeftShift) || Input::IsKeyPressed(Key::RightShift);
		}
		return true;
	}

	bool EditorLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e) {
		if (e.GetMouseButton() == Mouse::ButtonLeft) {
		//	if (m_ViewportHovered && !ImGuizmo::IsOver() && !Input::IsKeyPressed(Key::LeftAlt))
		//		m_SceneHierarchyPanel.SetSelectedEntity(m_HoveredEntity);
		}
		return false;
	}
}

