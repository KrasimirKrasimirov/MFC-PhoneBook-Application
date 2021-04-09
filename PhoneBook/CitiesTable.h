#pragma once
#include <afxwin.h>

#include <atldbcli.h>
#include <iostream>

#define CITY_NAME_SIZE 64
#define CITY_REGION_SIZE 128

/// <summary>
/// Структура CITIES - съдържа параметрите на таблицата с градове
/// </summary>
struct CITIES
{
	long lID;
	long lUpdateCounter;

	/// <summary>
	/// променлива szName - съхранява името на град от таблица CITIES
	/// </summary>
	TCHAR szName[CITY_NAME_SIZE];

	/// <summary>
	/// променлива szRegion - съхранява региона на град от таблица CITIES
	/// </summary>
	TCHAR szRegion[CITY_REGION_SIZE];

	CITIES()
	{
		lID = 0;
		lUpdateCounter = 0;

		_tcscpy_s(szName, _T(""));
		_tcscpy_s(szRegion, _T(""));
	}
};

class CCitiesAccessor
{
protected:
	CITIES m_recCity;

	BEGIN_ACCESSOR_MAP(CCitiesAccessor, 2)
		BEGIN_ACCESSOR(0, true)
		COLUMN_ENTRY(1, m_recCity.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(1, true)
		COLUMN_ENTRY(2, m_recCity.lUpdateCounter)
		COLUMN_ENTRY(3, m_recCity.szName)
		COLUMN_ENTRY(4, m_recCity.szRegion)
		END_ACCESSOR()
	END_ACCESSOR_MAP()
};

/// <summary>
/// typedef  CCitiesDataArray- съдържа масив CTypedPtrArray който съдържа pointers към structs на градове 
/// </summary>
typedef CTypedPtrArray<CPtrArray, CITIES*> CCitiesArray;

/// <summary>Клас за работа с таблица CITIES</summary>
class CCitiesTable : private CCommand<CAccessor<CCitiesAccessor>>
{
public:
	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------
public:
	CCitiesTable();
	~CCitiesTable();
	// Methods
	// ----------------
	BOOL SelectAll(CCitiesArray& oCitiesArray);
	BOOL SelectWhereID(const long lID, CITIES& recCities);
	BOOL UpdateWhereID(const long lID, const CITIES& recCities);
	BOOL Insert(CITIES& recCities);
	BOOL DeleteWhereID(const long lID);
	// Overrides
	// ----------------



	// Members
	// ----------------
	CSession m_oSession;
};

