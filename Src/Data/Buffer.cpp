/*
 * Buffer.cpp
 *
 *  Created on: Oct 4, 2023
 *      Author: XMF3944
 */

#include <FwIncludes.hpp>

namespace Data
{

	static const char DefaultChar = 0x00;
	static const str DefaultValue = NULL;

	static const uint32 DefaultSize = 0;
	static const uint32 DefaultLength = 0;

	//@Globals
	const uint32 Buffer::MaxSize = Defines::MbSize;
	const Buffer Buffer::Empty;

	Buffer::Buffer( uint32 size ) :
		Value( DefaultValue ),
		Size( DefaultSize ),
		Length( DefaultLength )
	{
		this->Resize( size );
	}

	Buffer::Buffer( cstr value, uint32 count ) :
		Value( DefaultValue ),
		Size( DefaultSize ),
		Length( DefaultLength )
	{
		this->Resize( count );
		this->Write( 0, value, count );
	}

	Buffer::Buffer( char value, uint32 count ) :
		Value( DefaultValue ),
		Size( DefaultSize ),
		Length( DefaultLength )
	{
		this->Resize( count );
		this->SetChar( value );
	}

	Buffer::Buffer( const Buffer& value ) :
		Value( DefaultValue ),
		Size( DefaultSize ),
		Length( DefaultLength )
	{
		value.CopyTo( *this );
	}

	Buffer::Buffer( const Buffer& value, uint32 count ) :
		Value( DefaultValue ),
		Size( DefaultSize ),
		Length( DefaultLength )
	{
		value.CopyTo( *this, count );
	}

	Buffer::Buffer( uint32 startIndex, const Buffer& value ) :
		Value( DefaultValue ),
		Size( DefaultSize ),
		Length( DefaultLength )
	{
		value.CopyTo( startIndex, *this );
	}

	Buffer::Buffer( uint32 startIndex, const Buffer& value, uint32 count ) :
		Value( DefaultValue ),
		Size( DefaultSize ),
		Length( DefaultLength )
	{
		value.CopyTo( startIndex, *this, count );
	}

	Buffer::~Buffer( )
	{
		if( this->Value != DefaultValue )
			delete[ ] this->Value;
	}

	//@Implements ILength
	uint32 Buffer::GetLength( ) const
	{
		return this->Length;
	}

	//@Implements IContenible
	void Buffer::Clean( )
	{
		this->CheckValue( );
		this->SetChar( DefaultChar );

		this->SetLength( DefaultLength );
		this->Value[ this->GetLength( ) ] = DefaultChar;

	}

	bool Buffer::IsEmpty( ) const
	{
		return !this->GetLength( );
	}

	uint32 Buffer::CopyTo( Buffer& destination ) const
	{
		return this->CopyTo( 0, destination, this->GetLength( ) );
	}

	uint32 Buffer::CopyTo( Buffer& destination, uint32 length ) const
	{
		return this->CopyTo( 0, destination, length );
	}

	uint32 Buffer::CopyTo( uint32 startIndex, Buffer& destination ) const
	{
		this->ValidateByLength( startIndex );
		return this->CopyTo( startIndex, destination, this->GetLength( ) - startIndex );
	}

	uint32 Buffer::CopyTo( uint32 startIndex, Buffer& destination, uint32 length ) const
	{
		if( this != &destination )
		{
			this->CheckValue( );
			this->ValidateByLength( startIndex, length );

			destination.CheckCapacity( length );

			destination.SetLength( Utils::Str::Copy( destination.Value, destination.GetSize( ), this->Value + startIndex, length ) );
			return destination.GetLength( );
		}
		//else
		//TODO agregar Logger

		return false;
	}

	char& Buffer::operator[]( uint32 index )
	{
		this->ValidateBySize( index );

		if( this->GetLength( ) < ( index + 1 ) )
			this->SetLength( index + 1 );

		return this->Value[ index ];
	}

	//@Implement IAddition
	Buffer Buffer::operator+( const Buffer& value ) const
	{
		Buffer newBuffer( this->GetLength( ) + value.GetLength( ) );

		newBuffer.Write( 0, this->Value, this->GetLength( ) );
		newBuffer.Write( this->GetLength( ), value, value.GetLength( ) );

		return newBuffer;
	}

	Buffer& Buffer::operator+=( const Buffer& value )
	{
		return *this = Buffer::Concat( *this, value );
	}

