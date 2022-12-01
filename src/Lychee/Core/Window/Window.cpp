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

//*** INCLUDES ***
#include "Lychee/Core/Window/Window.h"

//*** DEFINES ***
#include "Lychee/Events/KeyEvent.h"
#include "Lychee/Events/MouseEvent.h"
#include "Lychee/Events/ApplicationEvent.h"

// STB Image
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

//*** NAMESPACE ***
namespace Lychee {

static u8 s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(s32 error, const c8* description) {
		LY_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window::Window(std::string title, u32 width, u32 height) {
		m_sWindowData.title = title;
		m_sWindowData.width = width;
		m_sWindowData.height = height;
        Init();
	}

	Window::~Window() {
		Terminate();
	}

	void Window::Init() {
	
		LY_CORE_INFO("Initializing window: {0} ({1}, {2})", m_sWindowData.title, m_sWindowData.width, m_sWindowData.height);

        LY_CORE_INFO("Initializing glfw");
        if(!glfwInit()){
            LY_CORE_ERROR("Failed to initialize GLFW!");
        }
        glfwSetErrorCallback(GLFWErrorCallback);

		
		LY_CORE_INFO("Initializing glfw Window");
		m_glfwWindow = glfwCreateWindow((s32)m_sWindowData.width, 
                                        (s32)m_sWindowData.height, 
                                        m_sWindowData.title.c_str(), 
                                        nullptr, 
                                        nullptr);
		
		m_Context = GraphicsContext::Create(m_glfwWindow);
		m_Context->Init();

        // glad: load all OpenGL function pointers
		LY_CORE_INFO("Initializing glad");
	    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		    LY_CORE_ERROR("Failed to initalize GLAD!");
		    return;
	    }
		glfwSetWindowUserPointer(m_glfwWindow, &m_sWindowData);

		// Set window ico
		GLFWimage glfwWindowIco[1];
		glfwWindowIco[0].pixels = stbi_load(LY_ICON_PNG, &glfwWindowIco[0].width, &glfwWindowIco[0].height, nullptr, 4);
		glfwSetWindowIcon(m_glfwWindow, 1, glfwWindowIco) ;

        LY_CORE_INFO("Setting vsync to {0}", LY_VSYNC_DEFAULT);
		SetVSync(LY_VSYNC_DEFAULT);

		//** Callbacks **
		//* Window Resize *
		glfwSetWindowSizeCallback(m_glfwWindow, [](GLFWwindow* window, s32 width, s32 height) {
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
		glfwSetKeyCallback(m_glfwWindow, [](GLFWwindow* window, s32 key, s32 scancode, s32 action, s32 mods) {
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
		glfwSetMouseButtonCallback(m_glfwWindow, [](GLFWwindow* window, s32 button, s32 action, s32 mods) {
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

			MouseScrolledEvent event((f32)xOffset, (f32)yOffset);
			data.eventCallback(event);
		});

		//* Mous Pos *
		glfwSetCursorPosCallback(m_glfwWindow, [](GLFWwindow* window, f64 xPos, f64 yPos) {
			sWindowData& data = *(sWindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((f32)xPos, (f32)yPos);
			data.eventCallback(event);
		});

	}

	void Window::Terminate() {
        LY_CORE_INFO("Terminating window");
		glfwDestroyWindow(m_glfwWindow);	
        glfwTerminate();
	}

	void Window::OnUpdate(DeltaTime dt) {

		// NOTE: This function may use unnecessary resources.
		//		 It will not be compiled in releas builds.
		#ifdef LY_SHOW_WINDOWTITLE_FPS
			static u8 i = 50; 
			static const u8 p = 50;

			if (i > p) {
				i = 0;
				u8 fps = u8(1 / dt.GetSeconds());
				std::string title =  m_sWindowData.title + " FPS:  " + std::to_string(fps);
				glfwSetWindowTitle(m_glfwWindow, title.c_str());	
			} 
			else {
				i++;
			}
		#endif

		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void Window::SetVSync(bool enabled) {
        glfwSwapInterval(s32(enabled));
		m_sWindowData.isVSyncOn = enabled;
	}

	bool Window::IsVSync() const {
		return m_sWindowData.isVSyncOn;
	}

}
