/*
 * IGreatThan.hpp
 *
 *  Created on: Oct 2, 2023
 *      Author: XMF3944
 */

#ifndef _INCLUDE_FRAMEWORK_INTERFACES_IGREATTHAN_HPP_
#define _INCLUDE_FRAMEWORK_INTERFACES_IGREATTHAN_HPP_

#include <FwIncludes.hpp>

namespace Interfaces
{

	template< typename T >
	class IGreatThan
	{
		public:

			virtual ~IGreatThan( )
			{
			}

			virtual bool operator >( const T& value ) const = 0;
			virtual bool operator >=( const T& value ) const = 0;
	};

} /* namespace Interfaces */

#endif /* _INCLUDE_FRAMEWORK_INTERFACES_IGREATTHAN_HPP_ */
