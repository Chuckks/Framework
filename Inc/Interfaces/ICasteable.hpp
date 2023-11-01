/*
 * ICasteable.hpp
 *
 *  Created on: Oct 2, 2023
 *      Author: XMF3944
 */

#ifndef _INCLUDE_FRAMEWORK_INTERFACES_ICASTEABLE_HPP_
#define _INCLUDE_FRAMEWORK_INTERFACES_ICASTEABLE_HPP_

#include <FwIncludes.hpp>

namespace Interfaces
{

	class ICasteable
	{
		public:

			virtual ~ICasteable( )
			{
			}

			virtual operator cstr( ) const = 0;
			virtual operator uint32( ) const = 0;
	};

} /* namespace Interfaces */

#endif /* _INCLUDE_FRAMEWORK_INTERFACES_ICASTEABLE_HPP_ */
