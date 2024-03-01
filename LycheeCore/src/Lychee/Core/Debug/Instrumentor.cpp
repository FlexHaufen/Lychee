/**
 * @file Instrumentor.cpp
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2022-12-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// *** INCLUDES ***
#include "Lychee/Core/Debug/Instrumentor.h"

// *** DEFINES ***


// *** NAMESPACE ***
namespace Lychee {


    void Instrumentor::BeginSession(const std::string& name, const std::string& filepath) {
        std::lock_guard lock(m_Mutex);

        LY_CORE_INFO("Instrumentor: Begining Profile-Session");
        LY_CORE_INFO("Instrumentor: \\---- Name: {0}", name);
        LY_CORE_INFO("Instrumentor: \\---- Path: {0}", filepath);


        if (m_CurrentSession) {
            if (Log::GetCoreLogger()) {
                LY_CORE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.", name, m_CurrentSession->Name);
            }
            InternalEndSession();
        }
        m_OutputStream.open(filepath);

        if (m_OutputStream.is_open()) {
            m_CurrentSession = new sInstrumentationSession({name});
            WriteHeader();
        }
        else {
            if (Log::GetCoreLogger()) {
                LY_CORE_ERROR("Instrumentor: Could not open results file '{0}'.", filepath);
            }
        }
    }

    void Instrumentor::EndSession() {
        LY_CORE_INFO("Instrumentor: Ending Profile-Session");
        
        std::lock_guard lock(m_Mutex);
        InternalEndSession();
    }

    void Instrumentor::WriteProfile(const sProfileResult& result) {
        std::stringstream json;

        json << std::setprecision(3) << std::fixed;
        json << ",{";
        json << "\"cat\":\"function\",";
        json << "\"dur\":" << (result.ElapsedTime.count()) << ',';
        json << "\"name\":\"" << result.Name << "\",";
        json << "\"ph\":\"X\",";
        json << "\"pid\":0,";
        json << "\"tid\":" << result.ThreadID << ",";
        json << "\"ts\":" << result.Start.count();
        json << "}";

        std::lock_guard lock(m_Mutex);
        if (m_CurrentSession) {
            m_OutputStream << json.str();
            m_OutputStream.flush();
        }
    }

    void Instrumentor::WriteHeader() {
        m_OutputStream << "{\"otherData\": {},\"traceEvents\":[{}";
        m_OutputStream.flush();
    }

    void Instrumentor::WriteFooter() {
        m_OutputStream << "]}";
        m_OutputStream.flush();
    }

    void Instrumentor::InternalEndSession() {
        if (m_CurrentSession) {
            WriteFooter();
            m_OutputStream.close();
            delete m_CurrentSession;
            m_CurrentSession = nullptr;
        }
    }


    InstrumentationTimer::InstrumentationTimer(const char* name)
        : m_Name(name), m_Stopped(false) {
        m_StartTimepoint = std::chrono::steady_clock::now();
    }

    InstrumentationTimer::~InstrumentationTimer() {
        if (!m_Stopped) {
            Stop();
        }
    }

    void InstrumentationTimer::Stop() {
        auto endTimepoint = std::chrono::steady_clock::now();
        auto highResStart = float_ms_t{ m_StartTimepoint.time_since_epoch() };
        auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch();

        Instrumentor::Get().WriteProfile({ m_Name, highResStart, elapsedTime, std::this_thread::get_id() });

        m_Stopped = true;
    }
}