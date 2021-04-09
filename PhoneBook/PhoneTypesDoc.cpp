// PhoneTypesDoc.cpp : implementation of the PhoneTypesDoc class
//
#include "stdafx.h"
#include "PhoneBook.h"
#include "PhoneTypesDoc.h"

// CPhoneTypesDoc
IMPLEMENT_DYNCREATE(CPhoneTypesDoc, CDocument)

BEGIN_MESSAGE_MAP(CPhoneTypesDoc, CDocument)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CPhoneTypesDoc::CPhoneTypesDoc()
{
}

CPhoneTypesDoc::~CPhoneTypesDoc()
{
}

// Overrides
// ----------------
BOOL CPhoneTypesDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

#ifndef _WIN32_WCE
// CPhoneTypesDoc serialization

void CPhoneTypesDoc::Serialize(CArchive& ar)
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

// CPhoneTypesDoc diagnostics
#ifdef _DEBUG
void CPhoneTypesDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CPhoneTypesDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

// Methods
// ----------------
BOOL CPhoneTypesDoc::SelectAll(CPhoneTypesArray & oPhoneTypesArray)
{
	if (!m_oPhoneTypesData.SelectAll(oPhoneTypesArray))
	{
		return false;
	}
	return true;
}

BOOL CPhoneTypesDoc::SelectWhereID(const long lID, PHONE_TYPES & recPhoneTypes)
{
	if (!m_oPhoneTypesData.SelectWhereID(lID, recPhoneTypes))
	{
		return false;
	}

	UpdateAllViews(NULL, ON_SELECT_WHERE_ID_IDENTIFIER, (CObject*)&lID); // sends to OnUpdate()
	return true;
}

BOOL CPhoneTypesDoc::Insert(PHONE_TYPES & recPhoneTypes)
{
	if (!m_oPhoneTypesData.Insert(recPhoneTypes))
	{
		return false;
	}

	PHONE_TYPES* pPhoneType = new PHONE_TYPES(recPhoneTypes);
	m_oPhoneTypesArray.Add(pPhoneType);

	UpdateAllViews(NULL, ON_INSERT_IDENTIFIER, (CObject*)&recPhoneTypes); // sends to OnUpdate()
	return true;
}

BOOL CPhoneTypesDoc::UpdateWhereID(const long lID, const PHONE_TYPES & recPhoneTypes)
{
	if (!m_oPhoneTypesData.UpdateWhereID(lID, recPhoneTypes))
	{
		return false;
	}

	for (int i = 0; i < m_oPhoneTypesArray.GetSize(); i++)
	{
		if (m_oPhoneTypesArray.GetAt(i)->lID == lID)
		{
			*m_oPhoneTypesArray.GetAt(i) = recPhoneTypes;
		}
	}

	UpdateAllViews(NULL, ON_UPDATE_IDENTIFIER, (CObject*)&recPhoneTypes); // sends to OnUpdate()
	return true;
}

BOOL CPhoneTypesDoc::DeleteWhereID(const long lID, long lItemToBeDeletedViewLocation)
{
	if (!m_oPhoneTypesData.DeleteWhereID(lID))
	{
		return false;
	}

	for (int i = 0; i < m_oPhoneTypesArray.GetSize(); i++)
	{
		if (m_oPhoneTypesArray.GetAt(i)->lID == lID)
		{
			m_oPhoneTypesArray.RemoveAt(i);
		}
	}

	UpdateAllViews(NULL, ON_DELETE_IDENTIFIER, (CObject*)&lItemToBeDeletedViewLocation); // sends to OnUpdate()
	return true;
}

PHONE_TYPES * CPhoneTypesDoc::ReturnPhoneTypeByID(const long lID)
{
	for (int i = 0; i < m_oPhoneTypesArray.GetSize(); i++)
	{
		if (m_oPhoneTypesArray.GetAt(i)->lID == lID)
		{
			return m_oPhoneTypesArray.GetAt(i);
		}
	}
	return NULL;
}