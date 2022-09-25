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

		//** Callbacks **
		//* Window Resize *
		glfwSetWindowSizeCallback(m_glfwWindow, [](GLFWwindow* window, i32 width, i32 height) {
			sWindowData& data = *(sWindowData*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;
			WindowResizeEvent event(width, height);
			data.eventCallback(event);
		});

		//* Window Close *
		glfwSetWindowCloseCallback(m_glfwWindow, [](GLFWwindow* window) {
			sWindowData& data = *(sWindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.eventCallback(event);
		});

		//* Keys *
		glfwSetKeyCallback(m_glfwWindow, [](GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods) {
			sWindowData& data = *(sWindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: {
					KeyPressedEvent event(key, 0);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:{
					KeyReleasedEvent event(key);
					data.eventCallback(event);
					break;
				}
				case GLFW_REPEAT: {
					KeyPressedEvent event(key, true);
					data.eventCallback(event);
					break;
				}
			}
		});

		//* Char *
		glfwSetCharCallback(m_glfwWindow, [](GLFWwindow* window, u32 keycode) {
			sWindowData& data = *(sWindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(keycode);
			data.eventCallback(event);
		});

		//* Mouse Button *
		glfwSetMouseButtonCallback(m_glfwWindow, [](GLFWwindow* window, i32 button, i32 action, i32 mods) {
			sWindowData& data = *(sWindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: {
					MouseButtonPressedEvent event(button);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE: {
					MouseButtonReleasedEvent event(button);
					data.eventCallback(event);
					break;
				}
			}
		});

		//* Mouse Scroll *
		glfwSetScrollCallback(m_glfwWindow, [](GLFWwindow* window, f64 xOffset, f64 yOffset) {
			sWindowData& data = *(sWindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.eventCallback(event);
		});

		//* Mous Pos *
		glfwSetCursorPosCallback(m_glfwWindow, [](GLFWwindow* window, f64 xPos, f64 yPos) {
			sWindowData& data = *(sWindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.eventCallback(event);
		});

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
