/*
 * HSM.hpp
 *
 *  Created on: Oct 16, 2023
 *      Author: XMF3944
 */

#ifndef _INCLUDE_FRAMEWORK_SECURITY_HSM_HPP_
#define _INCLUDE_FRAMEWORK_SECURITY_HSM_HPP_

#include <FwIncludes.hpp>

namespace Security
{

	class HSM
	{
		public:

			HSM( );
			~HSM( );

			bool IsKeyEmpty( EKeySlot index ) const;
			byte GetKeyLength( EKeySlot index ) const;

			Data::Buffer GetKCV( const KeyInfo& keyInfo ) const;

			void InjectClearKey( EKeySlot index, const Data::Buffer& CryptoKey);
			void InjectClearKey( const KeyInfo& keyInfo, const Data::Buffer& key ) const;
	};

} /* namespace Security */

#endif /* _INCLUDE_FRAMEWORK_SECURITY_HSM_HPP_ */
