/**
 * @file EditorLayer.cpp
 * @author flexhaufen
 * @brief ImGui Main
 * @version 0.1
 * @date 2022-09-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//*** INCLUDE ***
#include "EditorLayer.h"

//*** DEFINES ***

//#define LY_LOG_KEY_EVENT

//*** NAMESPACE ***
namespace Lychee {

	extern const std::filesystem::path g_AssetPath;

	EditorLayer::EditorLayer()
		: Layer("EditorLayer"),
		  m_CameraController(1920.0f / 1080.0f, true) {

		LY_INFO("Initializing Editor");

		//! ------- TESTING -------
		m_VertexArray = VertexArray::Create();

		f32 vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,		// btm left
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,		// btm right
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,		// top right
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f		// top left
		};

		Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		BufferLayout layout = {
			{ eShaderDataType::Float3, "a_Position" },
			{ eShaderDataType::Float2, "a_TextCoord" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		// *** COLOR SHADERS ****
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
	
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			
			out vec3 v_Position;
			
			void main() {
				v_Position = a_Position;
			
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		// *** TEXTURE SHADERS ***
		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			uniform vec3 u_Color;

			void main() {
				color = vec4(u_Color, 1.0);
				
			}
		)";


		std::string vertexSrc_texture = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TextCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			
			out vec2 v_TextCoord;
			
			void main() {
				v_TextCoord = a_TextCoord;
			
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc_texture = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec2 v_TextCoord;
			
			uniform sampler2D u_Texture;

			void main() {
				color = texture(u_Texture, v_TextCoord);
				
			}
		)";

		// TODO: Find out relative path here
		m_Texture = Texture2D::Create("C:/Users/janin/Documents/01_Projects/Projects/Lychee/src/LycheeApp/src/assets/test_texture.png");

		m_Shader = Shader::Create("Srq", vertexSrc, fragmentSrc);
		m_Shader->Bind();
		m_Shader->SetFloat4("u_Color", glm::vec4(1.0, 1.0, 1.0, 1.0));

		m_TextureShader = Shader::Create("Sqr_Texture", vertexSrc_texture, fragmentSrc_texture);
		m_TextureShader->Bind();
		m_TextureShader->SetInt("u_Texture", 0);

		//! -----------------------

	}

	void EditorLayer::OnAttach() {
	}

	void EditorLayer::OnDetach() {
	}

	void EditorLayer::OnUpdate(DeltaTime dt) {
		//! ------- TESTING -------
		m_CameraController.OnUpdate(dt);

		RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
		RenderCommand::Clear();

		
		Renderer::BeginScene(m_CameraController.GetCamera());

		m_Texture->Bind();
		Renderer::Submit(m_TextureShader, m_VertexArray);

		Renderer::EndScene();
		//! -----------------------
	}

	void EditorLayer::OnImGuiRender() {
	#ifdef LY_RENDER_IMGUI
		// Note: Switch this to true to enable dockspace
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen) {
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		f32 minWinSizeX = style.WindowMinSize.x;
		style.WindowMinSize.x = 370.0f;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		style.WindowMinSize.x = minWinSizeX;

		#ifdef LY_IMGUI_SHOW_DEMO
			ImGui::ShowDemoWindow();
		#endif

		#ifdef LY_IMPLOT_SHOW_DEMO
			ImPlot::ShowDemoWindow();
		#endif
		// Render menubar
		OnMenuBarRender();

		if(m_Calculator.p_open)
			m_Calculator.OnImGuiRender(&m_Calculator.p_open);
		if(m_Settings.p_open)
			m_Settings.OnImGuiRender(&m_Settings.p_open);


		ImGui::End();
	#endif
	}

	void EditorLayer::OnEvent(Event& e)	{

		m_CameraController.OnEvent(e);

		#ifdef LY_LOG_KEY_EVENT
			if (e.GetEventType() == Lychee::eEventType::KeyPressed) {
				Lychee::KeyPressedEvent& eKey = (Lychee::KeyPressedEvent&)e;
				LY_TRACE("KEY PRESSED: {0}", (c8)eKey.GetKeyCode());
			}	
		#endif

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(LY_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
		dispatcher.Dispatch<MouseButtonPressedEvent>(LY_BIND_EVENT_FN(EditorLayer::OnMouseButtonPressed));
	}

	void EditorLayer::OnMenuBarRender() {

		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);1
				if (ImGui::MenuItem("New", "Ctrl+N")){}

				if (ImGui::MenuItem("Open...", "Ctrl+O")){}

				if (ImGui::MenuItem("Save", "Ctrl+S")){}

				if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S")){}

				if (ImGui::MenuItem("Exit")) Core::Get().Close();
					ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit")) {
				ImGui::Separator();
				ImGui::MenuItem("Settings", NULL, &m_Settings.p_open);
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("View")) {
				if (ImGui::MenuItem("V1.1")) {}
				if (ImGui::MenuItem("v1.2")) {}

				ImGui::Separator();

				if (ImGui::MenuItem("V2.0")) {}
				if (ImGui::MenuItem("V2.1")) {}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Tools")) {
				ImGui::MenuItem("Calculator", NULL, &m_Calculator.p_open);
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Help")) {
    			if (ImGui::MenuItem("Ask Google - you jerk")) {}				
				
				ImGui::Separator();
				
				//ImGui::ShowAboutWindow(&show_app_about);

				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e) {
		// Shortcuts
		if (e.IsRepeat()) {
			return false;

		bool control = Input::IsKeyPressed(Key::LeftControl) || Input::IsKeyPressed(Key::RightControl);
		bool shift = Input::IsKeyPressed(Key::LeftShift) || Input::IsKeyPressed(Key::RightShift);
		}
		return true;
	}

	bool EditorLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e) {
		if (e.GetMouseButton() == Mouse::ButtonLeft) {
		//	if (m_ViewportHovered && !ImGuizmo::IsOver() && !Input::IsKeyPressed(Key::LeftAlt))
		//		m_SceneHierarchyPanel.SetSelectedEntity(m_HoveredEntity);
		}
		return false;
	}

}

