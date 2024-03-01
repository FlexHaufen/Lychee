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
		auto* window = static_cast<GLFWwindow*>(Core::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, static_cast<s32>(key));
		return state == GLFW_PRESS;
	}

	bool Input::IsMouseButtonPressed(const MouseCode button) {
		auto* window = static_cast<GLFWwindow*>(Core::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<s32>(button));
		return state == GLFW_PRESS;
	}

	glm::vec2 Input::GetMousePosition() {
		auto* window = static_cast<GLFWwindow*>(Core::Get().GetWindow().GetNativeWindow());
		f64 xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (f32)xpos, (f32)ypos };
	}

	f32 Input::GetMouseX() {
		return GetMousePosition().x;
	}

	f32 Input::GetMouseY() {
		return GetMousePosition().y;
	}

}