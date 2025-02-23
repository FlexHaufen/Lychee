/**
 * @file WindowEvent.h
 * @author flexhaufen
 * @brief Handels Window events
 * @version 0.1
 * @date 2022-09-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

//*** INCLUDES ***
#include <string>

#include "Lychee/Events/Event.h"

//*** DEFINES ***

//*** NAMESPACE ***
namespace Lychee {

	class WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(uint32_t width, uint32_t height)
			: m_Width(width), m_Height(height) {}

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryWindow)
	private:
		uint32_t m_Width, m_Height;
	};

	class WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryWindow)
	};
}