/*
 * Buffer.hpp
 *
 *  Created on: Oct 4, 2023
 *      Author: XMF3944
 */

#ifndef _INCLUDE_FRAMEWORK_DATA_BUFFER_HPP_
#define _INCLUDE_FRAMEWORK_DATA_BUFFER_HPP_

#include <FwIncludes.hpp>

namespace Data
{

	class Buffer:
	             public ILength,
	             public IContenible,
	            // public ICopyTo< Buffer >,
	             public IIndexable< char >,
	             public IAddition< Buffer >,
	             public IAssignable< Buffer >,
	             public IComparison< Buffer >

	{
		public:

			Buffer( uint32 size = 0 );

			Buffer( cstr value, uint32 count );
			Buffer( char value, uint32 count );

			Buffer( const Buffer& value );
			Buffer( const Buffer& value, uint32 count );

			Buffer( uint32 startIndex, const Buffer& value );
			Buffer( uint32 startIndex, const Buffer& value, uint32 count );

			virtual ~Buffer( );

			//@Implements ILength
			virtual uint32 GetLength( ) const;

			//@Implements IContenible
			virtual void Clean( );
			virtual bool IsEmpty( ) const;

			//@Implements ICopyTo
			uint32 CopyTo( Buffer& destination ) const;
			uint32 CopyTo( Buffer& destination, uint32 length ) const;

			uint32 CopyTo( uint32 startIndex, Buffer& destination ) const;
			uint32 CopyTo( uint32 startIndex, Buffer& destination, uint32 length ) const;

			//@Implement Indexable
			virtual char& operator[]( uint32 index );

			//@Implement IAddition
			virtual Buffer operator+( const Buffer& value ) const;
			virtual Buffer& operator+=( const Buffer& value );

			//@Implement IAssignable
			virtual Buffer& operator =( const Buffer& value );

			//@Implement IComparison
			virtual int32 CompareTo( const Buffer& value ) const;

			//@Own Methods
			void Resize( uint32 newSize );
			void CheckCapacity( uint32 minSize );

			uint32 Add( char value );
			uint32 Add( char value, uint32 count );

			uint32 Add( const Buffer& value );
			uint32 Add( const Buffer& value, uint32 count );

			uint32 Add( uint32 startIndex, const Buffer& value );
			uint32 Add( uint32 startIndex, const Buffer& value, uint32 count );

			uint32 Add( cstr value );
			uint32 Add( cstr value, uint32 count );
			uint32 AddArguments( cstr format, va_list arg );

			uint32 GetSize( ) const;
			cstr GetBytes( uint32 index ) const;

			void Remove( uint32 startIndex );
			char Read( uint32 offset ) const;

			uint32 Read( uint32 offset, Buffer& value, uint32 count ) const;
			uint32 Read( uint32 offset, uint32 startIndex, Buffer& value, uint32 count ) const;

			uint32 Read( uint32 offset, str value, uint32 count ) const;
			uint32 Read( uint32 offset, str value, uint32 dataSize, uint32 count ) const;

			uint32 SetChar( char value );
			uint32 SetChar( char value, uint32 count );

			int32 SearchChar( char value ) const;
			int32 SearchChar( char value, uint32 count ) const;

			int32 SearchChar( uint32 startIndex, char value ) const;
			int32 SearchChar( uint32 startIndex, char value, uint32 count ) const;

			int32 SearchAnyChar( const Buffer& value ) const;
			int32 SearchAnyChar( const Buffer& value, uint32 count ) const;

			int32 SearchAnyChar( uint32 startIndex, const Buffer& value ) const;
			int32 SearchAnyChar( uint32 startIndex, const Buffer& value, uint32 count ) const;

			uint32 Write( uint32 offset, char value );
			uint32 Write( uint32 offset, char value, uint32 count );

			uint32 Write( uint32 offset, const Buffer& value );
			uint32 Write( uint32 offset, const Buffer& value, uint32 count );

			uint32 Write( uint32 offset, uint32 startIndex, const Buffer& value );
			uint32 Write( uint32 offset, uint32 startIndex, const Buffer& value, uint32 count );

			uint32 Write( uint32 offset, cstr value );
			uint32 Write( uint32 offset, cstr value, uint32 count );

			uint32 WriteFormat( uint32 offset, cstr format, ... );
			uint32 WriteArguments( uint32 offset, cstr format, va_list arguments );

			int32 ToInteger( ) const;

			Buffer SubBuffer( uint32 startIndex ) const;
			Buffer SubBuffer( uint32 startIndex, uint32 count ) const;

			//@Globals
			static const uint32 MaxSize;
			static const Buffer Empty;

			//@Static Methods
			static Buffer Concat( const Buffer& valueA, const Buffer& valueB );
			static Buffer Format( cstr format, ... );

			static bool Compare( const Buffer& valueA, const Buffer& valueB );
			static bool Compare( const Buffer& valueA, const Buffer& valueB, bool ignoreCase );

			static bool Compare( const Buffer& valueA, const Buffer& valueB, uint32 count );
			static bool Compare( const Buffer& valueA, const Buffer& valueB, uint32 count, bool ignoreCase );

			static bool Compare( const Buffer& valueA, uint32 indexA, const Buffer& valueB, uint32 indexB, uint32 count );
			static bool Compare( const Buffer& valueA, uint32 indexA, const Buffer& valueB, uint32 indexB, uint32 count, bool ignoreCase );

			static Buffer NumericToBuffer( byte value );
			static Buffer NumericToBuffer( uint16 value );

			static Buffer NumericToBuffer( uint32 value );
			static Buffer NumericToBuffer( uint64 value );

			static Buffer NumericToBuffer( single value );
			static Buffer NumericToBuffer( double value );

			static uint16 ToNumeric16( const Buffer& value );
			static uint32 ToNumeric32( const Buffer& value );
			static uint64 ToNumeric64( const Buffer& value );

			static single ToNumericSingle( const Buffer& value );
			static double ToNumericDouble( const Buffer& value );

			static Buffer XOR( const Buffer& valueA, const Buffer& valueB );
			static Buffer XOR( const Buffer& valueA, const Buffer& valueB, uint32 count );
			static Buffer XOR( uint32 indexA, const Buffer& valueA, uint32 indexB, const Buffer& valueB, uint32 count );

			static Buffer Reverse( const Buffer& value );
			static Buffer Reverse( const Buffer& value, uint32 count );

			static Buffer Reverse( uint32 startIndex, const Buffer& value );
			static Buffer Reverse( uint32 startIndex, const Buffer& value, uint32 count );

		private:

			void SetLength( uint32 value );
			void SetSize( uint32 value );

			void CheckValue( ) const;

			void ValidateBySize( uint32 position ) const;
			void ValidateBySize( uint32 position, uint32 count ) const;

			void ValidateByLength( uint32 position ) const;
			void ValidateByLength( uint32 position, uint32 count ) const;

			str Value;
			uint32 Size;
			uint32 Length;

	};

} /* namespace Data */

#endif /* _INCLUDE_FRAMEWORK_DATA_BUFFER_HPP_ */
