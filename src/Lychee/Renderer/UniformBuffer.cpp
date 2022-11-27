/**
 * @file UniformBuffer.cpp
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2022-11-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// *** INCLUDES *** 
#include "Lychee/Renderer/UniformBuffer.h"

#include "Lychee/Renderer/Renderer.h"
#include "Lychee/Platform/OpenGL/OpenGLUniformBuffer.h"

// *** NAMESPACE ***
namespace Lychee {

	Ref<UniformBuffer> UniformBuffer::Create(u32 size, u32 binding) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:    return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLUniformBuffer>(size, binding);
		}

		return nullptr;
	}

}