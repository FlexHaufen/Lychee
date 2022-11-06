/**
 * @file OrthographicCamera.h
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2022-11-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

// *** INCLUDE ***
#include "Lychee/lypch.h"

// *** NAMESPACE ***
namespace Lychee {

	class OrthographicCamera {
	public:
		OrthographicCamera(f32 left, f32 right, f32 bottom, f32 top);

		void SetProjection(f32 left, f32 right, f32 bottom, f32 top);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		f32 GetRotation() const { return m_Rotation; }
		void SetRotation(f32 rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		f32 m_Rotation = 0.0f;
	};

}
