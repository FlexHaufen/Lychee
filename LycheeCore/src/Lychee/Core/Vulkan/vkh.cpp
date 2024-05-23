/**
 * @file vkh..h
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-05-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */

// *** INCLUDES ***
#include "Lychee/lypch.h"

#include "Lychee/Core/Vulkan/vkh.h"

// *** DEFIENS ***
#define MAX_FRAMES_IN_FLIGHT 2

// *** NAMESPACE ***
namespace Lychee { namespace vkh {

    VkSurfaceKHR CreateSurfaceGlfw(VkInstance instance, GLFWwindow* window, VkAllocationCallbacks* allocator = nullptr) {
        VkSurfaceKHR surface = VK_NULL_HANDLE;
        if (glfwCreateWindowSurface(instance, window, allocator, &surface)) {
            LY_CORE_ERROR("VULKAN: Error creating window surface");
            surface = VK_NULL_HANDLE;
        }
        return surface;
    }

    std::vector<char> readFile(const std::string& filename) {
        std::ifstream file(filename, std::ios::ate | std::ios::binary);

        if (!file.is_open()) {
            LY_CORE_ERROR("VULKAN: Failed to open file [{0}]", filename);
            // TODO (flex): return here empty ector
        }
        size_t file_size = (size_t)file.tellg();
        std::vector<char> buffer(file_size);
        file.seekg(0);
        file.read(buffer.data(), static_cast<std::streamsize>(file_size));
        file.close();
        return buffer;
    }

    VkShaderModule createShaderModule(Instance& instance, const std::vector<char>& code) {
        VkShaderModuleCreateInfo create_info = {};
        create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        create_info.codeSize = code.size();
        create_info.pCode = reinterpret_cast<const uint32_t*>(code.data());

        VkShaderModule shaderModule;
        if (instance.disp.createShaderModule(&create_info, nullptr, &shaderModule) != VK_SUCCESS) {
            return VK_NULL_HANDLE; // failed to create shader module
        }

        return shaderModule;
    }


    // --------------

    Result DeviceInitialization(Instance& instance) {

        vkb::InstanceBuilder instance_builder;
        auto instance_ret = instance_builder.use_default_debug_messenger().request_validation_layers().build();
        if (!instance_ret) {
            LY_CORE_ERROR("VULKAN: {0}", instance_ret.error().message());
            return VKH_ERROR;
        }
        instance.instance = instance_ret.value();

        instance.inst_disp = instance.instance.make_table();

        instance.surface = CreateSurfaceGlfw(instance.instance, instance.window);

        vkb::PhysicalDeviceSelector phys_device_selector(instance.instance);
        auto phys_device_ret = phys_device_selector.set_surface(instance.surface).select();
        if (!phys_device_ret) {
            LY_CORE_ERROR("VULKAN: {0}", phys_device_ret.error().message());
            return VKH_ERROR;
        }
        vkb::PhysicalDevice physical_device = phys_device_ret.value();

        vkb::DeviceBuilder device_builder{ physical_device };
        auto device_ret = device_builder.build();
        if (!device_ret) {
            LY_CORE_ERROR("VULKAN: {0}", device_ret.error().message());
            return VKH_ERROR;
        }
        instance.device = device_ret.value();
        instance.disp = instance.device.make_table();
        return VKH_SUCCESS;
    }

    Result CreateSwapchain(Instance& instance) {
        vkb::SwapchainBuilder swapchain_builder{ instance.device };
        auto swap_ret = swapchain_builder.set_old_swapchain(instance.swapchain).build();
        if (!swap_ret) {
            LY_CORE_ERROR("VULKAN: {0} {1}", swap_ret.error().message(), swap_ret.vk_result());
            return VKH_ERROR;
        }
        vkb::destroy_swapchain(instance.swapchain);
        instance.swapchain = swap_ret.value();
        return VKH_SUCCESS;
    }

