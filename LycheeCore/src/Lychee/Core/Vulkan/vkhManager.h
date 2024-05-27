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



// *** NAMESPACE ***
namespace Lychee {


    class vkhManager {
    public:
        void setup(GLFWwindow* window, uint32_t frameCount);
        void cleanup();

        // getter & setter
        VkInstance getInstance() { return m_Instance; }
        VkPhysicalDevice getPhysicalDevice() { return m_PhysicalDevice; }
        VkDevice getDevice() { return m_Device; }
        VmaAllocator getAllocator() { return m_Allocator; }
        VkCommandPool getCommandPool() { return m_CommandPool; }
        VkQueue getGraphicsQueue() { return m_GraphicsQueue; }
        VkQueue getPresentQueue() { return m_PresentQueue; }
        VkDescriptorPool getDescriptorPool() { return m_DescriptorPool; }
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
        void createAllocator();
        void createCommandPool();
        void createDescriptorPool(uint32_t poolCount);
        void createSwapChain();
        void createImageViews();
        void createRenderPass();
        void createGraphicsPipeline();

    private:


        GLFWwindow* m_glfwWindow;

        VkInstance m_Instance;
        VkDebugUtilsMessengerEXT m_Callback;

        VkSurfaceKHR m_Surface;
        VkPhysicalDevice m_PhysicalDevice;
        VkDevice m_Device;

        vkhQueueFamilyIndices m_QueueFamilyIndices;
        VkQueue m_GraphicsQueue;
        VkQueue m_PresentQueue;

        VmaAllocator m_Allocator;
        VkCommandPool m_CommandPool;

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

        VkDescriptorPool m_DescriptorPool;
        VkDescriptorSetLayout m_DescriptorSetLayout;
    
        uint32_t m_FrameCount;
        uint32_t m_CurrentFrame;
    };
}
