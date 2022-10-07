/**
 * @file Input.h
 * @author flexhaufen
 * @brief Inputs
 * @version 0.1
 * @date 2022-10-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

//*** INCLUDES ***
#include "Lychee/lypch.h"

#include "Lychee/Helper/KeyCodes.h"
#include "Lychee/Helper/MouseCodes.h"

//*** DEFINES ***


//*** NAMESPACE ***
namespace Lychee {

    /**
     * @brief Input Class
     * 
     */
	class Input {
	public:

		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}