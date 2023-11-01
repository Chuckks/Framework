/*
 * IContenible.hpp
 *
 *  Created on: Oct 2, 2023
 *      Author: XMF3944
 */

#ifndef _INCLUDE_FRAMEWORK_INTERFACES_ICONTENIBLE_HPP_
#define _INCLUDE_FRAMEWORK_INTERFACES_ICONTENIBLE_HPP_

#include <FwIncludes.hpp>

namespace Interfaces
{
	class IContenible
	{
		public:

			virtual ~IContenible( )
			{
			}

			virtual void Clean( ) = 0;

			virtual void operator*=( int32 value )
			{
				this->Clean( );
			}

			virtual bool IsEmpty( ) const = 0;

			virtual bool operator!( ) const
			{
				return this->IsEmpty( );
			}

			virtual bool IsNotEmpty( ) const
			{
				return !this->IsEmpty( );
			}
	};
}

#endif /* _INCLUDE_FRAMEWORK_INTERFACES_ICONTENIBLE_HPP_ */
