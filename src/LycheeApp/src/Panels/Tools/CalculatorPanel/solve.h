/**
 * @file solve.h
 * @author flexhaufen
 * @brief Solve for calculator
 * @version 0.1
 * @date 2022-09-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

//*** INCLUDES ***
#include <cmath>
#include "Lychee/lypch.h"


/**
 * @brief 
 * 
 * @param eq    input equation
 * @param start start of string
 * @param end   end of string
 * @param vars  pointer to input
 * @return f32  solved equation as f32
 */
f32 CalcSolve(const c8* eq,c8 start,c8 end,const f32* vars = nullptr);

/**
 * @brief Reverse a c-sring
 * 
 * @param string    Input string
 * @param length    Input string length
 * @return c8*      Reversed string 
 */
c8* reverseString(const c8* string,c8 length);