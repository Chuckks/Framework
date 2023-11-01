/*
 * IComparable.hpp
 *
 *  Created on: Oct 2, 2023
 *      Author: XMF3944
 */

#ifndef _INCLUDE_FRAMEWORK_INTERFACES_ICOMPARABLE_HPP_
#define _INCLUDE_FRAMEWORK_INTERFACES_ICOMPARABLE_HPP_

#include <FwIncludes.hpp>

namespace Interfaces
{

	template< typename T >
	class IComparable
	{
		public:

			virtual ~IComparable( )
			{
			}

			virtual int32 CompareTo( const T& value ) const = 0;
	};

} /* namespace Interfaces */

#endif /* _INCLUDE_FRAMEWORK_INTERFACES_ICOMPARABLE_HPP_ */
