/*
 * Char.cpp
 *
 *  Created on: Oct 19, 2023
 *      Author: XMF3944
 */

#include <FwIncludes.hpp>

namespace Utils
{

	bool Char::IsControl( char value )
	{
		return ( iscntrl( value ) != 0 );
	}

	bool Char::IsHexaDigit( char value )
	{
		return ( isxdigit( value ) != 0 );
	}

	bool Char::IsLetter( char value )
	{
		return ( isalpha( value ) != 0 );
	}

	bool Char::IsNumber( char value )
	{
		return ( isdigit( value ) != 0 );
	}

	bool Char::IsLetterOrNumber( char value )
	{
		return ( isalnum( value ) != 0 );
	}

	bool Char::IsLower( char value )
	{
		return ( islower( value ) != 0 );
	}

	bool Char::IsUpper( char value )
	{
		return ( isupper( value ) != 0 );
	}

	bool Char::IsWhiteSpace( char value )
	{
		return ( isspace( value ) != 0 );
	}

	char Char::ToLower( char value )
	{
		return tolower( value );
	}

	char Char::ToUpper( char value )
	{
		return toupper( value );
	}

	//@ -> return 0x01  value: '1'
	byte Char::ToHexa( char value )
	{
		if( value >= 0x41 )
			return ( ( value - 7 ) & 0x0F );
		else
			return ( value & 0x0F );
	}

	//@ -> return '1'  value: 0x01
	char Char::HexaToChar( byte value )
	{
		if( value > 0x09 )
			return value + 0x37;
		else
			return value + 0x30;
	}

} /* namespace Utils */
