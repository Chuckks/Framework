/*
 * IHashable.hpp
 *
 *  Created on: Oct 4, 2023
 *      Author: XMF3944
 */

#ifndef _INCLUDE_FRAMEWORK_INTERFACES_IIHASHABLE_HPP_
#define _INCLUDE_FRAMEWORK_INTERFACES_IIHASHABLE_HPP_

#include <FwIncludes.hpp>

namespace Interfaces
{
	class IHashable
	{
		public:

			virtual ~IHashable( )
			{
			}

			virtual uint32 GetHashCode( ) const = 0;
	};
}

#endif /* _INCLUDE_FRAMEWORK_INTERFACES_IIHASHABLE_HPP_ */
