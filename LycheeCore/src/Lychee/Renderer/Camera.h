/**
 * @file Camera.h
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-03-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

// *** INCLUDES ***
#include "Lychee/lypch.h"

#include "Lychee/Core/Time/DeltaTime.h"
#include "Lychee/Core/Input/Input.h"
#include "Lychee/Events/Event.h"

// *** NAMESPACE ***
namespace Lychee {
    class Camera {
	public:
		Camera() = default;
		//Camera(const glm::mat4& projectionMatrix)
		//	: m_ProjectionMatrix(projectionMatrix) {}

		Camera(float fov, float aspectRatio, float nearClip, float farClip)
		: m_FOV(fov)
		, m_AspectRatio(aspectRatio)
		, m_NearClip(nearClip)
		, m_FarClip(farClip)
		, m_ProjectionMatrix(glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip)) {
		}
		
		void OnUpdate(DeltaTime dt) {
			float velocity = m_MoveSpeed * dt;
				if (Input::IsKeyPressed(Key::W))
					m_Position += m_Front * velocity;
				if (Input::IsKeyPressed(Key::S))
					m_Position -= m_Front * velocity;
				if (Input::IsKeyPressed(Key::A))
					m_Position -= glm::normalize(glm::cross(m_Front, m_Up)) * velocity;
				if (Input::IsKeyPressed(Key::D))
					m_Position += glm::normalize(glm::cross(m_Front, m_Up)) * velocity;
				m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
		}
		const glm::mat4 GetViewProjectionMatrix() const { return m_ProjectionMatrix * m_ViewMatrix; }

		void UpdateViewPort(uint32_t width, uint32_t height) { 
			m_AspectRatio = width / height;
			m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
		}

	private:
		float m_FOV, m_AspectRatio, m_NearClip, m_FarClip;

		glm::mat4 m_ProjectionMatrix;
    	glm::mat4 m_ViewMatrix;

		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
		float m_MoveSpeed = 2.5f;
    };
}