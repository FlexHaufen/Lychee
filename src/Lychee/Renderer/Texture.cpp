/**
 * @file Texture.cpp
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2022-11-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// *** INCLUDES ***
#include "Lychee/Renderer/Texture.h"

#include "Lychee/Renderer/Renderer.h"
#include "Lychee/Platform/OpenGL/OpenGLTexture.h"

// *** NAMESPACE ***
namespace Lychee {

	Ref<Texture2D> Texture2D::Create(u32 width, u32 height) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:    
				LY_CORE_ASSERT(false, "RenderAPI is NONE!");
				return nullptr;
			case RendererAPI::API::OpenGL:  
				return CreateRef<OpenGLTexture2D>(width, height);
		}
		
		LY_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:    
				LY_CORE_ASSERT(false, "RenderAPI is NONE!");
				return nullptr;
			case RendererAPI::API::OpenGL:  
				return CreateRef<OpenGLTexture2D>(path);
		}

		LY_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}

}