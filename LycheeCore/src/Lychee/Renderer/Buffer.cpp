/**
 * @file Buffer.cpp
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-02-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

// *** INCLUDES **

#include "Lychee/Renderer/Buffer.h"
#include "Lychee/Renderer/Renderer.h"

// *** NAMESPACE ***
namespace Lychee {

	// *** VERTEX BUFFER ***
	VertexBuffer::VertexBuffer(u32 size) {
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	VertexBuffer::VertexBuffer(f32* vertices, u32 size) {
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer() {
		glDeleteBuffers(1, &m_RendererID);
	}

	void VertexBuffer::Bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void VertexBuffer::Unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::SetData(const void* data, u32 size) {
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}


	// *** INDEX BUFFER ***
	IndexBuffer::IndexBuffer(u32* indices, u32 count)
		: m_Count(count) {

		glCreateBuffers(1, &m_RendererID);
		
		// GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
		// Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state. 
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(u32), indices, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer() {
		glDeleteBuffers(1, &m_RendererID);
	}

	void IndexBuffer::Bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void IndexBuffer::Unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}