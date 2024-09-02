/**
 * @file vkhManager.h
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-05-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

// *** INCLUDES ***
#include <vulkan/vulkan.hpp>
#include <VkBootstrap.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "Lychee/Config.h"


// *** DEFIENS ***

#define VKH_USE_VALIDATION_LAYERS   1
#define VKH_MAX_FRAMES_IN_FLIGHT    2

#define VKH_CLEAR_COLOR {0.1f, 0.1f, 0.1f, 1.0f}

// *** NAMESPACE ***
namespace Lychee {

    
    struct FrameData {
        VkCommandPool   commandPool;
        VkCommandBuffer mainCommandBuffer;
        VkSemaphore swapchainSemaphore;
        VkSemaphore renderSemaphore;
	    VkFence renderFence;
    };

    class vkhManager {
    public:

        vkhManager() {}
        ~vkhManager() {}

        void setup(GLFWwindow* window);
        void cleanup();

        void draw();

        FrameData& getCurrentFrame() { return m_Frames[m_CurrentFrame % VKH_MAX_FRAMES_IN_FLIGHT]; }

    private:
        // Initialization
        void setupVulkan();
        void setupSwapchain();
        void setupCommands();
        void setupSyncStructures();
    
        void createSwapchain(uint32_t width, uint32_t height);
	    void destroySwapchain();

    private:

        // ** Members **

        //bool _isInitialized{ false };
	    //int _frameNumber {0};
	    //bool stop_rendering{ false };

        GLFWwindow* m_glfwWindow;
        VkExtent2D m_WindowExtend {LY_WINDOW_SIZE_X, LY_WINDOW_SIZE_Y };

        VkInstance m_Instance;
        VkDebugUtilsMessengerEXT m_Callback;

        VkSurfaceKHR m_Surface;
        VkPhysicalDevice m_PhysicalDevice;
        VkDevice m_Device;

        VkSwapchainKHR m_Swapchain;
        VkFormat m_SwapchainImageFormat;
        VkExtent2D m_SwapchainExtent;

        std::vector<VkImage> m_SwapchainImages;
        std::vector<VkImageView> m_SwapchainImageViews;
        
        FrameData m_Frames[VKH_MAX_FRAMES_IN_FLIGHT];
        uint32_t m_CurrentFrame = 0;
        
        VkQueue m_GraphicsQueue;
        uint32_t m_GraphicsQueueFamily;


        /*
        std::vector<VkFramebuffer> m_SwapChainFramebuffers;

        VkRenderPass m_RenderPass;
        VkFormat m_DepthFormat;
        VkPipelineLayout m_PipelineLayout;
        VkPipeline m_GraphicsPipeline;

        VkCommandPool m_CommandPool;
        std::vector<VkCommandBuffer> m_CommandBuffers;
        VkDescriptorSetLayout m_DescriptorSetLayout;
        VkDescriptorPool m_DescriptorPool;
        std::vector<VkDescriptorSet> m_DescriptorSets;

        std::vector<VkSemaphore> m_ImageAvailableSemaphores;
        std::vector<VkSemaphore> m_RenderFinishedSemaphores;
        std::vector<VkFence> m_InFlightFences;

        VkBuffer m_VertexBuffer;
        VkDeviceMemory m_VertexBufferMemory;
        VkBuffer m_IndexBuffer;
        VkDeviceMemory m_IndexBufferMemory;

        std::vector<VkBuffer> m_UniformBuffers;
        std::vector<VkDeviceMemory> m_UniformBuffersMemory;
        std::vector<void*> m_UniformBuffersMapped;

        //! DEBUG
        const std::vector<Vertex> vertices = {
            {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
            {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
            {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
            {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
        };

        const std::vector<uint16_t> indices = {
            0, 1, 2, 2, 3, 0
        };
        //!

        uint32_t m_CurrentFrame = 0;
        bool m_isFramebufferResized = false;
        */

    };
}
