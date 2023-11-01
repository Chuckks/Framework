/*
 * IComparison.hpp
 *
 *  Created on: Oct 2, 2023
 *      Author: XMF3944
 */

#ifndef _INCLUDE_FRAMEWORK_INTERFACES_ICOMPARISON_HPP_
#define _INCLUDE_FRAMEWORK_INTERFACES_ICOMPARISON_HPP_

#include <FwIncludes.hpp>

namespace Interfaces
{
	template< typename T >
	class IComparison:
	                  public IComparable< T >,
	                  public IEqualitable< T >,
	                  public IGreatThan< T >,
	                  public ILessThan< T >
	{
		public:

			virtual ~IComparison( )
			{
			}

			//@Implements IComparable
			virtual int32 CompareTo( const T& value ) const = 0;

			//@Implements IEqualitable
			virtual bool operator==( const T& value ) const
			{
				return ( this->CompareTo( value ) == 0 );
			}

			virtual bool operator !=( const T& value ) const
			{
				return ( this->CompareTo( value ) != 0 );
			}

			//@Implements IGreatThan
			virtual bool operator >( const T& value ) const
			{
				return ( this->CompareTo( value ) > 0 );
			}

			virtual bool operator >=( const T& value ) const
			{
				return ( this->CompareTo( value ) >= 0 );
			}

			//@Implements ILessThan
			virtual bool operator <( const T& value ) const
			{
				return ( this->CompareTo( value ) < 0 );
			}

			virtual bool operator <=( const T& value ) const
			{
				return ( this->CompareTo( value ) <= 0 );
			}

	};

} /* namespace Interfaces */

#endif /* _INCLUDE_FRAMEWORK_INTERFACES_ICOMPARISON_HPP_ */