    Result GetQueue(Instance& instance, RenderData& data) {
        auto gq = instance.device.get_queue(vkb::QueueType::graphics);
        if (!gq.has_value()) {
            LY_CORE_ERROR("VULKAN: failed to get graphics queue: {0}", gq.error().message());
            return VKH_ERROR;
        }
        data.graphics_queue = gq.value();

        auto pq = instance.device.get_queue(vkb::QueueType::present);
        if (!pq.has_value()) {
            LY_CORE_ERROR("VULKAN: failed to get present queue:  {0}", pq.error().message());
            return VKH_ERROR;
        }
        data.present_queue = pq.value();
        return VKH_SUCCESS;
    }

    Result CreateRenderPass(Instance& instance, RenderData& data) {
        VkAttachmentDescription color_attachment = {};
        color_attachment.format = instance.swapchain.image_format;
        color_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
        color_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        color_attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        color_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        color_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        color_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        color_attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentReference color_attachment_ref = {};
        color_attachment_ref.attachment = 0;
        color_attachment_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass = {};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &color_attachment_ref;

        VkSubpassDependency dependency = {};
        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        dependency.dstSubpass = 0;
        dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.srcAccessMask = 0;
        dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

        VkRenderPassCreateInfo render_pass_info = {};
        render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        render_pass_info.attachmentCount = 1;
        render_pass_info.pAttachments = &color_attachment;
        render_pass_info.subpassCount = 1;
        render_pass_info.pSubpasses = &subpass;
        render_pass_info.dependencyCount = 1;
        render_pass_info.pDependencies = &dependency;

        if (instance.disp.createRenderPass(&render_pass_info, nullptr, &data.render_pass) != VK_SUCCESS) {
            LY_CORE_ERROR("VULKAN: failed to create render pass");
            return VKH_ERROR; // failed to create render pass!
        }
        return VKH_SUCCESS;
    }

    Result CreateGraphicsPipeline(Instance& instance, RenderData& data) {
        // TODO (flex): Compile shaders
        auto vert_code = readFile(std::string(LY_DEFAULT_SHADER_PATH) + "vert.spv");
        auto frag_code = readFile(std::string(LY_DEFAULT_SHADER_PATH) + "frag.spv");

        VkShaderModule vert_module = createShaderModule(instance, vert_code);
        VkShaderModule frag_module = createShaderModule(instance, frag_code);
        if (vert_module == VK_NULL_HANDLE || frag_module == VK_NULL_HANDLE) {
            LY_CORE_ERROR("VULKAN: failed to create shader module");
            return VKH_ERROR;
        }

        VkPipelineShaderStageCreateInfo vert_stage_info = {};
        vert_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vert_stage_info.stage = VK_SHADER_STAGE_VERTEX_BIT;
        vert_stage_info.module = vert_module;
        vert_stage_info.pName = "main";

        VkPipelineShaderStageCreateInfo frag_stage_info = {};
        frag_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        frag_stage_info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        frag_stage_info.module = frag_module;
        frag_stage_info.pName = "main";

        VkPipelineShaderStageCreateInfo shader_stages[] = { vert_stage_info, frag_stage_info };

        VkPipelineVertexInputStateCreateInfo vertex_input_info = {};
        vertex_input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        vertex_input_info.vertexBindingDescriptionCount = 0;
        vertex_input_info.vertexAttributeDescriptionCount = 0;

        VkPipelineInputAssemblyStateCreateInfo input_assembly = {};
        input_assembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        input_assembly.primitiveRestartEnable = VK_FALSE;

        VkViewport viewport = {};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float)instance.swapchain.extent.width;
        viewport.height = (float)instance.swapchain.extent.height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        VkRect2D scissor = {};
        scissor.offset = { 0, 0 };
        scissor.extent = instance.swapchain.extent;

        VkPipelineViewportStateCreateInfo viewport_state = {};
        viewport_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewport_state.viewportCount = 1;
        viewport_state.pViewports = &viewport;
        viewport_state.scissorCount = 1;
        viewport_state.pScissors = &scissor;

        VkPipelineRasterizationStateCreateInfo rasterizer = {};
        rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterizer.depthClampEnable = VK_FALSE;
        rasterizer.rasterizerDiscardEnable = VK_FALSE;
        rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
        rasterizer.lineWidth = 1.0f;
        rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
        rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
        rasterizer.depthBiasEnable = VK_FALSE;

