/**
 * @file Components.h
 * @author flexhaufen
 * @brief Entity Components
 * @version 0.1
 * @date 2024-01-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

// *** INCLUDES ***
#include "Lychee/lypch.h"
#include "Lychee/Helper/UUID/UUID.h"

//*** DEFINES ***


//*** NAMESPACE ***
namespace Lychee {

    /**
     * @brief This namespace contains all components
     *        that an entity can have
     */
    namespace Component {

        static const char* availableComponents[] = {"RectShape"};
  
        /**
         * @brief Tag Component
         * 
         */
        struct Tag {
            std::string tag = "";               // tag (name)
            UUID uuid;                          // uuid of entity (64bit)
            Tag() = default;
            Tag(const Tag&) = default;
        };


        /**
         * @brief Transform Component
         *  
         */
        struct Transform {
            s8 renderLayer      = 0;            // Order in the renderer [0..LY_MAX_RENDERLAYERS]
            sf::Vector2f pos    = {0, 0};       // Position [px]
            sf::Vector2f scale  = {1, 1};       // Scale [1].
            f32 rotation        = 0.f;          // Rotation
        };


        struct RectShape {
            sf::Vector2f size   = {10, 10};
            sf::Color color     = LY_COLOR_ORANGE;
        };
    };
}
