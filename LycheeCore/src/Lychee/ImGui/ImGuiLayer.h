/**
 * @file ImGuiLayer.h
 * @author flexhaufen
 * @brief ImGui Layer
 * 		  NOTE: ImGui has to be on docking branch
 * @version 0.1
 * @date 2022-09-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

// *** INCLUDES ***
#include "Lychee/Core/Layer/Layer.h"

//* Events *
//#include "Lychee/Events/ApplicationEvent.h"
//#include "Lychee/Events/KeyEvent.h"
//#include "Lychee/Events/MouseEvent.h"

// *** DEFINES ***

// *** NAMESPACE ***
namespace Lychee {

	class ImGuiLayer : public Layer { 
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }
		
		void SetStyle();
	private:
		bool m_BlockEvents = false;
	};
}
