/**
 * @file vkDebug.h
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-04-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

// *** INCLUDES ***
#include "Lychee/lypch.h"

// *** DEFIENS ***

// *** NAMESPACE ***
namespace Lychee {

    namespace vkIntern {

        VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                             VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                             const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                                             void* pUserData) {
            LY_CORE_ERROR("VULKAN: validation layer: {0}", pCallbackData->pMessage);
            return VK_FALSE;
        }

        vk::DebugUtilsMessengerEXT CreateDebugMessenger(vk::Instance& instance, vk::DispatchLoaderDynamic& dplD) {
            vk::DebugUtilsMessengerCreateInfoEXT vkCrateInfo = vk::DebugUtilsMessengerCreateInfoEXT(
                vk::DebugUtilsMessengerCreateFlagsEXT(),
                vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError,
                vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance,
                debugCallback,
                nullptr
            );
	        return instance.createDebugUtilsMessengerEXT(vkCrateInfo, nullptr, dplD);
        }
    }
}