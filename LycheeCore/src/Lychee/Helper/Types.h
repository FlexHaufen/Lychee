/**
 * @file Types.h
 * @author flexhaufen
 * @brief Custom types and macrose are defined here
 * @version 0.1
 * @date 2024-05-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

// *** DEFINES ***
// ** Macros **
#define LY_EXPAND_MACRO(x) x
#define LY_STRINGIFY_MACRO(x) #x

// *** NAMESPACE ***
namespace Lychee {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}