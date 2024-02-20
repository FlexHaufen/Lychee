/**
 * @file Renderer.h
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-02-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

// *** INCLUDES ***
#include "Lychee/lypch.h"

//#include "Lychee/Renderer/OrthographicCamera.h"
//#include "Lychee/Renderer/Shader.h"


// *** NAMESPACE ***
namespace Lychee {

	/**
	 * @brief Renderer Class
	 * 
	 */
	class Renderer {
	public:
		static void Init();
		static void Shutdown();
		
		//static void OnWindowResize(u32 width, u32 height);
		
		//static void BeginScene(OrthographicCamera& camera);
		//static void EndScene();

		//static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		//static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		//struct SceneData {
		//	glm::mat4 ViewProjectionMatrix;
		//};

		//static Scope<SceneData> m_SceneData;
	};
}