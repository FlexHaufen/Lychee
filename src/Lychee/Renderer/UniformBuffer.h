/**
 * @file UniformBuffer.h
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


// *** NAMESPACE ***
namespace Lychee {

    /**
     * @brief Uniform Buffer
     * 
     */
	class UniformBuffer {
	public:
		virtual ~UniformBuffer() {}
		virtual void SetData(const void* data, u32 size, u32 offset = 0) = 0;
		
		static Ref<UniformBuffer> Create(u32 size, u32 binding);
	};

}