/**
 * @file Voxel.h
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-02-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

// *** INCLUDE ***
#include "Lychee/lypch.h"

// *** NAMESPACE ***
namespace Lychee {



    /**
     * @brief VoxelVertex used for rendering
     * 
     */
    struct sVoxelVertex {
        glm::vec3 Position;
		glm::vec4 Color;
    };
}