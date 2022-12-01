/**
 * @file RenderCommand.h
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
#include "Lychee/Renderer/RendererAPI.h"

// *** NAMESPACE ***
namespace Lychee {

	class RenderCommand {
	public:
		static void Init() {
			m_RendererAPI->Init();
		}

		static void SetViewport(u32 x, u32 y, u32 width, u32 height) {
			m_RendererAPI->SetViewport(x, y, width, height);
		}

		static void SetClearColor(const glm::vec4& color) {
			m_RendererAPI->SetClearColor(color);
		}

		static void Clear() {
			m_RendererAPI->Clear();
		}

		static void DrawIndexed(const Ref<VertexArray>& vertexArray, u32 indexCount = 0) {
			m_RendererAPI->DrawIndexed(vertexArray, indexCount);
		}

		static void DrawLines(const Ref<VertexArray>& vertexArray, u32 vertexCount) {
			m_RendererAPI->DrawLines(vertexArray, vertexCount);
		}
 		 
		
		static void SetLineWidth(f32 width) {
			m_RendererAPI->SetLineWidth(width);
		}
	private:
		static Scope<RendererAPI> m_RendererAPI;
	};

}
