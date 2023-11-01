/*
 * Str.hpp
 *
 *  Created on: Oct 9, 2023
 *      Author: XMF3944
 */

#ifndef _INCLUDE_FRAMEWORK_UTILS_STR_HPP_
#define _INCLUDE_FRAMEWORK_UTILS_STR_HPP_

#include <FwIncludes.hpp>

namespace Utils
{

	class Str
	{
		public:

			static uint32 GetLength( cstr value );

			static uint32 Set( str value, char ch, uint32 sizeValue );

			static uint32 Copy( str dest, uint32 sizeDest, cstr src );
			static uint32 Copy( str dest, uint32 sizeDest, cstr src, uint32 count );

			static int16 CompareTo( cstr valueA, uint32 lengthA, cstr valueB, uint32 lengthB );

			static uint32 Format( str dest, uint32 destSize, cstr format, ... );
			static int32 Arguments( str dest, uint32 destSize, cstr format, va_list args );
	};

} /* namespace Utils */

#endif /* _INCLUDE_FRAMEWORK_UTILS_STR_HPP_ */
