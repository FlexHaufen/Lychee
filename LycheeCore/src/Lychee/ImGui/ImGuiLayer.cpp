
/**
 * @file ImGuiLayer.cpp
 * @author flexhaufen
 * @brief ImGui Layer
 * @version 0.1
 * @date 2022-09-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// *** INCLUDES *** 
#include "Lychee/lypch.h"
#include "Lychee/ImGui/ImGuiLayer.h"
#include "Lychee/Core/Core.h"


// *** DEFINES ***
#define IMGUI_IMPL_OPENGL_LOADER_GLAD

// *** NAMESPACE ***
namespace Lychee {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer") {
		LY_CORE_INFO("ImGuiLayer: Initializing");

	}

	void ImGuiLayer::OnAttach()	{
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();

		LY_CORE_INFO("ImGuiLayer: Setting up context");
		LY_CORE_INFO("ImGuiLayer: \\---- ImGui Version{0}", ImGui::GetVersion());
		//LY_CORE_INFO("Running ImPlot version: {0}", IMPLOT_VERSION);

		ImGui::CreateContext();
		//ImPlot::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		// Setup Dear ImGui style
		SetStyle();

		Core& app = Core::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeGlfwWindow());

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForVulkan(window, LY_IMGUI_INSTALL_CALLBACKS);

		// I
	}

	void ImGuiLayer::OnDetach() {
		LY_CORE_INFO("ImGuiLayer: Terminating");
		//ImPlot::DestroyContext();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnEvent(Event& e) {
		if (m_BlockEvents) {
			ImGuiIO& io = ImGui::GetIO();
			e.m_isHandled |= e.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
			e.m_isHandled |= e.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
		}
	}
	
	void ImGuiLayer::Begin() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End() {
		ImGuiIO& io = ImGui::GetIO();
		Core& app = Core::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}


	void ImGuiLayer::SetStyle() {
		LY_CORE_INFO("ImGuiLayer: Applying style");

		ImGuiIO &io = ImGui::GetIO();
		
		// TODO (flex): implement font
		//io.FontDefault = io.Fonts->AddFontFromFileTTF(LY_FONT_REGULAR, LY_FONT_SIZE);
		ImGuiStyle* style = &ImGui::GetStyle();

		/**
		 * @brief ImGui Style by https://github.com/Trippasch
		 * 
		 */
		auto &colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] 			= ImVec4{0.1f, 0.1f, 0.13f, 1.0f};
		colors[ImGuiCol_MenuBarBg] 			= ImVec4{0.16f, 0.16f, 0.21f, 1.0f};

		// Border
		colors[ImGuiCol_Border] 			= ImVec4{0.44f, 0.37f, 0.61f, 0.29f};
		colors[ImGuiCol_BorderShadow] 		= ImVec4{0.0f, 0.0f, 0.0f, 0.24f};
		// Text
		colors[ImGuiCol_Text] 				= ImVec4{1.0f, 1.0f, 1.0f, 1.0f};
		colors[ImGuiCol_TextDisabled] 		= ImVec4{0.5f, 0.5f, 0.5f, 1.0f};
		// Headers
		colors[ImGuiCol_Header] 			= ImVec4{0.13f, 0.13f, 0.17f, 1.0f};
		colors[ImGuiCol_HeaderHovered] 		= ImVec4{0.19f, 0.2f, 0.25f, 1.0f};
		colors[ImGuiCol_HeaderActive] 		= ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
		// Buttons
		colors[ImGuiCol_Button] 			= ImVec4{0.13f, 0.13f, 0.17f, 1.0f};
		colors[ImGuiCol_ButtonHovered] 		= ImVec4{0.19f, 0.2f, 0.25f, 1.0f};
		colors[ImGuiCol_ButtonActive] 		= ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
		colors[ImGuiCol_CheckMark] 			= ImVec4{0.74f, 0.58f, 0.98f, 1.0f};
		// Popups
		colors[ImGuiCol_PopupBg] 			= ImVec4{0.1f, 0.1f, 0.13f, 0.92f};
		// Slider
		colors[ImGuiCol_SliderGrab] 		= ImVec4{0.44f, 0.37f, 0.61f, 0.54f};
		colors[ImGuiCol_SliderGrabActive] 	= ImVec4{0.74f, 0.58f, 0.98f, 0.54f};
		// Frame BG
		colors[ImGuiCol_FrameBg] 			= ImVec4{0.13f, 0.13f, 0.17f, 1.0f};
		colors[ImGuiCol_FrameBgHovered] 	= ImVec4{0.19f, 0.2f, 0.25f, 1.0f};
		colors[ImGuiCol_FrameBgActive] 		= ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
		// Tabs
		colors[ImGuiCol_Tab] 				= ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
		colors[ImGuiCol_TabHovered] 		= ImVec4{0.24f, 0.24f, 0.32f, 1.0f};
		colors[ImGuiCol_TabActive] 			= ImVec4{0.2f, 0.22f, 0.27f, 1.0f};
		colors[ImGuiCol_TabUnfocused] 		= ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
		// Title
		colors[ImGuiCol_TitleBg] 			= ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
		colors[ImGuiCol_TitleBgActive] 		= ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
		colors[ImGuiCol_TitleBgCollapsed] 	= ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
		// Scrollbar
		colors[ImGuiCol_ScrollbarBg] 		= ImVec4{0.1f, 0.1f, 0.13f, 1.0f};
		colors[ImGuiCol_ScrollbarGrab] 		= ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
		colors[ImGuiCol_ScrollbarGrabHovered] 	= ImVec4{0.19f, 0.2f, 0.25f, 1.0f};
		colors[ImGuiCol_ScrollbarGrabActive] 	= ImVec4{0.24f, 0.24f, 0.32f, 1.0f};
		// Seperator
		colors[ImGuiCol_Separator] 			= ImVec4{0.44f, 0.37f, 0.61f, 1.0f};
		colors[ImGuiCol_SeparatorHovered] 	= ImVec4{0.74f, 0.58f, 0.98f, 1.0f};
		colors[ImGuiCol_SeparatorActive] 	= ImVec4{0.84f, 0.58f, 1.0f, 1.0f};
		// Resize Grip
		colors[ImGuiCol_ResizeGrip] 		= ImVec4{0.44f, 0.37f, 0.61f, 0.29f};
		colors[ImGuiCol_ResizeGripHovered] 	= ImVec4{0.74f, 0.58f, 0.98f, 0.29f};
		colors[ImGuiCol_ResizeGripActive] 	= ImVec4{0.84f, 0.58f, 1.0f, 0.29f};
		// Docking
		colors[ImGuiCol_DockingPreview] 	= ImVec4{0.44f, 0.37f, 0.61f, 1.0f};

		/*
		style.TabRounding = 4;
		style.ScrollbarRounding = 9;
		style.WindowRounding = 7;
		style.GrabRounding = 3;
		style.FrameRounding = 3;
		style.PopupRounding = 4;
		style.ChildRounding = 4;
		*/
	}
}