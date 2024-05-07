/**
 * @file Layer.cpp
 * @author flexhaufen
 * @brief Layer
 * @version 0.1
 * @date 2022-09-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// *** INCLUDES ***
#include "Lychee/lypch.h"

#include "Lychee/Core/Layer/Layer.h"

// *** DEFINES ***

// *** NAMESPACE ***
namespace Lychee {

	Layer::Layer(const std::string& debugName)
		: m_DebugName(debugName) {
	}
}