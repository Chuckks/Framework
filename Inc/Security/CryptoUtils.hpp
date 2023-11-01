/*
 * CryptoUtils.hpp
 *
 *  Created on: Oct 17, 2023
 *      Author: XMF3944
 */

#ifndef _INCLUDE_FRAMEWORK_SECURITY_CRYPTOUTILS_HPP_
#define _INCLUDE_FRAMEWORK_SECURITY_CRYPTOUTILS_HPP_

#include <FwIncludes.hpp>

namespace Security
{

	class CryptoUtils
	{
		public:

			static Buffer GenerateRandom( uint32 length );
			static uint32 GenerateRandomNumber( );

			static Buffer AjustParity( const Buffer& value, EParityKey parity );

		private:

			static String StrResult;
			static Buffer BuffResult;
	};

} /* namespace Security */

#endif /* _INCLUDE_FRAMEWORK_SECURITY_CRYPTOUTILS_HPP_ */
