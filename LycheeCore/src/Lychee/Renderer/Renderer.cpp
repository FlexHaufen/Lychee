/**
 * @file Renderer.cpp
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-03-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */

// *** INCLUDES ***
#include "Lychee/Renderer/Renderer.h"


// *** DEFINE ***

// *** NAMESPACE ***
namespace Lychee {
    
    void Renderer::Init() {
        LY_CORE_INFO("Renderer: Initializing");

        LY_CORE_INFO("OpenGL Info:");
        LY_CORE_INFO("  Vendor: {0}", 	(GL_VENDOR));
        LY_CORE_INFO("  Renderer: {0}", (GL_RENDERER));
        LY_CORE_INFO("  Version: {0}", 	(GL_VERSION));

        if(GLVersion.major < 4 || (GLVersion.major == 4 && GLVersion.minor < 5)) {
            LY_CORE_CRITICAL("Lychee requires at least OpenGL version 4.5!");
        }

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        // Shaders
        // TODO: No abs Path / Check if file exists
        m_VoxelShader = CreateRef<Shader>("LycheeCore/src/Lychee/Renderer/shaders/voxel.glsl");
        //LY_CORE_INFO("Linked Shader {0}", m_VoxelShader->GetName());

        // Buffers
        // Cube vertices
        GLfloat vertices[] = {
            // Front face
            -0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
            // Back face
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            -0.5f, 0.5f, -0.5f
        };

        // Cube indices
        GLuint indices[] = {
            0, 1, 2, 2, 3, 0,  // Front face
            1, 5, 6, 6, 2, 1,  // Right face
            7, 6, 5, 5, 4, 7,  // Back face
            4, 0, 3, 3, 7, 4,  // Left face
            4, 5, 1, 1, 0, 4,  // Bottom face
            3, 2, 6, 6, 7, 3   // Top face
        };

        // Generate VAO, VBO, and EBO
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        // Bind VAO
        glBindVertexArray(VAO);

        // Bind VBO and set vertex data
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Bind EBO and set index data
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Set vertex attribute pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);

        // Unbind VAO
        glBindVertexArray(0);


        // Set up viewport
        glViewport(0, 0, 1920, 1080);
    }

    

    void Renderer::Clear() {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::Render(const glm::mat4& viewProjectionMatrix) {
        // Use the shader program
        m_VoxelShader->Bind();

        // Retrieve the uniform location of the view projection matrix
        GLuint viewProjectionMatrixLocation = glGetUniformLocation(m_VoxelShader->GetID(), "viewProjectionMatrix");
        // Set the value of the view projection matrix uniform
        glUniformMatrix4fv(viewProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix));

        // Bind VAO and draw
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
}