/*
 * ICopyTo.hpp
 *
 *  Created on: Oct 2, 2023
 *      Author: XMF3944
 */

#ifndef _INCLUDE_FRAMEWORK_INTERFACES_ICOPYTO_HPP_
#define _INCLUDE_FRAMEWORK_INTERFACES_ICOPYTO_HPP_

#include <FwIncludes.hpp>

namespace Interfaces
{

	template< typename T >
	class ICopyTo
	{
		public:

			virtual ~ICopyTo( );

			virtual uint32 CopyTo( T& destination ) const = 0;
			virtual uint32 CopyTo( T& destination, uint32 length ) const = 0;

			virtual uint32 CopyTo( uint32 startIndex, T& destination ) const = 0;
			virtual uint32 CopyTo( uint32 startIndex, T& destination, uint32 length ) const = 0;
	};

} /* namespace Interfaces */

#endif /* _INCLUDE_FRAMEWORK_INTERFACES_ICOPYTO_HPP_ */
