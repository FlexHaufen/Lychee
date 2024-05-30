/**
 * @file Event.h
 * @author flexhaufen
 * @brief Event system
 * @version 0.1
 * @date 2022-09-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

// *** INCLUDES ***
#include <string>

//*** DEFINES ***
#define LY_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

//*** NAMESPACE ***
namespace Lychee {

    // ** GLOBALS **
    // Event types
	enum class eEventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowFocusLost, WindowMoved,   // Window events
		AppTick, AppUpdate, AppRender,                                          // App events
		KeyPressed, KeyReleased, KeyTyped,                                      // Key events
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled      // Mouse events
	};

    // Event categories
    // Event categories is implementet as a Bit field.
    // This means that it is possible to have a Evetn belong in to
    // mulltiple categories at once
	enum eEventCategory {
		None = 0,
		EventCategoryApplication    = (1 << 0),
		EventCategoryInput          = (1 << 1),
		EventCategoryKeyboard       = (1 << 2),
		EventCategoryMouse          = (1 << 3),
		EventCategoryMouseButton    = (1 << 4)
	};

    // ** DEFINES **
    #define EVENT_CLASS_TYPE(type) static eEventType GetStaticType() { return eEventType::type; } \
                                   virtual eEventType GetEventType() const override { return GetStaticType(); }\
                                   virtual const char* GetName() const override { return #type; }

    #define EVENT_CLASS_CATEGORY(category) virtual int32_t GetCategoryFlags() const override { return category; }

    /**
     * @brief Event class
     * 
     */
	class Event {
	public:
		virtual ~Event() = default;

		virtual eEventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int32_t GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		/**
		 * @brief Check if Event is in Catecory eEventCategory
		 * 
		 * @param category 
		 * @return true if event is in category
		 */
		bool IsInCategory(eEventCategory category) {
			return GetCategoryFlags() & category;
		}

        //** Members **
        bool m_isHandled = false;      // Ture if event is handeld
	};

    /**
     * @brief EventDispatcher class
     * 
     */
	class EventDispatcher {
	public:
		EventDispatcher(Event& event)
		: m_Event(event) {
		}
		
		// F will be deduced by the compiler
		template<typename T, typename F>
		bool Dispatch(const F& func) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.m_isHandled |= func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}

}

