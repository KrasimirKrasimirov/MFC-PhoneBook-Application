// CPersonsView.h : interface of the CCitiesView class
//
#pragma once
#include "PersonsDoc.h"
#include "PersonsDialog.h"

#define ON_SELECT_WHERE_ID_IDENTIFIER 0
#define ON_UPDATE_IDENTIFIER 1
#define ON_DELETE_IDENTIFIER 2
#define ON_INSERT_IDENTIFIER 3

class CPersonsView : public CListView
{
	
protected: // create from serialization only
	CPersonsView();
	DECLARE_DYNCREATE(CPersonsView)

// Attributes
public:
	CPersonsDoc* GetDocument() const;
// Methods
// ----------------
public:
	// Overrides
	virtual void OnDraw(CDC* /*pDC*/);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnUpdate(CView* /*pSender*/, LPARAM lHint, CObject* pHint);
protected:
	virtual void OnInitialUpdate();
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CPersonsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnMenuUpdate();
	afx_msg void OnMenuDelete();
	afx_msg void OnMenuInsert();
	afx_msg void OnMenuSelect();
};