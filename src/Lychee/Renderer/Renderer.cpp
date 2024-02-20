/**
 * @file Renderer.cpp
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-02-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

// *** INCLUDES ***
#include "Lychee/Renderer/Renderer.h"

// *** NAMESPACE ***
namespace Lychee {

	//Scope<Renderer::SceneData> Renderer::m_SceneData = CreateScope<Renderer::SceneData>();

	void Renderer::Init() {
        LY_CORE_INFO("Initializing Renderer");
	}

	void Renderer::Shutdown() {
        LY_CORE_INFO("Terminating Renderer");
	}

	//void Renderer::OnWindowResize(u32 width, u32 height) {
	//	RenderCommand::SetViewport(0, 0, width, height);
	//}

	//void Renderer::BeginScene(OrthographicCamera& camera) {
	//	m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	//}

	//void Renderer::EndScene() {
	//}

	/*
	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform) {
		shader->Bind();
		shader->SetMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
	*/
}