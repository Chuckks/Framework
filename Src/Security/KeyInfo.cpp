/*
 * KeyInfo.cpp
 *
 *  Created on: Oct 16, 2023
 *      Author: XMF3944
 */

#include <FwIncludes.hpp>

namespace Security
{
	static const EAlgoType DefaultAlgoType = AlgoType_Undef;
	static const EKeySlot DefaultKeySlot = KeySlot_0;

	const KeyInfo KeyInfo::Empty;

	KeyInfo::KeyInfo( )
	{
		this->SetKeyInfo( DefaultKeySlot, DefaultAlgoType );
	}

	KeyInfo::KeyInfo( const KeyInfo& value )
	{
		*this = value;
	}

	KeyInfo::KeyInfo( EKeySlot keySlot, EAlgoType algoType )
	{
		this->SetKeyInfo( keySlot, algoType );
	}

	KeyInfo::~KeyInfo( )
	{
	}

	//@Implements IContenible
	void KeyInfo::Clean( )
	{
		*this = KeyInfo::Empty;
	}

	bool KeyInfo::IsEmpty( ) const
	{
		return ( *this == KeyInfo::Empty );
	}

	//@Implements IAssignable
	KeyInfo& KeyInfo::operator=( const KeyInfo& value )
	{
		if( this != &value )
			this->SetKeyInfo( value.KeySlot, value.AlgoType );

		return *this;
	}

	//@Implements IEqualitable
	bool KeyInfo::operator==( const KeyInfo& value ) const
	{
		if( this == &value )
			return true;

		if( this->GetKeySlot( ) != value.GetKeySlot( ) )
			return false;

		return ( this->GetAlgoType( ) == value.GetAlgoType( ) );
	}

	//@Own Methods
	void KeyInfo::SetKeySlot( EKeySlot value )
	{
		this->KeySlot = value;
	}

	EKeySlot KeyInfo::GetKeySlot( ) const
	{
		return this->KeySlot;
	}

	void KeyInfo::SetAlgoType( EAlgoType value )
	{
		this->AlgoType = value;
	}

	EAlgoType KeyInfo::GetAlgoType( ) const
	{
		return this->AlgoType;
	}

	void KeyInfo::SetKeyInfo( EKeySlot keySlot, EAlgoType algoType )
	{
		this->SetKeySlot( keySlot );
		this->SetAlgoType( algoType );
	}

} /* namespace Security */
