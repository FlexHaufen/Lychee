/**
 * @file Renderer.h
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2022-11-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

// *** INCLUDES ***
#include "Lychee/lypch.h"

#include "Lychee/Renderer/RenderCommand.h"

//#include "Lychee/Renderer/OrthographicCamera.h"
#include "Lychee/Renderer/Shader.h"


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
		
		static void OnWindowResize(uint32_t width, uint32_t height);

		
		static void BeginScene();
		static void EndScene();

		// TODO: Sheder gose here
		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<SceneData> m_SceneData;
	};
}