	//@Implement IAssignable
	Buffer& Buffer::operator =( const Buffer& value )
	{
		value.CopyTo( *this );
		return *this;
	}

	int32 Buffer::CompareTo( const Buffer& value ) const
	{
		return Utils::Str::CompareTo( this->Value, this->GetLength( ), value.Value, value.GetLength( ) );
	}

	//@Own Methods
	void Buffer::Resize( uint32 newSize )
	{
		if( newSize > MaxSize )
			ThrowException( Exception::Ex_ArgumentOutOfRange, "New Size [%d] > Buffer::MaxSize [%d]", newSize, Buffer::MaxSize );

		if( ( this->GetSize( ) != newSize ) || ( newSize == 0 ) )
		{
			if( this->Value != NULL )
			{
				delete[ ] this->Value;
				this->Value = NULL;
			}

			this->SetSize( newSize );
			this->SetLength( DefaultLength );

			this->Value = new char[ this->GetSize( ) + 1 ];

			if( this->Value == NULL )
				ThrowException( Exception::Ex_OutOfMemory, "Size [%d]", newSize );
		}

		this->Clean( );

	}
	void Buffer::CheckCapacity( uint32 minSize )
	{
		if( this->GetSize( ) < minSize )
			this->Resize( minSize );
		else
			this->Clean( );
	}

	uint32 Buffer::Add( char value )
	{
		return this->Write( this->GetLength( ), value );
	}
	uint32 Buffer::Add( char value, uint32 count )
	{
		return this->Write( this->GetLength( ), value, count );
	}

	uint32 Buffer::Add( const Buffer& value )
	{
		return this->Write( this->GetLength( ), value );
	}

	uint32 Buffer::Add( const Buffer& value, uint32 count )
	{
		return this->Write( this->GetLength( ), value, count );
	}

	uint32 Buffer::Add( uint32 startIndex, const Buffer& value )
	{
		return this->Write( this->GetLength( ), startIndex, value );
	}

	uint32 Buffer::Add( uint32 startIndex, const Buffer& value, uint32 count )
	{
		return this->Write( this->GetLength( ), startIndex, value, count );
	}

	uint32 Buffer::Add( cstr value )
	{
		if( !value )
			ThrowException( Exception::Ex_ArgumentNull, "value" );

		return this->Write( this->GetLength( ), value, Str::GetLength( value ) );
	}

	uint32 Buffer::Add( cstr value, uint32 count )
	{
		return this->Write( this->GetLength( ), value, count );
	}

	uint32 Buffer::AddArguments( cstr format, va_list arg )
	{
		return this->WriteArguments( this->GetLength( ), format, arg );
	}

	uint32 Buffer::GetSize( ) const
	{
		return this->Size;
	}

	cstr Buffer::GetBytes( uint32 index ) const
	{
		this->CheckValue( );
		this->ValidateBySize( index );

		return this->Value + index;
	}

	void Buffer::Remove( uint32 startIndex )
	{
		this->CheckValue( );
		this->ValidateByLength( startIndex );

		uint32 length = this->GetLength( ) - this->Write( startIndex, DefaultChar, this->GetLength( ) - startIndex );
		this->SetLength( length );
	}

	char Buffer::Read( uint32 offset ) const
	{
		this->CheckValue( );
		this->ValidateByLength( offset );

		return this->Value[ offset ];

	}

	uint32 Buffer::Read( uint32 offset, Buffer& value, uint32 count ) const
	{
		return this->Read( offset, 0, value, count );
	}

	uint32 Buffer::Read( uint32 offset, uint32 startvalue, Buffer& value, uint32 count ) const
	{
		this->CheckValue( );
		this->ValidateByLength( offset, count );

		return value.Write( startvalue, this->Value + offset, count );
	}

	uint32 Buffer::Read( uint32 offset, str value, uint32 count ) const
	{
		return this->Read( offset, value, count, count );
	}

	uint32 Buffer::Read( uint32 offset, str value, uint32 valueSize, uint32 count ) const
	{
		this->CheckValue( );
		this->ValidateBySize( offset, count );

		return Utils::Str::Copy( value, valueSize, this->Value + offset, count );
	}

	uint32 Buffer::SetChar( char value )
	{
		return this->Write( 0, value, this->GetSize( ) );
	}

	uint32 Buffer::SetChar( char value, uint32 count )
	{
		return this->Write( 0, value, count );
	}

	int32 Buffer::SearchChar( char value ) const
	{
		return this->SearchChar( 0, value, this->GetLength( ) );
	}

