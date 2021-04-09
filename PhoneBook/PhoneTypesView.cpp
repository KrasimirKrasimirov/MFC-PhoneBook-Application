// PhoneTypesView.cpp : implementation of the PhoneTypesView class
//

#include "stdafx.h"
#include "PhoneBook.h"
#include "PhoneTypesView.h"


// CPhoneTypesView

IMPLEMENT_DYNCREATE(CPhoneTypesView, CListView)

BEGIN_MESSAGE_MAP(CPhoneTypesView, CListView)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_MENU_SELECT, &CPhoneTypesView::OnMenuSelect)
	ON_COMMAND(ID_MENU_INSERT, &CPhoneTypesView::OnMenuInsert)
	ON_COMMAND(ID_MENU_UPDATE, &CPhoneTypesView::OnMenuUpdate)
	ON_COMMAND(ID_MENU_DELETE, &CPhoneTypesView::OnMenuDelete)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CPhoneTypesView::CPhoneTypesView()
{
}

CPhoneTypesView::~CPhoneTypesView()
{
}

// Overrides
// ----------------
BOOL CPhoneTypesView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= LVS_REPORT;
	return CListView::PreCreateWindow(cs);
}

void CPhoneTypesView::OnDraw(CDC* pDC)
{
	CPhoneTypesDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

void CPhoneTypesView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	CPhoneTypesDoc* pDoc = GetDocument();
	CListCtrl& oListCtrl = GetListCtrl();

	if (oListCtrl.GetItemCount() == 0) // if list control is empty
	{
		CPhoneTypesTable oPhoneTypesTable;
		oListCtrl.DeleteAllItems();
		pDoc->m_oPhoneTypesArray.RemoveAll();

		pDoc->SelectAll(pDoc->m_oPhoneTypesArray);

		int nIndex;
		// Insert columns
		oListCtrl.InsertColumn(0, _T("Тип телефон"), LVCFMT_LEFT, -1, 0);

		for (int i = 0; i < pDoc->m_oPhoneTypesArray.GetSize(); i++)
		{
			// Insert row
			nIndex = oListCtrl.InsertItem(LVIF_TEXT, i, pDoc->m_oPhoneTypesArray.GetAt(i)->szType, 0, 0, 0, NULL);
			oListCtrl.SetItemData(nIndex, pDoc->m_oPhoneTypesArray.GetAt(i)->lID);
		}
		// Set column widths
		oListCtrl.SetColumnWidth(0, LVSCW_AUTOSIZE);
	}
}

void CPhoneTypesView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CPhoneTypesDoc* pDoc = GetDocument();
	CListCtrl& oListCtrl = GetListCtrl();
	long * lID; //used to point at ID of the item to be deleted, passed by method delete

	PHONE_TYPES * oChangedPhoneType; // used to point at city passed by methods update and insert
	int nItemID;

	if (oListCtrl.GetItemCount() > 0) // if there are items on the view
	{
		switch (lHint)
		{
		case ON_DELETE_IDENTIFIER:
			lID = (long*)pHint;

			oListCtrl.DeleteItem((int)*lID);

			return;
			break;
		case ON_UPDATE_IDENTIFIER:
			oChangedPhoneType = (PHONE_TYPES*)pHint;
			for (int i = 0; i < pDoc->m_oPhoneTypesArray.GetSize(); i++)
			{
				if (oListCtrl.GetItemData(i) == oChangedPhoneType->lID)
				{
					oListCtrl.SetItem(i, 0, LVIF_TEXT, oChangedPhoneType->szType, 0, 0, 0, NULL);
				}
			}
			break;
		case ON_INSERT_IDENTIFIER:
			oChangedPhoneType = (PHONE_TYPES*)pHint;

			int nIndex;
			nIndex = oListCtrl.InsertItem(LVIF_TEXT, oListCtrl.GetItemCount(), oChangedPhoneType->szType, 0, 0, 0, NULL);
			oListCtrl.SetItemData(nIndex, oChangedPhoneType->lID);
			break;
		}
	}
}

// CCitiesView printing
BOOL CPhoneTypesView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return CListView::OnPreparePrinting(pInfo);
}

void CPhoneTypesView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CListView::OnBeginPrinting(pDC, pInfo);
}

void CPhoneTypesView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CListView::OnEndPrinting(pDC, pInfo);
}

// CPhoneTypesView diagnostics
#ifdef _DEBUG
void CPhoneTypesView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CPhoneTypesView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG

