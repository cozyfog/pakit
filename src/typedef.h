/* date = July 5th 2023 8:31 am */

#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <array>
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

using std::array;
using std::string;
using std::map;
using std::vector;

extern "C" {
	typedef int8_t         i8;
	typedef int16_t        i16;
	typedef int32_t        i32;
	typedef int64_t        i64;
	
	typedef uint8_t        u8;
	typedef uint16_t       u16;
	typedef uint32_t       u32;
	typedef uint64_t       u64;
	
	typedef float          f32;
	typedef double         f64;
}

#endif //TYPEDEF_H
