/**
 * @file UniformBuffer.h
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-02-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

// *** INCLUDES ***
#include "Lychee/lypch.h"


// *** NAMESPACE ***
namespace Lychee {

    /**
     * @brief Uniform Buffer
     * 
     */
	class UniformBuffer {
	public:
		UniformBuffer(u32 size, u32 binding);
		~UniformBuffer();
		void SetData(const void* data, u32 size, u32 offset = 0);
		
	private:
		u32 m_RendererID = 0;

	};

}