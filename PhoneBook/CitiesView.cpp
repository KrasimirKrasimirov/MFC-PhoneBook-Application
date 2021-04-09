// CCitiesView.cpp : implementation of the CCitiesView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PhoneBook.h"
#endif

#include "CitiesView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCitiesView

IMPLEMENT_DYNCREATE(CCitiesView, CListView)

BEGIN_MESSAGE_MAP(CCitiesView, CListView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CListView::OnFilePrintPreview)
	ON_NOTIFY_REFLECT(LVN_ITEMACTIVATE, &CCitiesView::OnLvnItemActivate)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_MENU_UPDATE, &CCitiesView::OnMenuUpdate)
	ON_COMMAND(ID_MENU_DELETE, &CCitiesView::OnMenuDelete)
	ON_COMMAND(ID_MENU_INSERT, &CCitiesView::OnMenuInsert)
	ON_COMMAND(ID_MENU_SELECT, &CCitiesView::OnMenuSelect)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CCitiesView::CCitiesView() noexcept
{
}

CCitiesView::~CCitiesView()
{
}

// Overrides
// ----------------
BOOL CCitiesView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= LVS_REPORT;
	return CListView::PreCreateWindow(cs);
}

void CCitiesView::OnDraw(CDC* /*pDC*/)
{
	CCitiesDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

void CCitiesView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	CCitiesDoc* pDoc = GetDocument();
	CListCtrl& oListCtrl = GetListCtrl();

	if (oListCtrl.GetItemCount() == 0) // if list control is empty
	{
		CCitiesTable oCitiesTable;
		oListCtrl.DeleteAllItems();
		pDoc->m_oCitiesArray.RemoveAll();
		
		pDoc->SelectAll(pDoc->m_oCitiesArray);

		int nIndex;
		// Insert columns
		oListCtrl.InsertColumn(0, _T("Име"), LVCFMT_LEFT, -1, 0);
		oListCtrl.InsertColumn(1, _T("Регион"), LVCFMT_LEFT, -1, 1);

		for (int i = 0; i < pDoc->m_oCitiesArray.GetSize(); i++)
		{
			// Insert row
			nIndex = oListCtrl.InsertItem(LVIF_TEXT, i, pDoc->m_oCitiesArray.GetAt(i)->szName, 0, 0, 0, NULL);
			oListCtrl.SetItem(nIndex, 1, LVIF_TEXT, pDoc->m_oCitiesArray.GetAt(i)->szRegion, 0, 0, 0, NULL);
			oListCtrl.SetItemData(nIndex, pDoc->m_oCitiesArray.GetAt(i)->lID);
		}
		// Set column widths
		oListCtrl.SetColumnWidth(0, LVSCW_AUTOSIZE);
		oListCtrl.SetColumnWidth(1, LVSCW_AUTOSIZE);
	}
}

void CCitiesView::OnUpdate(CView * pSender, LPARAM lHint, CObject * pHint)
{
	CCitiesDoc* pDoc = GetDocument();
	CListCtrl& oListCtrl = GetListCtrl();
	long * lID; //used to point at ID of the item to be deleted, passed by method delete

	CITIES * oChangedCity; // used to point at city passed by methods update and insert
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
			oChangedCity = (CITIES*)pHint;
			for (int i = 0; i < pDoc->m_oCitiesArray.GetSize(); i++)
			{
				if (oListCtrl.GetItemData(i) == oChangedCity->lID)
				{
					oListCtrl.SetItem(i, 0, LVIF_TEXT, oChangedCity->szName, 0, 0, 0, NULL);
					oListCtrl.SetItem(i, 1, LVIF_TEXT, oChangedCity->szRegion, 0, 0, 0, NULL);
				}
			}
			break;
		case ON_INSERT_IDENTIFIER:
			oChangedCity = (CITIES*)pHint;

			int nIndex;
			nIndex = oListCtrl.InsertItem(LVIF_TEXT, oListCtrl.GetItemCount(), oChangedCity->szName, 0, 0, 0, NULL);
			oListCtrl.SetItem(nIndex, 1, LVIF_TEXT, oChangedCity->szRegion, 0, 0, 0, NULL);
			oListCtrl.SetItemData(nIndex, oChangedCity->lID);
			break;
		}
	}
}

// CCitiesView printing
BOOL CCitiesView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCitiesView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCitiesView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

