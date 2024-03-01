/**
 * @file VertexArray.h
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-02-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

// *** INCLUDES ***
#include "Lychee/lypch.h"
#include "Lychee/Renderer/Buffer.h"

// *** NAMESPACE ***
namespace Lychee {

	class VertexArray {
	public:
		VertexArray();
		~VertexArray();

		void Bind() const;
		void Unbind() const;

		void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer);
		void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer);

		const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

	private:
		u32 m_RendererID;
		u32 m_VertexBufferIndex = 0;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};

}
