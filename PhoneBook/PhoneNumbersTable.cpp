#include "stdafx.h"
#include "PhoneNumbersTable.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersTable

// Constructor / Destructor
// ----------------
CPhoneNumbersTable::CPhoneNumbersTable()
{
}


CPhoneNumbersTable::~CPhoneNumbersTable()
{
}

// Methods
// ----------------
BOOL CPhoneNumbersTable::SelectAll(CPhoneNumbersArray & oPhoneNumbersArray)
{
	CDataSource oDataSource;

	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("DESKTOP-NFEPPCB\\sqlexpress"));	// сървър
	oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));							// SSPI
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("INTERNSHIP_PHONEBOOK"));			// база данни
	oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
	oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));

	// Свързваме се към базата данни
	HRESULT hResult = oDataSource.Open(_T("MSOLEDBSQL"), &oDBPropSet);

	if (FAILED(hResult))
	{
		return FALSE;
	}

	// Отваряме сесия
	hResult = m_oSession.Open(oDataSource);
	if (FAILED(hResult))
	{
		oDataSource.Close();
		return FALSE;
	}

	// Конструираме заявката
	CString strQuery = _T("SELECT * FROM PHONE_NUMBERS");

	// Изпълняваме командата
	hResult = Open(m_oSession, strQuery);
	if (FAILED(hResult))
	{
		m_oSession.Close();
		oDataSource.Close();
		return FALSE;
	}

	hResult = MoveNext();
	// Прочитаме всички данни
	while (hResult == S_OK)
	{
		PHONE_NUMBERS * pPhoneNumber = new PHONE_NUMBERS(m_recPhoneNumber);
		oPhoneNumbersArray.Add(pPhoneNumber);

		hResult = MoveNext();
	}

	// Затваряме командата, сесията и връзката с базата данни. 
	Close();
	m_oSession.Close();
	oDataSource.Close();

	return TRUE;
}

BOOL CPhoneNumbersTable::SelectWhereID(const long lID, PHONE_NUMBERS & recPhoneNumbers)
{
	CDataSource oDataSource;

	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("DESKTOP-NFEPPCB\\sqlexpress"));	// сървър
	oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));							// SSPI
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("INTERNSHIP_PHONEBOOK"));			// база данни
	oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
	oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));

	// Свързваме се към базата данни
	HRESULT hResult = oDataSource.Open(_T("MSOLEDBSQL"), &oDBPropSet);

	if (FAILED(hResult))
	{
		return FALSE;
	}

	// Отваряме сесия
	hResult = m_oSession.Open(oDataSource);
	if (FAILED(hResult))
	{
		oDataSource.Close();
		return FALSE;
	}

	// Конструираме заявката
	CString strQuery;
	strQuery.Format(_T("SELECT * FROM PHONE_NUMBERS WHERE ID = %d"), lID);


	// Изпълняваме командата
	hResult = Open(m_oSession, strQuery);
	if (FAILED(hResult))
	{
		m_oSession.Close();
		oDataSource.Close();
		return FALSE;
	}

	hResult = MoveFirst();
	if (FAILED(hResult))
	{
		Close();
		m_oSession.Close();
		oDataSource.Close();
		return FALSE;
	}

	recPhoneNumbers = m_recPhoneNumber; // load phone number information

	// Затваряме командата, сесията и връзката с базата данни. 
	Close();
	m_oSession.Close();
	oDataSource.Close();

	return TRUE;
}

BOOL CPhoneNumbersTable::UpdateWhereID(const long lID, const PHONE_NUMBERS & recPhoneNumbers)
{
	CDataSource oDataSource;

	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("DESKTOP-NFEPPCB\\sqlexpress"));	// сървър
	oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));							// SSPI
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("INTERNSHIP_PHONEBOOK"));			// база данни
	oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
	oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));

	// Свързваме се към базата данни
	HRESULT hResult = oDataSource.Open(_T("MSOLEDBSQL"), &oDBPropSet);

	if (FAILED(hResult))
	{
		return FALSE;
	}

	// Отваряме сесия
	hResult = m_oSession.Open(oDataSource);
	if (FAILED(hResult))
	{
		oDataSource.Close();
		return FALSE;
	}

	// Конструираме заявката
	CString strQuery;
	strQuery.Format(_T("SELECT * FROM PHONE_NUMBERS WHERE ID = %d"), lID);

	// Настройка на типа на Rowset-а
	CDBPropSet oUpdateDBPropSet(DBPROPSET_ROWSET);
	oUpdateDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
	oUpdateDBPropSet.AddProperty(DBPROP_IRowsetScroll, true);
	oUpdateDBPropSet.AddProperty(DBPROP_IRowsetChange, true);
	oUpdateDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);

	// Изпълняваме командата
	hResult = Open(m_oSession, strQuery, &oUpdateDBPropSet);
	if (FAILED(hResult))
	{
		m_oSession.Close();
		oDataSource.Close();
		return FALSE;
	}

	hResult = MoveFirst();
	if (FAILED(hResult))
	{
		Close();
		m_oSession.Close();
		oDataSource.Close();
		return FALSE;
	}

	if (m_recPhoneNumber.lUpdateCounter == 0) // if the entry has not been updated before
	{
		m_recPhoneNumber = recPhoneNumbers;
		m_recPhoneNumber.lUpdateCounter++;
	}
	else {  //if entry has been updated before, it does not copy everything from recPhoneNumbers, since it needs to keep its update counter value 
		_tcscpy_s(m_recPhoneNumber.szPhoneNumber, _countof(m_recPhoneNumber.szPhoneNumber), recPhoneNumbers.szPhoneNumber);
		m_recPhoneNumber.lPhoneTypeID = recPhoneNumbers.lPhoneTypeID;
		m_recPhoneNumber.lUpdateCounter++;
	}

	hResult = SetData(1); // update entry
	if (FAILED(hResult))
	{
		Close();
		m_oSession.Close();
		oDataSource.Close();
		return FALSE;
	}

	// Затваряме командата, сесията и връзката с базата данни. 
	Close();
	m_oSession.Close();
	oDataSource.Close();

	return TRUE;
}

