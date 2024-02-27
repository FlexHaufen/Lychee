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

#include "Lychee/Renderer/Voxel.h"

#include "Lychee/Renderer/EditorCamera.h"
#include "Lychee/Scene/SceneCamera.h"

// *** NAMESPACE ***
namespace Lychee {


	struct sRenderer2DData {
		static const u32 MaxQuads = 20000;
		static const u32 MaxVertices = MaxQuads * 4;
		static const u32 MaxIndices = MaxQuads * 6;
		static const u32 MaxTextureSlots = 32;

		Ref<VertexArray> 	QuadVertexArray;
		Ref<VertexBuffer> 	QuadVertexBuffer;
		Ref<Shader> 		QuadShader;

		u32 QuadIndexCount = 0;
		sVoxelVertex* QuadVertexBufferBase = nullptr;
		sVoxelVertex* QuadVertexBufferPtr = nullptr;

		f32 LineWidth = 2.0f;

		glm::vec4 QuadVertexPositions[4];

		struct CameraData {
			glm::mat4 ViewProjection;
		};
		CameraData CameraBuffer;
		//Ref<UniformBuffer> CameraUniformBuffer;
	};


    static sRenderer2DData s_Data;

	/**
	 * @brief Renderer Class
	 * 
	 */
	class Renderer {
	public:
		static void Init();
		static void Shutdown();
		
		static void OnWindowResize(u32 width, u32 height);
		static void SetClearColor(const glm::vec4& color);
		static void Clear();

		static void BeginScene(const EditorCamera& camera);
		//static void BeginScene(const SceneCamera& camera);

		static void RenderVoxel(const glm::vec3& position, const glm::vec4& color);

		static void EndScene();

	private:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};
	};
}