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
        Camera(v2f size) {
            m_View.setSize(sf::Vector2f(size.x, size.y));
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


        void Move(f32 x = 0, f32 y = 0) { m_Pos += v2f(x, y); }
        void Zoom(f32 zoom) {  
            m_View.zoom(zoom); 
        }
   
        const sf::View& GetView() const { return m_View; }

        void SetSize(v2f size) { m_View.setSize(size.x , size.y); }


    private:

        // ** Members **
        sf::View    m_View;             // Current view
        
        v2f     m_Pos = {0, 0};         // Camera Pos
        
        const f32 m_SmoothSpeed = 5;    // smoothening speed
    };
}