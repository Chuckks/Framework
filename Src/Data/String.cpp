/*
 * String.cpp
 *
 *  Created on: Oct 16, 2023
 *      Author: XMF3944
 */

#include <FwIncludes.hpp>

namespace Data
{

	String::String( cstr value ) :
		Value( value, Utils::Str::GetLength( value ) )
	{
	}

	String::String( char value, uint32 count ) :
		Value( value, count )
	{
	}
	String::String( cstr value, uint32 count ) :
		Value( value, count )
	{
	}

	String::String( const Buffer& value ) :
		Value( value )
	{
	}

	String::String( const Buffer& value, uint32 count ) :
		Value( value, count )
	{
	}

	String::String( uint32 startIndex, const Buffer& value ) :
		Value( startIndex, value )
	{
	}

	String::String( uint32 startIndex, const Buffer& value, uint32 count ) :
		Value( startIndex, value, count )
	{
	}

	String::String( const String& value ) :
		Value( value.Value )
	{
	}

	String::String( const String& value, uint32 count ) :
		Value( value.Value, count )
	{
	}

	String::String( uint32 startIndex, const String& value ) :
		Value( startIndex, value.Value )
	{
	}

	String::String( uint32 startIndex, const String& value, uint32 count ) :
		Value( startIndex, value.Value, count )
	{
	}

	String::~String( )
	{
	}

	//@Implement ILength
	uint32 String::GetLength( ) const
	{
		return this->Value.GetLength( );
	}

	//@Implements IContenible
	void String::Clean( )
	{
		Value.Clean( );
	}

	bool String::IsEmpty( ) const
	{
		return Value.IsEmpty( );
	}

	//@Implements ICopyTo
	uint32 String::CopyTo( String& destination ) const
	{
		return this->Value.CopyTo( destination.Value );
	}

	uint32 String::CopyTo( String& destination, uint32 length ) const
	{
		return this->Value.CopyTo( destination.Value, length );
	}

	uint32 String::CopyTo( uint32 startIndex, String& destination ) const
	{
		return this->Value.CopyTo( startIndex, destination.Value );
	}

	uint32 String::CopyTo( uint32 startIndex, String& destination, uint32 length ) const
	{
		return this->Value.CopyTo( startIndex, destination.Value, length );
	}

	//@Implements IIdexable
	char& String::operator[]( uint32 index )
	{
		if( index < 0 || index >= this->Value.GetLength( ) )
			ThrowException( Exception::Ex_IndexOutOfRange, "Index [%d] >= Length [%d]", index, this->Value.GetLength( ) );

		return this->Value[ index ];
	}

	//@Implements IAddition
	String String::operator+( const String& value ) const
	{
		return String::Format( "%s%s", this->Value.GetBytes( 0 ), value.Value.GetBytes( 0 ) );
	}

	String& String::operator+=( const String& value )
	{
		*this = Concat( *this, value );
		return *this;
	}

	//@Implement IAssignable
	String& String::operator =( const String& value )
	{
		value.CopyTo( *this );
		return *this;
	}

	int32 String::CompareTo( const String& value ) const
	{
		return this->Value.CompareTo( value.Value );
	}

	//@Own Methods
	bool String::Contains( const String& value ) const
	{
		return this->Contains( value, false );
	}

	bool String::Contains( const String& value, bool ignoreCase ) const
	{
		uint32 ownLength = this->Value.GetLength( );
		uint32 valueLength = value.Value.GetLength( );

		if( ownLength < valueLength )
			return false;

		if( ownLength == valueLength )
			String::Compare( *this, 0, value, 0, ignoreCase );

		for( uint32 index = 0; index <= ( ownLength - valueLength ); ++index )
		{
			if( String::Compare( *this, index, value, 0, valueLength, ignoreCase ) )
				return true;
		}

		return false;
	}

	bool String::EndsWith( const String& value ) const
	{
		return this->EndsWith( value, false );
	}

	bool String::EndsWith( const String& value, bool ignoreCase ) const
	{
		uint32 ownLenth = this->Value.GetLength( );
		uint32 valueLenth = value.Value.GetLength( );

		uint32 position = ownLenth - valueLenth;
		return String::Compare( *this, position, value, 0, valueLenth, ignoreCase );
	}

