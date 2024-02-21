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

#include "Lychee/Renderer/VertexArray.h"
#include "Lychee/Renderer/Buffer.h"
#include "Lychee/Renderer/Shader.h"

// *** NAMESPACE ***
namespace Lychee {

	/**
	 * @brief Renderer Class
	 * 
	 */
	class Renderer {
	public:
		void Init();
		void Shutdown();
		
		void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

		void OnWindowResize(u32 width, u32 height);

		void Clear();


		void BeginScene();
		void EndScene();
		void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray);

	private:
		//struct SceneData {
		//	glm::mat4 ViewProjectionMatrix;
		//};

		//static Scope<SceneData> m_SceneData;
	};
}