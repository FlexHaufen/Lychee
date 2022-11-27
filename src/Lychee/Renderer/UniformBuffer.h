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
		virtual void SetData(const void* data, uint32_t size, uint32_t offset = 0) = 0;
		
		static Ref<UniformBuffer> Create(uint32_t size, uint32_t binding);
	};

}