	cstr String::GetBytes( uint32 index ) const
	{
		return this->Value.GetBytes( index );
	}

	const Buffer& String::GetBuffer( ) const
	{
		return this->Value;
	}

	int32 String::IndexOf( char value ) const
	{
		return this->IndexOf( value, 0, this->Value.GetLength( ) );
	}

	int32 String::IndexOf( char value, uint32 startIndex ) const
	{
		return this->IndexOf( value, startIndex, this->Value.GetLength( ) - startIndex );
	}

	int32 String::IndexOf( char value, uint32 startIndex, uint32 count ) const
	{
		if( value == 0x00 )
			ThrowException( Exception::Ex_ArgumentNull, "value" );

		uint32 length = this->Value.GetLength( );

		if( startIndex > length )
			ThrowException( Exception::Ex_ArgumentOutOfRange, "startIndex[%d] > Length[%d]", startIndex, length );

		if( count > ( length - startIndex ) )
			ThrowException( Exception::Ex_ArgumentOutOfRange, "count[%d] > (length[%d] - startIndex[%d])", count, length, startIndex );

		Buffer aux = this->Value;
		for( uint32 i = startIndex; i < ( startIndex + count ); ++i )
			if( value == aux[ i ] )
				return i;

		return -1;
	}

	int32 String::IndexOf( const String& value ) const
	{
		return this->IndexOf( value, 0, value.GetLength( ) );
	}

	int32 String::IndexOf( const String& value, uint32 startIndex ) const
	{
		return this->IndexOf( value, startIndex, value.GetLength( ) );
	}

	int32 String::IndexOf( const String& value, uint32 startIndex, uint32 count ) const
	{
		uint32 thisLength = this->Value.GetLength( );

		if( startIndex > thisLength )
			ThrowException( Exception::Ex_ArgumentOutOfRange, "startIndex [%d] > Length [%d]", startIndex, thisLength );

		if( count > ( thisLength - startIndex ) )
			ThrowException( Exception::Ex_ArgumentOutOfRange, "count [%d] > ( Length [%d] - startIndex [%d] )", count, thisLength, startIndex );

		for( uint32 i = startIndex; i <= thisLength - count; ++i )
			if( Compare( *this, i, value, 0, count, true ) )
				return i;

		return -1;
	}

	int32 String::IndexOfAny( const String& value ) const
	{
		return IndexOfAny( value, 0, this->Value.GetLength( ) );
	}

	int32 String::IndexOfAny( const String& value, uint32 startIndex ) const
	{
		return IndexOfAny( value, startIndex, this->Value.GetLength( ) - startIndex );
	}

	int32 String::IndexOfAny( const String& value, uint32 startIndex, uint32 count ) const
	{
		String valueAux = value;
		Buffer thisValue = this->Value;
		uint32 length = thisValue.GetLength( );

		if( startIndex > length )
			ThrowException( Exception::Ex_ArgumentOutOfRange, "StartIndex[%d] > Length[%d]", startIndex, length );

		if( count > ( length - startIndex ) )
			ThrowException( Exception::Ex_ArgumentOutOfRange, "count[%d] > (length[%d] - startIndex[%d] )", count, length, startIndex );

		for( uint32 index = startIndex; index < ( startIndex + count ); ++index )
		{
			for( uint32 rating = 0; rating < valueAux.Value.GetLength( ); ++rating )
			{
				if( valueAux[ rating ] == thisValue[ index ] )
					return index;
			}
		}
		return -1;
	}

	String String::Insert( uint32 startIndex, const String& value ) const
	{
		uint32 length = this->Value.GetLength( );

		if( startIndex > length )
			ThrowException( Exception::Ex_ArgumentOutOfRange, "StartIndex [%d] > Length [%d]", startIndex, length );

		uint32 position = 0;
		uint32 valueLength = value.Value.GetLength( );

		Buffer insertBuffer( length + valueLength );

		position += insertBuffer.Write( position, this->Value, startIndex );
		position += insertBuffer.Write( position, value.Value, valueLength );
		position += insertBuffer.Write( position, startIndex, this->Value, length - startIndex );

		return insertBuffer;
	}

