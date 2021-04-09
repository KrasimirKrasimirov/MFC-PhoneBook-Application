#pragma once
#include "PersonsTable.h"
#include "PhoneNumbersTable.h"
enum DataType {Person, PhoneNumber};
class CPersonsData
{
// Constructor / Destructor
// ----------------
public:
	CPersonsData();
	~CPersonsData();

	// Methods
	// ----------------
	//PersonsTable methods
	BOOL SelectAll(CPersonsArray & oPersonsArray);
	BOOL SelectWhereID(const long lID, PERSONS & recPersons);
	BOOL UpdateWhereID(const long lID, const PERSONS & recPersons);
	BOOL Insert(PERSONS & recPersons);
	//PhoneNumbersTable methods
	BOOL SelectAll(CPhoneNumbersArray& oPhoneNumbersArray);
	BOOL SelectWhereID(const long lID, PHONE_NUMBERS& recPhoneNumbers);
	BOOL UpdateWhereID(const long lID, const PHONE_NUMBERS& recPhoneNumbers);
	BOOL Insert(PHONE_NUMBERS& recPhoneNumbers);
	//PersonsTable and PhoneNumbersTable shared methods
	BOOL DeleteWhereID(const long lID, DataType eDataType);
	// Members
	// ----------------
	CPersonsTable m_oPersonsTable;
	CPhoneNumbersTable m_oPhoneNumbersTable;
};

