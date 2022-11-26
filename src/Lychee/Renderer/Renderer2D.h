/**
 * @file Renderer2D.h
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2022-11-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

// *** INCLUDES ***
#include "Lychee/lypch.h"

#include "Lychee/Renderer/Texture.h"

#include "Lychee/Renderer/OrthographicCamera.h"
#include "Lychee/Renderer/Camera.h"


// *** NAMESPACE ***
namespace Lychee {

	/**
	 * @brief Renderer2D Class
	 * 
	 */
	class Renderer2D {
    public:
        static void Init();
		static void Shutdown();

	//	static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void BeginScene(const OrthographicCamera& camera); // TODO: Remove
		static void EndScene();
		static void Flush();


        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D> texture);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D> texture);
    };
}