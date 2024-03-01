/**
 * @file LayerStack.h
 * @author flexhaufen
 * @brief LayerStack
 * @version 0.1
 * @date 2022-09-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

// *** INCLUDE ***
#include "Lychee/lypch.h"
#include "Lychee/Core/Layer/Layer.h"

// *** DEFINES ***

// *** NAMESPACE
namespace Lychee {

	class LayerStack {
	public:
		LayerStack() = default;
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
		std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }

		std::vector<Layer*>::const_iterator begin() const { return m_Layers.begin(); }
		std::vector<Layer*>::const_iterator end()	const { return m_Layers.end(); }
		std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator rend() const { return m_Layers.rend(); }
	private:
		std::vector<Layer*> m_Layers;			// Layer Vector
		u32 m_LayerInsertIndex = 0;
	};

}