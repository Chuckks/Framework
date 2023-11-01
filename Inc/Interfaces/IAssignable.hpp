/*
 * IAssignable.hpp
 *
 *  Created on: Oct 2, 2023
 *      Author: XMF3944
 */

#ifndef _INCLUDE_FRAMEWORK_INTERFACES_IASSIGNABLE_HPP_
#define _INCLUDE_FRAMEWORK_INTERFACES_IASSIGNABLE_HPP_

#include <FwIncludes.hpp>

namespace Interfaces
{

	template< typename T >
	class IAssignable
	{
		public:

			virtual ~IAssignable( )
			{
			}

			virtual T& operator =( const T& value ) = 0;
	};

} /* namespace Interfaces */

#endif /* _INCLUDE_FRAMEWORK_INTERFACES_IASSIGNABLE_HPP_ */
