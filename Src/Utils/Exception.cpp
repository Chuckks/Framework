/*
 * Exception.cpp
 *
 *  Created on: Oct 10, 2023
 *      Author: XMF3944
 */

#include <FwIncludes.hpp>

namespace Utils
{

	struct dataPacket
	{
			char data[ Defines::KbSize ];
			uint16 length;
	};

	static dataPacket buffer;

	static void BeepTono( )
	{
		Beep( 0x07, 0x05, 10, BEEP_ON | BEEP_WAIT | BEEP_OFF );  //sol
		Beep( 0x09, 0x05, 10, BEEP_ON | BEEP_WAIT | BEEP_OFF );  //la
		Beep( 0x0B, 0x05, 30, BEEP_ON | BEEP_WAIT | BEEP_OFF );  //si
	}

	cstr Exception::GetMessage( Exception::EType type )
	{
		switch( type )
		{
			case Ex_ArgumentInvalid:
				return "UNO DE LOS ARGUMENTOS PROPORCIONADOS AL MÉTODO NO ES VÁLIDO.";

			case Ex_ArgumentNull:
				return "REFERENCIA NULA O VACÍA PASADA AL MÉTODO.";

			case Ex_ArgumentOutOfRange:
				return "UN ARGUMENTO FUERA DEL INTERVALO DE VALORES PERMITIDOS.";

			case Ex_IndexOutOfRange:
				return "ÍNDICE FUERA DE LOS LÍMITES DE LA MATRIZ.";

			case Ex_Arithmetic:
				return "ERROR EN OPERACIÓN ARITMÉTICA O DE CONVERSIÓN DE TIPO.";

			case Ex_Cryptography:
				return "ERROR EN OPERACIÓN CRIPTOGRÁFICA.";

			case Ex_InternalBufferOverflow:
				return "EXCEPCIÓN POR DESBORDAMIENTO DE BÚFER INTERNO.";

			case Ex_InvalidOperation:
				return "LLAMADA A MÉTODO U OPERACIÓN NO VÁLIDA.";

			case Ex_InOut:
				return "SE HA PRODUCIDO UN ERROR DURANTE LA OPERACIÓN DE ENTRADA/SALIDA (E/S).";

			case Ex_IsEmpty:
				return "SE HA INTENTADO ACCEDER A UN OBJETO VACÍO.";

			case Ex_NotFound:
				return "NO SE ENCUENTRA O NO EXISTE EL ELEMENTO DE BÚSQUEDA INDICADO.";

			case Ex_NoImplemented:
				return "EL MÉTODO U OPERACIÓN SOLICITADA NO HA SIDO IMPLEMENTADO.";

			case Ex_NoSupported:
				return "NO ES COMPATIBLE CON LA FUNCIONALIDAD INVOCADA.";

			case Ex_NoInitialize:
				return "EL OBJETO NO HA SIDO INICIALIZADO.";

			case Ex_NullReference:
				return "INTENTO DE ACCEDER A UN OBJETO NULO.";

			case Ex_OutOfMemory:
				return "NO EXISTE SUFICIENTE MEMORIA PARA RESERVAR PARA UN NUEVO OBJETO.";

			case Ex_OutOfRange:
				return "LOS DATOS ESTÁN FUERA DEL RANGO PERMITIDO.";

			case Ex_Overflow:
				return "DESBORDO DEBIDO A UNA OPERACIÓN ARITMÉTICA O DE CONVERSIÓN.";

			case Ex_Security:
				return "ERROR DETECTADO: PROBLEMA DE SEGURIDAD IDENTIFICADO EN LA OPERACIÓN.";

			case Ex_System:
				return "LA FUNCIÓN DEL SDK HA RETORNADO UN ERROR DURANTE SU EJECUCIÓN.";

			default:
			case Ex_Undefined:
				return "SE HA GENERADO UNA EXCEPCIÓN NO ESPECIFICADA DURANTE LA EJECUCIÓN.";
		}
	}

	void Exception::Throw( cstr file, cstr function, uint32 line, EType type )
	{
		S_FS_FILE* handle = FS_open( "/HOST/EXCEPTION.LOG", "w+" );

		BuildHeader( file, function, line );
		FS_write( buffer.data, buffer.length, 1, handle );

		BuildMessage( type );
		buffer.length += Utils::Str::Copy( buffer.data + buffer.length, sizeof( buffer.data ) - buffer.length, "\r", 1 );

		FS_write( buffer.data, buffer.length, 1, handle );
		FS_close( handle );

		BeepTono( );
		//TODO Esperar Evento teclado
		Telium_Exit( 0 );

	}

	void Exception::Throw( cstr source, cstr targetSite, uint32 line, EType type, cstr format, ... )
	{
		va_list args;
		S_FS_FILE* handle = FS_open( "/HOST/EXCEPTION.LOG", "w+" );

		BuildHeader( source, targetSite, line );
		FS_write( buffer.data, buffer.length, 1, handle );

		BuildMessage( type );

		va_start( args, format );
		BuildAddicional( format, args );
		va_end( args );

		buffer.length += Utils::Str::Copy( buffer.data + buffer.length, sizeof( buffer.data ) - buffer.length, "\r", 1 );
		FS_write( buffer.data, buffer.length, 1, handle );
		FS_close( handle );


		BeepTono( );

		//TODO Se puede mostrar ventana con el error
		//TODO Esperar Evento teclado
		Telium_Exit( 0 );

	}

	void Exception::BuildMessage( Exception::EType type )
	{
		buffer.length = 0;
		buffer.length += Utils::Str::Copy( buffer.data + buffer.length, sizeof( buffer.data ) - buffer.length, GetMessage( type ) );
		buffer.length += Utils::Str::Copy( buffer.data + buffer.length, sizeof( buffer.data ) - buffer.length, " | ", 3 );
	}

	void Exception::BuildHeader( cstr file, cstr function, uint32 line )
	{
		DATE dateTime;
		ReadDateBooster( &dateTime );

		buffer.length = 0;
		buffer.length += Utils::Str::Format( buffer.data + buffer.length, sizeof( buffer.data ) - buffer.length, "%.2s/%.2s/%.2s %.2s:%.2s:%.2s", dateTime.year, dateTime.month, dateTime.day, dateTime.hour, dateTime.minute, dateTime.second );
		buffer.length += Utils::Str::Copy( buffer.data + buffer.length, sizeof( buffer.data ) - buffer.length, " | ", 3 );

		buffer.length += Utils::Str::Copy( buffer.data + buffer.length, sizeof( buffer.data ) - buffer.length, file );
		buffer.length += Utils::Str::Copy( buffer.data + buffer.length, sizeof( buffer.data ) - buffer.length, " | ", 3 );

		buffer.length += Utils::Str::Copy( buffer.data + buffer.length, sizeof( buffer.data ) - buffer.length, function );
		buffer.length += Utils::Str::Copy( buffer.data + buffer.length, sizeof( buffer.data ) - buffer.length, " | ", 3 );

		buffer.length += Utils::Str::Format( buffer.data + buffer.length, sizeof( buffer.data ) - buffer.length, "%04d", line );
		buffer.length += Utils::Str::Copy( buffer.data + buffer.length, sizeof( buffer.data ) - buffer.length, " | ", 3 );

	}

	void Exception::BuildAddicional( cstr format, va_list arguments )
	{
		buffer.length += Utils::Str::Arguments( buffer.data + buffer.length, sizeof( buffer.data ) - buffer.length, format, arguments );
	}

} /* namespace Utils */
