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


		s_Data.VoxelVertexArray = CreateRef<VertexArray>();

		s_Data.VoxelVertexBuffer = CreateRef<VertexBuffer>(u32(s_Data.MaxVertices * sizeof(sVoxelVertex)));
		s_Data.VoxelVertexBuffer->SetLayout({
			{ eShaderDataType::Float3, "a_Position"     },
			{ eShaderDataType::Float4, "a_Color"        }
		});
		s_Data.VoxelVertexArray->AddVertexBuffer(s_Data.VoxelVertexBuffer);

		s_Data.VoxelVertexBufferBase = new sVoxelVertex[s_Data.MaxVertices];

		const u32 voxelIndicesSize = 36;
		u32 quadIndices[voxelIndicesSize] =  {
			0, 1, 2, 2, 3, 0,
			1, 5, 6, 6, 2, 1,
			7, 6, 5, 5, 4, 7,
			4, 0, 3, 3, 7, 4,
			4, 5, 1, 1, 0, 4,
			3, 2, 6, 6, 7, 3
		};

		Ref<IndexBuffer> quadIB = CreateRef<IndexBuffer>(quadIndices, voxelIndicesSize);
		s_Data.VoxelVertexArray->SetIndexBuffer(quadIB);

		s_Data.VoxelShader = CreateRef<Shader>("src/Lychee/Renderer/shaders/VoxelShader.glsl");
		s_Data.VoxelVertexPositions[0] = { -1.0, -1.0,  1.0, 1.0 };
		s_Data.VoxelVertexPositions[1] = {  1.0, -1.0,  1.0, 1.0 };
		s_Data.VoxelVertexPositions[2] = {  1.0,  1.0,  1.0, 1.0 };
		s_Data.VoxelVertexPositions[3] = { -1.0,  1.0,  1.0, 1.0 };

		s_Data.VoxelVertexPositions[4] = { -1.0, -1.0, -1.0, 1.0 };
		s_Data.VoxelVertexPositions[5] = {  1.0, -1.0, -1.0, 1.0 };
		s_Data.VoxelVertexPositions[6] = {  1.0,  1.0, -1.0, 1.0 };
		s_Data.VoxelVertexPositions[7] = { -1.0,  1.0, -1.0, 1.0 };

		s_Data.CameraUniformBuffer = CreateRef<UniformBuffer>((u32)sizeof(sRenderer2DData::CameraData), 0);
	}

	void Renderer::Shutdown() {
        LY_CORE_INFO("Renderer: Terminating");
		delete[] s_Data.VoxelVertexBufferBase;
	}

	void Renderer::OnWindowResize(u32 width, u32 height) {
		glViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(const EditorCamera& camera) {
		s_Data.CameraBuffer.ViewProjection = camera.GetViewProjection();
		s_Data.CameraUniformBuffer->SetData(&s_Data.CameraBuffer, sizeof(sRenderer2DData::CameraData));

		s_Data.VoxelIndexCount = 0;
		s_Data.VoxelVertexBufferPtr = s_Data.VoxelVertexBufferBase;
	}

	void Renderer::EndScene() {
		// Flush
		if (s_Data.VoxelIndexCount) {
			u32 dataSize = (u32)((u8*)s_Data.VoxelVertexBufferPtr - (u8*)s_Data.VoxelVertexBufferBase);
			s_Data.VoxelVertexBuffer->SetData(s_Data.VoxelVertexBufferBase, dataSize);

			s_Data.VoxelShader->Bind();

			// Draw indexed
			s_Data.VoxelVertexArray->Bind();
			u32 count = s_Data.VoxelIndexCount ? s_Data.VoxelIndexCount : s_Data.VoxelVertexArray->GetIndexBuffer()->GetCount();
			glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		}
	}

	void Renderer::SetClearColor(const glm::vec4& color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void Renderer::RenderVoxel(const glm::vec3& position, const glm::vec4& color) {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
		constexpr size_t quadVertexCount = 8;

		for (size_t i = 0; i < quadVertexCount; i++) {
			s_Data.VoxelVertexBufferPtr->Position = transform * s_Data.VoxelVertexPositions[i];
			s_Data.VoxelVertexBufferPtr->Color = color;
			s_Data.VoxelVertexBufferPtr++;
		}
		// TODO (flex): remove magic number
		s_Data.VoxelIndexCount += 36;
	}

	void Renderer::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void SetLineWidth(f32 width) {
		glLineWidth(width);
	}
}