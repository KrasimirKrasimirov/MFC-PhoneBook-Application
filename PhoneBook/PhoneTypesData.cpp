#include "stdafx.h"
#include "PhoneTypesData.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesData

// Constructor / Destructor
// ----------------
CPhoneTypesData::CPhoneTypesData()
{
}

CPhoneTypesData::~CPhoneTypesData()
{
}

BOOL CPhoneTypesData::SelectAll(CPhoneTypesArray & oPhoneTypesArray)
{
	if (!m_oPhoneTypesTable.SelectAll(oPhoneTypesArray))
	{
		MessageBox(NULL, (LPCWSTR)_T("Грешка при селектирането на редове от таблицата с типове телефони."), (LPCWSTR)_T("Error"), MB_ICONERROR);
		return false;
	}
	return true;
}

BOOL CPhoneTypesData::SelectWhereID(const long lID, PHONE_TYPES & recPhoneTypes)
{
	if (!m_oPhoneTypesTable.SelectWhereID(lID, recPhoneTypes))
	{
		MessageBox(NULL, (LPCWSTR)_T("Грешка при селектиране на определен ред от таблицата с типове телефони."), (LPCWSTR)_T("Error"), MB_ICONERROR);
		return false;
	}
	return true;
}

BOOL CPhoneTypesData::Insert(PHONE_TYPES & recPhoneTypes)
{
	if (!m_oPhoneTypesTable.Insert(recPhoneTypes))
	{
		MessageBox(NULL, (LPCWSTR)_T("Грешка при добавянето на тип телефон."), (LPCWSTR)_T("Error"), MB_ICONERROR);
		return false;
	}
	return true;
}

BOOL CPhoneTypesData::UpdateWhereID(const long lID, const PHONE_TYPES & recPhoneTypes)
{
	if (!m_oPhoneTypesTable.UpdateWhereID(lID, recPhoneTypes))
	{
		MessageBox(NULL, (LPCWSTR)_T("Грешка при обновяването на данните на ред от таблицата с типове телефони."), (LPCWSTR)_T("Error"), MB_ICONERROR);
		return false;
	}
	return true;
}

BOOL CPhoneTypesData::DeleteWhereID(const long lID)
{
	if (!m_oPhoneTypesTable.DeleteWhereID(lID))
	{
		MessageBox(NULL, (LPCWSTR)_T("Този тип телефон е свързан с елемент от друга таблица и не може да бъде изтрит."), (LPCWSTR)_T("Error"), MB_ICONERROR);
		return false;
	}
	return true;
}
