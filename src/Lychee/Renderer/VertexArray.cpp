/**
 * @file VertexArray.cpp
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-02-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */

// *** INCLUDES ***
#include "Lychee/Renderer/VertexArray.h"

#include "Lychee/Renderer/Renderer.h"

// *** NAMESPACE ***
namespace Lychee {

	static GLenum eShaderDataTypeToOpenGLBaseType(eShaderDataType type) {
		switch (type) {
			case eShaderDataType::Float:    return GL_FLOAT;
			case eShaderDataType::Float2:   return GL_FLOAT;
			case eShaderDataType::Float3:   return GL_FLOAT;
			case eShaderDataType::Float4:   return GL_FLOAT;
			case eShaderDataType::Mat3:     return GL_FLOAT;
			case eShaderDataType::Mat4:     return GL_FLOAT;
			case eShaderDataType::Int:      return GL_INT;
			case eShaderDataType::Int2:     return GL_INT;
			case eShaderDataType::Int3:     return GL_INT;
			case eShaderDataType::Int4:     return GL_INT;
			case eShaderDataType::Bool:     return GL_BOOL;
		}
		return 0;
	}

	VertexArray::VertexArray() {
		glCreateVertexArrays(1, &m_RendererID);
	}

	VertexArray::~VertexArray() {
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void VertexArray::Bind() const {
		glBindVertexArray(m_RendererID);
	}

	void VertexArray::Unbind() const {
		glBindVertexArray(0);
	}

	void VertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {

		//ASSERT (vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout) {
			switch (element.Type) {
				case eShaderDataType::Float:
				case eShaderDataType::Float2:
				case eShaderDataType::Float3:
				case eShaderDataType::Float4: {
					glEnableVertexAttribArray(m_VertexBufferIndex);
					glVertexAttribPointer(m_VertexBufferIndex,
						element.GetComponentCount(),
						eShaderDataTypeToOpenGLBaseType(element.Type),
						element.Normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)element.Offset);
					m_VertexBufferIndex++;
					break;
				}
				case eShaderDataType::Int:
				case eShaderDataType::Int2:
				case eShaderDataType::Int3:
				case eShaderDataType::Int4:
				case eShaderDataType::Bool: {
					glEnableVertexAttribArray(m_VertexBufferIndex);
					glVertexAttribIPointer(m_VertexBufferIndex,
						element.GetComponentCount(),
						eShaderDataTypeToOpenGLBaseType(element.Type),
						layout.GetStride(),
						(const void*)element.Offset);
					m_VertexBufferIndex++;
					break;
				}
				case eShaderDataType::Mat3:
				case eShaderDataType::Mat4: {
					u8 count = element.GetComponentCount();
					for (u8 i = 0; i < count; i++) {
						glEnableVertexAttribArray(m_VertexBufferIndex);
						glVertexAttribPointer(m_VertexBufferIndex,
							count,
							eShaderDataTypeToOpenGLBaseType(element.Type),
							element.Normalized ? GL_TRUE : GL_FALSE,
							layout.GetStride(),
							(const void*)(element.Offset + sizeof(f32) * count * i));
						glVertexAttribDivisor(m_VertexBufferIndex, 1);
						m_VertexBufferIndex++;
					}
					break;
				}
				default:
					break;
					// ASSERT (false, "Unknown eShaderDataType!");
			}
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void VertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}