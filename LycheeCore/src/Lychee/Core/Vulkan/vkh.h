/**
 * @file vkh..h
 * @author flexhaufen
 * @brief Vulkan Handler
 * @version 0.1
 * @date 2024-05-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

// *** INCLUDES ***
#include <VkBootstrap.h>
#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

#include <vector>

#include "Lychee/Config.h"

// *** DEFIENS ***

// *** NAMESPACE ***
namespace Lychee { namespace vkh {


        typedef struct {
            GLFWwindow* window;
            vkb::Instance instance;
            vkb::InstanceDispatchTable inst_disp;
            VkSurfaceKHR surface;
            vkb::Device device;
            vkb::DispatchTable disp;
            vkb::Swapchain swapchain;
        } Instance;

        typedef struct RenderData {
            VkQueue graphics_queue;
            VkQueue present_queue;

            std::vector<VkImage> swapchain_images;
            std::vector<VkImageView> swapchain_image_views;
            std::vector<VkFramebuffer> framebuffers;

            VkRenderPass render_pass;
            VkPipelineLayout pipeline_layout;
            VkPipeline graphics_pipeline;

            VkCommandPool command_pool;
            std::vector<VkCommandBuffer> command_buffers;

            std::vector<VkSemaphore> available_semaphores;
            std::vector<VkSemaphore> finished_semaphore;
            std::vector<VkFence> in_flight_fences;
            std::vector<VkFence> image_in_flight;
            size_t current_frame = 0;
        } RenderData;

        typedef enum {
            VKH_SUCCESS = 0,
            VKH_ERROR = 1
        } Result;

        /**
         * @brief Initialize vulkan
         * 
         * @warning This function does not initialize the GLFW window
         * 
         * @param instance 
         * @return Result 
         */
        Result DeviceInitialization(Instance& instance);

        Result CreateSwapchain(Instance& instance);
        Result GetQueue(Instance& instance, RenderData& data);
        Result CreateRenderPass(Instance& instance, RenderData& data);  
        Result CreateGraphicsPipeline(Instance& instance, RenderData& data);
        Result CreateFramebuffers(Instance& instance, RenderData& data);
        Result CreateCommandPool(Instance& instance, RenderData& data);
        Result CreateCommandBuffers(Instance& instance, RenderData& data);
        Result CreateSyncObjects(Instance& instance, RenderData& data);


        int draw_frame(Instance& instance, RenderData& data);

        
        void Terminate(Instance& instance, RenderData& data);


}}