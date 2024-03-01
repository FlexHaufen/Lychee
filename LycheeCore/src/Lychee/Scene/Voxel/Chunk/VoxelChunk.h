/**
 * @file VoxelChunk.h
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-02-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

// *** INCLUDES ***
#include "Lychee/lypch.h"
#include "Lychee/Scene/Voxel/Voxel.h"

#include "Lychee/Core/Time/Deltatime.h"
#include "Lychee/Renderer/Renderer.h"

// *** DEFINES ***

#define VOXEL_CHUNK_SIZE    16

// *** NAMESPACE ***
namespace Lychee {



    class VoxelChunk {
    public:
        VoxelChunk();
        //~VoxelChunk();

        void OnUpdate(DeltaTime dt);

        /**
         * @brief Renders a Voxelchunk using the builtin
         *        renderer
         * 
         */
        void OnRender();

    private:

        // ** Members **

        // x y z
        sVoxelVertex m_Voxeldata[VOXEL_CHUNK_SIZE][VOXEL_CHUNK_SIZE][VOXEL_CHUNK_SIZE];   // TODO (flex): Maby use new struct

    };


    
}