BOOL CPhoneNumbersTable::Insert(PHONE_NUMBERS & recPhoneNumbers)
{
	CDataSource oDataSource;

	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("DESKTOP-NFEPPCB\\sqlexpress"));	// сървър
	oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));							// SSPI
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("INTERNSHIP_PHONEBOOK"));			// база данни
	oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
	oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));

	// Свързваме се към базата данни
	HRESULT hResult = oDataSource.Open(_T("MSOLEDBSQL"), &oDBPropSet);

	if (FAILED(hResult))
	{
		return FALSE;
	}

	// Отваряме сесия
	hResult = m_oSession.Open(oDataSource);
	if (FAILED(hResult))
	{
		oDataSource.Close();
		return FALSE;
	}

	// Конструираме заявката
	CString strQuery;
	strQuery.Format(_T("SELECT * FROM PHONE_NUMBERS"));

	// Настройка на типа на Rowset-а
	CDBPropSet oInsertDBPropSet(DBPROPSET_ROWSET);
	oInsertDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
	oInsertDBPropSet.AddProperty(DBPROP_IRowsetScroll, true);
	oInsertDBPropSet.AddProperty(DBPROP_IRowsetChange, true);
	oInsertDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);

	// Изпълняваме командата
	hResult = Open(m_oSession, strQuery, &oInsertDBPropSet);
	if (FAILED(hResult))
	{
		m_oSession.Close();
		oDataSource.Close();
		return FALSE;
	}

	hResult = MoveLast();
	if (FAILED(hResult))
	{
		Close();
		m_oSession.Close();
		oDataSource.Close();
		return FALSE;
	}
	

	m_recPhoneNumber = recPhoneNumbers;

	hResult = CCommand::Insert(1); // Insert entry
	MoveLast();
	recPhoneNumbers = m_recPhoneNumber; //assign new id to object passed to view

	if (FAILED(hResult))
	{
		Close();
		m_oSession.Close();
		oDataSource.Close();
		return FALSE;
	}

	// Затваряме командата, сесията и връзката с базата данни. 
	Close();
	m_oSession.Close();
	oDataSource.Close();

	return TRUE;
}

BOOL CPhoneNumbersTable::DeleteWhereID(const long lID)
{
	CDataSource oDataSource;

	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("DESKTOP-NFEPPCB\\sqlexpress"));	// сървър
	oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));							// SSPI
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("INTERNSHIP_PHONEBOOK"));			// база данни
	oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
	oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));

	// Свързваме се към базата данни
	HRESULT hResult = oDataSource.Open(_T("MSOLEDBSQL"), &oDBPropSet);

	if (FAILED(hResult))
	{
		return FALSE;
	}

	// Отваряме сесия
	hResult = m_oSession.Open(oDataSource);
	if (FAILED(hResult))
	{
		oDataSource.Close();
		return FALSE;
	}

	// Конструираме заявката
	CString strQuery;
	strQuery.Format(_T("SELECT * FROM PHONE_NUMBERS WHERE ID = %d"), lID);

	// Настройка на типа на Rowset-а
	CDBPropSet oDeleteDBPropSet(DBPROPSET_ROWSET);
	oDeleteDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
	oDeleteDBPropSet.AddProperty(DBPROP_IRowsetScroll, true);
	oDeleteDBPropSet.AddProperty(DBPROP_IRowsetChange, true);
	oDeleteDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);


	// Изпълняваме командата
	hResult = Open(m_oSession, strQuery, &oDeleteDBPropSet);
	if (FAILED(hResult))
	{
		m_oSession.Close();
		oDataSource.Close();
		return FALSE;
	}

	hResult = MoveFirst();
	if (FAILED(hResult))
	{
		Close();
		m_oSession.Close();
		oDataSource.Close();
		return FALSE;
	}

	hResult = CCommand::Delete(); // Delete entry
	if (FAILED(hResult))
	{
		Close();
		m_oSession.Close();
		oDataSource.Close();
		return FALSE;
	}

	// Затваряме командата, сесията и връзката с базата данни. 
	Close();
	m_oSession.Close();
	oDataSource.Close();

	return TRUE;
}