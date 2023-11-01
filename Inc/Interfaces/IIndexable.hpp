/*
 * IIndexable.hpp
 *
 *  Created on: Oct 2, 2023
 *      Author: XMF3944
 */

#ifndef INC_INTERFACES_IINDEXABLE_HPP_
#define INC_INTERFACES_IINDEXABLE_HPP_

#include <FwIncludes.hpp>

namespace Interfaces
{

	template< typename T >
	class IIndexable
	{
		public:

			virtual ~IIndexable( )
			{
			}

			virtual T& operator[]( uint32 index ) = 0;
	};

} /* namespace Interfaces */

#endif /* INC_INTERFACES_IINDEXABLE_HPP_ */
