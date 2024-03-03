/**
 * @file UUID.cpp
 * @author flexhaufen
 * @brief UUID
 * @version 0.1
 * @date 2023-02-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */

// *** INCLUDES ***
#include "Lychee/Helper/UUID/UUID.h"

#include <random>

// *** DEFINE ***

// *** NAMESPACE ***
namespace Lychee {

    static std::random_device s_RandomDevice;
    static std::mt19937_64 s_Engine(s_RandomDevice());
    static std::uniform_int_distribution<uint64_t> s_UniformDistribution;


    UUID::UUID() {
        m_UUID = s_UniformDistribution(s_Engine);
    }


    UUID::UUID(uint64_t uuid) {
        m_UUID = uuid;
    }
}