/**
 * @file vkhManager.h
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-05-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

// *** INCLUDES ***
#include <vulkan/vulkan.hpp>
#include <VkBootstrap.h>
#include <vk_mem_alloc.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <deque>
#include <functional>

#include "Lychee/Config.h"
#include "Lychee/Core/Vulkan/vkhUtil.h"

// *** DEFIENS ***

#define VKH_USE_VALIDATION_LAYERS   1
#define VKH_MAX_FRAMES_IN_FLIGHT    2

#define VKH_CLEAR_COLOR {0.1f, 0.1f, 0.1f, 1.0f}

// *** NAMESPACE ***
namespace Lychee {


    struct DeletionQueue  {
        std::deque<std::function<void()>> deletors;

        void push_function(std::function<void()>&& function) {
            deletors.push_back(function);
        }
        void flush() {
            for (auto it = deletors.rbegin(); it != deletors.rend(); it++) {
                (*it)(); //call functors
            }
            deletors.clear();
        }
    };
    
    struct FrameData {
        VkCommandPool   commandPool;
        VkCommandBuffer mainCommandBuffer;
        VkSemaphore swapchainSemaphore;
        VkSemaphore renderSemaphore;
	    VkFence renderFence;
        DeletionQueue deletionQueue;
    };

    class vkhManager {
    public:

        vkhManager() {}
        ~vkhManager() {}

        void setup(GLFWwindow* window);
        void cleanup();

        void draw();

        FrameData& getCurrentFrame() { return m_Frames[m_CurrentFrame % VKH_MAX_FRAMES_IN_FLIGHT]; }

    private:
        // Initialization
        void setupVulkan();
        void setupSwapchain();
        void setupCommands();
        void setupSyncStructures();
    
        void createSwapchain(uint32_t width, uint32_t height);
	    void destroySwapchain();

        void drawBackground(VkCommandBuffer cmd);

    private:

        // ** Members **

        GLFWwindow* m_glfwWindow;
        VkExtent2D m_WindowExtend {LY_WINDOW_SIZE_X, LY_WINDOW_SIZE_Y };

        VkInstance m_Instance;
        VkDebugUtilsMessengerEXT m_Callback;

        VkSurfaceKHR m_Surface;
        VkPhysicalDevice m_PhysicalDevice;
        VkDevice m_Device;

        VkSwapchainKHR m_Swapchain;
        VkFormat m_SwapchainImageFormat;
        VkExtent2D m_SwapchainExtent;

        std::vector<VkImage> m_SwapchainImages;
        std::vector<VkImageView> m_SwapchainImageViews;
        
        FrameData m_Frames[VKH_MAX_FRAMES_IN_FLIGHT];
        uint32_t m_CurrentFrame = 0;
        
        VkQueue m_GraphicsQueue;
        uint32_t m_GraphicsQueueFamily;

        DeletionQueue m_MainDeletionQueue;

        VmaAllocator m_Allocator;

        vkhAllocatedImage m_DrawImage;
        VkExtent2D m_DrawExtent;

    };
}