	int32 String::LastIndexOf( char value ) const
	{
		uint32 count = this->Value.GetLength( );
		return LastIndexOf( value, count - 1, count );
	}

	int32 String::LastIndexOf( char value, uint32 startIndex ) const
	{
		return LastIndexOf( value, startIndex, startIndex + 1 );
	}

	int32 String::LastIndexOf( char value, uint32 startIndex, uint32 count ) const
	{
		if( value == 0x00 )
			ThrowException( Exception::Ex_ArgumentNull, "anyOf" );

		if( startIndex > this->Value.GetLength( ) )
			ThrowException( Exception::Ex_ArgumentOutOfRange, "startIndex [%d] > this->Value.GetLength( ) [%d]", startIndex, this->Value.GetLength( ) );

		if( count > ( startIndex + 1 ) )
			ThrowException( Exception::Ex_ArgumentOutOfRange, "count [%d] > ( startIndex [%d] + 1 )", count, startIndex );

		Buffer thisValue = this->Value;
		for( uint32 i = startIndex; i != ( startIndex - count ); i-- )
		{
			if( thisValue[ i ] == value )
				return i;
		}

		return -1;
	}

	int32 String::LastIndexOfAny( const String& value ) const
	{
		uint32 length = this->Value.GetLength( );
		return this->LastIndexOfAny( value, length - 1, length );
	}

	int32 String::LastIndexOfAny( const String& value, uint32 startIndex ) const
	{
		return this->LastIndexOfAny( value, startIndex, startIndex + 1 );
	}

	int32 String::LastIndexOfAny( const String& value, uint32 startIndex, uint32 count ) const
	{
		if( startIndex > this->Value.GetLength( ) )
			ThrowException( Exception::Ex_ArgumentOutOfRange, "StartIndex[%d] > Length[%d]", startIndex, this->Value.GetLength( ) );

		if( count > ( startIndex + 1 ) )
			ThrowException( Exception::Ex_ArgumentOutOfRange, "count[%d] > (startIndex[%d] + 1 )", count, startIndex );

		Buffer thisAux = this->Value;
		String valueAux = value;

		for( uint32 index = startIndex; index != ( startIndex - count ); index-- )
		{
			for( uint32 i = 0; i < valueAux.Value.GetLength( ); ++i )
			{
				if( valueAux[ i ] == thisAux[ index ] )
					return index;
			}
		}

		return -1;
	}

	String String::PadLeft( uint32 totalWidth ) const
	{
		return this->PadLeft( totalWidth, ' ' );
	}

	String String::PadLeft( uint32 totalWidth, char paddingChar ) const
	{
		uint32 length = this->Value.GetLength( );

		if( this->Value.GetLength( ) > totalWidth )
			return this->Value;

		Buffer aux( totalWidth );
		uint32 padding = totalWidth - length;

		aux.SetChar( paddingChar, padding );
		aux.Write( padding, this->Value );

		return aux;
	}

	String String::PadRight( uint32 totalWidth ) const
	{
		return this->PadRight( totalWidth, ' ' );
	}

	String String::PadRight( uint32 totalWidth, char paddingChar ) const
	{
		uint32 length = this->Value.GetLength( );

		if( length > totalWidth )
			return this->Value;

		Buffer aux( totalWidth );
		aux.Write( 0, this->Value );
		aux.Write( length, paddingChar, totalWidth - length );

		return aux;
	}

	String String::Remove( uint32 startIndex ) const
	{
		if( startIndex > this->Value.GetLength( ) )
			ThrowException( Exception::Ex_ArgumentOutOfRange, "StartIndex [%d] > Length [%d]", startIndex, this->Value.GetLength( ) );

		Buffer removeAux( startIndex );
		removeAux.Write( 0, this->Value, startIndex );

		return removeAux;
	}

