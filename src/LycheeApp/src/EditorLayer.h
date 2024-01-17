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

// *** DEFINES ***

// *** NAMESPACE ***
namespace Lychee {

	class EditorLayer : public Layer {
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(DeltaTime dt) override;
		virtual void OnImGuiRender() override;
		void OnEvent(sf::Event& e) override;
	private:


		//bool OnKeyPressed(KeyPressedEvent& e);
		//bool OnMouseButtonPressed(MouseButtonPressedEvent& e);

		void OnMenuBarRender();

	private:

		// ** Members **
		Ref<Scene> m_ActiveScene;		// Current active Scene
		sf::Vector2f m_ViewportSize;	// Current ViewPortSize

		enum class SceneState {
			Edit = 0, Play = 1, Simulate = 2
		};
		SceneState m_SceneState = SceneState::Edit;
	};

}
