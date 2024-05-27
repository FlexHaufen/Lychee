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
#include <optional>

#include "Lychee/Config.h"


// *** DEFIENS ***
#define VKH_ENABLE_VALIDATION_LAYERS


// *** NAMESPACE ***
namespace Lychee {

    // Vulkan constants
    static const std::vector<const char*> s_ValidationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };
    static const std::vector<const char*> s_DeviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    struct vkhQueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    struct vkhSwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    struct vkhUniformBufferObject {
        glm::mat4x4 transform ;
    };

    static VKAPI_ATTR VkBool32 VKAPI_CALL vkhDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
        LY_CORE_TRACE("VULKAN: {0}", pCallbackData->pMessage);
        return VK_FALSE;
    }

    bool vkhCheckValidationLayerSupport();
    std::vector<const char *> vkhGetRequiredExtensions();
    VkResult vkhCreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pCallback);
    void vkhDestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT callback, const VkAllocationCallbacks* pAllocator);
    bool vkhIsDeviceSuitable(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
    vkhQueueFamilyIndices vkhFindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);
    bool vkhCheckDeviceExtensionSupport(VkPhysicalDevice device);
    vkhSwapChainSupportDetails vkhQuerySwapChainSupport(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);

}