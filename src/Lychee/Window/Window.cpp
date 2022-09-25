/**
 * @file Window.cpp
 * @author flexhaufen
 * @brief Window of app
 * @version 0.1
 * @date 2022-09-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

//*** INCLUDES ***
#include "Lychee/Window/Window.h"

//*** DEFINES ***
#include "Lychee/Events/KeyEvent.h"
#include "Lychee/Events/MouseEvent.h"
#include "Lychee/Events/ApplicationEvent.h"

//*** NAMESPACE ***
namespace Lychee {

static uint8_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int error, const char* description) {
		LY_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window::Window(std::string title, u32 width, u32 height) {
		m_sWindowData.title = title;
		m_sWindowData.width = width;
		m_sWindowData.height = height;
        Init();
	}

	Window::~Window() {
		Shutdown();
	}

	void Window::Init() {
	
		LY_CORE_INFO("Creating window {0} ({1}, {2})", m_sWindowData.title, m_sWindowData.width, m_sWindowData.height);

        LY_CORE_INFO("Init glfw");
        if(!glfwInit()){
            LY_CORE_ERROR("Failed to initialize GLFW!");
        }
        glfwSetErrorCallback(GLFWErrorCallback);

		
		LY_CORE_INFO("Create glfw Window");
		m_glfwWindow = glfwCreateWindow((int)m_sWindowData.width, 
                                        (int)m_sWindowData.height, 
                                        m_sWindowData.title.c_str(), 
                                        nullptr, 
                                        nullptr);
		
		glfwMakeContextCurrent(m_glfwWindow);

        // glad: load all OpenGL function pointers
	    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		    LY_CORE_ERROR("Failed to initalize GLAD");
		    return;
	    }
		glfwSetWindowUserPointer(m_glfwWindow, &m_sWindowData);

        LY_CORE_TRACE("Setting vsync to true");
		SetVSync(true);
	}

	void Window::Shutdown() {
        LY_CORE_INFO("Shutting down window");
		glfwDestroyWindow(m_glfwWindow);	
        glfwTerminate();
	}

	void Window::OnUpdate() {
		glfwPollEvents();
        glfwSwapBuffers(m_glfwWindow);
	}

	void Window::SetVSync(bool enabled) {
        glfwSwapInterval(int(enabled));
		m_sWindowData.isVSyncOn = enabled;
	}

	bool Window::IsVSync() const {
		return m_sWindowData.isVSyncOn;
	}
}
