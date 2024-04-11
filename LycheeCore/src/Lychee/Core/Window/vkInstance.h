/**
 * @file vkInstance.h
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-04-11
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

    namespace vk {
        void CreateInstance(const char* name, VkInstance& instance) {
            VkResult err;

            uint32_t vkVersion = 0;
            err = vkEnumerateInstanceVersion(&vkVersion);

            LY_CORE_INFO("VULKAN: Variante: {0}", VK_API_VERSION_VARIANT(vkVersion));
            LY_CORE_INFO("VULKAN: Version: {0}.{1}.{2}", VK_API_VERSION_MAJOR(vkVersion), VK_API_VERSION_MINOR(vkVersion), VK_API_VERSION_PATCH(vkVersion));

            // TODO (flex): check version here

            VkApplicationInfo vkAppInfo = {
                .pApplicationName = name,
                .applicationVersion = vkVersion,
                .pEngineName = LY_PROJECT_NAME,
                .engineVersion = vkVersion,
                .apiVersion = vkVersion
            };

            LY_CORE_INFO("VULKAN: Setting up extentions for GLFW");
            uint32_t glfwExtensionsCount = 0;
            const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);
            std::vector<const char*> extentions(glfwExtensions, glfwExtensions + glfwExtensionsCount);
            for (const char* i : extentions) {
                LY_CORE_INFO("VULKAN: Extention: {0}", i);
            }

            VkInstanceCreateInfo vkCrateInfo = { 
                .flags = VkInstanceCreateFlags(),
                .pApplicationInfo = &vkAppInfo,
                .enabledLayerCount = 0,                                     // layers
                .ppEnabledLayerNames = nullptr,                             //
                .enabledExtensionCount = (uint32_t)extentions.size(),       // extentions
                .ppEnabledExtensionNames = extentions.data()                //
            };

            err = vkCreateInstance(&vkCrateInfo, nullptr, &instance);
            
            if (err < 0) {
                LY_CORE_ERROR("VULKAN: VkResult = {0}", err);
            }
        }
    
        void DestroyInstance(VkInstace& instace) {
            vkDestroyInstance(instance, nullptr);
        }
    }
}