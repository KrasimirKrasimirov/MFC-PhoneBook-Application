#include "stdafx.h"
#include "PersonsData.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsData

// Constructor / Destructor
// ----------------
CPersonsData::CPersonsData()
{
}

CPersonsData::~CPersonsData()
{
}

// Methods
// ----------------
//PersonsTable methods
BOOL CPersonsData::SelectAll(CPersonsArray & oPersonsArray)
{
	if (!m_oPersonsTable.SelectAll(oPersonsArray))
	{
		MessageBox(NULL, (LPCWSTR)_T("Грешка при селектирането на абонатите от таблицата с абонати."), (LPCWSTR)_T("Error"), MB_ICONERROR);
		return false;
	}
	return true;
}

BOOL CPersonsData::SelectWhereID(const long lID, PERSONS & recPersons)
{
	if (!m_oPersonsTable.SelectWhereID(lID, recPersons))
	{
		MessageBox(NULL, (LPCWSTR)_T("Грешка при селектиране на определен ред от таблицата с абонати."), (LPCWSTR)_T("Error"), MB_ICONERROR);
		return false;
	}
	return true;
}

BOOL CPersonsData::Insert(PERSONS & recPersons)
{
	if (!m_oPersonsTable.Insert(recPersons))
	{
		MessageBox(NULL, (LPCWSTR)_T("Грешка при добавянето на абонат."), (LPCWSTR)_T("Error"), MB_ICONERROR);
		return false;
	}
	return true;
}

BOOL CPersonsData::UpdateWhereID(const long lID, const PERSONS & recPersons)
{
	if (!m_oPersonsTable.UpdateWhereID(lID, recPersons))
	{
		MessageBox(NULL, (LPCWSTR)_T("Грешка при обновяването на данните на таблица абонати."), (LPCWSTR)_T("Error"), MB_ICONERROR);
		return false;
	}
	return true;
}

//PhoneNumbersTable methods
BOOL CPersonsData::SelectAll(CPhoneNumbersArray & oPhoneNumbersArray)
{
	if (!m_oPhoneNumbersTable.SelectAll(oPhoneNumbersArray))
	{
		MessageBox(NULL, (LPCWSTR)_T("Грешка при селектирането на телефонни номера от таблицата с тел. номера."), (LPCWSTR)_T("Error"), MB_ICONERROR);
		return false;
	}
	return true;
}

BOOL CPersonsData::SelectWhereID(const long lID, PHONE_NUMBERS & recPhoneNumbers)
{
	if (!m_oPhoneNumbersTable.SelectWhereID(lID, recPhoneNumbers))
	{
		MessageBox(NULL, (LPCWSTR)_T("Грешка при селектиране на определен ред от таблицата с телефонни номера."), (LPCWSTR)_T("Error"), MB_ICONERROR);
		return false;
	}
	return true;
}

BOOL CPersonsData::Insert(PHONE_NUMBERS & recPhoneNumbers)
{
	if (!m_oPhoneNumbersTable.Insert(recPhoneNumbers))
	{
		MessageBox(NULL, (LPCWSTR)_T("Грешка при добавянето на телефонен номер."), (LPCWSTR)_T("Error"), MB_ICONERROR);
		return false;
	}
	return true;
}

BOOL CPersonsData::UpdateWhereID(const long lID, const PHONE_NUMBERS & recPhoneNumbers)
{
	if (!m_oPhoneNumbersTable.UpdateWhereID(lID, recPhoneNumbers))
	{
		MessageBox(NULL, (LPCWSTR)_T("Грешка при обновяването на данните на таблица с телефонни номера."), (LPCWSTR)_T("Error"), MB_ICONERROR);
		return false;
	}
	return true;
}

//PersonsTable and PhoneNumbersTable shared methods
BOOL CPersonsData::DeleteWhereID(const long lID, DataType eDataType)
{
	if (eDataType == PhoneNumber)
	{
		if (!m_oPhoneNumbersTable.DeleteWhereID(lID))
		{
			MessageBox(NULL, (LPCWSTR)_T("Този телефонен номер е свързан с елемент от друга таблица и не може да бъде изтрит."), (LPCWSTR)_T("Error"), MB_ICONERROR);
			return false;
		}
	}

	if (eDataType == Person)
	{
		if (!m_oPersonsTable.DeleteWhereID(lID))
		{
			MessageBox(NULL, (LPCWSTR)_T("Този човек е свързан с елемент от друга таблица и не може да бъде изтрит."), (LPCWSTR)_T("Error"), MB_ICONERROR);
			return false;
		}
	}
	
	return true;
}