/**
 * @file GraphicsContext.h
 * @author flaxhaufen
 * @brief 
 * @version 0.1
 * @date 2022-11-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
// *** INCLUDES ***
#include "Lychee/lypch.h"


// *** NAMESPACE ***
namespace Lychee {

	class GraphicsContext {
	public:
		virtual ~GraphicsContext() = default;

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		static Scope<GraphicsContext> Create(void* window);
	};

}
