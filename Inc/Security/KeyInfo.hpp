/*
 * KeyInfo.hpp
 *
 *  Created on: Oct 16, 2023
 *      Author: XMF3944
 */

#ifndef _INClUDE_FRAMEWORK_SECURITY_KEYINFO_HPP_
#define _INClUDE_FRAMEWORK_SECURITY_KEYINFO_HPP_

#include <FwIncludes.hpp>

namespace Security
{

	class KeyInfo:
	              public IContenible,
	              public IAssignable< KeyInfo >,
	              public IEqualitable< KeyInfo >
	{
		public:
			KeyInfo( );

			KeyInfo( const KeyInfo& value );
			KeyInfo( EKeySlot keySlot, EAlgoType algoType );

			virtual ~KeyInfo( );

			//@Implements IContenible
			virtual void Clean( );
			virtual bool IsEmpty( ) const;

			//@Implements IAssignable
			virtual KeyInfo& operator=( const KeyInfo& value );

			//@Implements IEqualitable
			virtual bool operator==( const KeyInfo& value ) const;

			//@Own Methods
			void SetKeySlot( EKeySlot value );
			EKeySlot GetKeySlot( ) const;

			void SetAlgoType( EAlgoType value );
			EAlgoType GetAlgoType( ) const;

			void SetKeyInfo( EKeySlot keySlot, EAlgoType algoType );

			static const KeyInfo Empty;

		private:
			EKeySlot KeySlot;
			EAlgoType AlgoType;
	};

} /* namespace Security */

#endif /* _INClUDE_FRAMEWORK_SECURITY_KEYINFO_HPP_ */
