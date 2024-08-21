/**
 * @file vkhManager.cpp
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-05-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

// *** INCLUDES ***
#include "Lychee/lypch.h"

#include "Lychee/Config.h"
#include "Lychee/Core/Vulkan/vkhManager.h"
#include "Lychee/Helper/File.h"


// *** DEFINES ***

// *** NAMESPACE ***
namespace Lychee {

    void vkhManager::setup(GLFWwindow* window) {
        LY_CORE_INFO("Setting up vkhManager");
        m_glfwWindow = window;
        setupVulkan();
        setupSwapchain();
        //setupCommands();
        //setupSyncStructures();
    }

    void vkhManager::cleanup() {
        LY_CORE_INFO("Setting up vkhManager");
        destroySwapchain();
        vkDestroyDevice(m_Device, nullptr);
        vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);
        vkb::destroy_debug_utils_messenger(m_Instance, m_Callback);
        vkDestroyInstance(m_Instance, nullptr);
    }


    // Private
    void vkhManager::setupVulkan() {
        vkb::InstanceBuilder builder;

        builder.set_debug_callback(
            [] (VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                VkDebugUtilsMessageTypeFlagsEXT messageType,
                const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                void *pUserData) -> VkBool32 {
                    const char* severity = vkb::to_string_message_severity (messageSeverity);
                    switch (messageSeverity) {
                        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
                            LY_CORE_CRITICAL("[VULKAN] [{0}] {1}", severity, pCallbackData->pMessage);
                            break;
                        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
                            LY_CORE_ERROR("[VULKAN] [{0}] {1}", severity, pCallbackData->pMessage);
                            break;
                        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
                            LY_CORE_WARN("[VULKAN] [{0}] {1}", severity, pCallbackData->pMessage);
                            break;
                        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
                            LY_CORE_INFO("[VULKAN] [{0}] {1}", severity, pCallbackData->pMessage);
                            break;
                        default:
                            LY_CORE_ERROR("Received unknown message type from Vulkan. This should not happen:");
                            LY_CORE_ERROR("[VULKAN] [{0}] {1}", severity, pCallbackData->pMessage);
                            break;
                    }
                    return VK_FALSE;
            }
        );

        //make the vulkan instance, with basic debug features
        auto inst_ret = builder.set_app_name("Lychee")              // TODO (flex): use define
            .request_validation_layers(VKH_USE_VALIDATION_LAYERS)
            .require_api_version(1, 3, 0)
            .build();


        //grab the instance 
        m_Instance = inst_ret.value().instance;
        m_Callback = inst_ret.value().debug_messenger;

        if (glfwCreateWindowSurface(m_Instance, m_glfwWindow, nullptr, &m_Surface) != VK_SUCCESS) {
            LY_CORE_ERROR("VULKAN: Failed to create window surface!");
        }

        //vulkan 1.3 features
        VkPhysicalDeviceVulkan13Features features{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES };
        features.dynamicRendering = true;
        features.synchronization2 = true;

        //vulkan 1.2 features
        VkPhysicalDeviceVulkan12Features features12{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES };
        features12.bufferDeviceAddress = true;
        features12.descriptorIndexing = true;

        //use vkbootstrap to select a gpu. 
        //We want a gpu that can write to the SDL surface and supports vulkan 1.3 with the correct features
        vkb::PhysicalDeviceSelector selector{ inst_ret.value() };
        vkb::PhysicalDevice physicalDevice = selector
            .set_minimum_version(1, 3)
            .set_required_features_13(features)
            .set_required_features_12(features12)
            .set_surface(m_Surface)
            .select()
            .value();
        //create the final vulkan device
        vkb::DeviceBuilder deviceBuilder{ physicalDevice };
        vkb::Device vkbDevice = deviceBuilder.build().value();
        // Get the VkDevice handle used in the rest of a vulkan application
        m_Device = vkbDevice.device;
        m_PhysicalDevice = physicalDevice.physical_device;
    }

    void vkhManager::createSwapchain(uint32_t width, uint32_t height) {
        vkb::SwapchainBuilder swapchainBuilder { m_PhysicalDevice, m_Device, m_Surface };

        m_SwapchainImageFormat = VK_FORMAT_B8G8R8A8_UNORM;

        vkb::Swapchain vkbSwapchain = swapchainBuilder
            //.use_default_format_selection()
            .set_desired_format(VkSurfaceFormatKHR{ .format = m_SwapchainImageFormat, .colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR })
            //use vsync present mode
            .set_desired_present_mode(VK_PRESENT_MODE_FIFO_KHR)
            .set_desired_extent(width, height)
            .add_image_usage_flags(VK_IMAGE_USAGE_TRANSFER_DST_BIT)
            .build()
            .value();

        m_SwapchainExtent = vkbSwapchain.extent;
        //store swapchain and its related images
        m_Swapchain = vkbSwapchain.swapchain;
        m_SwapchainImages = vkbSwapchain.get_images().value();
        m_SwapchainImageViews = vkbSwapchain.get_image_views().value();
    }

    void vkhManager::setupSwapchain() {
        createSwapchain(m_WindowExtend.width, m_WindowExtend.height);
    }

    void vkhManager::destroySwapchain() {
        vkDestroySwapchainKHR(m_Device, m_Swapchain, nullptr);
        // destroy swapchain resources
        for (uint32_t i = 0; i < m_SwapchainImageViews.size(); i++) {
            vkDestroyImageView(m_Device, m_SwapchainImageViews[i], nullptr);
        }
    }

}