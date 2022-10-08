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

//*** INCLUDES ***
#include <Lychee/lypch.h>

//*** DEFINES ***

//*** NAMESPACE ***
namespace Lychee {
    
    /**
     * @brief DeltaTime class
     * 
     */
    class DeltaTime {
    public:
        DeltaTime(f32 time = 0.0f)
        :   m_time(time)
        {

        }

        f32 GetSeconds() const { return m_time; }
        f32 GetMillisecons() const { return m_time * 1000.0f;}

    private:
        //** Members **
        f32 m_time;

    };
}