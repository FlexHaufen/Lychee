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
#include <GLFW/glfw3.h>

#include <vk_mem_alloc.h>

#include <vector>

#include "Lychee/Config.h"
#include "Lychee/Core/Vulkan/vkhUtils.h"


// *** DEFIENS ***
#define VKH_MAX_FRAMES_IN_FLIGHT 1


// *** NAMESPACE ***
namespace Lychee {


    class vkhManager {
    public:
        void setup(GLFWwindow* window, uint32_t frameCount);
        void cleanup();

        void drawFrame();

        void waitIdle() { vkDeviceWaitIdle(m_Device); }

        // getter & setter
        VkInstance getInstance() { return m_Instance; }
        VkPhysicalDevice getPhysicalDevice() { return m_PhysicalDevice; }
        VkDevice getDevice() { return m_Device; }
        VkCommandPool getCommandPool() { return m_CommandPool; }
        VkQueue getGraphicsQueue() { return m_GraphicsQueue; }
        VkQueue getPresentQueue() { return m_PresentQueue; }
        uint32_t getFrameCount() { return m_FrameCount; }
        void setCurrentFrame(uint32_t currentFrame) { m_CurrentFrame = currentFrame; }
        uint32_t getCurrentFrame() { return m_CurrentFrame; }

    private:
        // Initialization
        void createInstance();
        void setupDebugCallback();
        void createSurface();
        void pickPhysicalDevice();
        void createLogicalDevice();
        // void createDescriptorPool(uint32_t poolCount);
        void createSwapChain();
        void createImageViews();
        void createRenderPass();
        void createGraphicsPipeline();
        void createFramebuffers();
        void createCommandPool();
        void createCommandBuffer();
        void createSyncObjects();

        void recordCommandBuffer(uint32_t imageIndex);

    private:

        // ** Members **

        GLFWwindow* m_glfwWindow;

        VkInstance m_Instance;
        VkDebugUtilsMessengerEXT m_Callback;

        VkSurfaceKHR m_Surface;
        VkPhysicalDevice m_PhysicalDevice;
        VkDevice m_Device;

        vkhQueueFamilyIndices m_QueueFamilyIndices;
        VkQueue m_GraphicsQueue;
        VkQueue m_PresentQueue;

        VkSwapchainKHR m_SwapChain;
        VkFormat m_SwapChainImageFormat;
        VkExtent2D m_SwapChainExtent;
        std::vector<VkImage> m_SwapChainImages;
        std::vector<VkImageView> m_SwapChainImageViews;
        std::vector<VkFramebuffer> m_SwapChainFramebuffers;

        VkRenderPass m_RenderPass;
        VkFormat m_DepthFormat;
        VkPipelineLayout m_PipelineLayout;
        VkPipeline m_GraphicsPipeline;

        VkCommandPool m_CommandPool;
        VkCommandBuffer m_CommandBuffer;
        VkDescriptorSetLayout m_DescriptorSetLayout;

        //std::vector<VkSemaphore> m_ImageAvailableSemaphores;
        //std::vector<VkSemaphore> m_RenderFinishedSemaphores;
        //std::vector<VkFence> m_InFlightFences;

        VkSemaphore m_ImageAvailableSemaphores;
        VkSemaphore m_RenderFinishedSemaphores;
        VkFence m_InFlightFences;

        uint32_t m_FrameCount;
        uint32_t m_CurrentFrame = 0;
    };
}
