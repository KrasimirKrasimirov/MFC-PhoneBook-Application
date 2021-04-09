// PersonsDoc.cpp : implementation of the PersonsDoc class
//
#include "stdafx.h"
#include "PhoneBook.h"
#include "PersonsDoc.h"


// CPersonsDoc
IMPLEMENT_DYNCREATE(CPersonsDoc, CDocument)

// Constructor / Destructor
// ----------------
CPersonsDoc::CPersonsDoc()
{
}

CPersonsDoc::~CPersonsDoc()
{
}

// Overrides
// ----------------
BOOL CPersonsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

BEGIN_MESSAGE_MAP(CPersonsDoc, CDocument)
END_MESSAGE_MAP()


// CPersonsDoc diagnostics

#ifdef _DEBUG
void CPersonsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CPersonsDoc serialization
void CPersonsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}
#endif


// Methods
// ----------------
BOOL CPersonsDoc::SelectAll(CPersonsArray & oPersonsArray)
{
	if (!m_oPersonsData.SelectAll(oPersonsArray))
	{
		return false;
	}
	return true;
}

BOOL CPersonsDoc::SelectWhereID(const long lID, PERSONS & recPersons)
{
	if (!m_oPersonsData.SelectWhereID(lID, recPersons))
	{
		return false;
	}

	UpdateAllViews(NULL, ON_SELECT_WHERE_ID_IDENTIFIER, (CObject*)&lID); // sends to OnUpdate()
	return true;
}

BOOL CPersonsDoc::Insert(PERSONS & recPersons, CString szCityName)
{
	for(int i = 0; i < m_oCitiesArray.GetSize(); i++)
	{ 
		if (szCityName == m_oCitiesArray.GetAt(i)->szName)
		{
			recPersons.lCityID = m_oCitiesArray.GetAt(i)->lID;
		}
	}

	if (!m_oPersonsData.Insert(recPersons))
	{
		return false;
	}

	PERSONS* pPerson = new PERSONS(recPersons);
	m_oPersonsArray.Add(pPerson);

	UpdateAllViews(NULL, ON_INSERT_IDENTIFIER, (CObject*)&recPersons); // sends to OnUpdate()
	return true;
}

BOOL CPersonsDoc::UpdateWhereID(const long lID, const PERSONS & recPersons)
{
	if (!m_oPersonsData.UpdateWhereID(lID, recPersons))
	{
		return false;
	}

	for (int i = 0; i < m_oPersonsArray.GetSize(); i++)
	{
		if (m_oPersonsArray.GetAt(i)->lID == lID)
		{
			*m_oPersonsArray.GetAt(i) = recPersons;
		}
	}

	UpdateAllViews(NULL, ON_UPDATE_IDENTIFIER, (CObject*)&recPersons); // sends to OnUpdate()
	return true;
}

PERSONS * CPersonsDoc::ReturnPersonByID(const long lID)
{
	for (int i = 0; i < m_oPersonsArray.GetSize(); i++)
	{
		if (m_oPersonsArray.GetAt(i)->lID == lID)
		{
			return m_oPersonsArray.GetAt(i);
		}
	}
	return NULL;
}

BOOL CPersonsDoc::SelectAll(CPhoneNumbersArray & oPhoneNumbersArray)
{
	if (!m_oPersonsData.SelectAll(oPhoneNumbersArray))
	{
		return false;
	}
	return true;
}

BOOL CPersonsDoc::SelectWhereID(const long lID, PHONE_NUMBERS & recPhoneNumbers)
{
	if (!m_oPersonsData.SelectWhereID(lID, recPhoneNumbers))
	{
		return false;
	}

	return true;
}

BOOL CPersonsDoc::Insert(PHONE_NUMBERS & recPhoneNumbers, CString szPhoneTypeName)
{
	for (int i = 0; i < m_oPhoneTypesArray.GetSize(); i++)
	{
		if (szPhoneTypeName == m_oPhoneTypesArray.GetAt(i)->szType)
		{
			recPhoneNumbers.lPhoneTypeID = m_oPhoneTypesArray.GetAt(i)->lID;
		}
	}

	if (!m_oPersonsData.Insert(recPhoneNumbers))
	{
		return false;
	}

	PHONE_NUMBERS* pPhoneNumber = new PHONE_NUMBERS(recPhoneNumbers);
	m_oPhoneNumbersArray.Add(pPhoneNumber);

	return true;
}

BOOL CPersonsDoc::UpdateWhereID(const long lID, const PHONE_NUMBERS & recPhoneNumbers)
{
	if (!m_oPersonsData.UpdateWhereID(lID, recPhoneNumbers))
	{
		return false;
	}

	for (int i = 0; i < m_oPhoneNumbersArray.GetSize(); i++)
	{
		if (m_oPhoneNumbersArray.GetAt(i)->lID == lID)
		{
			*m_oPhoneNumbersArray.GetAt(i) = recPhoneNumbers;
		}
	}

	return true;
}

PHONE_NUMBERS * CPersonsDoc::ReturnPhoneNumberByID(const long lID)
{
	for (int i = 0; i < m_oPhoneNumbersArray.GetSize(); i++)
	{
		if (m_oPhoneNumbersArray.GetAt(i)->lPersonID == lID)
		{
			return m_oPhoneNumbersArray.GetAt(i);
		}
	}
	return NULL;
}

BOOL CPersonsDoc::DeleteWhereID(const long lID, long lItemToBeDeletedViewLocation)
{
	for (int i = 0; i < m_oPhoneNumbersArray.GetSize(); i++)
	{
		if (m_oPhoneNumbersArray.GetAt(i)->lPersonID == lID)
		{
			if (!m_oPersonsData.DeleteWhereID(m_oPhoneNumbersArray.GetAt(i)->lID, PhoneNumber)) //remove phone number from db
			{
				return false;
			}
			m_oPhoneNumbersArray.RemoveAt(i);
		}
	}

	if (!m_oPersonsData.DeleteWhereID(lID, Person)) // remove person from db
	{
		return false;
	}
	UpdateAllViews(NULL, ON_DELETE_IDENTIFIER, (CObject*)&lItemToBeDeletedViewLocation); // sends to OnUpdate()
	return true;
}

CCitiesArray * CPersonsDoc::SelectAllCities()
{
	m_oCitiesArray.RemoveAll();
	if (m_oCitiesData.SelectAll(m_oCitiesArray))
	{
		return &m_oCitiesArray;
	}
	return NULL;
}

CPhoneTypesArray * CPersonsDoc::SelectAllPhoneTypes()
{
	m_oPhoneTypesArray.RemoveAll();
	if (m_oPhoneTypesData.SelectAll(m_oPhoneTypesArray))
	{
		return &m_oPhoneTypesArray;
	}
	return NULL;
}