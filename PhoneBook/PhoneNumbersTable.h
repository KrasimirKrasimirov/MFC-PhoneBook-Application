#pragma once
#include <afxwin.h>

#include <atldbcli.h>
#include <iostream>

#define PHONE_NUMBER_SIZE 32

/// <summary>
/// Структура PHONE_NUMBERS - съдържа параметрите на таблицата с телефонни номера
/// </summary>
struct PHONE_NUMBERS
{
	long lID;
	long lUpdateCounter;
	long lPersonID;
	long lPhoneTypeID;

	/// <summary>
	/// променлива szPhoneNumber - съхранява телефонен номер от таблица PHONE_NUMBERS
	/// </summary>
	TCHAR szPhoneNumber[PHONE_NUMBER_SIZE];

	PHONE_NUMBERS()
	{
		lID = 0;
		lUpdateCounter = 0;
		lPersonID = 0;
		lPhoneTypeID = 0;

		_tcscpy_s(szPhoneNumber, _T(""));
	}
};

class CPhoneNumbersAccessor
{
protected:
	PHONE_NUMBERS m_recPhoneNumber;

	BEGIN_ACCESSOR_MAP(CPhoneNumbersAccessor, 2)
		BEGIN_ACCESSOR(0, true)
		COLUMN_ENTRY(1, m_recPhoneNumber.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(1, true)
		COLUMN_ENTRY(2, m_recPhoneNumber.lUpdateCounter)
		COLUMN_ENTRY(3, m_recPhoneNumber.lPersonID)
		COLUMN_ENTRY(4, m_recPhoneNumber.lPhoneTypeID)
		COLUMN_ENTRY(5, m_recPhoneNumber.szPhoneNumber)
		END_ACCESSOR()
	END_ACCESSOR_MAP()
};

/// <summary>
/// typedef  CPhoneNumbersArray- съдържа масив CTypedPtrArray който съдържа pointers към structs на телефонни номера 
/// </summary>
typedef CTypedPtrArray<CPtrArray, PHONE_NUMBERS*> CPhoneNumbersArray;

/// <summary>Клас за работа с таблица PHONE_NUMBERS</summary>
class CPhoneNumbersTable : private CCommand<CAccessor<CPhoneNumbersAccessor>>
{
	// Constructor / Destructor
	// ----------------
public:
	CPhoneNumbersTable();
	~CPhoneNumbersTable();
	// Methods
	// ----------------
	BOOL SelectAll(CPhoneNumbersArray& oPhoneNumbersArray);
	BOOL SelectWhereID(const long lID, PHONE_NUMBERS& recPhoneNumbers);
	BOOL UpdateWhereID(const long lID, const PHONE_NUMBERS& recPhoneNumbers);
	BOOL Insert(PHONE_NUMBERS& recPhoneNumbers);
	BOOL DeleteWhereID(const long lID);
	// Overrides
	// ----------------



	// Members
	// ----------------
	CSession m_oSession;
};