	int32 Buffer::SearchChar( char value, uint32 count ) const
	{
		this->ValidateByLength( count );
		return this->SearchChar( 0, value, count );
	}

	int32 Buffer::SearchChar( uint32 startIndex, char value ) const
	{
		this->ValidateByLength( startIndex );
		return this->SearchChar( startIndex, value, this->GetLength( ) - startIndex );
	}

	int32 Buffer::SearchChar( uint32 startIndex, char value, uint32 count ) const
	{
		this->CheckValue( );
		this->ValidateByLength( startIndex, count );

		for( uint32 index = startIndex; index < count; ++index )
		{
			if( this->Value[ index ] == value )
				return index;
		}

		return -1;
	}

	int32 Buffer::SearchAnyChar( const Buffer& value ) const
	{
		return this->SearchAnyChar( 0, value, value.GetLength( ) );
	}

	int32 Buffer::SearchAnyChar( const Buffer& value, uint32 count ) const
	{
		this->ValidateByLength( count );
		return this->SearchAnyChar( 0, value, count );
	}

	int32 Buffer::SearchAnyChar( uint32 startIndex, const Buffer& value ) const
	{
		this->ValidateByLength( startIndex );
		return this->SearchAnyChar( startIndex, value, this->GetLength( ) - startIndex );
	}

	int32 Buffer::SearchAnyChar( uint32 startIndex, const Buffer& value, uint32 count ) const
	{
		this->ValidateByLength( startIndex, count );

		Buffer aux = value;
		uint32 finalIndex = startIndex + count;

		for( uint32 index = startIndex; index < finalIndex; ++index )
		{
			char ch = this->Value[ index ];

			for( uint32 indexAny = 0; indexAny < value.GetLength( ); ++indexAny )

				if( ch == aux[ indexAny ] )
					return index;
		}

		return -1;
	}

	uint32 Buffer::Write( uint32 offset, char value )
	{
		return this->Write( offset, &value, sizeof( value ) );
	}

	uint32 Buffer::Write( uint32 offset, char value, uint32 count )
	{
		this->CheckValue( );
		this->ValidateBySize( offset, count );

		Str::Set( this->Value + offset, value, count );

		if( ( offset + count ) > this->GetLength( ) )
			this->SetLength( offset + count );

		return count;
	}

	uint32 Buffer::Write( uint32 offset, const Buffer& value )
	{
		return this->Write( offset, 0, value, value.GetLength( ) );
	}

	uint32 Buffer::Write( uint32 offset, const Buffer& value, uint32 count )
	{
		value.ValidateByLength( count );
		return this->Write( offset, 0, value, count );
	}

	uint32 Buffer::Write( uint32 offset, uint32 startIndex, const Buffer& value )
	{
		value.ValidateByLength( startIndex );
		return this->Write( offset, startIndex, value, value.GetLength( ) - startIndex );
	}

	uint32 Buffer::Write( uint32 offset, uint32 startIndex, const Buffer& value, uint32 count )
	{
		value.ValidateByLength( startIndex, count );
		return this->Write( offset, value.Value + startIndex, count );
	}

	uint32 Buffer::Write( uint32 offset, cstr value )
	{
		return this->Write( offset, value, Str::GetLength( value ) );
	}

	uint32 Buffer::Write( uint32 offset, cstr value, uint32 count )
	{
		if( !value )
			ThrowException( Exception::Ex_ArgumentNull, "value" );

		this->CheckValue( );
		this->ValidateBySize( offset, count );

		if( this->Length < ( offset + count ) )
			this->SetLength( offset + count );

		return Str::Copy( this->Value + offset, this->GetSize( ) - offset, value, count );
	}

	uint32 Buffer::WriteFormat( uint32 offset, cstr format, ... )
	{
		if( !format )
			ThrowException( Exception::Ex_ArgumentNull, "format" );

		va_list args;
		va_start( args, format );

		uint32 ret = this->WriteArguments( offset, format, args );
		va_end( args );

		return ret;
	}

	uint32 Buffer::WriteArguments( uint32 offset, cstr format, va_list arg )
	{
		if( !format )
			ThrowException( Exception::Ex_ArgumentNull, "format" );

		this->CheckValue( );
		int32 buffLength = Utils::Str::Arguments( this->Value + offset, this->GetSize( ) - offset, format, arg );

		if( buffLength < 0 )
			ThrowException( Exception::Ex_System, "Returned [%d] ", buffLength );

		this->ValidateBySize( offset, buffLength );

		if( this->GetLength( ) < ( offset + buffLength ) )
			this->SetLength( offset + buffLength );

		return buffLength;
	}

