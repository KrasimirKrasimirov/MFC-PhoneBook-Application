#include "stdafx.h"
#include "CitiesTable.h"

using namespace std;


/////////////////////////////////////////////////////////////////////////////
// CCitiesTable

// Constructor / Destructor
// ----------------
CCitiesTable::CCitiesTable()
{
}

CCitiesTable::~CCitiesTable()
{
}

// Methods
// ----------------
BOOL CCitiesTable::SelectAll(CCitiesArray & oCitiesArray)
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
	CString strQuery = _T("SELECT * FROM CITIES");

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
		CITIES * pCity = new CITIES(m_recCity);

		oCitiesArray.Add(pCity);

		hResult = MoveNext();
	}

	// Затваряме командата, сесията и връзката с базата данни. 
	Close();
	m_oSession.Close();
	oDataSource.Close();
	return TRUE;
}

BOOL CCitiesTable::SelectWhereID(const long lID, CITIES & recCities)
{
	CDataSource oDataSource;

	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("DESKTOP-NFEPPCB\\sqlexpress"));	// сървър
	oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));			// SSPI
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("INTERNSHIP_PHONEBOOK"));	// база данни
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
	strQuery.Format(_T("SELECT * FROM CITIES WHERE ID = %d"), lID);


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


	recCities = m_recCity; // load city information

	// Затваряме командата, сесията и връзката с базата данни. 
	Close();
	m_oSession.Close();
	oDataSource.Close();

	return TRUE;
}

BOOL CCitiesTable::UpdateWhereID(const long lID, const CITIES & recCities)
{
	CDataSource oDataSource;

	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("DESKTOP-NFEPPCB\\sqlexpress"));	// сървър
	oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));			// SSPI
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("INTERNSHIP_PHONEBOOK"));	// база данни
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
	strQuery.Format(_T("SELECT * FROM CITIES WHERE ID = %d"), lID);

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

	if (m_recCity.lUpdateCounter == 0) // if the entry has not been updated before
	{
		m_recCity = recCities; //copy the information from new entry
		m_recCity.lUpdateCounter++; 
	}
	else { //if entry has been updated before, it does not copy everything from recCities, since it needs to keep its update counter value 
		_tcscpy_s(m_recCity.szName, _countof(m_recCity.szName), recCities.szName);
		_tcscpy_s(m_recCity.szRegion, _countof(m_recCity.szRegion), recCities.szRegion);
		m_recCity.lUpdateCounter++;
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

BOOL CCitiesTable::Insert(CITIES & recCities)
{
	CDataSource oDataSource;

	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("DESKTOP-NFEPPCB\\sqlexpress"));	// сървър
	oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));			// SSPI
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("INTERNSHIP_PHONEBOOK"));	// база данни
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
	strQuery.Format(_T("SELECT * FROM CITIES"));

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

	m_recCity = recCities;

	hResult = CCommand::Insert(1); // Insert entry
	MoveLast();
	recCities = m_recCity; //assign new id to object passed to view

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

BOOL CCitiesTable::DeleteWhereID(const long lID)
{
	CDataSource oDataSource;

	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("DESKTOP-NFEPPCB\\sqlexpress"));	// сървър
	oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));			// SSPI
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("INTERNSHIP_PHONEBOOK"));	// база данни
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
	strQuery.Format(_T("SELECT * FROM CITIES WHERE ID = %d"), lID);

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