/**
 * @file RendererAPI.cpp
 * @author flaxhaufen
 * @brief 
 * @version 0.1
 * @date 2022-11-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// *** INCLUDES ***
#include "Lychee/Renderer/RendererAPI.h"

#include "Lychee/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Lychee {

	RendererAPI::API RendererAPI::m_API = RendererAPI::API::OpenGL;

	Scope<RendererAPI> RendererAPI::Create() {
		switch (m_API) {
			case RendererAPI::API::None:  
				LY_CORE_ASSERT(false, "RenderAPI is NONE!");
				return nullptr;
			case RendererAPI::API::OpenGL:  
				return CreateScope<OpenGLRendererAPI>();
		}

		LY_CORE_ASSERT(false, "Unknown RenderAPI");
		return nullptr;
	}

}