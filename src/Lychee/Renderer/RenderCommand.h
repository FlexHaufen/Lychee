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

			// Check if given RendererAPI exists
			if (m_RendererAPI == nullptr) {
				LY_CORE_CRITICAL("Render API does not exist or is unknown");
				return;
			}
			m_RendererAPI->Init();
		}

		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
			m_RendererAPI->SetViewport(x, y, width, height);
		}

		static void SetClearColor(const glm::vec4& color) {
			m_RendererAPI->SetClearColor(color);
		}

		static void Clear() {
			m_RendererAPI->Clear();
		}

		static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) {
			m_RendererAPI->DrawIndexed(vertexArray, indexCount);
		}

		static void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount) {
			m_RendererAPI->DrawLines(vertexArray, vertexCount);
		}
 		 
		
		static void SetLineWidth(f32 width) {
			m_RendererAPI->SetLineWidth(width);
		}
	private:
		static Scope<RendererAPI> m_RendererAPI;
	};

}
