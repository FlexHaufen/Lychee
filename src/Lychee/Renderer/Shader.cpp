/**
 * @file shader.cpp
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2022-10-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// *** INCLUDES ***
#include "Lychee/Renderer/Shader.h"
#include "Lychee/Renderer/Renderer.h"


#include "Lychee/Platform/OpenGL/OpenGLShader.h"

// *** NAMESPACE ***
namespace Lychee {

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:  
				// Not supported
				return nullptr;
			case RendererAPI::API::OpenGL:  
				break;
		}
        return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader) {
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader) {
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name) {
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const {
		return m_Shaders.find(name) != m_Shaders.end();
	}
 
}