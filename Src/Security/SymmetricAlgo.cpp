/*
 * SymmetricAlgo.cpp
 *
 *  Created on: Oct 18, 2023
 *      Author: XMF3944
 */

#include <FwIncludes.hpp>

namespace Security
{

	SymmetricAlgo::SymmetricAlgo( EAlgoType algo, uint32 blockSize, uint32 minSize, uint32 maxSize, uint32 skipSize ) :
		CryptoAlgorithm( algo ),
		Padding( Padding_None ),
		BlockSize( blockSize ),
		KeySize( minSize, maxSize, skipSize )
	{
	}

	SymmetricAlgo::SymmetricAlgo( EAlgoType algo, EPadding padding, uint32 blockSize, uint32 minSize, uint32 maxSize, uint32 skipSize ) :
		CryptoAlgorithm( algo ),
		Padding( padding ),
		BlockSize( blockSize ),
		KeySize( minSize, maxSize, skipSize )

	{
	}

	SymmetricAlgo::~SymmetricAlgo( )
	{
	}

	void SymmetricAlgo::SetKey( const CryptoKey& key )
	{
		uint16 max = this->KeySize.GetMax( ) / SymmetricAlgo::BlockDiv;
		uint16 length = key.GetComponentA( ).GetLength( );

		if( length > max )
			ThrowException( Exception::Ex_Cryptography, "Invalid KeySize [%d] bits", key.GetComponentA( ) );

		this->Key = key;
	}

	void SymmetricAlgo::SetKeySlot( EKeySlot keySlot )
	{
		//TODO Revisar hasta tener el GetBlock del Hsm
		//HSM hsm;
		//this->SetKey( CryptoKey( AlgoType_3DES, hsm.GetBlock( keySlot ) ) );
	}

	uint32 SymmetricAlgo::GetBlockSize( ) const
	{
		return this->BlockSize;
	}

	uint32 SymmetricAlgo::GetKeySize( ) const
	{
		return this->Key.GetComponentA( ).GetLength( ) * BlockDiv;
	}

	SymmetricAlgo::EPadding SymmetricAlgo::GetPadding( ) const
	{
		return this->Padding;
	}

	void SymmetricAlgo::SetPadding( EPadding value )
	{
		this->Padding = value;
	}

	const KeySizes& SymmetricAlgo::GetLegalKeySizes( ) const
	{
		return this->KeySize;
	}

	//@Implements Encrypt
	const Buffer& SymmetricAlgo::Encrypt( const Buffer& data )
	{
		this->CheckKeySize( );
		this->Cipher( data );

		return this->Treated;
	}

	const Buffer& SymmetricAlgo::Encrypt( const String& data )
	{
		return this->Encrypt( data.GetBuffer( ) );
	}

	//@Implements Decrypt
	const Buffer& SymmetricAlgo::Decrypt( const Buffer& data )
	{
		this->CheckKeySize( );
		this->Decipher( data );

		return this->Treated;
	}

	const Buffer& SymmetricAlgo::Decrypt( const String& data )
	{
		return this->Decrypt( data.GetBuffer( ) );
	}

	void SymmetricAlgo::AddPad( )
	{
		uint32 blockSize = this->BlockSize / BlockDiv;
		uint32 initialLength = Padded.GetLength( );

		if( !initialLength )
			ThrowException( Exception::Ex_Cryptography, "No initialLength [%d]", initialLength );

		if( initialLength >= blockSize )
			ThrowException( Exception::Ex_Cryptography, "initialLength [%d] >= blockSize [%d]", initialLength, blockSize );

		byte paddingLenth = blockSize - initialLength;

		switch( this->Padding )
		{
			case Padding_ANSIX923:
				this->Padded.Add( char( 0x00 ), paddingLenth - 1 );
				this->Padded.Add( paddingLenth );
				break;

			case Padding_ISO10126:
				this->Padded.Add( CryptoUtils::GenerateRandom( paddingLenth - 1 ) );
				this->Padded.Add( paddingLenth );
				break;

			case Padding_PKCS7:
				this->Padded.Add( paddingLenth, paddingLenth );
				break;

			case Padding_None:
			case Padding_Zeros:
				this->Padded.Add( char( 0x00 ), paddingLenth );
				break;

			default:
				ThrowException( Exception::Ex_Cryptography, "Pad Mode [%d] wrong", this->Padding );
				break;
		}
	}

	void SymmetricAlgo::DeletePad( )
	{
		uint32 padLength = 0, blockSize = ( this->BlockSize / BlockDiv );
		uint32 buffLengh = this->Treated.GetLength( );

		switch( this->Padding )
		{
			case Padding_None:
				break;

			case Padding_PKCS7:  //
			case Padding_ANSIX923:  //
			case Padding_ISO10126:
				padLength = this->Treated.Read( buffLengh - 1 );
				break;

			case Padding_Zeros:
				byte ch;

				for( byte index = buffLengh - 1; index >= buffLengh - blockSize; --index )
				{
					ch = this->Treated.Read( index );

					if( ch == 0x00 )
						++padLength;
					else
						break;
				}

				break;

			default:
				ThrowException( Exception::Ex_Cryptography, "Pad Mode [%d] wrong", this->Padding );
				break;
		}

		if( padLength >= blockSize )
			ThrowException( Exception::Ex_Cryptography, "padLength [%d] >= blockSize [%d]", padLength, blockSize );

		if( padLength )
			this->Treated.Remove( buffLengh - padLength );
	}

	void SymmetricAlgo::CheckKeySize( )
	{
		uint32 length = this->Key.GetComponentA( ).GetLength( ) * BlockDiv;

		if( !length )
			ThrowException( Exception::Ex_Cryptography, "No KeySize [%d] bits", length );

		if( ( length % this->KeySize.GetSkip( ) ) || ( length < this->KeySize.GetMin( ) ) || ( length > this->KeySize.GetMax( ) ) )
			ThrowException( Exception::Ex_Cryptography, "No valid KeySize [%d] bits", length );
	}

} /* namespace Security */
