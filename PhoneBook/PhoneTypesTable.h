#pragma once
#include <afxwin.h>

#include <atldbcli.h>
#include <iostream>

#define PHONE_TYPE_TYPE_SIZE 64

/// <summary>
/// Структура PHONE_TYPES - съдържа параметрите на таблицата с типове телефони
/// </summary>
struct PHONE_TYPES
{
	long lID;
	long lUpdateCounter;

	/// <summary>
	/// променлива szType - съхранява телефонен тип от таблица PHONE_TYPES
	/// </summary>
	TCHAR szType[PHONE_TYPE_TYPE_SIZE];

	PHONE_TYPES()
	{
		lID = 0;
		lUpdateCounter = 0;

		_tcscpy_s(szType, _T(""));
	}
};

class CPhoneTypesAccessor
{
protected:
	PHONE_TYPES m_recPhoneType;

	BEGIN_ACCESSOR_MAP(CPhoneTypesAccessor, 2)
		BEGIN_ACCESSOR(0, true)
		COLUMN_ENTRY(1, m_recPhoneType.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(1, true)
		COLUMN_ENTRY(2, m_recPhoneType.lUpdateCounter)
		COLUMN_ENTRY(3, m_recPhoneType.szType)
		END_ACCESSOR()
	END_ACCESSOR_MAP()
};

/// <summary>
/// typedef  CPhoneTypesArray- съдържа масив CTypedPtrArray който съдържа pointers към structs на типове телефони
/// </summary>
typedef CTypedPtrArray<CPtrArray, PHONE_TYPES*> CPhoneTypesArray;

/// <summary>Клас за работа с таблица PHONE_NUMBERS</summary>
class CPhoneTypesTable : private CCommand<CAccessor<CPhoneTypesAccessor>>
{
	// Constructor / Destructor
	// ----------------
public:
	CPhoneTypesTable();
	~CPhoneTypesTable();
	// Methods
	// ----------------
	BOOL SelectAll(CPhoneTypesArray& oPhoneTypesArray);
	BOOL SelectWhereID(const long lID, PHONE_TYPES& recPhoneTypes);
	BOOL UpdateWhereID(const long lID, const PHONE_TYPES& recPhoneTypes);
	BOOL Insert(PHONE_TYPES& recPhoneTypes);
	BOOL DeleteWhereID(const long lID);
	// Overrides
	// ----------------



	// Members
	// ----------------
	CSession m_oSession;
};

