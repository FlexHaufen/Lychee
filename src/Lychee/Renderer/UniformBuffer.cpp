/**
 * @file UniformBuffer.cpp
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-02-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */

// *** INCLUDES *** 
#include "Lychee/Renderer/UniformBuffer.h"

#include "Lychee/Renderer/Renderer.h"

// *** NAMESPACE ***
namespace Lychee {

	UniformBuffer::UniformBuffer(u32 size, u32 binding) {
		glCreateBuffers(1, &m_RendererID);
		glNamedBufferData(m_RendererID, size, nullptr, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_RendererID);
	}

	UniformBuffer::~UniformBuffer() {
		glDeleteBuffers(1, &m_RendererID);
	}

	void UniformBuffer::SetData(const void* data, u32 size, u32 offset) {
		glNamedBufferSubData(m_RendererID, offset, size, data);
	}

}