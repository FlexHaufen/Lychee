/**
 * @file Frambuffer.cpp
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2022-12-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// *** INCLUDES ***
#include "Lychee/Renderer/Framebuffer.h"
#include "Lychee/Renderer/Renderer.h"

#include "Lychee/Platform/OpenGL/OpenGLFramebuffer.h"

namespace Lychee {
	
	Ref<Framebuffer> Framebuffer::Create(const sFramebufferSpecification& spec) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:    LY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLFramebuffer>(spec);
		}

		LY_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
