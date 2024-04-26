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

        /**
         * @brief Extract the transforms from the given bitmask.
         * 
         * @param bits  bits a bitmask describing various transforms
         * @return std::vector<std::string>  a vector of strings describing the transforms
         */
        std::vector<std::string> LogTransformBits(const vk::SurfaceTransformFlagsKHR& bits) {
            std::vector<std::string> result;
            if (bits & vk::SurfaceTransformFlagBitsKHR::eIdentity)  { result.push_back("identity");}
            if (bits & vk::SurfaceTransformFlagBitsKHR::eRotate90)  { result.push_back("90 degree rotation");}
            if (bits & vk::SurfaceTransformFlagBitsKHR::eRotate180) { result.push_back("180 degree rotation");}
            if (bits & vk::SurfaceTransformFlagBitsKHR::eRotate270) { result.push_back("270 degree rotation");}
            if (bits & vk::SurfaceTransformFlagBitsKHR::eHorizontalMirror)          { result.push_back("horizontal mirror");}
            if (bits & vk::SurfaceTransformFlagBitsKHR::eHorizontalMirrorRotate90)  { result.push_back("horizontal mirror, then 90 degree rotation");}
            if (bits & vk::SurfaceTransformFlagBitsKHR::eHorizontalMirrorRotate180) { result.push_back("horizontal mirror, then 180 degree rotation");}
            if (bits & vk::SurfaceTransformFlagBitsKHR::eHorizontalMirrorRotate270) { result.push_back("horizontal mirror, then 270 degree rotation");}
            if (bits & vk::SurfaceTransformFlagBitsKHR::eInherit)   { result.push_back("inherited");}
            return result;
        }

        /**
         * @brief Extract the alpha composite blend modes from the given bitmask.
         * 
         * @param bits a bitmask describing a combination of alpha composite options.
         * @return std::vector<std::string> a vector of strings describing the options.
         */
        std::vector<std::string> LogAlphaCompositeBits(const vk::CompositeAlphaFlagsKHR& bits) {
            std::vector<std::string> result;
            if (bits & vk::CompositeAlphaFlagBitsKHR::eOpaque) { result.push_back("opaque (alpha ignored)");}
            if (bits & vk::CompositeAlphaFlagBitsKHR::ePreMultiplied) { result.push_back("pre multiplied (alpha expected to already be multiplied in image)");}
            if (bits & vk::CompositeAlphaFlagBitsKHR::ePostMultiplied) { result.push_back("post multiplied (alpha will be applied during composition)");}
            if (bits & vk::CompositeAlphaFlagBitsKHR::eInherit) { result.push_back("inherited");}
            return result;
        }

        /**
         * @brief Extract image usage options.
         * 
         * @param bits a bitmask describing various image usages
         * @return std::vector<std::string>  a vector of strings describing the image usages
         */
    	std::vector<std::string> LogImageUsageBits(const vk::ImageUsageFlags& bits) {
            std::vector<std::string> result;

            if (bits & vk::ImageUsageFlagBits::eTransferSrc) {  result.push_back("transfer src: image can be used as the source of a transfer command.");}
            if (bits & vk::ImageUsageFlagBits::eTransferDst) {  result.push_back("transfer dst: image can be used as the destination of a transfer command.");}
            if (bits & vk::ImageUsageFlagBits::eSampled) {      result.push_back("sampled: image can be used to create a VkImageView suitable for occupying a \
VkDescriptorSet slot either of type VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE or \
VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, and be sampled by a shader.");}
            if (bits & vk::ImageUsageFlagBits::eStorage) {      result.push_back("storage: image can be used to create a VkImageView suitable for occupying a \
VkDescriptorSet slot of type VK_DESCRIPTOR_TYPE_STORAGE_IMAGE.");}
            if (bits & vk::ImageUsageFlagBits::eColorAttachment) { result.push_back("color attachment: image can be used to create a VkImageView suitable for use as \
a color or resolve attachment in a VkFramebuffer.");}
            if (bits & vk::ImageUsageFlagBits::eDepthStencilAttachment) { result.push_back("depth/stencil attachment: image can be used to create a VkImageView \
suitable for use as a depth/stencil or depth/stencil resolve attachment in a VkFramebuffer.");}
            if (bits & vk::ImageUsageFlagBits::eTransientAttachment) { result.push_back("transient attachment: implementations may support using memory allocations \
with the VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT to back an image with this usage. This \
bit can be set for any image that can be used to create a VkImageView suitable for use as \
a color, resolve, depth/stencil, or input attachment.");}
            if (bits & vk::ImageUsageFlagBits::eInputAttachment) { result.push_back("input attachment: image can be used to create a VkImageView suitable for \
occupying VkDescriptorSet slot of type VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT; be read from \
a shader as an input attachment; and be used as an input attachment in a framebuffer.");}
            if (bits & vk::ImageUsageFlagBits::eFragmentDensityMapEXT) { result.push_back("fragment density map: image can be used to create a VkImageView suitable \
for use as a fragment density map image.");}
            if (bits & vk::ImageUsageFlagBits::eFragmentShadingRateAttachmentKHR) { result.push_back("fragment shading rate attachment: image can be used to create a VkImageView \
suitable for use as a fragment shading rate attachment or shading rate image");}

            return result;
        }

        /**
         * @brief Extract present mode options.
         * 
         * @param presentMode Bitmask present mode
         * @return std::string a string description of the given present mode.
         */
        std::string LogPresentMode(const vk::PresentModeKHR& presentMode) {
  
            if (presentMode == vk::PresentModeKHR::eImmediate) { return "immediate"; }
            if (presentMode == vk::PresentModeKHR::eMailbox) { return "mailbox"; }
            if (presentMode == vk::PresentModeKHR::eFifo) { return "fifo"; }
            if (presentMode == vk::PresentModeKHR::eFifoRelaxed) { return "relaxed fifo"; }
            if (presentMode == vk::PresentModeKHR::eSharedDemandRefresh) { return "shared demand refresh"; }
            if (presentMode == vk::PresentModeKHR::eSharedContinuousRefresh) { return "shared continuous refresh"; }
            return "none / undefined";
        }
    }
}