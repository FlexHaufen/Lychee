/**
 * @file OpenGLRendererAPI.h
 * @author flaxhaufen
 * @brief Abstraction of RendererAPI
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

	class OpenGLRendererAPI : public RendererAPI {
	public:
		virtual void Init() override;
		virtual void SetViewport(u32 x, u32 y, u32 width, u32 height) override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		/* virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, u32 indexCount = 0) override;
		virtual void DrawLines(const Ref<VertexArray>& vertexArray, u32 vertexCount) override;
		*/
		virtual void SetLineWidth(f32 width) override;
	};


}
