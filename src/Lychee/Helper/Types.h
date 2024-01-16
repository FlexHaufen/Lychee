#include <cstdint>

#pragma once

// *** CUSTOM TYPE DEFINTIONS ***

// unsigned
typedef uint8_t         u8;
typedef uint16_t        u16;
typedef uint32_t        u32;
typedef uint64_t        u64;

// signed
typedef char            c8;

typedef int8_t          s8;
typedef int16_t         s16;
typedef int32_t         s32;
typedef int64_t         s64;

// floatingpoints
typedef float           f32;
typedef double          f64;
typedef long double     f128;

/**
 * @brief 2D vector
 * 
 * @tparam T type of vector
 */
template <typename T>
struct v2{
    T x;
    T y;

    // ** Operator Overloading **
    inline v2<T> operator+ (const v2<T>& a) const { return {x + a.x, y + a.y}; }
    inline v2<T> operator- (const v2<T>& a) const { return {x - a.x, y - a.y}; }
    inline v2<T> operator* (const v2<T>& a) const { return {x * a.x, y * a.y}; }
    inline v2<T> operator/ (const v2<T>& a) const { return {x / a.x, y / a.y}; }
    inline v2<T> operator= (const v2<T>& a)       { x = a.x; y = a.y; return a; }
    inline bool operator== (const v2<T>& a) const { return (x == a.x && y == a.y); }
};


#define LY_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace Lychee {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}