        VkPipelineMultisampleStateCreateInfo multisampling = {};
        multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisampling.sampleShadingEnable = VK_FALSE;
        multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

        VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
        colorBlendAttachment.colorWriteMask =
            VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        colorBlendAttachment.blendEnable = VK_FALSE;

        VkPipelineColorBlendStateCreateInfo color_blending = {};
        color_blending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        color_blending.logicOpEnable = VK_FALSE;
        color_blending.logicOp = VK_LOGIC_OP_COPY;
        color_blending.attachmentCount = 1;
        color_blending.pAttachments = &colorBlendAttachment;
        color_blending.blendConstants[0] = 0.0f;
        color_blending.blendConstants[1] = 0.0f;
        color_blending.blendConstants[2] = 0.0f;
        color_blending.blendConstants[3] = 0.0f;

        VkPipelineLayoutCreateInfo pipeline_layout_info = {};
        pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipeline_layout_info.setLayoutCount = 0;
        pipeline_layout_info.pushConstantRangeCount = 0;

        if (instance.disp.createPipelineLayout(&pipeline_layout_info, nullptr, &data.pipeline_layout) != VK_SUCCESS) {
            LY_CORE_ERROR("VULKAN: failed to create pipeline layout");
            return VKH_ERROR;
        }

        std::vector<VkDynamicState> dynamic_states = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };

        VkPipelineDynamicStateCreateInfo dynamic_info = {};
        dynamic_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        dynamic_info.dynamicStateCount = static_cast<uint32_t>(dynamic_states.size());
        dynamic_info.pDynamicStates = dynamic_states.data();

        VkGraphicsPipelineCreateInfo pipeline_info = {};
        pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipeline_info.stageCount = 2;
        pipeline_info.pStages = shader_stages;
        pipeline_info.pVertexInputState = &vertex_input_info;
        pipeline_info.pInputAssemblyState = &input_assembly;
        pipeline_info.pViewportState = &viewport_state;
        pipeline_info.pRasterizationState = &rasterizer;
        pipeline_info.pMultisampleState = &multisampling;
        pipeline_info.pColorBlendState = &color_blending;
        pipeline_info.pDynamicState = &dynamic_info;
        pipeline_info.layout = data.pipeline_layout;
        pipeline_info.renderPass = data.render_pass;
        pipeline_info.subpass = 0;
        pipeline_info.basePipelineHandle = VK_NULL_HANDLE;

        if (instance.disp.createGraphicsPipelines(VK_NULL_HANDLE, 1, &pipeline_info, nullptr, &data.graphics_pipeline) != VK_SUCCESS) {
            LY_CORE_ERROR("VULKAN: failed to create pipline");
            return VKH_ERROR;
        }

