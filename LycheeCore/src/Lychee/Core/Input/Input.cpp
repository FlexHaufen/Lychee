/**
 * @file Input.cpp
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2022-10-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

//*** INCLUDES ***
#include "Lychee/Core/Input/Input.h"
#include "Lychee/Core/Core.h"

//*** DEFINES ***


//*** NAMESPACE ***
namespace Lychee {

	bool Input::IsKeyPressed(const KeyCode key)	{
		auto* window = static_cast<GLFWwindow*>(Core::Get().GetWindow().GetNativeGlfwWindow());
		auto state = glfwGetKey(window, static_cast<int32_t>(key));
		return state == GLFW_PRESS;
	}

	bool Input::IsMouseButtonPressed(const MouseCode button) {
		auto* window = static_cast<GLFWwindow*>(Core::Get().GetWindow().GetNativeGlfwWindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	glm::vec2 Input::GetMousePosition() {
		auto* window = static_cast<GLFWwindow*>(Core::Get().GetWindow().GetNativeGlfwWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float Input::GetMouseX() {
		return GetMousePosition().x;
	}

	float Input::GetMouseY() {
		return GetMousePosition().y;
	}

}