#pragma once
#include <afxwin.h>

#include <atldbcli.h>
#include <iostream>

#define PERSON_FIRST_NAME_SIZE 64
#define PERSON_MIDDLE_NAME_SIZE 64
#define PERSON_FAMILY_NAME_SIZE 64
#define UCN_SIZE 16
#define ADDRESS_SIZE 128

/// <summary>
/// Структура PERSONS - съдържа параметрите на таблицата с хора
/// </summary>
struct PERSONS
{
	long lID;
	long lUpdateCounter;
	long lCityID;


	/// <summary>
	/// променлива szFirstName - съхранява името на човек от таблица PERSONS
	/// </summary>
	TCHAR szFirstName[PERSON_FIRST_NAME_SIZE];

	/// <summary>
	/// променлива szMiddleName - съхранява бащино име на човек от таблица PERSONS
	/// </summary>
	TCHAR szMiddleName[PERSON_MIDDLE_NAME_SIZE];

	/// <summary>
	/// променлива szFamilyName - съхранява фамилията на човек от таблица PERSONS
	/// </summary>
	TCHAR szFamilyName[PERSON_FAMILY_NAME_SIZE];

	/// <summary>
	/// променлива szUCN - съхранява ЕГН на човек от таблица PERSONS
	/// </summary>
	TCHAR szUCN[UCN_SIZE];

	/// <summary>
	/// променлива szAddress - съхранява адрес на човек от таблица PERSONS
	/// </summary>
	TCHAR szAddress[ADDRESS_SIZE];

	PERSONS()
	{
		lID = 0;
		lUpdateCounter = 0;
		lCityID = 0;

		_tcscpy_s(szFirstName, _T(""));
		_tcscpy_s(szMiddleName, _T(""));
		_tcscpy_s(szFamilyName, _T(""));
		_tcscpy_s(szUCN, _T(""));
		_tcscpy_s(szAddress, _T(""));
	}
};

class CPersonsAccessor
{
protected:
	PERSONS m_recPerson;

	BEGIN_ACCESSOR_MAP(CPersonsAccessor, 2)
		BEGIN_ACCESSOR(0, true)
		COLUMN_ENTRY(1, m_recPerson.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(1, true)
		COLUMN_ENTRY(2, m_recPerson.lUpdateCounter)
		COLUMN_ENTRY(3, m_recPerson.szFirstName)
		COLUMN_ENTRY(4, m_recPerson.szMiddleName)
		COLUMN_ENTRY(5, m_recPerson.szFamilyName)
		COLUMN_ENTRY(6, m_recPerson.szUCN)
		COLUMN_ENTRY(7, m_recPerson.lCityID)
		COLUMN_ENTRY(8, m_recPerson.szAddress)
		END_ACCESSOR()
	END_ACCESSOR_MAP()
};


/// <summary>
/// typedef  CPersonsArray- съдържа масив CTypedPtrArray който съдържа pointers към structs на хората 
/// </summary>
typedef CTypedPtrArray<CPtrArray, PERSONS*> CPersonsArray;

/// <summary>Клас за работа с таблица PERSONS</summary>
class CPersonsTable : private CCommand<CAccessor<CPersonsAccessor>>
{
	// Constructor / Destructor
	// ----------------
public:
	CPersonsTable();
	~CPersonsTable();
	// Methods
	// ----------------
	BOOL SelectAll(CPersonsArray& oPersonsArray);
	BOOL SelectWhereID(const long lID, PERSONS& recPersons);
	BOOL UpdateWhereID(const long lID, const PERSONS& recPersons);
	BOOL Insert(PERSONS& recPersons);
	BOOL DeleteWhereID(const long lID);
	// Overrides
	// ----------------


	// Members
	// ----------------
	CSession m_oSession;
};