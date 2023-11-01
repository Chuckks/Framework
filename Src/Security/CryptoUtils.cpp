/*
 * CryptoUtils.cpp
 *
 *  Created on: Oct 17, 2023
 *      Author: XMF3944
 */

#include <FwIncludes.hpp>

namespace Security
{

	static const byte RandomBuffSize = 8;

	Buffer CryptoUtils::GenerateRandom( uint32 length )
	{
		if( !length )
			ThrowException( Exception::Ex_ArgumentInvalid, "Lenght Set [%d]", length );

		byte random[ RandomBuffSize ];
		uint32 index = 0, lengthCopy;

		Buffer result( length );
		while( index < length )
		{
			//::GenerateRandom( random );
			if( index + RandomBuffSize < length )
				lengthCopy = RandomBuffSize;
			else
				lengthCopy = length - index;

			index += result.Write( index, cstr( random ), lengthCopy );
		}

		return result;
	}

	uint32 CryptoUtils::GenerateRandomNumber( )
	{
		return rand( );
	}

	Buffer CryptoUtils::AjustParity( const Buffer& value, EParityKey parity )
	{
		uint32 valueLength = value.GetLength( );
		Buffer result( valueLength );

		for( uint32 index = 0; index < valueLength; ++index )
		{
			char b = value.Read( index );
			char c = ( ( b & 0xfe ) | ( ( ( b >> 1 ) ^ ( b >> 2 ) ^ ( b >> 3 ) ^ ( b >> 4 ) ^ ( b >> 5 ) ^ ( b >> 6 ) ^ ( b >> 7 ) ^ char( parity ) ) & 0x01 ) );
			result.Write( index, c );
		}

		return result;
	}

} /* namespace Security */
