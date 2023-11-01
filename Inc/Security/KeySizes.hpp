/*
 * KeySizes.hpp
 *
 *  Created on: Oct 18, 2023
 *      Author: XMF3944
 */

#ifndef _INCLUDE_FRAMEWORK_SECURITY_KEYSIZES_HPP_
#define _INCLUDE_FRAMEWORK_SECURITY_KEYSIZES_HPP_

#include <FwIncludes.hpp>

namespace Security
{

	class KeySizes
	{
		public:

			KeySizes( uint32 minSize, uint32 maxSize, uint32 skipSize );
			virtual ~KeySizes( );

			uint32 GetMin( ) const;
			uint32 GetMax( ) const;
			uint32 GetSkip( ) const;

		private:
			uint32 MinSize;
			uint32 MaxSize;
			uint32 SkipSize;
	};

} /* namespace Security */

#endif /* _INCLUDE_FRAMEWORK_SECURITY_KEYSIZES_HPP_ */
