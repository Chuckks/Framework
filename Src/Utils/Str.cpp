/*
 * Str.cpp
 *
 *  Created on: Oct 9, 2023
 *      Author: XMF3944
 */

#include <FwIncludes.hpp>

namespace Utils
{

	uint32 Str::GetLength( cstr value )
	{
		if( value == NULL )
			ThrowException( Exception::Ex_ArgumentNull, "value" );

		uint32 length = strlen( value );

		return length;

	}

	uint32 Str::Set( str value, char ch, uint32 sizeValue )
	{
		if( value == NULL )
			ThrowException( Exception::Ex_ArgumentNull, "value" );

		memset( value, ch, sizeValue );
		return sizeValue;
	}

	uint32 Str::Copy( str dest, uint32 sizeDest, cstr src )
	{
		uint32 count = Str::GetLength( src );
		uint32 result = Str::Copy( dest, sizeDest, src, count );

		dest[ count ] = 0x00;
		return result;
	}

	uint32 Str::Copy( str dest, uint32 sizeDest, cstr src, uint32 count )
	{
		if( !dest )
			ThrowException( Exception::Ex_ArgumentNull, "dest" );

		if( !src )
			ThrowException( Exception::Ex_ArgumentNull, "src" );

		if( count > sizeDest )
			ThrowException( Exception::Ex_ArgumentOutOfRange, "count[%d] > sizeDest[%d]", count, sizeDest );

		memcpy( dest, src, count );
		return count;
	}

	int16 Str::CompareTo( cstr valueA, uint32 lengthA, cstr valueB, uint32 lengthB )
	{
		if( valueA == NULL )
			ThrowException( Exception::Ex_ArgumentNull, "valueA" );

		if( valueB == NULL )
			ThrowException( Exception::Ex_ArgumentNull, "valueB" );

		if( valueA == valueB )
			return 0;

		if( lengthA != lengthB )
		{
			if( lengthA < lengthB )
				return -1;
			else
				return 1;
		}

		return memcmp( valueA, valueB, lengthA );
	}

	uint32 Str::Format( str dest, uint32 destSize, cstr format, ... )
	{
		if( !format )
			ThrowException( Exception::Ex_ArgumentNull, "format" );

		va_list args;
		va_start( args, format );

		int32 result = Str::Arguments( dest, destSize, format, args );
		va_end( args );

		if( result < 0 )
			ThrowException( Exception::Ex_Overflow, "vsnprintf" );

		return result;
	}

	int32 Str::Arguments( str dest, uint32 destSize, cstr format, va_list args )
	{
		if( !dest )
			ThrowException( Exception::Ex_ArgumentNull, "dest" );

		if( !destSize )
			ThrowException( Exception::Ex_ArgumentNull, "destSize" );

		if( !format )
			ThrowException( Exception::Ex_ArgumentNull, "format" );

		return vsnprintf( dest, destSize + 1, format, args );
	}

} /* namespace Utils */
