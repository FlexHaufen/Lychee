#pragma once

#include "Lychee/lypch.h"
#include "Lychee/Renderer/Shader.h"


// TODO: REMOVE!
typedef u32 GLenum;

namespace Lychee {

	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetInt(const std::string& name, s32 value) override;
		virtual void SetIntArray(const std::string& name, s32* values, u32 count) override;
		virtual void SetFloat(const std::string& name, f32 value) override;
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) override;
	
		void UploadUniformInt(const std::string& name, s32 value);
		void UploadUniformIntArray(const std::string& name, s32* values, u32 count);

		void UploadUniformFloat(const std::string& name, f32 value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

		virtual const std::string& GetName() const override { return m_Name; }
		
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
		void CreateProgram();

	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);

	private:
		u32 m_RendererID;
		std::string m_FilePath;
		std::string m_Name;

		//std::unordered_map<GLenum, std::vector<u32>> m_VulkanSPIRV;
		std::unordered_map<GLenum, std::vector<u32>> m_OpenGLSPIRV;
		std::unordered_map<GLenum, std::string> m_OpenGLSourceCode;
	};

}
