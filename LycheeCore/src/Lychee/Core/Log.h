/**
 * @file Log.h
 * @author flexhaufen
 * @brief logger
 *          TRACE       -> For debugging
 *          INFO        -> Generally useful information to log
 *          WARNING     -> Anything that can potentially cause application oddities.
 *          ERROR       -> Any error which is fatal to the operation, but not the application
 *          CIRTICAL    -> Any error that is forcing a shutdown of the service or application
 * 
 * @version 0.1
 * @date 2022-09-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

// *** INCLUDES ***


// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <filesystem>
#pragma warning(pop)


// *** DEFINES ***
#ifndef NLY_DEBUG
    #define LY_LOGGER_ENABLE
    #define LY_ENABLE_ASSERTS
#else
    // TODO: This will change later -> maby logger is only file logging is enabled
    #define LY_LOGGER_ENABLE
    #define LY_ENABLE_ASSERTS
#endif


// *** NAMESPACE ***
namespace Lychee {
    /**
     * @brief Logger Class
     * 
     */
	class Log {
	public:
        /**
         * @brief initializes the logger
         * 
         */
		static void Init();

        /**
         * @brief Get the Core Logger object
         * 
         * @return std::shared_ptr<spdlog::logger>& 
         */
		static inline std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }

        /**
         * @brief Get the Client Logger object
         * 
         * @return std::shared_ptr<spdlog::logger>& 
         */
		static inline std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:

        // *** MEMBERS ***
		static inline std::shared_ptr<spdlog::logger> s_CoreLogger;     // Core Logger
		static inline std::shared_ptr<spdlog::logger> s_ClientLogger;   // Client Logger
	};

}

// *** LOGGER ***
#ifdef LY_LOGGER_ENABLE
    // Core log macros
    #define LY_CORE_TRACE(...)    ::Lychee::Log::GetCoreLogger()->trace(__VA_ARGS__)
    #define LY_CORE_INFO(...)     ::Lychee::Log::GetCoreLogger()->info(__VA_ARGS__)
    #define LY_CORE_WARN(...)     ::Lychee::Log::GetCoreLogger()->warn(__VA_ARGS__)
    #define LY_CORE_ERROR(...)    ::Lychee::Log::GetCoreLogger()->error(__VA_ARGS__)
    #define LY_CORE_CRITICAL(...) ::Lychee::Log::GetCoreLogger()->critical(__VA_ARGS__)

    // Client log macros
    #define LY_TRACE(...)         ::Lychee::Log::GetClientLogger()->trace(__VA_ARGS__)
    #define LY_INFO(...)          ::Lychee::Log::GetClientLogger()->info(__VA_ARGS__)
    #define LY_WARN(...)          ::Lychee::Log::GetClientLogger()->warn(__VA_ARGS__)
    #define LY_ERROR(...)         ::Lychee::Log::GetClientLogger()->error(__VA_ARGS__)
    #define LY_CRITICAL(...)      ::Lychee::Log::GetClientLogger()->critical(__VA_ARGS__)

#else
    // Core log macros
    #define LY_CORE_TRACE(...)   
    #define LY_CORE_INFO(...)     
    #define LY_CORE_WARN(...)     
    #define LY_CORE_ERROR(...)    
    #define LY_CORE_CRITICAL(...) 

    // Client log macros
    #define LY_TRACE(...)         
    #define LY_INFO(...)          
    #define LY_WARN(...)          
    #define LY_ERROR(...)         
    #define LY_CRITICAL(...)      
#endif

// *** LOGGER ***
#ifdef LY_ENABLE_ASSERTS

	// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
	// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
	#define LY_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { LY##type##ERROR(msg, __VA_ARGS__); LY_DEBUGBREAK(); } }
	#define LY_INTERNAL_ASSERT_WITH_MSG(type, check, ...) LY_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define LY_INTERNAL_ASSERT_NO_MSG(type, check) LY_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", LY_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define LY_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define LY_INTERNAL_ASSERT_GET_MACRO(...) LY_EXPAND_MACRO( LY_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, LY_INTERNAL_ASSERT_WITH_MSG, LY_INTERNAL_ASSERT_NO_MSG) )

	// Currently accepts at least the condition and one additional parameter (the message) being optional
	#define LY_ASSERT(...) LY_EXPAND_MACRO( LY_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define LY_CORE_ASSERT(...) LY_EXPAND_MACRO( LY_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
	#define LY_ASSERT(...)
	#define LY_CORE_ASSERT(...)
#endif