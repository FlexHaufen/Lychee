/**
 * @file OpenGLUniformBuffer.cpp
 * @author flaxhaufen
 * @brief 
 * @version 0.1
 * @date 2022-11-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// *** INCLUDES ***
#include "Lychee/Platform/OpenGL/OpenGLUniformBuffer.h"

// *** NAMESPACE ***
namespace Lychee {

	OpenGLUniformBuffer::OpenGLUniformBuffer(u32 size, u32 binding) {
		glCreateBuffers(1, &m_RendererID);
		glNamedBufferData(m_RendererID, size, nullptr, GL_DYNAMIC_DRAW); // TODO: investigate usage hint
		glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_RendererID);
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer() {
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLUniformBuffer::SetData(const void* data, u32 size, u32 offset) {
		glNamedBufferSubData(m_RendererID, offset, size, data);
	}

}