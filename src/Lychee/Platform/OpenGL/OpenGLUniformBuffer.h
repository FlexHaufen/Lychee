/**
 * @file OpenGLUniformBuffer.h
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2022-11-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

// *** INCLUDES ***
#include "Lychee/lypch.h"

#include "Lychee/Renderer/UniformBuffer.h"

// *** NAMESPACE ***
namespace Lychee {

    /**
     * @brief OpenGLUniformBuffer
     * 
     */
	class OpenGLUniformBuffer : public UniformBuffer {
	public:
		OpenGLUniformBuffer(u32 size, u32 binding);
		virtual ~OpenGLUniformBuffer();

		virtual void SetData(const void* data, u32 size, u32 offset = 0) override;
	private:
		u32 m_RendererID = 0;
	};
}