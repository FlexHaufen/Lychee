/**
 * @file lyphc.h
 * @author flexhaufen
 * @brief Precompiled header
 * @version 0.1
 * @date 2022-09-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

// *** INCLUDES ***
// ** External Files **
#pragma warning(push, 0)  // Disable all warnings
#include <algorithm>
#include <array>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <math.h>
#include <memory>
#include <random>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#define NOMINMAX        // Else std::min / max do not work
#include <Windows.h>


// GLFW
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

// Vulkan
#include <vulkan/vulkan.hpp>

// glm
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

// ImGui
#define IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <imgui.h>
#include <imconfig.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_vulkan.h>

// EnTT
#include "entt.hpp"

// Stb image
#include <stb_image.h>

// * yaml-cpp *
#include <yaml-cpp/yaml.h>

#pragma warning(pop)  // Restore previous warning settings

// ** Local Files **
#include "Lychee/Core/Log.h"
#include "Lychee/Core/Debug/Instrumentor.h"
#include "Lychee/Helper/Types.h"