/*
 * Char.hpp
 *
 *  Created on: Oct 19, 2023
 *      Author: XMF3944
 */

#ifndef _INCLUDE_FRAMEWORK_UTILS_CHAR_HPP_
#define _INCLUDE_FRAMEWORK_UTILS_CHAR_HPP_

#include <FwIncludes.hpp>

namespace Utils
{

	class Char
	{
		public:

			static bool IsControl( char value );
			static bool IsHexaDigit( char value );

			static bool IsLetter( char value );
			static bool IsNumber( char value );

			static bool IsLetterOrNumber( char value );

			static bool IsLower( char value );
			static bool IsUpper( char value );

			static bool IsWhiteSpace( char value );

			static char ToLower( char value );
			static char ToUpper( char value );

			//@ -> return 0x01  value: '1'
			static byte ToHexa( char value );

			//@ -> return '1'  value: 0x01
			static char HexaToChar( byte value );
	};

} /* namespace Utils */

#endif /* _INCLUDE_FRAMEWORK_UTILS_CHAR_HPP_ */
