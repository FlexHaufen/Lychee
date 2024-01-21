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
#include "Lychee/Core/Time/Deltatime.h"

//*** DEFINES ***


//*** NAMESPACE ***
namespace Lychee {

    class Camera {
   
    public:
        Camera(sf::Vector2f size) {
            m_View.setSize(size);
        }

        /**
         * @brief Update function for camera
         * 
         * @param pos       camera position
         * @param zoom      camera zoom
         * @param dt        delta time
         */
        void OnUpdate(DeltaTime dt) {
            // ----- Smoothening in x & y
            //sf::Vector2f movement = sf::Vector2f(pos.x, pos.y) - m_View.getCenter();
            //m_View.move(movement * dt * m_SmoothSpeed);
            
            // ----- No smoothening
            m_View.setCenter(sf::Vector2(m_Pos.x, m_Pos.y));
        }


        void Move(f32 x = 0, f32 y = 0) { m_Pos += sf::Vector2f(x, y); }

        void Zoom(f32 zoom) {  
            m_View.zoom(zoom); 
        }
   
        const sf::View& GetView() const { return m_View; }

        void SetSize(sf::Vector2f size) { m_View.setSize(size); }


    private:

        // ** Members **
        sf::View         m_View;             // Current view
        sf::Vector2f     m_Pos = {0, 0};     // Camera Pos
        
        const f32 m_SmoothSpeed = 5;    // smoothening speed
    };
}