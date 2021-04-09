#pragma once
#include "CitiesData.h"

#define ON_SELECT_WHERE_ID_IDENTIFIER 0
#define ON_UPDATE_IDENTIFIER 1
#define ON_DELETE_IDENTIFIER 2
#define ON_INSERT_IDENTIFIER 3

/////////////////////////////////////////////////////////////////////////////
// CCitiesDoc
class CCitiesDoc : public CDocument
{
protected: // create from serialization only
	CCitiesDoc() noexcept;
	DECLARE_DYNCREATE(CCitiesDoc)
// Attributes
public:
	CCitiesArray m_oCitiesArray;
	CCitiesData m_oCitiesData;
	CITIES m_recCity;
// Operations
public:
	BOOL SelectAll(CCitiesArray & oCitiesArray);
	BOOL SelectWhereID(const long lID, CITIES & recCities);
	BOOL Insert(CITIES & recCities);
	BOOL UpdateWhereID(const long lID, const CITIES & recCities);
	BOOL DeleteWhereID(const long lID, long lItemToBeDeletedViewLocation);
	CITIES* ReturnCityByID(const long lID);
// Overrides
protected:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CCitiesDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
