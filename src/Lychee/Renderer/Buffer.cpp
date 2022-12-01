/**
 * @file Buffer.cpp
 * @author flaxhaufen
 * @brief 
 * @version 0.1
 * @date 2022-11-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// *** INCLUDES **
#include "Lychee/Renderer/Buffer.h"
#include "Lychee/Renderer/Renderer.h"

#include "Lychee/Platform/OpenGL/OpenGLBuffer.h"

// *** NAMESPACE ***
namespace Lychee {

	Ref<VertexBuffer> VertexBuffer::Create(u32 size) {
        switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:  
				LY_CORE_ASSERT(false, "RenderAPI is NONE!");
				return nullptr;
			case RendererAPI::API::OpenGL:  
				return CreateRef<OpenGLVertexBuffer>(size);
			
			LY_CORE_ASSERT(false, "Unknown RenderAPI!");
		}
		return CreateRef<OpenGLVertexBuffer>(size);
	}

	Ref<VertexBuffer> VertexBuffer::Create(f32* vertices, u32 size) {
        switch (Renderer::GetAPI()) {
			case RendererAPI::API::None: 
				LY_CORE_ASSERT(false, "RenderAPI is NONE!");
				return nullptr;
			case RendererAPI::API::OpenGL:  
				return CreateRef<OpenGLVertexBuffer>(vertices, size);
		
			LY_CORE_ASSERT(false, "Unknown RenderAPI!");
		}

		return CreateRef<OpenGLVertexBuffer>(vertices, size);
	}

	Ref<IndexBuffer> IndexBuffer::Create(u32* indices, u32 size) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:   
				LY_CORE_ASSERT(false, "RenderAPI is NONE!");
				return nullptr;
			case RendererAPI::API::OpenGL: 
				break;

			LY_CORE_ASSERT(false, "Unknown RenderAPI!");
		}
		return CreateRef<OpenGLIndexBuffer>(indices, size);
	}

}