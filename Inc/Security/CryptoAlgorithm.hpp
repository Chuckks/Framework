/*
 * CryptoAlgorithm.hpp
 *
 *  Created on: Oct 18, 2023
 *      Author: XMF3944
 */

#ifndef _INCLUDE_FRAMEWORK_SECURITY_CRYPTOALGORITHM_HPP_
#define _INCLUDE_FRAMEWORK_SECURITY_CRYPTOALGORITHM_HPP_

#include <FwIncludes.hpp>

namespace Security
{

	class CryptoAlgorithm
	{
		public:
			CryptoAlgorithm( EAlgoType algo );
			CryptoAlgorithm( const CryptoKey& key );

			virtual ~CryptoAlgorithm( );

			virtual void SetKey( const CryptoKey& key );
			virtual void SetKeySlot( EKeySlot keySlot ) = 0;

			virtual bool IsLoadKey( );

			virtual const Buffer& Encrypt( const Buffer& data ) = 0;
			virtual const Buffer& Encrypt( const String& data ) = 0;

			virtual const Buffer& Decrypt( const Buffer& data ) = 0;
			virtual const Buffer& Decrypt( const String& data ) = 0;

		protected:

			Buffer Treated;
			CryptoKey Key;
			EAlgoType Algo;
	};

} /* namespace Security */

#endif /* INC_SECURITY_CRYPTOALGORITHM_HPP_ */
