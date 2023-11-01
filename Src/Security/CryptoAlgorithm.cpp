/*
 * CryptoAlgorithm.cpp
 *
 *  Created on: Oct 18, 2023
 *      Author: XMF3944
 */

#include <FwIncludes.hpp>

namespace Security
{

	CryptoAlgorithm::CryptoAlgorithm( EAlgoType algo ) :
		Algo( algo )
	{
	}

	CryptoAlgorithm::CryptoAlgorithm( const CryptoKey& key ) :
		Key( key ),
		Algo( key.GetAlgo( ) )
	{
	}

	CryptoAlgorithm::~CryptoAlgorithm( )
	{
	}

	void CryptoAlgorithm::SetKey( const CryptoKey& key )
	{
		this->Key = key;
	}

	bool CryptoAlgorithm::IsLoadKey( )
	{
		return ( this->Key.IsNotEmpty( ) );
	}


} /* namespace Security */
