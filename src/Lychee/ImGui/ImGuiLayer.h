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
#include "Lychee/lypch.h"
#include "Lychee/Core/Layer/Layer.h"

//* Events *
//#include "Lychee/Events/ApplicationEvent.h"
//#include "Lychee/Events/KeyEvent.h"
//#include "Lychee/Events/MouseEvent.h"

#include "Lychee/Core/Time/DeltaTime.h"

#include "Lychee/Core/Layer/LayerStack.h"

// *** DEFINES ***

// *** NAMESPACE ***
namespace Lychee {

	class ImGuiLayer : public Layer { 
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(sf::Event& e) override;

		void OnSfmlUpdate(DeltaTime dt);
		void OnSfmlRender();
		
		void BlockEvents(bool block) { m_BlockEvents = block; }
		
		void SetStyle();
	private:
		sf::RenderWindow& m_Window;
		bool m_BlockEvents = false;
	};
}
