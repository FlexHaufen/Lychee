/**
 * @file Log.h
 * @author flexhaufen
 * @brief logger
 * @version 0.1
 * @date 2022-09-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

// *** INCLUDES ***
#include "Lychee/Core/Core.h"


// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
    #include <spdlog/spdlog.h>
    #include <spdlog/fmt/ostr.h>
#pragma warning(pop)

//*** DEFINES ***
#define LY_LOGGER_ENABLE

//*** NAMESPACE ***
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

        //*** MEMBERS ***
		static inline std::shared_ptr<spdlog::logger> s_CoreLogger;     // Core Logger
		static inline std::shared_ptr<spdlog::logger> s_ClientLogger;   // Client Logger
	};

}

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