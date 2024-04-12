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

    namespace vkIntern {

        /**
         * @brief Checks if given extentions are supported
         * 
         * @param extention 
         * @param layers 
         */
        bool IsExtentionSupported(std::vector<const char*>& extention) {
            // Enumerate available extensions
            std::vector<vk::ExtensionProperties> properties = vk::enumerateInstanceExtensionProperties();
            
            bool IsExtentionSupported = false;
            for (auto*  e : extention) {
                IsExtentionSupported = false;
                for (const auto& p : properties) {
                    if (strcmp(p.extensionName, e) == 0) {
                        IsExtentionSupported = true;
                    }
                }
                if (!IsExtentionSupported) {
                    LY_CORE_ERROR("VULKAN: Extention [{0}] is not supported", e);
                    return false;
                }
            }
            return true;
        }

        bool IsLayerSupported(std::vector<const char*>& layers) {
            // Enumerate available layers
            std::vector<vk::LayerProperties> properties = vk::enumerateInstanceLayerProperties();
            
            bool IsLayerSupported = false;
            for (auto*  e : layers) {
                IsLayerSupported = false;
                for (const auto& p : properties) {
                    if (strcmp(p.layerName, e) == 0) {
                        IsLayerSupported = true;
                    }
                }
                if (!IsLayerSupported) {
                    LY_CORE_ERROR("VULKAN: Layer [{0}] is not supported", e);
                    return false;
                }
            }
            return true;
        }

        vk::Instance CreateInstance(const char* name) {
            uint32_t vkVersion = 0;
            vkEnumerateInstanceVersion(&vkVersion);

            LY_CORE_INFO("VULKAN: Variante: {0}", VK_API_VERSION_VARIANT(vkVersion));
            LY_CORE_INFO("VULKAN: Version: {0}.{1}.{2}", VK_API_VERSION_MAJOR(vkVersion), VK_API_VERSION_MINOR(vkVersion), VK_API_VERSION_PATCH(vkVersion));

            // TODO (flex): check version here

            vk::ApplicationInfo vkAppInfo = vk::ApplicationInfo(
                name,
                vkVersion,
                LY_PROJECT_NAME,
                vkVersion,
                vkVersion
            );

            LY_CORE_INFO("VULKAN: Setting up extentions for GLFW");
            uint32_t glfwExtensionsCount = 0;
            const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);
            std::vector<const char*> extentions(glfwExtensions, glfwExtensions + glfwExtensionsCount);
            
            #ifdef LY_DEBUG
                extentions.push_back("VK_EXT_debug_utils");
            #endif

            if (!vkIntern::IsExtentionSupported(extentions)) {
                LY_CORE_ERROR("VULKAN: Extention not supported");
                return nullptr;
            }
            
            LY_CORE_INFO("VULKAN: Setting up layers");
            std::vector<const char*> layers = {};

            #ifdef LY_DEBUG
                layers.push_back("VK_LAYER_KHRONOS_validation");
            #endif

            if (!vkIntern::IsLayerSupported(layers)) {
                LY_CORE_ERROR("VULKAN: Layer not supported");
                return nullptr;
            }

            vk::InstanceCreateInfo vkCrateInfo = vk::InstanceCreateInfo(
                vk::InstanceCreateFlags(),
                &vkAppInfo,
                (uint32_t)layers.size(),      // layers
                layers.data(),                //
                (uint32_t)extentions.size(),  // extentions
                extentions.data()             //
            );


            try {
			    return vk::createInstance(vkCrateInfo);
		    }
            catch (vk::SystemError err) {
                LY_CORE_ERROR("Failed to create Instance");
                return nullptr;
            }
        }
 
 
        vk::PhysicalDevice CreatePhysicalDevice(vk::Instance& instance) {
            
            LY_CORE_INFO("VULKAN: Choosing physical device");

            std::vector<vk::PhysicalDevice> availablePhysicalDevices = instance.enumeratePhysicalDevices();
            for (vk::PhysicalDevice d : availablePhysicalDevices) {
                #ifdef LY_DEBUG
                    vk::PhysicalDeviceProperties properties = d.getProperties();
                    LY_CORE_INFO("VULKAN: Device name: {0}", properties.deviceName);
                    switch (properties.deviceType) {
                        case (vk::PhysicalDeviceType::eCpu):            LY_CORE_INFO("VULKAN: Device Type [CPU]"); break;
                        case (vk::PhysicalDeviceType::eDiscreteGpu):    LY_CORE_INFO("VULKAN: Device Type [Discrete GPU]"); break;
                        case (vk::PhysicalDeviceType::eIntegratedGpu):  LY_CORE_INFO("VULKAN: Device Type [Integrated GPU]"); break;
                        case (vk::PhysicalDeviceType::eVirtualGpu):     LY_CORE_INFO("VULKAN: Device Type [Virtual GPU]"); break;
                        default: LY_CORE_INFO("VULKAN: Device Type [other]");
                    }
                #endif
                
                const std::vector<const char*> requestedExtensions = { 
                    VK_KHR_SWAPCHAIN_EXTENSION_NAME 
                };
                std::set<std::string> extentions(requestedExtensions.begin(), requestedExtensions.end());

                for (vk::ExtensionProperties& extension : d.enumerateDeviceExtensionProperties()) {
                    //remove this from the list of required extensions (set checks for equality automatically)
                    extentions.erase(extension.extensionName);
                }

                //if the set is empty then all requirements have been satisfied
                if (extentions.empty()) {
                    LY_CORE_INFO("VULKAN: Device can support the requested extensions");
                    return d;
                }
                LY_CORE_INFO("VULKAN: Device cannot support the requested extensions");
            }
            return nullptr;
        }
    }
}