	String String::Remove( uint32 startIndex, uint32 count ) const
	{
		uint32 ownLength = this->Value.GetLength( );

		if( ownLength < ( startIndex + count ) )
			ThrowException( Exception::Ex_ArgumentOutOfRange, "Value.Length [%d] < ( startIndex [%d] + count [%d] )", this->Value.GetLength( ), startIndex, count );

		uint32 newPosition = startIndex + count;
		Buffer removeAux( ownLength - count );

		removeAux.Write( 0, this->Value, startIndex );
		removeAux.Write( startIndex, newPosition, this->Value, ownLength - newPosition );

		return removeAux;
	}

	String String::Replace( char oldValue, char newValue ) const
	{
		uint32 index = 0;
		uint32 length = this->Value.GetLength( );

		Buffer aux( length );

		for( uint32 i = 0; i < length; ++i )
		{
			char ch = this->Value.Read( i );

			if( ch == oldValue )
			{
				if( newValue )
					aux.Write( index++, newValue );
			}
			else
				aux.Write( index++, ch );
		}

		return aux;
	}

	String String::Replace( const String& oldValue, const String& newValue ) const
	{
		uint32 oldLength = oldValue.Value.GetLength( );
		uint32 newLength = newValue.Value.GetLength( );

		if( !oldLength )
			ThrowException( Exception::Ex_ArgumentInvalid, "oldValue" );

		uint32 bufferLength;
		uint32 length = this->Value.GetLength( );

		if( !newLength )
			bufferLength = oldLength;
		else
		{
			if( oldLength > newLength )
				bufferLength = oldLength;
			else
			{
				bufferLength = ( length / oldLength ) + 1;
				bufferLength *= newLength - oldLength;

				bufferLength += length;
			}
		}

		Buffer aux( bufferLength );
		uint32 indexThis = 0, indexBuffer = 0;

		while( indexThis < length )
		{
			if( ( length - indexThis ) >= oldLength )
			{
				if( Compare( *this, indexThis, oldValue, 0, oldLength, false ) )
				{
					indexThis += oldLength;

					if( newLength )
						indexBuffer += aux.Write( indexBuffer, newValue.Value, newLength );
				}
				else
					aux.Write( indexBuffer++, this->Value.Read( indexThis++ ) );
			}
			else
				aux.Write( indexBuffer++, this->Value.Read( indexThis++ ) );
		}

		return aux;
	}

	bool String::StartsWith( const String& value ) const
	{
		return Compare( *this, value, value.Value.GetLength( ), false );
	}

	bool String::StartsWith( const String& value, bool ignoreCase ) const
	{
		return Compare( *this, value, value.Value.GetLength( ), ignoreCase );
	}

	String String::Substring( uint32 startIndex ) const
	{
		uint32 length = this->Value.GetLength( );

		if( length < startIndex )
			ThrowException( Exception::Ex_ArgumentOutOfRange, "Length[%d] < startIndex[%d]", length, startIndex );

		length -= startIndex;
		Buffer aux( length );

		aux.Write( 0, startIndex, this->Value, length );
		return aux;
	}

	String String::Substring( uint32 startIndex, uint32 length ) const
	{
		if( this->Value.GetLength( ) < ( startIndex + length ) )
			ThrowException( Exception::Ex_ArgumentOutOfRange, "this->Value.GetLength()[%d] < (stratIndex[%d] < length[%d])", this->Value.GetLength( ), startIndex, length );

		Buffer aux( length );
		aux.Write( 0, startIndex, this->Value, length );

		return aux;
	}

	String String::ToLower( ) const
	{
		uint32 length = this->Value.GetLength( );

		Buffer aux( length );
		for( uint32 index = 0; index < length; ++index )
			aux.Write( index, Utils::Char::ToLower( this->Value.Read( index ) ) );

		return aux;
	}

	String String::ToUpper( ) const
	{
		uint32 length = this->Value.GetLength( );

		Buffer aux( length );
		for( uint32 index = 0; index < length; ++index )
			aux.Write( index, Utils::Char::ToUpper( this->Value.Read( index ) ) );

		return aux;
	}

	int32 String::ToInteger( ) const
	{
		return this->Value.ToInteger( );
	}

	String String::Trim( ) const
	{
		String temp = this->TrimStart( ' ' );
		return temp.TrimEnd( ' ' );
	}

