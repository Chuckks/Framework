/*
 * Enums.hpp
 *
 *  Created on: Oct 16, 2023
 *      Author: XMF3944
 */

#ifndef _INCLUDE_FRAMEWORK_SECURITY_ENUMS_HPP_
#define _INCLUDE_FRAMEWORK_SECURITY_ENUMS_HPP_

	enum EAlgoType
	{
		AlgoType_Undef,
		AlgoType_DES,
		AlgoType_3DES,
		AlgoType_AES,
		AlgoType_RSA
	};

	enum EKeySlot
	{
		KeySlot_0,
		KeySlot_1,
		KeySlot_2,
		KeySlot_3,
		KeySlot_4,
		KeySlot_5,
		KeySlot_6,
		KeySlot_7,
		KeySlot_8,
		KeySlot_DUKPT
	};

	enum EKeyLength
	{
		KeyLength_0,
		KeyLength_8,
		KeyLength_16,
		KeyLength_24,
		KeyLength_32
	};

	enum EParityKey
	{
		ParityKey_Even,
		ParityKey_Odd
	};


#endif /* _INCLUDE_FRAMEWORK_SECURITY_ENUMS_HPP_ */