        instance.disp.destroyShaderModule(frag_module, nullptr);
        instance.disp.destroyShaderModule(vert_module, nullptr);
        return VKH_SUCCESS;
    }

    Result CreateFramebuffers(Instance& instance, RenderData& data) {
        data.swapchain_images = instance.swapchain.get_images().value();
        data.swapchain_image_views = instance.swapchain.get_image_views().value();
        data.framebuffers.resize(data.swapchain_image_views.size());

        for (size_t i = 0; i < data.swapchain_image_views.size(); i++) {
            VkImageView attachments[] = { data.swapchain_image_views[i] };
            VkFramebufferCreateInfo framebuffer_info = {};
            framebuffer_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebuffer_info.renderPass = data.render_pass;
            framebuffer_info.attachmentCount = 1;
            framebuffer_info.pAttachments = attachments;
            framebuffer_info.width = instance.swapchain.extent.width;
            framebuffer_info.height = instance.swapchain.extent.height;
            framebuffer_info.layers = 1;
            if (instance.disp.createFramebuffer(&framebuffer_info, nullptr, &data.framebuffers[i]) != VK_SUCCESS) {
                return VKH_ERROR; // failed to create framebuffer
            }
        }
        return VKH_SUCCESS;
    }

    Result CreateCommandPool(Instance& instance, RenderData& data) {
        VkCommandPoolCreateInfo pool_info = {};
        pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        pool_info.queueFamilyIndex = instance.device.get_queue_index(vkb::QueueType::graphics).value();

        if (instance.disp.createCommandPool(&pool_info, nullptr, &data.command_pool) != VK_SUCCESS) {
            LY_CORE_ERROR("VULKAN: failed to create command pool");
            return VKH_ERROR;
        }
        return VKH_SUCCESS;
    }
    
    Result CreateCommandBuffers(Instance& instance, RenderData& data) {
        data.command_buffers.resize(data.framebuffers.size());

        VkCommandBufferAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = data.command_pool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = (uint32_t)data.command_buffers.size();

        if (instance.disp.allocateCommandBuffers(&allocInfo, data.command_buffers.data()) != VK_SUCCESS) {
            LY_CORE_ERROR("VULKAN: failed to allocate command buffers");
            return VKH_ERROR;
        }

        for (size_t i = 0; i < data.command_buffers.size(); i++) {
            VkCommandBufferBeginInfo begin_info = {};
            begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

            if (instance.disp.beginCommandBuffer(data.command_buffers[i], &begin_info) != VK_SUCCESS) {
                LY_CORE_ERROR("VULKAN: failed to begin recording command buffer");
                return VKH_ERROR;
            }

            VkRenderPassBeginInfo render_pass_info = {};
            render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            render_pass_info.renderPass = data.render_pass;
            render_pass_info.framebuffer = data.framebuffers[i];
            render_pass_info.renderArea.offset = { 0, 0 };
            render_pass_info.renderArea.extent = instance.swapchain.extent;
            VkClearValue clearColor{ { { 0.0f, 0.0f, 0.0f, 1.0f } } };
            render_pass_info.clearValueCount = 1;
            render_pass_info.pClearValues = &clearColor;

            VkViewport viewport = {};
            viewport.x = 0.0f;
            viewport.y = 0.0f;
            viewport.width = (float)instance.swapchain.extent.width;
            viewport.height = (float)instance.swapchain.extent.height;
            viewport.minDepth = 0.0f;
            viewport.maxDepth = 1.0f;

            VkRect2D scissor = {};
            scissor.offset = { 0, 0 };
            scissor.extent = instance.swapchain.extent;

            instance.disp.cmdSetViewport(data.command_buffers[i], 0, 1, &viewport);
            instance.disp.cmdSetScissor(data.command_buffers[i], 0, 1, &scissor);
            instance.disp.cmdBeginRenderPass(data.command_buffers[i], &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);
            instance.disp.cmdBindPipeline(data.command_buffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, data.graphics_pipeline);
            instance.disp.cmdDraw(data.command_buffers[i], 3, 1, 0, 0);
            instance.disp.cmdEndRenderPass(data.command_buffers[i]);

            if (instance.disp.endCommandBuffer(data.command_buffers[i]) != VK_SUCCESS) {
                LY_CORE_ERROR("VULKAN: failed to record command buffer");
                return VKH_ERROR;
            }
        }
        return VKH_SUCCESS;
    }

    Result CreateSyncObjects(Instance& instance, RenderData& data) {
        data.available_semaphores.resize(MAX_FRAMES_IN_FLIGHT);
        data.finished_semaphore.resize(MAX_FRAMES_IN_FLIGHT);
        data.in_flight_fences.resize(MAX_FRAMES_IN_FLIGHT);
        data.image_in_flight.resize(instance.swapchain.image_count, VK_NULL_HANDLE);

        VkSemaphoreCreateInfo semaphore_info = {};
        semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        VkFenceCreateInfo fence_info = {};
        fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fence_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            if (instance.disp.createSemaphore(&semaphore_info, nullptr, &data.available_semaphores[i]) != VK_SUCCESS ||
                instance.disp.createSemaphore(&semaphore_info, nullptr, &data.finished_semaphore[i]) != VK_SUCCESS ||
                instance.disp.createFence(&fence_info, nullptr, &data.in_flight_fences[i]) != VK_SUCCESS) {
                LY_CORE_ERROR("VULKAN: failed to create sync objects");
                return VKH_ERROR;
            }
        }
        return VKH_SUCCESS;
    }


    int recreate_swapchain(Instance& instance, RenderData& data) {
        instance.disp.deviceWaitIdle();

        instance.disp.destroyCommandPool(data.command_pool, nullptr);

        for (auto framebuffer : data.framebuffers) {
            instance.disp.destroyFramebuffer(framebuffer, nullptr);
        }

        instance.swapchain.destroy_image_views(data.swapchain_image_views);

        if (0 != CreateSwapchain(instance)) return -1;
        if (0 != CreateFramebuffers(instance, data)) return -1;
        if (0 != CreateCommandPool(instance, data)) return -1;
        if (0 != CreateCommandBuffers(instance, data)) return -1;
        return 0;
    }

    int draw_frame(Instance& instance, RenderData& data) {
        instance.disp.waitForFences(1, &data.in_flight_fences[data.current_frame], VK_TRUE, UINT64_MAX);

        uint32_t image_index = 0;
        VkResult result = instance.disp.acquireNextImageKHR(
            instance.swapchain, UINT64_MAX, data.available_semaphores[data.current_frame], VK_NULL_HANDLE, &image_index);

        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            return recreate_swapchain(instance, data);
        } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            std::cout << "failed to acquire swapchain image. Error " << result << "\n";
            return -1;
        }

        if (data.image_in_flight[image_index] != VK_NULL_HANDLE) {
            instance.disp.waitForFences(1, &data.image_in_flight[image_index], VK_TRUE, UINT64_MAX);
        }
        data.image_in_flight[image_index] = data.in_flight_fences[data.current_frame];

        VkSubmitInfo submitInfo = {};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        VkSemaphore wait_semaphores[] = { data.available_semaphores[data.current_frame] };
        VkPipelineStageFlags wait_stages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = wait_semaphores;
        submitInfo.pWaitDstStageMask = wait_stages;

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &data.command_buffers[image_index];

        VkSemaphore signal_semaphores[] = { data.finished_semaphore[data.current_frame] };
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signal_semaphores;

        instance.disp.resetFences(1, &data.in_flight_fences[data.current_frame]);

        if (instance.disp.queueSubmit(data.graphics_queue, 1, &submitInfo, data.in_flight_fences[data.current_frame]) != VK_SUCCESS) {
            std::cout << "failed to submit draw command buffer\n";
            return -1; //"failed to submit draw command buffer
        }

        VkPresentInfoKHR present_info = {};
        present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        present_info.waitSemaphoreCount = 1;
        present_info.pWaitSemaphores = signal_semaphores;

        VkSwapchainKHR swapChains[] = { instance.swapchain };
        present_info.swapchainCount = 1;
        present_info.pSwapchains = swapChains;

        present_info.pImageIndices = &image_index;

        result = instance.disp.queuePresentKHR(data.present_queue, &present_info);
        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) {
            return recreate_swapchain(instance, data);
        } else if (result != VK_SUCCESS) {
            std::cout << "failed to present swapchain image\n";
            return -1;
        }

        data.current_frame = (data.current_frame + 1) % MAX_FRAMES_IN_FLIGHT;
        return 0;
    }



    void Terminate(Instance& instance, RenderData& data) {
        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            instance.disp.destroySemaphore(data.finished_semaphore[i], nullptr);
            instance.disp.destroySemaphore(data.available_semaphores[i], nullptr);
            instance.disp.destroyFence(data.in_flight_fences[i], nullptr);
        }

        instance.disp.destroyCommandPool(data.command_pool, nullptr);

        for (auto framebuffer : data.framebuffers) {
            instance.disp.destroyFramebuffer(framebuffer, nullptr);
        }

        instance.disp.destroyPipeline(data.graphics_pipeline, nullptr);
        instance.disp.destroyPipelineLayout(data.pipeline_layout, nullptr);
        instance.disp.destroyRenderPass(data.render_pass, nullptr);

        instance.swapchain.destroy_image_views(data.swapchain_image_views);

        vkb::destroy_swapchain(instance.swapchain);
        vkb::destroy_device(instance.device);
        vkb::destroy_surface(instance.instance, instance.surface);
        vkb::destroy_instance(instance.instance);

    }

}}