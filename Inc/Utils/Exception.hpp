/*
 * Exception.hpp
 *
 *  Created on: Oct 10, 2023
 *      Author: XMF3944
 */

#ifndef _INCLUDE_FRAMEWORK_UTILS_EXCEPTIONS_HPP_
#define _INCLUDE_FRAMEWORK_UTILS_EXCEPTIONS_HPP_

#include <FwIncludes.hpp>

namespace Utils
{

	class Exception
	{
		public:
			enum EType
			{
				Ex_ArgumentInvalid,
				Ex_ArgumentNull,
				Ex_ArgumentOutOfRange,
				Ex_IndexOutOfRange,
				Ex_Arithmetic,
				Ex_Cryptography,
				Ex_InternalBufferOverflow,
				Ex_InvalidOperation,
				Ex_InOut,
				Ex_IsEmpty,
				Ex_NotFound,
				Ex_NoImplemented,
				Ex_NoSupported,
				Ex_NoInitialize,
				Ex_NullReference,
				Ex_OutOfMemory,
				Ex_OutOfRange,
				Ex_Overflow,
				Ex_Security,
				Ex_System,
				Ex_Undefined
			};

			static void Throw( cstr file, cstr function, uint32 line, EType type );
			static void Throw( cstr source, cstr targetSite, uint32 line, EType type, cstr format, ... );

		private:

			static cstr GetMessage( Exception::EType type );
			static void BuildMessage( Exception::EType type );

			static void BuildAddicional( cstr format, va_list argument );
			static void BuildHeader( cstr file, cstr function, uint32 line );

	};


#define ThrowException( type, format, ... ) Exception::Throw( "__MODULE__", __FUNCTION__, __LINE__, type, format, ##__VA_ARGS__ )

} /* namespace Utils */

#endif /* _INCLUDE_FRAMEWORK_UTILS_EXCEPTIONS_HPP_ */