// CCitiesView diagnostics
#ifdef _DEBUG
void CCitiesView::AssertValid() const
{
	CListView::AssertValid();
}

void CCitiesView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CCitiesDoc* CCitiesView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCitiesDoc)));
	return (CCitiesDoc*)m_pDocument;
}
#endif //_DEBUG

// Methods
// ----------------
void CCitiesView::OnLvnItemActivate(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
}


void CCitiesView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CCitiesDoc* pDoc = GetDocument();

	CMenu cm;
	cm.LoadMenuW(IDR_MENU1);
	cm.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

void CCitiesView::OnMenuSelect() //Select where ID
{
	CCitiesDoc* pDoc = GetDocument();
	CListCtrl& oListCtrl = GetListCtrl();

	POSITION oPos = oListCtrl.GetFirstSelectedItemPosition();
	long lSelectedItemPosition = 0;
	long lSelectedItemID = 0;

	if (oPos) // ако реално има избран елемент
	{
		lSelectedItemPosition = oListCtrl.GetSelectionMark(); //selection position
		lSelectedItemID = oListCtrl.GetItemData(lSelectedItemPosition); // selection id

		if (pDoc->ReturnCityByID(lSelectedItemID) != NULL)
		{
			CCitiesDialog oCitiesDialog(NULL, pDoc->ReturnCityByID(lSelectedItemID), Select);

			if (lSelectedItemPosition >= 0)
			{
				INT_PTR nRet = -1;
				nRet = oCitiesDialog.DoModal();
				if (nRet == IDOK)
				{
					pDoc->SelectWhereID(oCitiesDialog.m_recCity.lID, oCitiesDialog.m_recCity);
				}
			}
		}
	}
}

void CCitiesView::OnMenuInsert() //Insert
{
	CCitiesDoc* pDoc = GetDocument();
	CListCtrl& oListCtrl = GetListCtrl();

	CITIES oCityForDialog;
	
	CCitiesDialog oCitiesDialog(NULL, &oCityForDialog, Insert);

	INT_PTR nRet = -1;
	nRet = oCitiesDialog.DoModal();
	if (nRet == IDOK)
	{
		pDoc->Insert(oCitiesDialog.m_recCity);
	}
}

void CCitiesView::OnMenuUpdate() // Update
{
	CCitiesDoc* pDoc = GetDocument();
	CListCtrl& oListCtrl = GetListCtrl();

	POSITION oPos = oListCtrl.GetFirstSelectedItemPosition();
	long lSelectedItemPosition = 0;
	long lSelectedItemID = 0;

	if (oPos)
	{
		lSelectedItemPosition = oListCtrl.GetSelectionMark(); //selection position
		lSelectedItemID = oListCtrl.GetItemData(lSelectedItemPosition); // selection id

		if (pDoc->ReturnCityByID(lSelectedItemID) != NULL)
		{
			CCitiesDialog oCitiesDialog(NULL, pDoc->ReturnCityByID(lSelectedItemID), Update);
			if (lSelectedItemPosition >= 0)
			{
				INT_PTR nRet = -1;
				nRet = oCitiesDialog.DoModal();
				if (nRet == IDOK)
				{
					pDoc->UpdateWhereID(oCitiesDialog.m_recCity.lID, oCitiesDialog.m_recCity);
				}
			}
		}
	}
}

void CCitiesView::OnMenuDelete() // Delete
{
	CCitiesDoc* pDoc = GetDocument();
	CListCtrl& oListCtrl = GetListCtrl();

	POSITION oPos = oListCtrl.GetFirstSelectedItemPosition();
	long lSelectedItemPosition = 0;
	long lSelectedItemID = 0;

	if (oPos)
	{
		lSelectedItemPosition = oListCtrl.GetSelectionMark(); // selection position
		lSelectedItemID = oListCtrl.GetItemData(lSelectedItemPosition); // selection id
		
		if (pDoc->ReturnCityByID(lSelectedItemID) != NULL)
		{
			CCitiesDialog oCitiesDialog(NULL, pDoc->ReturnCityByID(lSelectedItemID), Delete); //entity to pass data to console 
			if (lSelectedItemPosition >= 0)
			{
				INT_PTR nRet = -1;
				nRet = oCitiesDialog.DoModal();
				if (nRet == IDOK)
				{
					pDoc->DeleteWhereID(oCitiesDialog.m_recCity.lID, lSelectedItemPosition);
				}
			}
		}
	}
}