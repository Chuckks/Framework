/*
 * SymmetricAlgo.hpp
 *
 *  Created on: Oct 18, 2023
 *      Author: XMF3944
 */

#ifndef INC_SECURITY_SYMMETRICALGO_HPP_
#define INC_SECURITY_SYMMETRICALGO_HPP_

namespace Security
{

	class SymmetricAlgo:
	                    public CryptoAlgorithm
	{
		public:

			enum EPadding
			{
				Padding_None,
				Padding_Zeros,
				Padding_PKCS7,
				Padding_ANSIX923,
				Padding_ISO10126
			};

			SymmetricAlgo( EAlgoType algo, uint32 blockSize, uint32 minSize, uint32 maxSize, uint32 skipSize );
			SymmetricAlgo( EAlgoType algo, EPadding padding, uint32 blockSize, uint32 minSize, uint32 maxSize, uint32 skipSize );

			virtual ~SymmetricAlgo( );

			virtual void SetKey( const CryptoKey& key );
			virtual void SetKeySlot( EKeySlot keySlot );

			uint32 GetBlockSize( ) const;
			uint32 GetKeySize( ) const;

			EPadding GetPadding( ) const;
			void SetPadding( EPadding value );

			const KeySizes& GetLegalKeySizes( ) const;

			//@Implements Encrypt
			virtual const Buffer& Encrypt( const Buffer& data );
			virtual const Buffer& Encrypt( const String& data );

			//@Implements Decrypt
			virtual const Buffer& Decrypt( const Buffer& data );
			virtual const Buffer& Decrypt( const String& data );

		protected:

			virtual uint32 Cipher( const Buffer& data ) = 0;
			virtual uint32 Decipher( const Buffer& data ) = 0;

			void CheckKeySize( );

			void AddPad( );
			void DeletePad( );

			Buffer Padded;
			EPadding Padding;

			uint32 BlockSize;
			KeySizes KeySize;

			static const byte BlockDiv;
	};

} /* namespace Security */

#endif /* INC_SECURITY_SYMMETRICALGO_HPP_ */
