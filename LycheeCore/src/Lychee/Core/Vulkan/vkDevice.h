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


        /**
         * @brief Holds properties of the swapchain
		 *        capabilities: no. of images and supported sizes
		 *        formats: eg. supported pixel formats
		 *        present modes: available presentation modes (eg. double buffer, fifo, mailbox)
         */
        struct sSwapChainSupportDetails {
            vk::SurfaceCapabilitiesKHR capabilities;
            std::vector<vk::SurfaceFormatKHR> formats;
            std::vector<vk::PresentModeKHR> presentModes;
        };

        /**
         * @brief Various data structures associated with the swapchain.
         * 
         */
        struct sSwapChainBundle {
            vk::SwapchainKHR swapchain;
            std::vector<vk::Image> images;
            vk::Format format;
            vk::Extent2D extent;
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

            std::vector<const char* > deviceExtentions = {
                VK_KHR_SWAPCHAIN_EXTENSION_NAME
            };

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
                deviceExtentions.size(), 
                deviceExtentions.data(),
                &deviceFeatures
            );

            try {
                vk::Device device = physicalDevice.createDevice(deviceInfo);
                LY_CORE_INFO("VULKAN: GPU has been successfully abstracted");
                return device;
            }
            catch (vk::SystemError err) {
                LY_CORE_ERROR("VULKAN: Logical device creation failed");
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
    
        sSwapChainSupportDetails QuerySwapchainSupport(const vk::PhysicalDevice& device, const vk::SurfaceKHR& surface) {
		    sSwapChainSupportDetails support;

		    support.capabilities = device.getSurfaceCapabilitiesKHR(surface);

            #ifdef LY_DEBUG
                LY_CORE_INFO("VULKAN: Swapchain can support the following surface capabilities:");
                LY_CORE_INFO("VULKAN: - min. image count: {0}", support.capabilities.minImageCount);
                LY_CORE_INFO("VULKAN: - max. image count: {0}", support.capabilities.maxImageCount);
                LY_CORE_INFO("VULKAN: - current extent:        [{0}, {1}]", support.capabilities.currentExtent.width, support.capabilities.currentExtent.height);
                LY_CORE_INFO("VULKAN: - min. supported extent: [{0}, {1}]", support.capabilities.minImageExtent.width, support.capabilities.minImageExtent.height);
                LY_CORE_INFO("VULKAN: - max. supported extent: [{0}, {1}]",support.capabilities.maxImageExtent.width, support.capabilities.maxImageExtent.height);
                LY_CORE_INFO("VULKAN: - max. image array layers: {0}", support.capabilities.maxImageArrayLayers);
                
                LY_CORE_INFO("VULKAN: - supported transforms:");
                std::vector<std::string> stringList = LogTransformBits(support.capabilities.supportedTransforms);
                for (auto& line : stringList) {
                    LY_CORE_INFO("VULKAN:   - {0}", line);
                }

                LY_CORE_INFO("VULKAN: - current transform:");
                stringList = LogTransformBits(support.capabilities.currentTransform);
                for (auto& line : stringList) {
                    LY_CORE_INFO("VULKAN:   - {0}", line);
                }

                LY_CORE_INFO("VULKAN: - supported alpha operations:");
                stringList = LogAlphaCompositeBits(support.capabilities.supportedCompositeAlpha);
                for (std::string line : stringList) {
                    LY_CORE_INFO("VULKAN:   - {0}", line);
                }

                LY_CORE_INFO("VULKAN: - supported image usage:");
                stringList = LogImageUsageBits(support.capabilities.supportedUsageFlags);
                for (std::string line : stringList) {
                    LY_CORE_INFO("VULKAN:   - {0}", line);
                }
            #endif

            support.formats = device.getSurfaceFormatsKHR(surface);

            #ifdef LY_DEBUG
                for (vk::SurfaceFormatKHR supportedFormat : support.formats) {
                    LY_CORE_INFO("VULKAN supported pixel format: {0}", vk::to_string(supportedFormat.format));
                    LY_CORE_INFO("VULKAN supported color space: {0}", vk::to_string(supportedFormat.colorSpace));
                }
            #endif

            support.presentModes = device.getSurfacePresentModesKHR(surface);
            #ifdef LY_DEBUG
                for (vk::PresentModeKHR presentMode : support.presentModes) {
                    LY_CORE_INFO("VULKAN Present mode:\t {0}", LogPresentMode(presentMode));
                }
            #endif

            return support;
        }
	
        /**
         * @brief Choose a surface format for the swapchain
         * 
         * @param formats a vector of surface formats supported by the device
         * @return vk::SurfaceFormatKHR 
         */
        vk::SurfaceFormatKHR ChooseSwapchainSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& formats) {
            for (vk::SurfaceFormatKHR format : formats) {
                if (format.format == vk::Format::eB8G8R8A8Unorm && format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
                    return format;
                }
            }
            return formats[0];
        }

        /**
         * @brief Choose a present mode.
         * 
         * @param presentModes a vector of present modes supported by the device
         * @return vk::PresentModeKHR 
         */
        vk::PresentModeKHR ChooseSwapchainPresentMode(const std::vector<vk::PresentModeKHR>& presentModes) {
            for (vk::PresentModeKHR presentMode : presentModes) {
                if (presentMode == vk::PresentModeKHR::eMailbox) {
                    return presentMode;
                }
            }
            return vk::PresentModeKHR::eFifo;
        }

        /**
         * @brief Choose an extent for the swapchain.
         * 
         * @param width the requested width
         * @param height the requested height
         * @param capabilities a struct describing the supported capabilities of the device
         * @return vk::Extent2D chosen extent
         */
        vk::Extent2D ChooseSwapchainExtent(uint32_t width, uint32_t height, const vk::SurfaceCapabilitiesKHR& capabilities) {

            if (capabilities.currentExtent.width != UINT32_MAX) {
                return capabilities.currentExtent;
            }
            else {
                vk::Extent2D extent = { width, height };

                extent.width = std::min(
                    capabilities.maxImageExtent.width, 
                    std::max(capabilities.minImageExtent.width, extent.width)
                );

                extent.height = std::min(
                    capabilities.maxImageExtent.height,
                    std::max(capabilities.minImageExtent.height, extent.height)
                );

                return extent;
            }
        }

        /**
         * @brief Create a Swapchain
         * 
         * @param logicalDevice the logical device
         * @param physicalDevice the physical device
         * @param surface the window surface to use the swapchain with
         * @param width the requested width
         * @param height the requested height
         * @return SwapChainBundle 
         */
        sSwapChainBundle CreateSwapchain(const vk::Device& logicalDevice, const vk::PhysicalDevice& physicalDevice, const vk::SurfaceKHR& surface, int width, int height) {

            sSwapChainSupportDetails support = QuerySwapchainSupport(physicalDevice, surface);
            vk::SurfaceFormatKHR format = ChooseSwapchainSurfaceFormat(support.formats);
            vk::PresentModeKHR presentMode = ChooseSwapchainPresentMode(support.presentModes);
            vk::Extent2D extent = ChooseSwapchainExtent(width, height, support.capabilities);

            uint32_t imageCount = std::min(
                support.capabilities.maxImageCount,
                support.capabilities.minImageCount + 1
            );

            vk::SwapchainCreateInfoKHR createInfo = vk::SwapchainCreateInfoKHR(
                vk::SwapchainCreateFlagsKHR(), surface, imageCount, format.format, format.colorSpace,
                extent, 1, vk::ImageUsageFlagBits::eColorAttachment
            );

            sQueueFamilyIndices indices = FindQueueFamilies(physicalDevice, surface);
            uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

            if (indices.graphicsFamily != indices.presentFamily) {
                createInfo.imageSharingMode = vk::SharingMode::eConcurrent;
                createInfo.queueFamilyIndexCount = 2;
                createInfo.pQueueFamilyIndices = queueFamilyIndices;
            }
            else {
                createInfo.imageSharingMode = vk::SharingMode::eExclusive;
            }

            createInfo.preTransform = support.capabilities.currentTransform;
            createInfo.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
            createInfo.presentMode = presentMode;
            createInfo.clipped = VK_TRUE;

            createInfo.oldSwapchain = vk::SwapchainKHR(nullptr);

            sSwapChainBundle bundle;
            try {
                bundle.swapchain = logicalDevice.createSwapchainKHR(createInfo);
            }
            catch (vk::SystemError err) {
                LY_CORE_ERROR("VULKAN: failed to create swap chain!");
            }
            bundle.images = logicalDevice.getSwapchainImagesKHR(bundle.swapchain);
            bundle.format = format.format;
            bundle.extent = extent;
            return bundle;
        }
        
    }
}