	String String::Trim( const String& value ) const
	{
		String aux = this->TrimStart( value );
		return aux.TrimEnd( value );
	}

	String String::TrimEnd( char value ) const
	{
		if( value == 0x00 )
			ThrowException( Exception::Ex_ArgumentNull, "character null" );

		uint32 index;
		Buffer thisValue = this->Value;

		for( index = thisValue.GetLength( ); index != 0; index-- )
		{
			bool found = false;

			if( value == thisValue[ index - 1 ] )
				found = true;

			if( !found )
				break;
		}

		Buffer aux( index );
		aux.Write( 0, thisValue, index );

		return aux;
	}

	String String::TrimEnd( const String& value ) const
	{
		uint32 index;
		String strValue = value;
		Buffer thisBuffer = this->Value;

		for( index = thisBuffer.GetLength( ); index != 0; index-- )
		{
			bool found = false;

			for( uint32 j = 0; j < strValue.Value.GetLength( ); ++j )
			{
				if( strValue[ j ] == thisBuffer[ index - 1 ] )
					found = true;
			}

			if( !found )
				break;
		}

		Buffer aux( index );
		aux.Write( 0, thisBuffer, index );

		return aux;
	}

	String String::TrimStart( char value ) const
	{
		if( value == 0x00 )
			ThrowException( Exception::Ex_ArgumentNull, "character null" );

		uint32 index = 0;
		Buffer thisBuffer = this->Value;

		for( index = 0; index < this->Value.GetLength( ); ++index )
		{
			bool found = false;

			if( value == thisBuffer[ index ] )
				found = true;

			if( !found )
				break;
		}

		uint32 newLength = thisBuffer.GetLength( ) - 1;

		Buffer aux( newLength );
		aux.Write( 0, index, thisBuffer, newLength );

		return aux;

	}

	String String::TrimStart( const String& value ) const
	{
		uint32 i, j = 0;
		String strValue = value;
		Buffer thisBuffer = this->Value;

		for( i = 0; i < this->Value.GetLength( ); ++i )
		{
			bool found = false;

			for( j = 0; j < value.Value.GetLength( ); ++j )
			{
				if( strValue.Value[ j ] == thisBuffer[ i ] )
				{
					found = true;
					break;
				}
			}

			if( !found )
				break;
		}

		uint32 newLength = this->Value.GetLength( );
		Buffer aux( newLength );

		aux.Write( 0, i, this->Value, newLength );
		return aux;
	}

	//@Static Methods
	bool String::Compare( const String& valueA, const String& valueB )
	{
		return Buffer::Compare( valueA.Value, valueB.Value );
	}

	bool String::Compare( const String& valueA, const String& valueB, bool ignoreCase )
	{
		return Buffer::Compare( valueA.Value, valueB.Value, ignoreCase );
	}

	bool String::Compare( const String& valueA, const String& valueB, uint32 count )
	{
		return Buffer::Compare( valueA.Value, valueB.Value, count );
	}

	bool String::Compare( const String& valueA, const String& valueB, uint32 count, bool ignoreCase )
	{
		return Buffer::Compare( valueA.Value, valueB.Value, count, ignoreCase );
	}

	bool String::Compare( const String& valueA, uint32 indexA, const String& valueB, uint32 indexB, uint32 count )
	{
		return Buffer::Compare( valueA.Value, indexA, valueB.Value, indexB, count );
	}

	bool String::Compare( const String& valueA, uint32 indexA, const String& valueB, uint32 indexB, uint32 count, bool ignoreCase )
	{
		return Buffer::Compare( valueA.Value, indexA, valueB.Value, indexB, count, ignoreCase );
	}

	String String::Concat( const String& valueA, const String& valueB )
	{
		return Buffer::Concat( valueA.Value, valueB.Value );
	}

	String String::Format( cstr format, ... )
	{
		Buffer StrBuffer( Defines::KbSize );

		if( !format )
			ThrowException( Exception::Ex_ArgumentNull, "format" );

		va_list args;
		va_start( args, format );

		StrBuffer.AddArguments( format, args );
		va_end( args );

		return StrBuffer;
	}

} /* namespace Data */
