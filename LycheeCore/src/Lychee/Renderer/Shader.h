/**
 * @file Shader.h
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-02-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

// *** INCLUDES ***
#include "Lychee/lypch.h"

// *** NAMESPACE ***
namespace Lychee {

    class Shader {
    public:
		Shader(const std::string& filepath);
		Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();
        
        void Bind() const;
        void Unbind() const;

        void SetInt(const std::string& name, s32 value);
		void SetIntArray(const std::string& name, s32* values, u32 count);
		void SetFloat(const std::string& name, f32 value);
		//void SetFloat2(const std::string& name, const glm::vec2& value);
		//void SetFloat3(const std::string& name, const glm::vec3& value);
		//void SetFloat4(const std::string& name, const glm::vec4& value);
		//void SetMat4(const std::string& name, const glm::mat4& value);

		void UploadUniformInt(const std::string& name, s32 value);
		void UploadUniformIntArray(const std::string& name, s32* values, u32 count);
		void UploadUniformFloat(const std::string& name, f32 value);
		//void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		//void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		//void UploadUniformFloat4(const std::string& name, const glm::vec4& value);
		//void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		//void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

        const std::string& GetName() const { return m_Name; };
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
		void CreateProgram();
        
	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);

	private:
		u32 m_RendererID;
		std::string m_FilePath;
		std::string m_Name;

		std::unordered_map<GLenum, std::vector<u32>> m_OpenGLSPIRV;
		std::unordered_map<GLenum, std::string> m_OpenGLSourceCode;
    };

    class ShaderLibrary {
	public:
		void Add(const std::string& name, const Ref<Shader>& shader);
		void Add(const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);

		Ref<Shader> Get(const std::string& name);

		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}