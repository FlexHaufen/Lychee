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

		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void BeginScene(const OrthographicCamera& camera); // TODO: Remove
		static void EndScene();
		static void Flush();

		// Primitives
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, f32 tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, f32 tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color, s32 entityID = -1);
		static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, f32 tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f), s32 entityID = -1);

		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, f32 rotation, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, f32 rotation, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, f32 rotation, const Ref<Texture2D>& texture, f32 tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, f32 rotation, const Ref<Texture2D>& texture, f32 tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		static void DrawCircle(const glm::mat4& transform, const glm::vec4& color, f32 thickness = 1.0f, f32 fade = 0.005f, s32 entityID = -1);
		
		static void DrawLine(const glm::vec3& p0, glm::vec3& p1, const glm::vec4& color, s32 entityID = -1);

		static void DrawRect(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, s32 entityID = -1);
		static void DrawRect(const glm::mat4& transform, const glm::vec4& color, s32 entityID = -1);


		static f32 GetLineWidth();
		static void SetLineWidth(f32 width);

		// Stats
		struct Statistics {
			u32 DrawCalls = 0;
			u32 QuadCount = 0;

			u32 GetTotalVertexCount() const { return QuadCount * 4; }
			u32 GetTotalIndexCount() const { return QuadCount * 6; }
		};
		static void ResetStats();
		static Statistics GetStats();

	private:
		static void StartBatch();
		static void NextBatch();
	};
}