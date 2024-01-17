/**
 * @file Camera.h
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-01-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

// *** INCLUDES ***
#include "Lychee/lypch.h"

//*** DEFINES ***


//*** NAMESPACE ***
namespace Lychee {

    class Camera {
   
    public:
        Camera() {
            m_View.setSize(sf::Vector2f(LY_WINDOW_SIZE_X, LY_WINDOW_SIZE_Y));
        }

        /**
         * @brief Update function for camera
         * 
         * @param window    sf::RenderWindow
         * @param pos       camera position
         * @param zoom      camera zoom
         * @param dt        delta time
         */
        void OnUpdate(sf::RenderWindow &window, v2f pos, f32 zoom, f32 dt) {
            // ----- Smoothening in x & y
            //sf::Vector2f movement = sf::Vector2f(pos.x, pos.y) - m_View.getCenter();
            //m_View.move(movement * dt * m_SmoothSpeed);
            
            // ----- No smoothening
            m_View.setCenter(sf::Vector2(pos.x, pos.y));
            m_View.setSize(sf::Vector2f(window.getSize().x * zoom, window.getSize().y * zoom));
            window.setView(m_View);
        }

    private:

        // ** Members **
        sf::View    m_View;             // Current view

        const f32 m_SmoothSpeed = 5;    // smoothening speed
    };
}