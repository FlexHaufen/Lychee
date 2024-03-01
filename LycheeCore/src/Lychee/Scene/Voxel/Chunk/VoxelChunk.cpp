

#include "Lychee/Scene/Voxel/Chunk/VoxelChunk.h"


namespace Lychee { 

    VoxelChunk::VoxelChunk() {
        for (u8 x = 0; x < VOXEL_CHUNK_SIZE; x++) {
            for (u8 y = 0; y < VOXEL_CHUNK_SIZE; y++) {
                for (u8 z = 0; z < VOXEL_CHUNK_SIZE; z++) {
                    m_Voxeldata[x][y][z] = {
                        {x, y, z},
                        { 0.8f, 0.2f, ((double) rand() / (RAND_MAX)), 1.0f }
                    };
                }
            }
        }
    }

    void VoxelChunk::OnRender() {
        for (u8 x = 0; x < VOXEL_CHUNK_SIZE; x++) {
            for (u8 y = 0; y < VOXEL_CHUNK_SIZE; y++) {
                for (u8 z = 0; z < VOXEL_CHUNK_SIZE; z++) {
                    Renderer::RenderVoxel(m_Voxeldata[x][y][z].Position, m_Voxeldata[x][y][z].Color);
                }
            }
        }
    }

}