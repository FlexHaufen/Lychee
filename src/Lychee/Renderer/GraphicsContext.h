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
		GraphicsContext(GLFWwindow* windowHandle);

		void Init();
		void SwapBuffers();

	private:
		GLFWwindow* m_WindowHandle;

	};

}