	int32 Buffer::ToInteger( ) const
	{
		return atol( this->Value );
	}

	Buffer Buffer::SubBuffer( uint32 startIndex ) const
	{
		return Buffer( startIndex, *this );
	}

	Buffer Buffer::SubBuffer( uint32 startIndex, uint32 count ) const
	{
		return Buffer( startIndex, *this, count );
	}

//@Static Methods
	Buffer Buffer::Concat( const Buffer& valueA, const Buffer& valueB )
	{
		Buffer newBuffer( valueA.GetLength( ) + valueB.GetLength( ) );

		newBuffer.Write( 0, valueA );
		newBuffer.Write( valueA.GetLength( ), valueB );

		return newBuffer;
	}

	Buffer Buffer::Format( cstr format, ... )
	{
		Buffer aux( Defines::KbSize );

		if( format == NULL )
			ThrowException( Exception::Ex_ArgumentNull, "format" );

		va_list arguments;
		va_start( arguments, format );

		aux.WriteArguments( 0, format, arguments );

		va_end( arguments );
		return aux;
	}

	bool Buffer::Compare( const Buffer& valueA, const Buffer& valueB )
	{
		if( valueA.GetLength( ) != valueB.GetLength( ) )
			return false;

		return Compare( valueA, 0, valueB, 0, valueA.GetLength( ), false );
	}

	bool Buffer::Compare( const Buffer& valueA, const Buffer& valueB, bool ignoreCase )
	{

		if( valueA.GetLength( ) != valueB.GetLength( ) )
			return false;

		return Compare( valueA, 0, valueB, 0, valueA.GetLength( ), ignoreCase );
	}

	bool Buffer::Compare( const Buffer& valueA, const Buffer& valueB, uint32 count )
	{
		return Compare( valueA, 0, valueB, 0, count, false );
	}

	bool Buffer::Compare( const Buffer& valueA, const Buffer& valueB, uint32 count, bool ignoreCase )
	{
		return Compare( valueA, 0, valueB, 0, count, ignoreCase );
	}

	bool Buffer::Compare( const Buffer& valueA, uint32 indexA, const Buffer& valueB, uint32 indexB, uint32 count )
	{
		return Compare( valueA, indexA, valueB, indexB, count, false );
	}

	bool Buffer::Compare( const Buffer& valueA, uint32 indexA, const Buffer& valueB, uint32 indexB, uint32 count, bool ignoreCase )
	{
		if( &valueA == &valueB )
			return true;

		valueA.CheckValue( );
		valueA.ValidateByLength( indexA, count );

		valueB.CheckValue( );
		valueB.ValidateByLength( indexB, count );

		if( ignoreCase )
		{
			for( uint32 index = 0; index < count; ++index )
			{
				if( Utils::Char::ToUpper( valueA.Value[ indexA + index ] ) != Utils::Char::ToUpper( valueB.Value[ indexB + index ] ) )
					return false;
			}
		}
		else
		{
			for( uint32 index = 0; index < count; ++index )
				if( valueA.Value[ indexA + index ] != valueB.Value[ indexB + index ] )
					return false;
		}

		return true;
	}

	Buffer Buffer::NumericToBuffer( byte value )
	{
		return Buffer( cstr( &value ), sizeof( value ) );
	}

	Buffer Buffer::NumericToBuffer( uint16 value )
	{
		return Buffer( cstr( &value ), sizeof( value ) );
	}

	Buffer Buffer::NumericToBuffer( uint32 value )
	{
		return Buffer( cstr( &value ), sizeof( value ) );
	}

	Buffer Buffer::NumericToBuffer( uint64 value )
	{
		return Buffer( cstr( &value ), sizeof( value ) );
	}

	Buffer Buffer::NumericToBuffer( single value )
	{
		return Buffer( cstr( &value ), sizeof( value ) );
	}

	Buffer Buffer::NumericToBuffer( double value )
	{
		return Buffer( cstr( &value ), sizeof( value ) );
	}

	uint16 Buffer::ToNumeric16( const Buffer& value )
	{
		uint16 code;
		value.Read( 0, str( &code ), sizeof( code ) );
		return code;
	}

