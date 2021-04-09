// CCitiesDoc.cpp : implementation of the CCitiesDoc class
//
#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PhoneBook.h"
#endif

#include "CitiesDoc.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCitiesDoc
IMPLEMENT_DYNCREATE(CCitiesDoc, CDocument)

BEGIN_MESSAGE_MAP(CCitiesDoc, CDocument)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CCitiesDoc::CCitiesDoc() noexcept
{
}

CCitiesDoc::~CCitiesDoc()
{
}

// Overrides
// ----------------
BOOL CCitiesDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

// CCitiesDoc serialization
void CCitiesDoc::Serialize(CArchive& ar)
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

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CCitiesDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CCitiesDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CCitiesDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CCitiesDoc diagnostics
#ifdef _DEBUG
void CCitiesDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCitiesDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

// Methods
// ----------------
BOOL CCitiesDoc::SelectAll(CCitiesArray & oCitiesArray)
{
	if (!m_oCitiesData.SelectAll(oCitiesArray))
	{
		return false;
	}
	return true;
}

BOOL CCitiesDoc::SelectWhereID(const long lID, CITIES & recCities)
{
	if (!m_oCitiesData.SelectWhereID(lID, recCities))
	{
		return false;
	}

	UpdateAllViews(NULL, ON_SELECT_WHERE_ID_IDENTIFIER, (CObject*)&lID); // sends to OnUpdate()
	return true;
}

BOOL CCitiesDoc::Insert(CITIES & recCities)
{
	if (!m_oCitiesData.Insert(recCities))
	{
		return false;
	}

	CITIES* pCity = new CITIES(recCities);
	m_oCitiesArray.Add(pCity);

	UpdateAllViews(NULL, ON_INSERT_IDENTIFIER, (CObject*)&recCities); // sends to OnUpdate()
	return true;
}

BOOL CCitiesDoc::UpdateWhereID(const long lID, const CITIES & recCities)
{
	if (!m_oCitiesData.UpdateWhereID(lID, recCities))
	{
		return false;
	}
	
	for (int i = 0; i < m_oCitiesArray.GetSize(); i++)
	{
		if (m_oCitiesArray.GetAt(i)->lID == lID)
		{
			*m_oCitiesArray.GetAt(i) = recCities;
		}
	}
	
	UpdateAllViews(NULL, ON_UPDATE_IDENTIFIER, (CObject*)&recCities); // sends to OnUpdate()
	return true;
}

BOOL CCitiesDoc::DeleteWhereID(const long lID, long lItemToBeDeletedViewLocation)
{
	if (!m_oCitiesData.DeleteWhereID(lID))
	{
		return false;
	}

	for (int i = 0; i < m_oCitiesArray.GetSize(); i++)
	{
		if (m_oCitiesArray.GetAt(i)->lID == lID)
		{
			m_oCitiesArray.RemoveAt(i);
		}
	}

	UpdateAllViews(NULL, ON_DELETE_IDENTIFIER, (CObject*)&lItemToBeDeletedViewLocation); // sends to OnUpdate()
	return true;
}

CITIES* CCitiesDoc::ReturnCityByID(const long lID)
{
	for (int i = 0; i < m_oCitiesArray.GetSize(); i++)
	{
		if (m_oCitiesArray.GetAt(i)->lID == lID)
		{
			return m_oCitiesArray.GetAt(i);
		}
	}
	return NULL;
}