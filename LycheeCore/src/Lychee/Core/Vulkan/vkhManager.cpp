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

#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>


// *** DEFINES ***

// *** NAMESPACE ***
namespace Lychee {

    void vkhManager::setup(GLFWwindow* window) {
        LY_CORE_INFO("Setting up vkhManager");
        m_glfwWindow = window;
        setupVulkan();
        setupSwapchain();
        setupCommands();
        setupSyncStructures();
    }

    void vkhManager::cleanup() {
        LY_CORE_INFO("Cleaning up vkhManager");

        vkDeviceWaitIdle(m_Device);

        m_MainDeletionQueue.flush();
		for (int i = 0; i < VKH_MAX_FRAMES_IN_FLIGHT; i++) {
			vkDestroyCommandPool(m_Device, m_Frames[i].commandPool, nullptr);

            //destroy sync objects
            vkDestroyFence(m_Device, m_Frames[i].renderFence, nullptr);
            vkDestroySemaphore(m_Device, m_Frames[i].renderSemaphore, nullptr);
            vkDestroySemaphore(m_Device ,m_Frames[i].swapchainSemaphore, nullptr);
            m_Frames[i].deletionQueue.flush();
        }

        destroySwapchain();
        vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);
        vkDestroyDevice(m_Device, nullptr);
        vkb::destroy_debug_utils_messenger(m_Instance, m_Callback);
        vkDestroyInstance(m_Instance, nullptr);
    }

    void vkhManager::draw() {
        // wait until the gpu has finished rendering the last frame. Timeout of 1 second
        if (vkWaitForFences(m_Device, 1, &getCurrentFrame().renderFence, true, 1000000000) != VK_SUCCESS) {
            LY_CORE_ERROR("Error waiting for vulkan fence");
        }

        getCurrentFrame().deletionQueue.flush();


        uint32_t swapchainImageIndex;
	    VkResult e = vkAcquireNextImageKHR(m_Device, m_Swapchain, 1000000000, getCurrentFrame().swapchainSemaphore, nullptr, &swapchainImageIndex);
        if (e == VK_ERROR_OUT_OF_DATE_KHR) {
            // Rebuild Swapchain
        }
        
        if (vkResetFences(m_Device, 1, &getCurrentFrame().renderFence) != VK_SUCCESS) {
            LY_CORE_ERROR("Error resetting vulkan fence");
        }
        if (vkResetCommandBuffer(getCurrentFrame().mainCommandBuffer, 0) != VK_SUCCESS) {
            LY_CORE_ERROR("Error resetting vulkan command buffer");
        }

        //naming it cmd for shorter writing
	    VkCommandBuffer cmd = getCurrentFrame().mainCommandBuffer;

        //begin the command buffer recording. We will use this command buffer exactly once, so we want to let vulkan know that
        VkCommandBufferBeginInfo cmdBeginInfo = {};
        cmdBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        cmdBeginInfo.pNext = nullptr;
        cmdBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        cmdBeginInfo.pInheritanceInfo = nullptr;
        
        // ------ DRAW_FIRST ------
        m_DrawExtent.width = m_DrawImage.imageExtent.width;
	    m_DrawExtent.height = m_DrawImage.imageExtent.height;
        //start the command buffer recording
        if (vkBeginCommandBuffer(cmd, &cmdBeginInfo) != VK_SUCCESS) {
            LY_CORE_ERROR("Error couldn't begin vulkan command buffer");
        }

        //make the swapchain image into writeable mode before rendering
	    vkhTransitionImage(cmd, m_DrawImage.image, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_GENERAL);

        drawBackground(cmd);

        //make the swapchain image into presentable mode
        //transition the draw image and the swapchain image into their correct transfer layouts
        vkhTransitionImage(cmd, m_DrawImage.image, VK_IMAGE_LAYOUT_GENERAL, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL); //! ERROR HERE
        vkhTransitionImage(cmd, m_SwapchainImages[swapchainImageIndex], VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

        // execute a copy from the draw image into the swapchain
	    vkhCopyImageToImage(cmd, m_DrawImage.image, m_SwapchainImages[swapchainImageIndex], m_DrawExtent, m_SwapchainExtent);

	    // set swapchain image layout to Attachment Optimal so we can draw it
	    vkhTransitionImage(cmd, m_SwapchainImages[swapchainImageIndex], VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);

	    //finalize the command buffer (we can no longer add commands, but it can now be executed)
        if(vkEndCommandBuffer(cmd) != VK_SUCCESS) {
            LY_CORE_ERROR("Error couldn't end vulkan command buffer");
        }
        // ------------------------

        //prepare the submission to the queue. 
        //we want to wait on the _presentSemaphore, as that semaphore is signaled when the swapchain is ready
        //we will signal the _renderSemaphore, to signal that rendering has finished
        VkCommandBufferSubmitInfo cmdinfo = {};
        cmdinfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO;
        cmdinfo.pNext = nullptr;
        cmdinfo.commandBuffer = cmd;
        cmdinfo.deviceMask = 0;

        VkSemaphoreSubmitInfo waitInfo = {};
        waitInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
        waitInfo.pNext = nullptr;
        waitInfo.semaphore = getCurrentFrame().swapchainSemaphore;
        waitInfo.value = 1;
        waitInfo.stageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT_KHR;
        waitInfo.deviceIndex = 0;
        
        VkSemaphoreSubmitInfo signalInfo = {};
        signalInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
        signalInfo.pNext = nullptr;
        signalInfo.semaphore = getCurrentFrame().renderSemaphore;
        signalInfo.value = 1;
        signalInfo.stageMask = VK_PIPELINE_STAGE_2_ALL_GRAPHICS_BIT;
        signalInfo.deviceIndex = 0;

        VkSubmitInfo2 submit = {};
        submit.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2;
        submit.pNext = nullptr;   
        submit.waitSemaphoreInfoCount = &waitInfo == nullptr ? 0 : 1;
        submit.pWaitSemaphoreInfos = &waitInfo;   
        submit.commandBufferInfoCount = 1;
        submit.pCommandBufferInfos = &cmdinfo;
        submit.signalSemaphoreInfoCount = &signalInfo == nullptr ? 0 : 1;
        submit.pSignalSemaphoreInfos = &signalInfo;

        //submit command buffer to the queue and execute it.
        // _renderFence will now block until the graphic commands finish execution
        if(vkQueueSubmit2(m_GraphicsQueue, 1, &submit, getCurrentFrame().renderFence) != VK_SUCCESS) {
            LY_CORE_ERROR("Couldn't submit queue");
        }


        VkPresentInfoKHR presentInfo = {};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        presentInfo.pNext = nullptr;
        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = &getCurrentFrame().renderSemaphore;
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = &m_Swapchain;
        presentInfo.pImageIndices = &swapchainImageIndex;

        if(vkQueuePresentKHR(m_GraphicsQueue, &presentInfo) != VK_SUCCESS) {
            LY_CORE_ERROR("Couldn't present queue");
        }

        //increase the number of frames drawn
        m_CurrentFrame++;
    }

    // Private
    void vkhManager::setupVulkan() {
        vkb::InstanceBuilder builder;

        // debug Callback
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

        // use vkbootstrap to get a Graphics queue
	    m_GraphicsQueue = vkbDevice.get_queue(vkb::QueueType::graphics).value();
	    m_GraphicsQueueFamily = vkbDevice.get_queue_index(vkb::QueueType::graphics).value();

        // initialize the memory allocator
        VmaAllocatorCreateInfo allocatorInfo = {};
        allocatorInfo.physicalDevice = m_PhysicalDevice;
        allocatorInfo.device = m_Device;
        allocatorInfo.instance = m_Instance;
        allocatorInfo.flags = VMA_ALLOCATOR_CREATE_BUFFER_DEVICE_ADDRESS_BIT;
        vmaCreateAllocator(&allocatorInfo, &m_Allocator);

        m_MainDeletionQueue.push_function([&]() {
            vmaDestroyAllocator(m_Allocator);
        });
    }

    void vkhManager::setupSwapchain() {
        createSwapchain(m_WindowExtend.width, m_WindowExtend.height);
    }

    void vkhManager::setupCommands() {
        // create a command pool for commands submitted to the graphics queue.
        // we also want the pool to allow for resetting of individual command buffers
        VkCommandPoolCreateInfo commandPoolInfo =  {};
        commandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        commandPoolInfo.pNext = nullptr;
        commandPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        commandPoolInfo.queueFamilyIndex = m_GraphicsQueueFamily;
        
        
        for (int i = 0; i < VKH_MAX_FRAMES_IN_FLIGHT; i++) {

            if (vkCreateCommandPool(m_Device, &commandPoolInfo, nullptr, &m_Frames[i].commandPool) != VK_SUCCESS) {
                LY_CORE_ERROR("Could not create vulkan command pool");
            }

            // allocate the default command buffer that we will use for rendering
            VkCommandBufferAllocateInfo cmdAllocInfo = {};
            cmdAllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
            cmdAllocInfo.pNext = nullptr;
            cmdAllocInfo.commandPool = m_Frames[i].commandPool;
            cmdAllocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
            cmdAllocInfo.commandBufferCount = 1;
            

            if (vkAllocateCommandBuffers(m_Device, &cmdAllocInfo, &m_Frames[i].mainCommandBuffer) != VK_SUCCESS) {
                LY_CORE_ERROR("Could not allocate vulkan command buffer");
            }
        }
    }

    void vkhManager::setupSyncStructures() {
        //create syncronization structures
        //one fence to control when the gpu has finished rendering the frame,
        //and 2 semaphores to syncronize rendering with swapchain
        //we want the fence to start signalled so we can wait on it on the first frame
        VkFenceCreateInfo fenceCreateInfo = {};
        fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceCreateInfo.pNext = nullptr;
        fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
        

        VkSemaphoreCreateInfo semaphoreCreateInfo = {};
        semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
        semaphoreCreateInfo.pNext = nullptr;
        semaphoreCreateInfo.flags = 0;

        for (int i = 0; i < VKH_MAX_FRAMES_IN_FLIGHT; i++) {
            if (vkCreateFence(m_Device, &fenceCreateInfo, nullptr, &m_Frames[i].renderFence) != VK_SUCCESS) {
                LY_CORE_ERROR("Could create vulkan fence");
            }
            if (vkCreateSemaphore(m_Device, &semaphoreCreateInfo, nullptr, &m_Frames[i].swapchainSemaphore) != VK_SUCCESS) {
                LY_CORE_ERROR("Could create vulkan swapchain semaphore");
            }
            if (vkCreateSemaphore(m_Device, &semaphoreCreateInfo, nullptr, &m_Frames[i].renderSemaphore) != VK_SUCCESS) {
                LY_CORE_ERROR("Could create vulkan render semaphore");
            }
        }
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

        //draw image size will match the window
        VkExtent3D drawImageExtent = {
            m_WindowExtend.width,
            m_WindowExtend.height,
            1
        };

        //hardcoding the draw format to 32 bit float
        m_DrawImage.imageFormat = VK_FORMAT_R16G16B16A16_SFLOAT;
        m_DrawImage.imageExtent = drawImageExtent;

        VkImageUsageFlags drawImageUsages{};
        drawImageUsages |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
        drawImageUsages |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
        drawImageUsages |= VK_IMAGE_USAGE_STORAGE_BIT;
        drawImageUsages |= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        VkImageCreateInfo rimg_info = {};
        rimg_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        rimg_info.pNext = nullptr;
        rimg_info.imageType = VK_IMAGE_TYPE_2D;
        rimg_info.format = m_DrawImage.imageFormat;
        rimg_info.extent = drawImageExtent;
        rimg_info.mipLevels = 1;
        rimg_info.arrayLayers = 1;
        rimg_info.samples = VK_SAMPLE_COUNT_1_BIT;  //for MSAA. we will not be using it by default, so default it to 1 sample per pixel.
        rimg_info.tiling = VK_IMAGE_TILING_OPTIMAL;  //optimal tiling, which means the image is stored on the best gpu format
        rimg_info.usage = drawImageUsages;   

        //for the draw image, we want to allocate it from gpu local memory
        VmaAllocationCreateInfo rimg_allocinfo = {};
        rimg_allocinfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;
        rimg_allocinfo.requiredFlags = VkMemoryPropertyFlags(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

        //allocate and create the image
        vmaCreateImage(m_Allocator, &rimg_info, &rimg_allocinfo, &m_DrawImage.image, &m_DrawImage.allocation, nullptr);

        //build a image-view for the draw image to use for rendering
        VkImageViewCreateInfo rview_info = {};
        rview_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        rview_info.pNext = nullptr;
        rview_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
        rview_info.image = m_DrawImage.image;
        rview_info.format = m_DrawImage.imageFormat;
        rview_info.subresourceRange.baseMipLevel = 0;
        rview_info.subresourceRange.levelCount = 1;
        rview_info.subresourceRange.baseArrayLayer = 0;
        rview_info.subresourceRange.layerCount = 1;
        rview_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        if(vkCreateImageView(m_Device, &rview_info, nullptr, &m_DrawImage.imageView) != VK_SUCCESS) {
            LY_CORE_ERROR("VULKAN: Failed to create image view!");
        }

        //add to deletion queues
        m_MainDeletionQueue.push_function([=]() {
            vkDestroyImageView(m_Device, m_DrawImage.imageView, nullptr);
            vmaDestroyImage(m_Allocator, m_DrawImage.image, m_DrawImage.allocation);
	    });
    }

    void vkhManager::destroySwapchain() {
        vkDestroySwapchainKHR(m_Device, m_Swapchain, nullptr);
        // destroy swapchain resources
        for (uint32_t i = 0; i < m_SwapchainImageViews.size(); i++) {
            vkDestroyImageView(m_Device, m_SwapchainImageViews[i], nullptr);
        }
    }


    void vkhManager::drawBackground(VkCommandBuffer cmd) {
        VkClearColorValue clearValue;
        float flash = std::abs(std::sin(m_CurrentFrame / 120.f));
        clearValue = { { 0.0f, 0.0f, flash, 1.0f } };

        VkImageSubresourceRange clearRange = {};
        clearRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        clearRange.baseMipLevel = 0;
        clearRange.levelCount = VK_REMAINING_MIP_LEVELS;
        clearRange.baseArrayLayer = 0;
        clearRange.layerCount = VK_REMAINING_ARRAY_LAYERS;

        //clear image
        vkCmdClearColorImage(cmd, m_DrawImage.image, VK_IMAGE_LAYOUT_GENERAL, &clearValue, 1, &clearRange);
    }

}