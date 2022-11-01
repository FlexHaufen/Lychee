/**
 * @file RenderCommand.cpp
 * @author flaxhaufen
 * @brief 
 * @version 0.1
 * @date 2022-11-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// *** INCLUDES ***
#include "Lychee/Renderer/RenderCommand.h"


// *** NAMESPACE ***
namespace Lychee {

	Scope<RendererAPI> RenderCommand::m_RendererAPI = RendererAPI::Create();

}