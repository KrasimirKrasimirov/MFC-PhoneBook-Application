#pragma once
#include "PhoneTypesTable.h"
class CPhoneTypesData
{
	// Constructor / Destructor
	// ----------------
public:
	CPhoneTypesData();
	~CPhoneTypesData();
	// Methods
	// ----------------
	BOOL SelectAll(CPhoneTypesArray & oPhoneTypesArray);
	BOOL SelectWhereID(const long lID, PHONE_TYPES & recPhoneTypes);
	BOOL Insert(PHONE_TYPES & recPhoneTypes);
	BOOL UpdateWhereID(const long lID, const PHONE_TYPES & recPhoneTypes);
	BOOL DeleteWhereID(const long lID);

	// Members
	// ----------------
	CPhoneTypesTable m_oPhoneTypesTable;
};