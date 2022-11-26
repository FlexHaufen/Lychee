/**
 * @file Renderer2D.cpp
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2022-11-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// *** INCLUDES ***
#include "Renderer2D.h"

#include "Lychee/Renderer/VertexArray.h"
#include "Lychee/Renderer/Shader.h"
#include "Lychee/Renderer/RenderCommand.h"


// *** NAMESPACE ***
namespace Lychee {

    struct Renderer2D_Data {
        Ref<VertexArray>    QuadVertexArray;
		//Ref<VertexBuffer>   QuadVertexBuffer;
		Ref<Shader>         FlatColorShader;
		Ref<Shader>         TextureShader;

    };

    static Renderer2D_Data* s_Data;

    void Renderer2D::Init() {
        LY_CORE_INFO("Initializing Renderer2D");

        s_Data = new Renderer2D_Data();

        s_Data->QuadVertexArray = VertexArray::Create();

		f32 vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // btm left
			 0.5f, -0.5f, 0.0f,	1.0f, 0.0f, // btm right
			 0.5f,  0.5f, 0.0f,	1.0f, 1.0f, // top right
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f  // top left
		};

		Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
	    vertexBuffer->SetLayout({
			{ eShaderDataType::Float3, "a_Position" },
			{ eShaderDataType::Float2, "a_TextCoord" }
		});
		s_Data->QuadVertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		s_Data->QuadVertexArray->SetIndexBuffer(indexBuffer);

        // FIXME: this path is bad - find other loaction for simple shaders
		s_Data->FlatColorShader = Shader::Create("src/LycheeApp/src/assets/shaders/FlatColorShader.glsl");
        s_Data->TextureShader = Shader::Create("src/LycheeApp/src/assets/shaders/TextureShader.glsl");

        s_Data->TextureShader->Bind();
        s_Data->TextureShader->SetInt("u_Texture", 0);
    }
    
    void Renderer2D::Shutdown() {
        LY_CORE_INFO("Terminating Renderer2D");
        delete s_Data;
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera) {
        s_Data->FlatColorShader->Bind();
        s_Data->FlatColorShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

        s_Data->TextureShader->Bind();
        s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
    }
    
    void Renderer2D::EndScene() {

    }
    
    void Renderer2D::Flush() {

    }


    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
        DrawQuad({position.x, position.y, 0.0f}, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
        s_Data->FlatColorShader->Bind();
        s_Data->FlatColorShader->SetFloat4("u_Color", color); 

        // Calculate transform: Translation * Rotation * Scale
        // Rotation is not added!
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
        s_Data->FlatColorShader->SetMat4("u_Transform", transform); 
        
        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }


    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D> texture) {
        DrawQuad({position.x, position.y, 0.0f}, size, texture);
    }
    
    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D> texture) {
        s_Data->TextureShader->Bind();

        // Calculate transform: Translation * Rotation * Scale
        // Rotation is not added!
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
        s_Data->TextureShader->SetMat4("u_Transform", transform); 
        
        texture->Bind();

        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
        
    }


}