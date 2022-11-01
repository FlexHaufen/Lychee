/**
 * @file OpenGLRendererAPI.cpp
 * @author flaxhaufen
 * @brief 
 * @version 0.1
 * @date 2022-11-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// *** INCLUDES ***
#include "Lychee/Platform/OpenGL/OpenGLRendererAPI.h"

// *** NAMESPACE ***
namespace Lychee {
	
	void OpenGLMessageCallback(
		u16 source,
		u16 type,
		u16 id,
		u16 severity,
		i16 length,
		const c8* message,
		const void* userParam) 
	{
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_HIGH:         LY_CORE_CRITICAL(message); return;
			case GL_DEBUG_SEVERITY_MEDIUM:       LY_CORE_ERROR(message); return;
			case GL_DEBUG_SEVERITY_LOW:          LY_CORE_WARN(message); return;
			case GL_DEBUG_SEVERITY_NOTIFICATION: LY_CORE_TRACE(message); return;
		}
	}

	void OpenGLRendererAPI::Init() {

	#ifdef LY_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		//glDebugMessageCallback(OpenGLMessageCallback, nullptr);
		
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
	#endif

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LINE_SMOOTH);
	}

	void OpenGLRendererAPI::SetViewport(u32 x, u32 y, u32 width, u32 height) {
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, u32 indexCount) {
		vertexArray->Bind();
		u32 count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::DrawLines(const Ref<VertexArray>& vertexArray, u32 vertexCount) {
		vertexArray->Bind();
		glDrawArrays(GL_LINES, 0, vertexCount);
	}
 
	void OpenGLRendererAPI::SetLineWidth(f32 width) {
		glLineWidth(width);
	}

}
