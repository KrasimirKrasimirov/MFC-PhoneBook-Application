// CCitiesView.h : interface of the CCitiesView class
//
#pragma once
#include "CitiesDoc.h"
#include "CitiesDialog.h"

#define ON_SELECT_WHERE_ID_IDENTIFIER 0
#define ON_UPDATE_IDENTIFIER 1
#define ON_DELETE_IDENTIFIER 2
#define ON_INSERT_IDENTIFIER 3

class CCitiesView : public CListView
{
protected: // create from serialization only
	CCitiesView() noexcept;
	DECLARE_DYNCREATE(CCitiesView)

// Attributes
public:
	CCitiesDoc* GetDocument() const;
// Methods
// ----------------
public:
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CCitiesView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemActivate(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnMenuInsert();
	afx_msg void OnMenuUpdate();
	afx_msg void OnMenuDelete();
	afx_msg void OnMenuSelect();
};

#ifndef _DEBUG  // debug version in CCitiesView.cpp
inline CCitiesDoc* CCitiesView::GetDocument() const
   { return reinterpret_cast<CCitiesDoc*>(m_pDocument); }
#endif

