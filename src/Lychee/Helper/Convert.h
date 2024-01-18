/**
 * @file Convert.h
 * @author flexhaufen
 * @brief Functions to make your live easier
 * @version 0.1
 * @date 2024-01-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

// *** INCLUDES ***
#include "Lychee/lypch.h"

// *** DEFINES ***

// *** NAMESPACE ***
namespace Lychee {



    namespace Conv {

        /**
         * @brief Convert a sf::Color object to an ImVec4 color object
         * 
         * @note ImGui is using 0..1 and sfml 0..255
         * 
         * @param color     sf::Color
         * @return ImVec4   ImVec4 Color
         */
        inline ImVec4 sfColor_to_ImColor(sf::Color c) { return ImVec4(c.r / 255.f, c.g / 255.f, c.b / 255.f, c.a / 255.f); }

    }
}