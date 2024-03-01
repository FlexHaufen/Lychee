/**
 * @file EditorCamera.h
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-02-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

// *** INCLUDE ***

#include "Lychee/lypch.h"

#include "Lychee/Core/Time/Deltatime.h"
#include "Lychee/Events/Event.h"
#include "Lychee/Events/MouseEvent.h"
#include "Lychee/Renderer/Camera.h"



// *** NAMESPACE ***
namespace Lychee {


    class EditorCamera : public Camera {
	public:
		EditorCamera() = default;
		EditorCamera(f32 fov, f32 aspectRatio, f32 nearClip, f32 farClip);

		void OnUpdate(DeltaTime dt);
		void OnEvent(Event& e);

		inline f32 GetDistance() const { return m_Distance; }
		inline void SetDistance(f32 distance) { m_Distance = distance; }

		inline void SetViewportSize(f32 width, f32 height) { m_ViewportWidth = width; m_ViewportHeight = height; UpdateProjection(); }

		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		glm::mat4 GetViewProjection() const { return m_Projection * m_ViewMatrix; }

		glm::vec3 GetUpDirection() const;
		glm::vec3 GetRightDirection() const;
		glm::vec3 GetForwardDirection() const;
		const glm::vec3& GetPosition() const { return m_Position; }
		glm::quat GetOrientation() const;

		f32 GetPitch() const { return m_Pitch; }
		f32 GetYaw() const { return m_Yaw; }
	private:
		void UpdateProjection();
		void UpdateView();

		bool OnMouseScroll(MouseScrolledEvent& e);

		void MousePan(const glm::vec2& delta);
		void MouseRotate(const glm::vec2& delta);
		void MouseZoom(f32 delta);

		glm::vec3 CalculatePosition() const;

		std::pair<f32, f32> PanSpeed() const;
		f32 RotationSpeed() const;
		f32 ZoomSpeed() const;
	private:
		f32 m_FOV = 45.0f, m_AspectRatio = 1.778f, m_NearClip = 0.1f, m_FarClip = 1000.0f;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_FocalPoint = { 0.0f, 0.0f, 0.0f };

		glm::vec2 m_InitialMousePosition = { 0.0f, 0.0f };

		f32 m_Distance = 10.0f;
		f32 m_Pitch = 0.0f, m_Yaw = 0.0f;

		f32 m_ViewportWidth = 1280, m_ViewportHeight = 720;
	};

}
