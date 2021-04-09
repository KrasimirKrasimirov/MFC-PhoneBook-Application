#pragma once
#include "PersonsData.h"
#include "CitiesDoc.h"
#include "PhoneTypesDoc.h"

#define ON_SELECT_WHERE_ID_IDENTIFIER 0
#define ON_UPDATE_IDENTIFIER 1
#define ON_DELETE_IDENTIFIER 2
#define ON_INSERT_IDENTIFIER 3

/////////////////////////////////////////////////////////////////////////////
// CPersonsDoc
class CPersonsDoc : public CDocument
{
protected:
	CPersonsDoc();
	DECLARE_DYNCREATE(CPersonsDoc)
// Attributes
public:
	CPersonsArray m_oPersonsArray;
	CPhoneNumbersArray m_oPhoneNumbersArray;
	CPersonsData m_oPersonsData;
	PERSONS m_recPerson;
	PHONE_NUMBERS m_recPhoneNumber;

	CCitiesData m_oCitiesData;
	CCitiesArray m_oCitiesArray;
	CPhoneTypesData m_oPhoneTypesData;
	CPhoneTypesArray m_oPhoneTypesArray;
// Methods
// ----------------
public:
	//PersonsTable methods
	BOOL SelectAll(CPersonsArray & oPersonsArray);
	BOOL SelectWhereID(const long lID, PERSONS & recPersons);
	BOOL UpdateWhereID(const long lID, const PERSONS & recPersons);
	BOOL Insert(PERSONS & recPersons, CString szCityName);
	PERSONS* ReturnPersonByID(const long lID);

	//PhoneNumbersTable methods
	BOOL SelectAll(CPhoneNumbersArray& oPhoneNumbersArray);
	BOOL SelectWhereID(const long lID, PHONE_NUMBERS& recPhoneNumbers);
	BOOL UpdateWhereID(const long lID, const PHONE_NUMBERS& recPhoneNumbers);
	BOOL Insert(PHONE_NUMBERS& recPhoneNumbers, CString szPhoneTypeName);
	PHONE_NUMBERS* ReturnPhoneNumberByID(const long lID);

	//PersonsTable and PhoneNumbersTable shared methods
	BOOL DeleteWhereID(const long lID, long lItemToBeDeletedViewLocation);

	//CitiesDoc methods
	CCitiesArray * SelectAllCities();

	//PhoneTypesDoc methods
	CPhoneTypesArray * SelectAllPhoneTypes();

// Overrides
// ----------------
protected:
	virtual BOOL OnNewDocument();
#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#endif

//Implementation 
public:
	virtual ~CPersonsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
// Generated message map functions
	DECLARE_MESSAGE_MAP()
};
