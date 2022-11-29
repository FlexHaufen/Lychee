/**
 * @file VertexArray.cpp
 * @author flaxhaufen
 * @brief 
 * @version 0.1
 * @date 2022-11-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// *** INCLUDES ***
#include "Lychee/Renderer/VertexArray.h"

#include "Lychee/Renderer/Renderer.h"
#include "Lychee/Platform/OpenGL/OpenGLVertexArray.h"

// *** NAMESPACE ***
namespace Lychee {

	Ref<VertexArray> VertexArray::Create() {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:   
				LY_CORE_ASSERT(false, "RenderAPI is NONE!");
				return nullptr;
			case RendererAPI::API::OpenGL:  
				return CreateRef<OpenGLVertexArray>();
		}

		LY_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}

}