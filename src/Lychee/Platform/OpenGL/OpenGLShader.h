#pragma once

#include "Lychee/lypch.h"
#include "Lychee/Renderer/Shader.h"


// TODO: REMOVE!
typedef unsigned int GLenum;

namespace Lychee {

	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;
	
		virtual const std::string& GetName() const override { return m_Name; }
		
		void CreateProgram();

	private:
		uint32_t m_RendererID;
		std::string m_FilePath;
		std::string m_Name;

		//std::unordered_map<GLenum, std::vector<uint32_t>> m_VulkanSPIRV;
		std::unordered_map<GLenum, std::vector<uint32_t>> m_OpenGLSPIRV;
		std::unordered_map<GLenum, std::string> m_OpenGLSourceCode;
	};

}
