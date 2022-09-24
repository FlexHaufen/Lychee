/**
 * @file Window.h
 * @author flexhaufen
 * @brief Window interface
 * @version 0.1
 * @date 2022-09-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#pragma once


//*** INCLUDES ***
#include "Lychee/lypch.h"
#include "Lychee/Events/Event.h"


//*** DEFINES ***


//*** NAMESPACE ***

namespace Hazel {

    // Properties
	struct WindowProps {
		std::string Title;
		u32 Width;
		u32 Height;

		WindowProps(const std::string& title = "Hazel Engine",
			        u32 width = 1600,
			        u32 height = 900)
		: Title(title), Width(width), Height(height) {
		}
	};

    /**
     * @brief Interface representing a desktop system based Window  
     * 
     */
	class Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		void OnUpdate() = 0;

		u32 GetWidth() const = 0;
		u32 GetHeight() const = 0;

		// Window attributes
		void SetEventCallback(const EventCallbackFn& callback) = 0;
		void SetVSync(bool enabled) = 0;
		bool IsVSync() const = 0;

		void* GetNativeWindow() const = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};

}