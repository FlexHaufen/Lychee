/**
 * @file Layer.h
 * @author flaxhaufen
 * @brief Layer
 * @version 0.1
 * @date 2022-09-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

// *** INCLUDES ***
#include <string>

#include "Lychee/Events/Event.h"
#include "Lychee/Core/Time/DeltaTime.h"

// *** DEFINES ***

// *** NAMESPACE ***
namespace Lychee {

	class Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(DeltaTime dt) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}

		const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}