	uint32 Buffer::ToNumeric32( const Buffer& value )
	{
		uint32 code;
		value.Read( 0, str( &code ), sizeof( code ) );
		return code;
	}
	uint64 Buffer::ToNumeric64( const Buffer& value )
	{
		uint64 code;
		value.Read( 0, str( &code ), sizeof( code ) );
		return code;
	}

	single Buffer::ToNumericSingle( const Buffer& value )
	{
		single code;
		value.Read( 0, str( &code ), sizeof( code ) );
		return code;
	}

	double Buffer::ToNumericDouble( const Buffer& value )
	{
		double code;
		value.Read( 0, str( &code ), sizeof( code ) );
		return code;
	}

	Buffer Buffer::XOR( const Buffer& valueA, const Buffer& valueB )
	{
		uint32 valueALength = valueA.GetLength( );
		uint32 valueBLength = valueB.GetLength( );

		if( valueALength != valueBLength )
			ThrowException( Exception::Ex_ArgumentOutOfRange, "valueALength [%d] != valueBLength [%d]", valueALength, valueBLength );

		return Buffer::XOR( valueA, valueB, valueALength );
	}

	Buffer Buffer::XOR( const Buffer& valueA, const Buffer& valueB, uint32 count )
	{
		return Buffer::XOR( 0, valueA, 0, valueB, count );
	}

	Buffer Buffer::XOR( uint32 indexA, const Buffer& valueA, uint32 indexB, const Buffer& valueB, uint32 count )
	{
		Buffer auxA = valueA;
		Buffer auxB = valueB;

		auxA.ValidateByLength( indexA, count );
		auxB.ValidateByLength( indexB, count );

		Buffer result( count );

		for( uint32 index = 0; index < count; ++index )
			result.Write( index, auxA[ index + indexA ] ^ auxB[ index + indexB ] );

		return result;
	}

	Buffer Buffer::Reverse( const Buffer& value )
	{
		return Buffer::Reverse( value, value.GetLength( ) );
	}

	Buffer Buffer::Reverse( const Buffer& value, uint32 count )
	{
		return Buffer::Reverse( 0, value, count );
	}

	Buffer Buffer::Reverse( uint32 startIndex, const Buffer& value )
	{
		value.ValidateByLength( startIndex );
		return Buffer::Reverse( startIndex, value, value.GetLength( ) - startIndex );
	}

	Buffer Buffer::Reverse( uint32 startIndex, const Buffer& value, uint32 count )
	{
		Buffer aux = value;
		aux.ValidateByLength( startIndex, count );

		Buffer result( count );
		uint32 valueIndex = startIndex + count;

		for( uint32 index = 0; index < count; ++index )
			result.Add( aux[ --valueIndex ] );

		return result;
	}
//Methods Private
	void Buffer::SetLength( uint32 value )
	{
		this->Length = value;
	}

	void Buffer::SetSize( uint32 value )
	{
		this->Size = value;
	}

	void Buffer::CheckValue( ) const
	{
		if( !this->Value )
			ThrowException( Exception::Ex_ArgumentNull, "value" );
	}

	void Buffer::ValidateBySize( uint32 position ) const
	{
		if( this->GetSize( ) < position )
			ThrowException( Exception::Ex_ArgumentOutOfRange, "Size [%d] < Position [%d]", this->GetSize( ), position );
	}

	void Buffer::ValidateBySize( uint32 position, uint32 count ) const
	{
		if( this->GetSize( ) < position )
			ThrowException( Exception::Ex_ArgumentOutOfRange, "Size [%d] < Position [%d]", this->GetSize( ), position );

		if( this->GetSize( ) < ( position + count ) )
			ThrowException( Exception::Ex_InternalBufferOverflow, "Size [%d] < ( position [%d] + count [%d] )", this->GetSize( ), position, count );
	}

	void Buffer::ValidateByLength( uint32 position ) const
	{
		if( this->GetLength( ) < position )
			ThrowException( Exception::Ex_ArgumentOutOfRange, "Size [%d] < Position [%d]", this->GetSize( ), position );
	}

	void Buffer::ValidateByLength( uint32 position, uint32 count ) const
	{
		if( this->GetLength( ) < position )
			ThrowException( Exception::Ex_ArgumentOutOfRange, "Size [%d] < Position [%d]", this->GetSize( ), position );

		if( this->GetLength( ) < ( position + count ) )
			ThrowException( Exception::Ex_InternalBufferOverflow, "Size [%d] < (position [%d] + count [%d])", this->GetSize( ), position, count );
	}
} /* namespace Data */
