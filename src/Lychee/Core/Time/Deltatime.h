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
        void OnUpdate() { m_time = m_clk.restart(); }

        f32 GetSeconds() const { return m_time.asSeconds(); }
        f32 GetMillisecons() const { return (f32)m_time.asMilliseconds();}

        operator sf::Time() {return m_time;}
        operator float() const { return m_time.asSeconds(); }

    private:
        //** Members **
        sf::Time m_time;
        sf::Clock m_clk;

    };
}