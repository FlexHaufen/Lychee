/**
 * @file RendererAPI.h
 * @author flaxhaufen
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
#include "Lychee/Renderer/VertexArray.h"

// *** NAMESPACE ***
namespace Lychee {

	class RendererAPI {
	public:

		// NOTE: Render API's can be added here.
		//		 They also have to be implementet in ./Lychee/Platforms/
		//		 and in RendererAPI.cpp -> See exampel with OpenGL
		enum class API {
			None = 0, 
			OpenGL = 1
		};
	public:
		virtual ~RendererAPI() = default;

		virtual void Init() = 0;
		virtual void SetViewport(u32 x, u32 y, u32 width, u32 height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, u32 indexCount = 0) = 0;
		virtual void DrawLines(const Ref<VertexArray>& vertexArray, u32 vertexCount) = 0;
		
		virtual void SetLineWidth(f32 width) = 0;

		static API GetAPI() { return m_API; }
		static Scope<RendererAPI> Create();
	private:
		static API m_API;
	};

}
