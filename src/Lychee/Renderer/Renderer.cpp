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

	void Renderer::Init() {
        LY_CORE_INFO("Renderer: Initializing");

		LY_CORE_INFO("OpenGL Info:");
		LY_CORE_INFO("  Vendor: {0}", 	(GL_VENDOR));
		LY_CORE_INFO("  Renderer: {0}", (GL_RENDERER));
		LY_CORE_INFO("  Version: {0}", 	(GL_VERSION));

		if(GLVersion.major < 4 || (GLVersion.major == 4 && GLVersion.minor < 5)) {
			LY_CORE_CRITICAL("Lychee requires at least OpenGL version 4.5!");
		}

		//#ifdef LY_DEBUG
		//	glEnable(GL_DEBUG_OUTPUT);
		//	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		//	//glDebugMessageCallback(OpenGLMessageCallback, nullptr);
		//	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
		//#endif

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LINE_SMOOTH);
	}

	void Renderer::Shutdown() {
        LY_CORE_INFO("Renderer: Terminating");
	}

	void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
		va.Bind();
		ib.Bind();
		shader.Bind();
		glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	}


	//void Renderer::OnWindowResize(u32 width, u32 height) {
	//	glViewport(x, y, width, height);
	//}

	void Renderer::BeginScene() {
		//m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene() {
	
	}


	
	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray) {
		//shader->Bind();
		//shader->SetMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		//shader->SetMat4("u_Transform", transform);

		vertexArray->Bind();
		//DrawIndexed(vertexArray);
	}
	

	// TODO (flex): Add to renderer Class
	//void SetClearColor(const glm::vec4& color) {
	//	glClearColor(color.r, color.g, color.b, color.a);
	//}

	void Renderer::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void DrawIndexed(const Ref<VertexArray>& vertexArray, u32 indexCount) {
		vertexArray->Bind();
		u32 count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}

	void DrawLines(const Ref<VertexArray>& vertexArray, u32 vertexCount) {
		vertexArray->Bind();
		glDrawArrays(GL_LINES, 0, vertexCount);
	}
 
	void SetLineWidth(f32 width) {
		glLineWidth(width);
	}
}