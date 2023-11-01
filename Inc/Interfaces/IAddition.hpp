/*
 * IAddition.hpp
 *
 *  Created on: Oct 2, 2023
 *      Author: XMF3944
 */

#ifndef _INCLUDE_FRAMEWORK_INTERFACES_IADDITION_HPP_
#define _INCLUDE_FRAMEWORK_INTERFACES_IADDITION_HPP_

#include <FwIncludes.hpp>

namespace Interfaces
{

	template< typename T >
	class IAddition
	{
		public:

			virtual ~IAddition( )
			{
			}

			virtual T operator+( const T& value ) const = 0;
			virtual T& operator+=( const T& value ) = 0;
	};

} /* namespace Interfaces */

#endif /* _INCLUDE_FRAMEWORK_INTERFACES_IADDITION_HPP_ */