CPhoneTypesDoc * CPhoneTypesView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPhoneTypesDoc)));
	return (CPhoneTypesDoc*)m_pDocument;
}

// Methods
// ----------------
void CPhoneTypesView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CPhoneTypesDoc* pDoc = GetDocument();

	CMenu cm;
	cm.LoadMenuW(IDR_MENU1);
	cm.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

void CPhoneTypesView::OnMenuSelect()
{
	CPhoneTypesDoc* pDoc = GetDocument();
	CListCtrl& oListCtrl = GetListCtrl();

	POSITION oPos = oListCtrl.GetFirstSelectedItemPosition();
	long lSelectedItemPosition = 0;
	long lSelectedItemID = 0;

	if (oPos) // ако реално има избран елемент
	{
		lSelectedItemPosition = oListCtrl.GetSelectionMark(); //selection position
		lSelectedItemID = oListCtrl.GetItemData(lSelectedItemPosition); // selection id

		if (pDoc->ReturnPhoneTypeByID(lSelectedItemID) != NULL)
		{
			CPhoneTypesDialog oPhoneTypesDialog(NULL, pDoc->ReturnPhoneTypeByID(lSelectedItemID), Select);

			if (lSelectedItemPosition >= 0)
			{
				INT_PTR nRet = -1;
				nRet = oPhoneTypesDialog.DoModal();
				if (nRet == IDOK)
				{
					pDoc->SelectWhereID(oPhoneTypesDialog.m_recPhoneType.lID, oPhoneTypesDialog.m_recPhoneType);
				}
			}
		}
	}
}

void CPhoneTypesView::OnMenuInsert()
{
	CPhoneTypesDoc* pDoc = GetDocument();
	CListCtrl& oListCtrl = GetListCtrl();

	PHONE_TYPES oPhoneTypeForDialog;

	CPhoneTypesDialog oPhoneTypesDialog(NULL, &oPhoneTypeForDialog, Insert);

	INT_PTR nRet = -1;
	nRet = oPhoneTypesDialog.DoModal();
	if (nRet == IDOK)
	{
		pDoc->Insert(oPhoneTypesDialog.m_recPhoneType);
	}
}

void CPhoneTypesView::OnMenuUpdate()
{
	CPhoneTypesDoc* pDoc = GetDocument();
	CListCtrl& oListCtrl = GetListCtrl();

	POSITION oPos = oListCtrl.GetFirstSelectedItemPosition();
	long lSelectedItemPosition = 0;
	long lSelectedItemID = 0;

	if (oPos)
	{
		lSelectedItemPosition = oListCtrl.GetSelectionMark(); //selection position
		lSelectedItemID = oListCtrl.GetItemData(lSelectedItemPosition); // selection id

		if (pDoc->ReturnPhoneTypeByID(lSelectedItemID) != NULL)
		{
			CPhoneTypesDialog oPhoneTypesDialog(NULL, pDoc->ReturnPhoneTypeByID(lSelectedItemID), Update);
			if (lSelectedItemPosition >= 0)
			{
				INT_PTR nRet = -1;
				nRet = oPhoneTypesDialog.DoModal();
				if (nRet == IDOK)
				{
					pDoc->UpdateWhereID(oPhoneTypesDialog.m_recPhoneType.lID, oPhoneTypesDialog.m_recPhoneType);
				}
			}
		}
	}
}

void CPhoneTypesView::OnMenuDelete()
{
	CPhoneTypesDoc* pDoc = GetDocument();
	CListCtrl& oListCtrl = GetListCtrl();

	POSITION oPos = oListCtrl.GetFirstSelectedItemPosition();
	long lSelectedItemPosition = 0;
	long lSelectedItemID = 0;

	if (oPos)
	{
		lSelectedItemPosition = oListCtrl.GetSelectionMark(); // selection position
		lSelectedItemID = oListCtrl.GetItemData(lSelectedItemPosition); // selection id

		if (pDoc->ReturnPhoneTypeByID(lSelectedItemID) != NULL)
		{
			CPhoneTypesDialog oPhoneTypesDialog(NULL, pDoc->ReturnPhoneTypeByID(lSelectedItemID), Delete); //entity to pass data to console 
			if (lSelectedItemPosition >= 0)
			{
				INT_PTR nRet = -1;
				nRet = oPhoneTypesDialog.DoModal();
				if (nRet == IDOK)
				{
					pDoc->DeleteWhereID(oPhoneTypesDialog.m_recPhoneType.lID, lSelectedItemPosition);
				}
			}
		}
	}
}