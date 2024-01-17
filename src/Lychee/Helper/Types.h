#include <cstdint>

#pragma once

// *** CUSTOM TYPE DEFINTIONS ***

// unsigned
typedef uint8_t         u8;
typedef uint16_t        u16;
typedef uint32_t        u32;
typedef uint64_t        u64;

// signed
typedef int8_t          s8;
typedef int16_t         s16;
typedef int32_t         s32;
typedef int64_t         s64;

// floatingpoints
typedef float           f32;
typedef double          f64;
typedef long double     f128;

// boolean
typedef bool            b8;

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


/**
 * @brief 2D vector
 * 
 */
struct v2f {
    f32 x;
    f32 y;

    // ** Operator Overloading **
    inline v2f operator+ (const v2f& a) const { return {x + a.x, y + a.y}; }
    inline v2f operator- (const v2f& a) const { return {x - a.x, y - a.y}; }
    inline v2f operator* (const v2f& a) const { return {x * a.x, y * a.y}; }
    inline v2f operator/ (const v2f& a) const { return {x / a.x, y / a.y}; }
    inline v2f operator= (const v2f& a)       { x = a.x; y = a.y; return a; }
    inline bool operator== (const v2f& a) const { return (x == a.x && y == a.y); }
};

/**
 * @brief 3D Vector
 * 
 * @tparam T type of vector
 */
template <typename T>
struct v3 {
    T x;
    T y;
    T z;

    // ** Operator Overloading **
    inline v3<T> operator+ (const v3<T>& a) const { return {x + a.x, y + a.y, z + a.z}; }
    inline v3<T> operator- (const v3<T>& a) const { return {x - a.x, y - a.y, z - a.z}; }
    inline v3<T> operator* (const v3<T>& a) const { return {x * a.x, y * a.y, z * a.z}; }
    inline v3<T> operator/ (const v3<T>& a) const { return {x / a.x, y / a.y, z / a.z}; }
    inline v3<T> operator= (const v3<T>& a)       { x = a.x; y = a.y; z = a.z; return a; }
    inline bool operator== (const v3<T>& a) const { return (x == a.x && y == a.y && z == a.z); }
};

/**
 * @brief 4D Vector
 * 
 * @tparam T type of vector
 */
template <typename T>
struct v4 {
    T w;
    T x;
    T y;
    T z;
    
    // ** Operator Overloading **
    inline v4<T> operator+ (const v4<T>& a) const { return {w + a.w, x + a.x, y + a.y, z + a.z}; }
    inline v4<T> operator- (const v4<T>& a) const { return {w - a.w, x - a.x, y - a.y, z - a.z}; }
    inline v4<T> operator* (const v4<T>& a) const { return {w * a.w, x * a.x, y * a.y, z * a.z}; }
    inline v4<T> operator/ (const v4<T>& a) const { return {w / a.w, x / a.x, y / a.y, z / a.z}; }
    inline v4<T> operator= (const v4<T>& a)       { w = a.w; x = a.x; y = a.y; z = a.z; return a; }
    inline bool operator== (const v4<T>& a) const { return (w == a.w && x == a.x && y == a.y && z == a.z); }
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