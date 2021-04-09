#include "stdafx.h"
#include "CitiesData.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesData

// Constructor / Destructor
// ----------------
CCitiesData::CCitiesData()
{
}

CCitiesData::~CCitiesData()
{
}

BOOL CCitiesData::SelectAll(CCitiesArray & oCitiesArray)
{
	if (!m_oCitiesTable.SelectAll(oCitiesArray))
	{
		MessageBox(NULL, (LPCWSTR)_T("Грешка при селектирането на редове от таблицата с градове."), (LPCWSTR)_T("Error"), MB_ICONERROR);
		return false;
	}
	return true;
}

BOOL CCitiesData::SelectWhereID(const long lID, CITIES & recCities)
{
	if (!m_oCitiesTable.SelectWhereID(lID, recCities))
	{
		MessageBox(NULL, (LPCWSTR)_T("Грешка при селектиране на определен ред от таблицата с градове."), (LPCWSTR)_T("Error"), MB_ICONERROR);
		return false;
	}
	return true;
}

BOOL CCitiesData::Insert(CITIES & recCities)
{
	if (!m_oCitiesTable.Insert(recCities))
	{
		MessageBox(NULL, (LPCWSTR)_T("Грешка при добавянето на град."), (LPCWSTR)_T("Error"), MB_ICONERROR);
		return false;
	}
	return true;
}

BOOL CCitiesData::UpdateWhereID(const long lID, const CITIES & recCities)
{
	if (!m_oCitiesTable.UpdateWhereID(lID, recCities))
	{
		MessageBox(NULL, (LPCWSTR)_T("Грешка при обновяването на данните на ред от таблицата с градове."), (LPCWSTR)_T("Error"), MB_ICONERROR);
		return false;
	}
	return true;
}

BOOL CCitiesData::DeleteWhereID(const long lID)
{
	if (!m_oCitiesTable.DeleteWhereID(lID))
	{
		MessageBox(NULL, (LPCWSTR)_T("Този град е свързан с елемент от друга таблица и не може да бъде изтрит."), (LPCWSTR)_T("Error"), MB_ICONERROR);
		return false;
	}
	return true;
}