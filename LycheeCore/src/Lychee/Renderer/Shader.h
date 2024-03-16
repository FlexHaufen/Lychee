/**
 * @file Shader.h
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-03-12
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
        ~Shader();

        void Bind() const;
        void Unbind() const;

        const std::string& GetName() const { return m_Name; }
        const uint32_t& GetID() const { return m_RendererID; }

    private:
        void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
        void CreateProgram();
        std::string ReadFile(const std::string& filepath);
        std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);

    private:
        uint32_t m_RendererID;
        std::string m_FilePath;
        std::string m_Name;
        std::unordered_map<GLenum, std::vector<uint32_t>> m_OpenGLSPIRV;
    };
}