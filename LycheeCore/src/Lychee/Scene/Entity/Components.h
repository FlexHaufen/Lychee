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

#include "Lychee/Scene/SceneCamera.h"

//*** DEFINES ***


//*** NAMESPACE ***
namespace Lychee {

    /**
     * @brief This namespace contains all components
     *        that an entity can have
     */
    namespace Component {


        static const char* availableComponents[] {"Camera"};

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
            glm::vec2 pos       = {0, 0};       // Position [px]
            glm::vec2 scale     = {1, 1};       // Scale [1].
            f32 rotation        = 0.f;          // Rotation
        };


        /**
         * @brief Camera Component
         * 
         */
        struct Camera {
            SceneCamera camera;

            b8 isPrimary = true;
        };
    }
}
