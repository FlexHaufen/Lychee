/**
 * @file Renderer.cpp
 * @author flaxheaufen
 * @brief 
 * @version 0.1
 * @date 2022-11-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// *** INCLUDES ***
#include "Lychee/Renderer/Renderer.h"
#include "Lychee/Renderer/Renderer2D.h"

// *** NAMESPACE ***
namespace Lychee {

	Scope<Renderer::SceneData> Renderer::m_SceneData = CreateScope<Renderer::SceneData>();

	void Renderer::Init() {
        LY_CORE_INFO("Initializing Renderer");
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::Shutdown() {
        LY_CORE_INFO("Terminating Renderer");
		Renderer2D::Shutdown();
	}

	void Renderer::OnWindowResize(u32 width, u32 height) {
        LY_PROFILE_FUNCTION();

		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(OrthographicCamera& camera) {
        LY_PROFILE_FUNCTION();

		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene() {
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform) {
        LY_PROFILE_FUNCTION();

		shader->Bind();
		shader->SetMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}