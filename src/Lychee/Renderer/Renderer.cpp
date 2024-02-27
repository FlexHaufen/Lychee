/**
 * @file Renderer.cpp
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-02-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

// *** INCLUDES ***
#include "Lychee/Renderer/Renderer.h"

// *** NAMESPACE ***
namespace Lychee {


	void Renderer::Init() {
        LY_CORE_INFO("Renderer: Initializing");

		LY_CORE_INFO("OpenGL Info:");
		LY_CORE_INFO("  Vendor: {0}", 	(GL_VENDOR));
		LY_CORE_INFO("  Renderer: {0}", (GL_RENDERER));
		LY_CORE_INFO("  Version: {0}", 	(GL_VERSION));

		if(GLVersion.major < 4 || (GLVersion.major == 4 && GLVersion.minor < 5)) {
			LY_CORE_CRITICAL("Lychee requires at least OpenGL version 4.5!");
		}

		//#ifdef LY_DEBUG
		//	glEnable(GL_DEBUG_OUTPUT);
		//	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		//	//glDebugMessageCallback(OpenGLMessageCallback, nullptr);
		//	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
		//#endif

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LINE_SMOOTH);


		s_Data.QuadVertexArray = CreateRef<VertexArray>();

		s_Data.QuadVertexBuffer = CreateRef<VertexBuffer>(u32(s_Data.MaxVertices * sizeof(sVoxelVertex)));
		s_Data.QuadVertexBuffer->SetLayout({
			{ eShaderDataType::Float3, "a_Position"     },
			{ eShaderDataType::Float4, "a_Color"        }
		});
		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBufferBase = new sVoxelVertex[s_Data.MaxVertices];

		u32* quadIndices = new u32[s_Data.MaxIndices];

		u32 offset = 0;
		for (u32 i = 0; i < s_Data.MaxIndices; i += 6) {
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> quadIB = CreateRef<IndexBuffer>(quadIndices, s_Data.MaxIndices);
		s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;


		s_Data.QuadShader = CreateRef<Shader>("src/Lychee/Renderer/shaders/BasicShader.glsl");
		// Set first texture slot to 0
		s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

		s_Data.CameraUniformBuffer = CreateRef<UniformBuffer>((u32)sizeof(sRenderer2DData::CameraData), 0);
	}

	void Renderer::Shutdown() {
        LY_CORE_INFO("Renderer: Terminating");
		delete[] s_Data.QuadVertexBufferBase;
	}

	void Renderer::OnWindowResize(u32 width, u32 height) {
		glViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(const EditorCamera& camera) {
		s_Data.CameraBuffer.ViewProjection = camera.GetViewProjection();
		s_Data.CameraUniformBuffer->SetData(&s_Data.CameraBuffer, sizeof(sRenderer2DData::CameraData));

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
	}

	void Renderer::EndScene() {
		// Flush
		if (s_Data.QuadIndexCount) {
			u32 dataSize = (u32)((u8*)s_Data.QuadVertexBufferPtr - (u8*)s_Data.QuadVertexBufferBase);
			s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

			s_Data.QuadShader->Bind();

			// Draw indexed
			s_Data.QuadVertexArray->Bind();
			u32 count = s_Data.QuadIndexCount ? s_Data.QuadIndexCount : s_Data.QuadVertexArray->GetIndexBuffer()->GetCount();
			glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		}
	}

	void Renderer::SetClearColor(const glm::vec4& color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void Renderer::RenderVoxel(const glm::vec3& position, const glm::vec4& color) {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
		constexpr size_t quadVertexCount = 4;

		for (size_t i = 0; i < quadVertexCount; i++) {
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr++;
		}
		s_Data.QuadIndexCount += 6;
	}

	void Renderer::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void SetLineWidth(f32 width) {
		glLineWidth(width);
	}
}