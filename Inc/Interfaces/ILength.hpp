/*
 * ILength.hpp
 *
 *  Created on: Oct 2, 2023
 *      Author: XMF3944
 */

#ifndef _INCLUDE_FRAMEWORK_INTERFACES_ILENGTH_HPP_
#define _INCLUDE_FRAMEWORK_INC_INTERFACES_ILENGTH_HPP_

#include <FwIncludes.hpp>

namespace Interfaces
{
	class ILength
	{
		public:
			virtual ~ILength( )
			{
			}

			virtual uint32 GetLength( ) const = 0;
	};
}

#endif /* _INCLUDE_FRAMEWORK_INTERFACES_ILENGTH_HPP_ */
