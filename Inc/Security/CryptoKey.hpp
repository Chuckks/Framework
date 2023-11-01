/*
 * CryptoKey.hpp
 *
 *  Created on: Oct 17, 2023
 *      Author: XMF3944
 */

#ifndef _INCLUDE_FRAMEWORK_SECURITY_CRYPTOKEY_HPP_
#define _INCLUDE_FRAMEWORK_SECURITY_CRYPTOKEY_HPP_

#include <FwIncludes.hpp>

namespace Security
{
	const byte KeyBlockSize = 8;

	class CryptoKey:
	                public IContenible,
	                public IAssignable< CryptoKey >,
	                public IEqualitable< CryptoKey >
	{
		public:
			CryptoKey( );
			CryptoKey( EAlgoType algo );
			CryptoKey( const CryptoKey& value );

			CryptoKey( EAlgoType algo, const Data::Buffer& value );
			CryptoKey( EAlgoType algo, const Data::Buffer& componentA, const Data::Buffer& componenteB );

			virtual ~CryptoKey( );

			//@Implements IContenible
			virtual void Clean( );
			virtual bool IsEmpty( ) const;

			//@Implements IAssignable
			virtual CryptoKey& operator=( const CryptoKey& value );

			//@Implements IEqualitable
			virtual bool operator==( const CryptoKey& value ) const;

			//@Own Methods
			EAlgoType GetAlgo( ) const;
			void SetAlgo( EAlgoType algo );

			const Data::Buffer& GetComponentA( ) const;
			void SetComponentA( const Data::Buffer& componentA );

			const Data::Buffer& GetComponentB( ) const;
			void SetComponentB( const Data::Buffer& componentB );

			void Set( const Data::Buffer& componentA, const Data::Buffer& componentB );
			void Set( EAlgoType algo, const Buffer& componentA );
			void Set( EAlgoType algo, const Buffer& componentA, const Buffer& componentB );

			void SetKCV( );

			static const CryptoKey Empty;

			//static Methods
			static CryptoKey GenerateKey( EAlgoType algo, EKeyLength length, EParityKey parity );
			static Data::Buffer CalculateKCV( const CryptoKey& value );
			static byte CalculateKeyLength( EKeyLength value );

		private:
			EAlgoType Algo;

			Data::Buffer ComponentA;
			Data::Buffer ComponentB;
	};

} /* namespace Security */

#endif /* _INCLUDE_FRAMEWORK_SECURITY_CRYPTOKEY_HPP_ */
