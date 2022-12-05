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

//*** INCLUDES ***
#include <Lychee/lypch.h>
#include <Lychee/Lychee.h>
#include "Panels/Tools/CalculatorPanel/CalculatorPanel.h"
#include "Panels/Settings/SettingsPanel.h"

//*** DEFINES ***

//*** NAMESPACE ***
namespace Lychee {

	class EditorLayer : public Layer {
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(DeltaTime dt) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;
	private:

		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);

		Lychee::Ref<Lychee::Texture2D> m_Texture;
		Lychee::Ref<Lychee::Framebuffer> m_Framebuffer;

		Lychee::OrthographicCameraController m_CameraController;

		void OnMenuBarRender();

		CalculatorPanel m_Calculator;
		SettingsPanel	m_Settings;


		enum class SceneState {
			Edit = 0, Play = 1, Simulate = 2
		};
		SceneState m_SceneState = SceneState::Edit;
	};

}
