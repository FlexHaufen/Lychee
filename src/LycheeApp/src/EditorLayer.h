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
#include <Lychee/Lychee.h>
#include "Panels/CalculatorPanel/CalculatorPanel.h"
//*** DEFINES ***

//*** NAMESPACE ***
namespace Lychee {

	class EditorLayer : public Layer {
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;
	private:
	
		CalculatorPanel m_Calculator;

		enum class SceneState {
			Edit = 0, Play = 1, Simulate = 2
		};
		SceneState m_SceneState = SceneState::Edit;
	};

}
