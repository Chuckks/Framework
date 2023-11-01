/*
 * CryptoKey.cpp
 *
 *  Created on: Oct 17, 2023
 *      Author: XMF3944
 */

#include <FwIncludes.hpp>

namespace Security
{

	const CryptoKey CryptoKey::Empty;

	CryptoKey::CryptoKey( ) :
		Algo( AlgoType_Undef )
	{
	}

	CryptoKey::CryptoKey( EAlgoType algo ) :
		Algo( algo )
	{
	}

	CryptoKey::CryptoKey( const CryptoKey& value )
	{
		*this = value;
	}

	CryptoKey::CryptoKey( EAlgoType algo, const Data::Buffer& value )
	{
	}

	CryptoKey::CryptoKey( EAlgoType algo, const Data::Buffer& componentA, const Data::Buffer& componenteB )
	{
	}

	CryptoKey::~CryptoKey( )
	{
	}

	//@Implements IContenible
	void CryptoKey::Clean( )
	{
		*this = CryptoKey::Empty;
	}

	bool CryptoKey::IsEmpty( ) const
	{
		return ( *this == CryptoKey::Empty );
	}

	//@Implements IAssignable
	CryptoKey& CryptoKey::operator=( const CryptoKey& value )
	{
		if( this != &value )
			this->Set( value.GetAlgo( ), value.GetComponentA( ), value.GetComponentB( ) );

		return *this;
	}

	//@Implements IEqualitable
	bool CryptoKey::operator==( const CryptoKey& value ) const
	{
		if( this == &value )
			return true;

		if( this->GetAlgo( ) != value.GetAlgo( ) )
			return false;

		if( this->GetComponentA( ) != value.GetComponentA( ) )
			return false;

		return ( this->GetComponentB( ) == value.GetComponentB( ) );
	}

	//@Own Methods
	EAlgoType CryptoKey::GetAlgo( ) const
	{
		return this->Algo;
	}

	void CryptoKey::SetAlgo( EAlgoType algo )
	{
		this->Algo = algo;
	}

	const Data::Buffer& CryptoKey::GetComponentA( ) const
	{
		return this->ComponentA;
	}

	void CryptoKey::SetComponentA( const Data::Buffer& componentA )
	{
		this->ComponentA = componentA;
	}

	const Data::Buffer& CryptoKey::GetComponentB( ) const
	{
		return this->ComponentB;
	}

	void CryptoKey::SetComponentB( const Data::Buffer& componentB )
	{
		this->ComponentB = componentB;
	}

	void CryptoKey::Set( const Data::Buffer& componentA, const Data::Buffer& componentB )
	{
		this->SetComponentA( componentA );
		this->SetComponentB( componentB );
	}

	void CryptoKey::Set( EAlgoType algo, const Buffer& componentA )
	{
		this->Set( algo, componentA, Data::Buffer( 0 ) );

		if( algo != AlgoType_Undef )
			this->SetKCV( );
	}
	void CryptoKey::Set( EAlgoType algo, const Buffer& componentA, const Buffer& componentB )
	{
		this->SetAlgo( algo );
		this->Set( componentA, componentB );
	}

	void CryptoKey::SetKCV( )
	{
		this->SetComponentB( CryptoKey::CalculateKCV( *this ) );
	}

	//static Methods
	CryptoKey GenerateKey( EAlgoType algo, EKeyLength length, EParityKey parity )
	{
		CryptoKey key( algo, CryptoUtils::AjustParity( CryptoUtils::GenerateRandom( length * 8 ), parity ) );
		key.SetKCV( );
		return key;
	}

	Data::Buffer CryptoKey::CalculateKCV( const CryptoKey& value )
	{
		static const byte KcvLength = 3;
		static const Buffer emptyData( char( 0x00 ), 16 );

		//TODO  Pendiente la clase SymmetricAlgo
		SymmetricAlgo* SymAlgo = NULL;

		switch( value.GetAlgo( ) )
		{
			case AlgoType_AES:
				break;

			case AlgoType_DES:
				break;

			case AlgoType_3DES:
				break;
			default:
				ThrowException( Exception::Ex_Cryptography, "Crypto algo [%d] wrong", value.GetAlgo( ) );
				break;
		}

		SymAlgo->SetKey( value );
		Buffer kcv( SymAlgo->Encrypt( emptyData ), KcvLength );

		delete SymAlgo;
		return kcv;

	}

	byte CryptoKey::CalculateKeyLength( EKeyLength value )
	{
		return value * KeyBlockSize;
	}

} /* namespace Security */
