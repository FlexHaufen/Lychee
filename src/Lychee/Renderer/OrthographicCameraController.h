/**
 * @file OrthographicCameraController.h
 * @author flaxhaufen
 * @brief 
 * @version 0.1
 * @date 2022-11-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

// *** INCLUDES ***
#include "Lychee/lypch.h"
#include "Lychee/Renderer/OrthographicCamera.h"
#include "Lychee/Core/Time/Deltatime.h"

#include "Lychee/Events/ApplicationEvent.h"
#include "Lychee/Events/MouseEvent.h"

// *** NAMESPACE ***
namespace Lychee {

	class OrthographicCameraController {
	public:
		OrthographicCameraController(f32 aspectRatio, bool rotation = false);

		void OnUpdate(DeltaTime dt);
		void OnEvent(Event& e);

		void OnResize(f32 width, f32 height);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		f32 GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(f32 level) { m_ZoomLevel = level; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		f32 m_AspectRatio;
		f32 m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		f32 m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
		f32 m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};

}