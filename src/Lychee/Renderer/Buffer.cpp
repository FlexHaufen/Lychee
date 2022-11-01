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

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size) {
        switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:  
				return nullptr;
			case RendererAPI::API::OpenGL:  
				return CreateRef<OpenGLVertexBuffer>(size);
		}
		return CreateRef<OpenGLVertexBuffer>(size);
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size) {
        switch (Renderer::GetAPI()) {
			case RendererAPI::API::None: 
				return nullptr;
			case RendererAPI::API::OpenGL:  
				return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}

		return CreateRef<OpenGLVertexBuffer>(vertices, size);
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:   
				return nullptr;
			case RendererAPI::API::OpenGL: 
				break;
		}
		return CreateRef<OpenGLIndexBuffer>(indices, size);
	}

}