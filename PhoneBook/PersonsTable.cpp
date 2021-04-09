#include "stdafx.h"
#include "PersonsTable.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsTable

// Constructor / Destructor
// ----------------
CPersonsTable::CPersonsTable()
{
}


CPersonsTable::~CPersonsTable()
{
}


// Methods
// ----------------
BOOL CPersonsTable::SelectAll(CPersonsArray & oPersonsArray)
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
	CString strQuery = _T("SELECT * FROM PERSONS");

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
		PERSONS * pPerson = new PERSONS(m_recPerson);
		oPersonsArray.Add(pPerson);

		hResult = MoveNext();
	}

	// Затваряме командата, сесията и връзката с базата данни. 
	Close();
	m_oSession.Close();
	oDataSource.Close();
	return TRUE;
}

BOOL CPersonsTable::SelectWhereID(const long lID, PERSONS & recPersons)
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
	strQuery.Format(_T("SELECT * FROM PERSONS WHERE ID = %d"), lID);

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


	recPersons = m_recPerson; // load person information

	// Затваряме командата, сесията и връзката с базата данни. 
	Close();
	m_oSession.Close();
	oDataSource.Close();

	return TRUE;
}

BOOL CPersonsTable::UpdateWhereID(const long lID, const PERSONS & recPersons)
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
	strQuery.Format(_T("SELECT * FROM PERSONS WHERE ID = %d"), lID);

	//m_oSession.StartTransaction();
	//m_oSession.Commit();
	//m_oSession.Abort();

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
	
	if (m_recPerson.lUpdateCounter == 0) // if the entry has not been updated before
	{
		m_recPerson = recPersons;
		m_recPerson.lUpdateCounter++;
	}
	else {  //if entry has been updated before, it does not copy everything from recPersons, since it needs to keep its update counter value 
		_tcscpy_s(m_recPerson.szFirstName, _countof(m_recPerson.szFirstName), recPersons.szFirstName);
		_tcscpy_s(m_recPerson.szMiddleName, _countof(m_recPerson.szMiddleName), recPersons.szMiddleName);
		_tcscpy_s(m_recPerson.szFamilyName, _countof(m_recPerson.szFamilyName), recPersons.szFamilyName);
		_tcscpy_s(m_recPerson.szUCN, _countof(m_recPerson.szUCN), recPersons.szUCN);
		_tcscpy_s(m_recPerson.szAddress, _countof(m_recPerson.szAddress), recPersons.szAddress);
		m_recPerson.lCityID = recPersons.lCityID;

		m_recPerson.lUpdateCounter++;
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

BOOL CPersonsTable::Insert(PERSONS & recPersons)
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
	strQuery.Format(_T("SELECT * FROM PERSONS"));

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

	m_recPerson = recPersons;

	hResult = CCommand::Insert(1); // Insert entry
	MoveLast();
	recPersons = m_recPerson; //assign new id to object passed to view
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

BOOL CPersonsTable::DeleteWhereID(const long lID)
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
	strQuery.Format(_T("SELECT * FROM PERSONS WHERE ID = %d"), lID);

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