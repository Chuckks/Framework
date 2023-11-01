/*
 * String.hpp
 *
 *  Created on: Oct 16, 2023
 *      Author: XMF3944
 */

#ifndef _INCLUDE_FRAMEWORK_DATA_STRING_HPP_
#define _INCLUDE_FRAMEWORK_DATA_STRING_HPP_

#include <FwIncludes.hpp>

namespace Data
{

	class String:
	             public ILength,
	             public IContenible,
	             public ICopyTo< String >,
	             public IIndexable< char >,
	             public IAddition< String >,
	             public IAssignable< String >,
	             public IComparison< String >

	{
		public:

			String( cstr value = "" );

			String( char value, uint32 count );
			String( cstr value, uint32 count );

			String( const Buffer& value );
			String( const Buffer& value, uint32 count );

			String( uint32 startIndex, const Buffer& value );
			String( uint32 startIndex, const Buffer& value, uint32 count );

			String( const String& value );
			String( const String& value, uint32 count );

			String( uint32 startIndex, const String& value );
			String( uint32 startIndex, const String& value, uint32 count );

			virtual ~String( );

			//@Implement ILength
			virtual uint32 GetLength( ) const;

			//@Implements IContenible
			virtual void Clean( );
			virtual bool IsEmpty( ) const;

			//@Implements ICopyTo
			virtual uint32 CopyTo( String& destination ) const;
			virtual uint32 CopyTo( String& destination, uint32 length ) const;

			virtual uint32 CopyTo( uint32 startIndex, String& destination ) const;
			virtual uint32 CopyTo( uint32 startIndex, String& destination, uint32 length ) const;

			//@Implements IIdexable
			virtual char& operator[]( uint32 index );

			//@Implements IAddition
			virtual String operator+( const String& value ) const;
			virtual String& operator+=( const String& value );

			//@Implement IAssignable
			virtual String& operator =( const String& value );

			//@Implement IComparison
			virtual int32 CompareTo( const String& value ) const;

			//@Own Methods
			bool Contains( const String& value ) const;
			bool Contains( const String& value, bool ignoreCase ) const;

			bool EndsWith( const String& value ) const;
			bool EndsWith( const String& value, bool ignoreCase ) const;

			cstr GetBytes( uint32 index ) const;
			const Buffer& GetBuffer( ) const;

			int32 IndexOf( char value ) const;
			int32 IndexOf( char value, uint32 startIndex ) const;
			int32 IndexOf( char value, uint32 startIndex, uint32 count ) const;

			int32 IndexOf( const String& value ) const;
			int32 IndexOf( const String& value, uint32 startIndex ) const;
			int32 IndexOf( const String& value, uint32 startIndex, uint32 count ) const;

			int32 IndexOfAny( const String& value ) const;
			int32 IndexOfAny( const String& value, uint32 startIndex ) const;
			int32 IndexOfAny( const String& value, uint32 startIndex, uint32 count ) const;

			String Insert( uint32 startIndex, const String& value ) const;

			int32 LastIndexOf( char value ) const;
			int32 LastIndexOf( char value, uint32 startIndex ) const;
			int32 LastIndexOf( char value, uint32 startIndex, uint32 count ) const;

			int32 LastIndexOfAny( const String& value ) const;
			int32 LastIndexOfAny( const String& value, uint32 startIndex ) const;
			int32 LastIndexOfAny( const String& value, uint32 startIndex, uint32 count ) const;

			String PadLeft( uint32 totalWidth ) const;
			String PadLeft( uint32 totalWidth, char paddingChar ) const;

			String PadRight( uint32 totalWidth ) const;
			String PadRight( uint32 totalWidth, char paddingChar ) const;

			String Remove( uint32 startIndex ) const;
			String Remove( uint32 startIndex, uint32 count ) const;

			String Replace( char oldValue, char newValue ) const;
			String Replace( const String& oldValue, const String& newValue ) const;

			bool StartsWith( const String& value ) const;
			bool StartsWith( const String& value, bool ignoreCase ) const;

			String Substring( uint32 startIndex ) const;
			String Substring( uint32 startIndex, uint32 length ) const;

			String ToLower( ) const;
			String ToUpper( ) const;

			int32 ToInteger( ) const;

			String Trim( ) const;
			String Trim( const String& value ) const;

			String TrimEnd( char value ) const;
			String TrimEnd( const String& value ) const;

			String TrimStart( char value ) const;
			String TrimStart( const String& value ) const;

			//@Static Methods
			static bool Compare( const String& valueA, const String& valueB );
			static bool Compare( const String& valueA, const String& valueB, bool ignoreCase );

			static bool Compare( const String& valueA, const String& valueB, uint32 count );
			static bool Compare( const String& valueA, const String& valueB, uint32 count, bool ignoreCase );

			static bool Compare( const String& valueA, uint32 indexA, const String& valueB, uint32 indexB, uint32 count );
			static bool Compare( const String& valueA, uint32 indexA, const String& valueB, uint32 indexB, uint32 count, bool ignoreCase );

			static String Concat( const String& valueA, const String& valueB );
			static String Format( cstr format, ... );

		private:

			Buffer Value;
	};

} /* namespace Data */

#endif /* _INCLUDE_FRAMEWORK_DATA_STRING_HPP_ */
