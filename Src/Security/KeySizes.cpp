/*
 * KeySizes.cpp
 *
 *  Created on: Oct 18, 2023
 *      Author: XMF3944
 */

#include <FwIncludes.hpp>

namespace Security
{

	KeySizes::KeySizes( uint32 minSize, uint32 maxSize, uint32 skipSize ) :
		MinSize( minSize ),
		MaxSize( maxSize ),
		SkipSize( skipSize )
	{
	}

	KeySizes::~KeySizes( )
	{
	}

	uint32 KeySizes::GetMin( ) const
	{
		return this->MinSize;
	}

	uint32 KeySizes::GetMax( ) const
	{
		return this->MaxSize;
	}

	uint32 KeySizes::GetSkip( ) const
	{
		return this->SkipSize;
	}

} /* namespace Security */
