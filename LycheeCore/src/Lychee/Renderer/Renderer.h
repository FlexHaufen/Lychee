/**
 * @file Renderer.h
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-03-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

// *** INCLUDES ***
#include "Lychee/lypch.h"
#include "Lychee/Renderer/Shader.h"



// *** NAMESPACE ***
namespace Lychee {

    class Renderer {
    public:
        Renderer() {}

        void Init();
        void Clear();
        void Render(const glm::mat4& viewProjectionMatrix);

        static void OnWindowResize(uint32_t width, uint32_t height) { glViewport(0, 0, width, height); };

    private:
        Ref<Shader> m_VoxelShader;
    
        GLuint VAO, VBO, EBO;
    };
}