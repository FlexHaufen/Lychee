/**
 * @file Buffer.h
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-02-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

// *** INCLUDE ***
#include "Lychee/lypch.h"

// *** NAMESPACE ***
namespace Lychee {

	enum class eShaderDataType {
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static u32 ShaderDataTypeSize(eShaderDataType type) {
		switch (type) {
			case eShaderDataType::Float:    return 4;
			case eShaderDataType::Float2:   return 4 * 2;
			case eShaderDataType::Float3:   return 4 * 3;
			case eShaderDataType::Float4:   return 4 * 4;
			case eShaderDataType::Mat3:     return 4 * 3 * 3;
			case eShaderDataType::Mat4:     return 4 * 4 * 4;
			case eShaderDataType::Int:      return 4;
			case eShaderDataType::Int2:     return 4 * 2;
			case eShaderDataType::Int3:     return 4 * 3;
			case eShaderDataType::Int4:     return 4 * 4;
			case eShaderDataType::Bool:     return 1;
		}
		return 0;
	}

	struct BufferElement {
		std::string Name;
		eShaderDataType Type;
		u32 Size;
		size_t Offset;
		bool Normalized;

		BufferElement() = default;

		BufferElement(eShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized) {
		}

		u32 GetComponentCount() const {
			switch (Type) {
				case eShaderDataType::Float:   return 1;
				case eShaderDataType::Float2:  return 2;
				case eShaderDataType::Float3:  return 3;
				case eShaderDataType::Float4:  return 4;
				case eShaderDataType::Mat3:    return 3; // 3* float3
				case eShaderDataType::Mat4:    return 4; // 4* float4
				case eShaderDataType::Int:     return 1;
				case eShaderDataType::Int2:    return 2;
				case eShaderDataType::Int3:    return 3;
				case eShaderDataType::Int4:    return 4;
				case eShaderDataType::Bool:    return 1;
			}

			return 0;
		}
	};

	class BufferLayout {
	public:
		BufferLayout() {}

		BufferLayout(std::initializer_list<BufferElement> elements)
			: m_Elements(elements) {
			CalculateOffsetsAndStride();
		}

		u32 GetStride() const { return m_Stride; }
		const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void CalculateOffsetsAndStride() {
			size_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements) {
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		u32 m_Stride = 0;
	};

	class VertexBuffer {
	public:
		VertexBuffer(u32 size);
		VertexBuffer(f32* vertices, u32 size);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;

		void SetData(const void* data, u32 size);

		const BufferLayout& GetLayout() { return m_Layout; }
		void SetLayout(const BufferLayout& layout) { m_Layout = layout; }

	private:
		u32 m_RendererID;
		BufferLayout m_Layout;
	};

	class IndexBuffer {
	public:
		IndexBuffer(u32* indices, u32 count);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		u32 GetCount() const { return m_Count; }

	private:
		u32 m_RendererID;
		u32 m_Count;
	};

}