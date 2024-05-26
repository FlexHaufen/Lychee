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

#define VKH_ENABLE_VALIDATION_LAYERS


// *** NAMESPACE ***
namespace Lychee {


    class vkhManager {
    public:
        void setup(GLFWwindow* window, bool enableValidationLayers, uint32_t frameCount);
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

        // Single time command buffer prep
        //VkCommandBuffer beginSingleTimeCommands();
        //void endSingleTimeCommands(VkCommandBuffer commandBuffer);

        // Image layout transition
        //void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t layerCount);

    private:
        // Initialization
        void createInstance();
        void setupDebugCallback();
        void createSurface(GLFWwindow* window);
        void pickPhysicalDevice();
        void createLogicalDevice();
        void createAllocator();
        void createCommandPool();
        void createDescriptorPool(uint32_t poolCount);
        //void createDescriptorSetLayout();

        bool checkValidationLayerSupport();
        std::vector<const char *> getRequiredExtensions();
        VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pCallback);
        void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT callback, const VkAllocationCallbacks* pAllocator);
        bool isDeviceSuitable(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
        vkhQueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        vkhSwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
        //bool hasStencilComponent(VkFormat format);

    private:

        vkhQueueFamilyIndices m_QueueFamilyIndices;
        
        VkInstance m_Instance;
        VkSurfaceKHR m_Surface;
        VkPhysicalDevice m_PhysicalDevice;
        VkDevice m_Device;
        VkDebugUtilsMessengerEXT m_Callback;
        VmaAllocator m_Allocator;
        VkCommandPool m_CommandPool;
        VkQueue m_GraphicsQueue;
        VkQueue m_PresentQueue;
        VkDescriptorPool m_DescriptorPool;
        VkDescriptorSetLayout m_DescriptorSetLayout;

        
        // Vulkan constants
        const std::vector<const char*> m_ValidationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };
        const std::vector<const char*> m_DeviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };
        bool m_EnableValidationLayers;
        uint32_t m_FrameCount;
        uint32_t m_CurrentFrame;
    };
}
