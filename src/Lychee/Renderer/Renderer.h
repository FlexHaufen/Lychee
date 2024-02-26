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

#include "Lychee/Renderer/EditorCamera.h"
#include "Lychee/Scene/SceneCamera.h"

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
		

		static void OnWindowResize(u32 width, u32 height);

		static void Clear();


		//static void BeginScene();
		static void BeginScene(const EditorCamera& camera);
		//static void BeginScene(const SceneCamera& camera);

		static void SetClearColor(const glm::vec4& color);


		static void EndScene();
		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray);

	private:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};
		
		static Scope<SceneData> m_SceneData;
	};
}