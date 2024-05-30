/**
 * @file KeyEvent.h
 * @author flexhaufen
 * @brief Handels KeyEvents
 * @version 0.1
 * @date 2022-09-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

//*** INCLUDES ***
#include <string>

#include "Lychee/Events/Event.h"
#include "Lychee/Helper/KeyCodes.h"

//*** NAMESPACE ***
namespace Lychee {

    /**
     * @brief KeyEvent Class
     * 
     */
	class KeyEvent : public Event {
	public:
		KeyCode GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(const KeyCode keycode)
			: m_KeyCode(keycode) {}

		KeyCode m_KeyCode;
	};

    /**
     * @brief KeyPressed Class
     * 
     */
	class KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(const KeyCode keycode, bool isRepeat = false)
			: KeyEvent(keycode), m_IsRepeat(isRepeat) {}

		bool IsRepeat() const { return m_IsRepeat; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (repeat = " << m_IsRepeat << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
        //** Members **
		bool m_IsRepeat;
	};

    /**
     * @brief KeyReleasd Class
     * 
     */
	class KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(const KeyCode keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

    /**
     * @brief KeyTyped Class
     * 
     */
	class KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(const KeyCode keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}