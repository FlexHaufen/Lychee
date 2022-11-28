/**
 * @file GraphicsContext.cpp
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2022-11-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// *** INCLUDES ***
#include "Lychee/Renderer/GraphicsContext.h"

#include "Lychee/Renderer/Renderer.h"
#include "Lychee/Platform/OpenGL/OpenGLContext.h"

// *** NAMESPACE ***
namespace Lychee {

	Scope<GraphicsContext> GraphicsContext::Create(void* window) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:   	
				LY_CORE_ASSERT(false, "RenderAPI is NONE!");
				return nullptr;
			
			case RendererAPI::API::OpenGL:  
				return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		LY_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}

}