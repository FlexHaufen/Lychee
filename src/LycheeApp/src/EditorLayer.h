/**
 * @file EditorLayer.h
 * @author flexhaufen
 * @brief ImGui Main
 * @version 0.1
 * @date 2022-09-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

// *** INCLUDES ***
#include <Lychee/lypch.h>
#include <Lychee/Lychee.h>

#include "LycheeApp/src/Panels/ContentBrowserPanel.h"

// *** DEFINES ***

// *** NAMESPACE ***
namespace Lychee {

	class EditorLayer : public Layer {
	public:
		EditorLayer();
		~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(DeltaTime dt) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;
	private:


		b8 OnKeyPressed(KeyPressedEvent& e);
		b8 OnMouseButtonPressed(MouseButtonPressedEvent& e);

		void OnMenuBarRender();

	private:

		// ** Members **
		Ref<Scene> m_ActiveScene;					// Current active Scene
		enum class SceneState {
			Edit = 0, Play = 1, Simulate = 2
		};
		SceneState m_SceneState = SceneState::Edit;

		Ref<Framebuffer> m_Framebuffer;

		b8 m_ViewportFocused = false;				// True if viewport is focused
		b8 m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		glm::vec2 m_ViewportBounds[2];
		EditorCamera m_EditorCamera;

		// Panels
		ContentBrowserPanel m_ContentBrowserPanel;
	};

}
