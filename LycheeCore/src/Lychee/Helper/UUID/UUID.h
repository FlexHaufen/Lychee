/**
 * @file UUID.h
 * @author flexhaufen
 * @brief UUID
 * @version 0.1
 * @date 2023-02-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

// *** INCLUDES ***
#include <xhash>

// *** NAMESPACE ***
namespace Lychee {

    /**
     * @brief UUID class
     * 
     */
    class UUID {
    public:
        UUID();
        UUID(uint64_t uuid);


        operator uint64_t() const { return m_UUID; }

    private:
        // ** Members **
        uint64_t m_UUID;         // UUID
    };
}


namespace std {
	template <typename T> struct hash;

	template<>
	struct hash<Lychee::UUID>{
		std::size_t operator()(const Lychee::UUID& uuid) const {
			return (uint64_t)uuid;
		}
	};
}
