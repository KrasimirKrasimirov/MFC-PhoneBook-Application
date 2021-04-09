#pragma once
#include "PhoneTypesData.h"

#define ON_SELECT_WHERE_ID_IDENTIFIER 0
#define ON_UPDATE_IDENTIFIER 1
#define ON_DELETE_IDENTIFIER 2
#define ON_INSERT_IDENTIFIER 3

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesDoc
class CPhoneTypesDoc : public CDocument
{
protected: // create from serialization only
	CPhoneTypesDoc();
	DECLARE_DYNCREATE(CPhoneTypesDoc)

// Attributes
public:
	CPhoneTypesArray m_oPhoneTypesArray;
	CPhoneTypesData m_oPhoneTypesData;
	PHONE_TYPES m_recPhoneType;
// Operations
public:
	BOOL SelectAll(CPhoneTypesArray & oPhoneTypesArray);
	BOOL SelectWhereID(const long lID, PHONE_TYPES & recPhoneTypes);
	BOOL Insert(PHONE_TYPES & recPhoneTypes);
	BOOL UpdateWhereID(const long lID, const PHONE_TYPES & recPhoneTypes);
	BOOL DeleteWhereID(const long lID, long lItemToBeDeletedViewLocation);
	PHONE_TYPES* ReturnPhoneTypeByID(const long lID);
// Overrides
public:
	virtual BOOL OnNewDocument();
#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#endif
#ifdef _DEBUG
//Implementation
public:
	virtual ~CPhoneTypesDoc();
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};