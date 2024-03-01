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
#include "Lychee/lypch.h"

#include <xhash>

// *** DEFINES ***


// *** NAMESPACE ***
namespace Lychee {

    /**
     * @brief UUID class
     * 
     */
    class UUID {
    public:
        UUID();
        UUID(u64 uuid);


        operator u64() const { return m_UUID; }

    private:
        // ** Members **
        u64 m_UUID;         // UUID
    };
}


namespace std {
	template <typename T> struct hash;

	template<>
	struct hash<Lychee::UUID>{
		std::size_t operator()(const Lychee::UUID& uuid) const {
			return (u64)uuid;
		}
	};
}
