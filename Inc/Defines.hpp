/*
 * Defines.hpp
 *
 *  Created on: Sep 22, 2023
 *      Author: XMF3944
 */

#ifndef _INCLUDE_FRAMEWORK_DEFINES_HPP_
#define _INCLUDE_FRAMEWORK_DEFINES_HPP_

//@Signed
typedef signed char sbyte;
typedef short int16;
typedef int int32;
typedef long long int64;

//@Unsigned
typedef unsigned char byte;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

//@char
typedef char* str;
typedef const char* cstr;

//@Floating
typedef float single;

class Defines
{
	public:
		static const uint32 KbSize = 1024;
		static const uint32 MbSize = 1024 * KbSize;
		static const uint32 GbSize = 1024 * MbSize;

		static const byte BitsPerByte = 8;

};

#endif /* _INCLUDE_FRAMEWORK_DEFINES_HPP_ */
