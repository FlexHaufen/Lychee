/**
 * @file OpenGLContext.cpp
 * @author flaxhaufen
 * @brief 
 * @version 0.1
 * @date 2022-11-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// *** INCLUDES ***
#include "Lychee/Platform/OpenGL/OpenGLContext.h"

// *** NAMESPACE ***
namespace Lychee {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle) {

		LY_CORE_ASSERT(windowHandle, "Could not create OpenGL window");
	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);
		s32 status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		
		if(!status) {
			LY_CORE_ERROR("Failed to initialize Glad!");
		}

		LY_CORE_INFO("OpenGL Info:");
		LY_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		LY_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		LY_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

		if(GLVersion.major < 4 || (GLVersion.major == 4 && GLVersion.minor < 5)) {
			LY_CORE_CRITICAL("Lychee requires at least OpenGL version 4.5!");
		}
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}
}
