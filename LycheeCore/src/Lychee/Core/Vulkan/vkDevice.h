/**
 * @file vkDevice.h
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

        /**
         * @brief Holds the indices of the graphics and presentation queue families.
         * 
         */
        struct sQueueFamilyIndices {
            std::optional<uint32_t> graphicsFamily;
            std::optional<uint32_t> presentFamily;

            /**
             * @brief Check whether all of the Queue family indices have been set.
             * 
             * @return true 
             * @return false 
             */
            bool IsComplete() {
                return graphicsFamily.has_value() && presentFamily.has_value();
            }
        };




        vk::PhysicalDevice CreatePhysicalDevice(vk::Instance& instance) {
                
            LY_CORE_INFO("VULKAN: Creating physical device");

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
 
        sQueueFamilyIndices FindQueueFamilies(const vk::PhysicalDevice& device, const vk::SurfaceKHR& surface) {
            sQueueFamilyIndices indices;

            std::vector<vk::QueueFamilyProperties> queueFamilies = device.getQueueFamilyProperties();

            LY_CORE_INFO("VULKAN: Available families: {0}", queueFamilies.size());


            int i = 0;
            for (vk::QueueFamilyProperties queueFamily : queueFamilies) {
                if (queueFamily.queueFlags & vk::QueueFlagBits::eGraphics) {
                    indices.graphicsFamily = i;
                    LY_CORE_INFO("VULKAN: Queue Family [{0}] is suitable for graphics", i);
                }

                if (device.getSurfaceSupportKHR(i, surface)) {
                    indices.presentFamily = i;
                    LY_CORE_INFO("VULKAN: Queue Family [{0}] is suitable for presenting", i);
                }

                if (indices.IsComplete()) { break; }
                i++;
            }
            return indices;
        }

        vk::Device CreateLogicalDevice(const vk::PhysicalDevice& physicalDevice, const vk::SurfaceKHR& surface) {
            LY_CORE_INFO("VULKAN: Creating logical device");
            sQueueFamilyIndices indices = FindQueueFamilies(physicalDevice, surface);

            std::vector<uint32_t> uniqueIndices;
            uniqueIndices.push_back(indices.graphicsFamily.value());
            if (indices.graphicsFamily.value() != indices.presentFamily.value()) {
                uniqueIndices.push_back(indices.presentFamily.value());
            }
            float queuePriority = 1.0f;
        
            std::vector<vk::DeviceQueueCreateInfo> queueCreateInfo;
            for (uint32_t queueFamilyIndex : uniqueIndices) {
                queueCreateInfo.push_back(
                    vk::DeviceQueueCreateInfo(
                        vk::DeviceQueueCreateFlags(),
                        queueFamilyIndex,
                        1,
                        &queuePriority
                    )
                );
            }

            vk::PhysicalDeviceFeatures deviceFeatures = vk::PhysicalDeviceFeatures();

            std::vector<const char*> enabledLayers;
            
            #ifdef LY_DEBUG
                enabledLayers.push_back("VK_LAYER_KHRONOS_validation");
            #endif


            // FIXME (flex): results in vulkan error
            vk::DeviceCreateInfo deviceInfo = vk::DeviceCreateInfo(
                vk::DeviceCreateFlags(), 
                queueCreateInfo.size(), 
                queueCreateInfo.data(),
                enabledLayers.size(), 
                enabledLayers.data(),
                0, 
                nullptr,
                &deviceFeatures
            );

            try {
                vk::Device device = physicalDevice.createDevice(deviceInfo);
                LY_CORE_INFO("GPU has been successfully abstracted");
                return device;
            }
            catch (vk::SystemError err) {
                LY_CORE_ERROR("Logical device creation failed");
                return nullptr;
            }
            return nullptr;
        }
    

        std::array<vk::Queue, 2> GetQueues(const vk::PhysicalDevice& physicalDevice,const vk::SurfaceKHR& surface, const vk::Device& device) {
            sQueueFamilyIndices indices = FindQueueFamilies(physicalDevice, surface);
            return  {
                device.getQueue(indices.graphicsFamily.value(), 0),
                device.getQueue(indices.presentFamily.value(), 0)
            };
        }
    }
}