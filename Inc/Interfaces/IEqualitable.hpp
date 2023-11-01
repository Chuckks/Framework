/*
 * IEqualitable.hpp
 *
 *  Created on: Oct 2, 2023
 *      Author: XMF3944
 */

#ifndef _INCLUDE_FRAMEWORK_INTERFACES_IEQUALITABLE_HPP_
#define _INCLUDE_FRAMEWORK_INTERFACES_IEQUALITABLE_HPP_

#include <FwIncludes.hpp>

namespace Interfaces
{
	template< typename T >
	class IEqualitable
	{
		public:

			virtual ~IEqualitable( )
			{
			}

			virtual bool operator==( const T& value ) const = 0;

			virtual bool operator!=( const T& value ) const
			{
				return ( this->operator==( value ) != true );
			}
	};
}

#endif /* _INCLUDE_FRAMEWORK_INTERFACES_IEQUALITABLE_HPP_ */
