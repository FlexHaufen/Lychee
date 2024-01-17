/**
 * @file Instrumentor.h
 * @author flexhaufen
 * @brief Usage:
 *        Begin a profile session via LY_PROFILE_BEGIN_SESSION(name, filepath)
 *        End a session via LY_PROFILE_END_SESSION()
 *        Profile a scope with LY_PROFILE_SCOPE(name)
 *        Profile a function with LY_PROFILE_FUNCTION
 * 
 *        After running Lychee ther will be a file generatet with the name given in LY_PROFILE_BEGIN_SESSION
 *        Open Google-Chrome and type "chrome://tracing"
 *        Press load and upload the json file
 *        Examin the data.
 * 
 *  TODO (flex): Write brief description of functions
 * 
 * @version 0.1
 * @date 2022-12-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once


// *** INCLUDES ***
#include "Lychee/Core/Log.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <thread>
#include <mutex>
#include <sstream>


// *** NAMESPACE ***
namespace Lychee {

	using float_ms_t = std::chrono::duration<double, std::micro>;

	struct sProfileResult {
		std::string Name;

		float_ms_t Start;
		std::chrono::microseconds ElapsedTime;
		std::thread::id ThreadID;
	};

	struct sInstrumentationSession {
		std::string Name;
	};

	class Instrumentor {
	
    public:
		Instrumentor(const Instrumentor&) = delete;
		Instrumentor(Instrumentor&&) = delete;

        /**
         * @brief Beginn a profiling session
         * 
         * @param name          File name
         * @param filepath      File save path
         */
		void BeginSession(const std::string& name, const std::string& filepath = "results.json");

        /**
         * @brief End a profiling session
         * 
         */
		void EndSession();


		void WriteProfile(const sProfileResult& result);


		static Instrumentor& Get() { static Instrumentor instance; return instance;}

	private:
		Instrumentor(): m_CurrentSession(nullptr) {}

		~Instrumentor() {EndSession();}		

		void WriteHeader();

		void WriteFooter();

		void InternalEndSession();

	private:
        // ** MEMBERS **
		std::mutex m_Mutex;
		sInstrumentationSession* m_CurrentSession;
		std::ofstream m_OutputStream;
	};

	class InstrumentationTimer {
	public:
		InstrumentationTimer(const char* name);
		~InstrumentationTimer();

		void Stop();

	private:
        // ** MEMBERS **
		const char* m_Name;
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
		bool m_Stopped;
	};

	namespace InstrumentorUtils {
		template <size_t N>
		struct ChangeResult {
			char Data[N];
		};

		template <size_t N, size_t K>
		constexpr auto CleanupOutputString(const char(&expr)[N], const char(&remove)[K]) {
			ChangeResult<N> result = {};

			size_t srcIndex = 0;
			size_t dstIndex = 0;
			while (srcIndex < N) {
				size_t matchIndex = 0;
				while (matchIndex < K - 1 && srcIndex + matchIndex < N - 1 && expr[srcIndex + matchIndex] == remove[matchIndex]) {
					matchIndex++;
                }
				if (matchIndex == K - 1) {
					srcIndex += matchIndex;
                }
                result.Data[dstIndex++] = expr[srcIndex] == '"' ? '\'' : expr[srcIndex];
				srcIndex++;
			}
			return result;
		}
	}
}

// *** DEFINES ***
// NOTE (flex): The Profiler may be desabled here
//#define LY_PROFILE

#ifdef LY_PROFILE

    // NOTE (flex): Compilers may be added here.
	#if (defined(__FUNCSIG__) || (_MSC_VER))
		#define LY_FUNC_SIG __FUNCSIG__
	#else
		#define LY_FUNC_SIG "LY_FUNC_SIG unknown!"
	#endif

	#define LY_PROFILE_BEGIN_SESSION(name, filepath) ::Lychee::Instrumentor::Get().BeginSession(name, filepath)
	#define LY_PROFILE_END_SESSION() ::Lychee::Instrumentor::Get().EndSession()
	#define LY_PROFILE_SCOPE_LINE2(name, line) constexpr auto fixedName##line = ::Lychee::InstrumentorUtils::CleanupOutputString(name, "__cdecl ");\
											   ::Lychee::InstrumentationTimer timer##line(fixedName##line.Data)
	#define LY_PROFILE_SCOPE_LINE(name, line) LY_PROFILE_SCOPE_LINE2(name, line)
	#define LY_PROFILE_SCOPE(name) LY_PROFILE_SCOPE_LINE(name, __LINE__)
	#define LY_PROFILE_FUNCTION() LY_PROFILE_SCOPE(LY_FUNC_SIG)
#else
	#define LY_PROFILE_BEGIN_SESSION(name, filepath)
	#define LY_PROFILE_END_SESSION()
	#define LY_PROFILE_SCOPE(name)
	#define LY_PROFILE_FUNCTION()
#endif