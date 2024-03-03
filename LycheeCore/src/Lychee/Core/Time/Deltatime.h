/**
 * @file DeltaTime.h
 * @author flexhaufen
 * @brief mesures time - lol
 * @version 0.1
 * @date 2022-10-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

// *** INCLUDES ***
#include <Lychee/lypch.h>

// *** DEFINES ***

// *** NAMESPACE ***
namespace Lychee {
    
    /**
     * @brief DeltaTime class
     * 
     */
    class DeltaTime {
    public:
        DeltaTime(float time = 0.0f)
        :   m_time(time) {}

        float GetSeconds() const { return m_time; }
        float GetMillisecons() const { return m_time * 1000.0f;}

        operator float() const {return m_time;}
    private:
        //** Members **
        float m_time;
    };
}