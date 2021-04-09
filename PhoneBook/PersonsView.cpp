// PersonsView.cpp : implementation of the PersonsView class
//
#include "stdafx.h"
#include "PhoneBook.h"
#include "PersonsView.h"

// CPersonsView

IMPLEMENT_DYNCREATE(CPersonsView, CListView)

BEGIN_MESSAGE_MAP(CPersonsView, CListView)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_MENU_UPDATE, &CPersonsView::OnMenuUpdate)
	ON_COMMAND(ID_MENU_DELETE, &CPersonsView::OnMenuDelete)
	ON_COMMAND(ID_MENU_INSERT, &CPersonsView::OnMenuInsert)
	ON_COMMAND(ID_MENU_SELECT, &CPersonsView::OnMenuSelect)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CPersonsView::CPersonsView()
{
}

CPersonsView::~CPersonsView()
{
}

// CPersonsView diagnostics

#ifdef _DEBUG
void CPersonsView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonsView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CPersonsDoc* CPersonsView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPersonsDoc)));
	return (CPersonsDoc*)m_pDocument;
}
#endif
#endif //_DEBUG

BOOL CPersonsView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= LVS_REPORT;
	return CListView::PreCreateWindow(cs);
}

void CPersonsView::OnDraw(CDC* /*pDC*/)
{
	CPersonsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

void CPersonsView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	CPersonsDoc* pDoc = GetDocument();
	CListCtrl& oListCtrl = GetListCtrl();

	if (oListCtrl.GetItemCount() == 0) // if list control is empty
	{
		//CPersonsTable oCitiesTable;
		oListCtrl.DeleteAllItems();

		pDoc->m_oPersonsArray.RemoveAll();
		pDoc->SelectAll(pDoc->m_oPersonsArray);

		pDoc->m_oPhoneNumbersArray.RemoveAll();
		pDoc->SelectAll(pDoc->m_oPhoneNumbersArray);

		int nIndex;
		// Insert columns
		oListCtrl.InsertColumn(0, _T("Име"), LVCFMT_LEFT, -1, 0);
		oListCtrl.InsertColumn(1, _T("Презиме"), LVCFMT_LEFT, -1, 1);
		oListCtrl.InsertColumn(2, _T("Фамилия"), LVCFMT_LEFT, -1, 2);
		oListCtrl.InsertColumn(3, _T("ЕГН"), LVCFMT_LEFT, -1, 3);
		oListCtrl.InsertColumn(4, _T("Адрес"), LVCFMT_LEFT, -1, 4);

		for (int i = 0; i < pDoc->m_oPersonsArray.GetSize(); i++)
		{
			// Insert row
			nIndex = oListCtrl.InsertItem(LVIF_TEXT, i, pDoc->m_oPersonsArray.GetAt(i)->szFirstName, 0, 0, 0, NULL);
			oListCtrl.SetItem(nIndex, 1, LVIF_TEXT, pDoc->m_oPersonsArray.GetAt(i)->szMiddleName, 0, 0, 0, NULL);
			oListCtrl.SetItem(nIndex, 2, LVIF_TEXT, pDoc->m_oPersonsArray.GetAt(i)->szFamilyName, 0, 0, 0, NULL);
			oListCtrl.SetItem(nIndex, 3, LVIF_TEXT, pDoc->m_oPersonsArray.GetAt(i)->szUCN, 0, 0, 0, NULL);
			oListCtrl.SetItem(nIndex, 4, LVIF_TEXT, pDoc->m_oPersonsArray.GetAt(i)->szAddress, 0, 0, 0, NULL);

			oListCtrl.SetItemData(nIndex, pDoc->m_oPersonsArray.GetAt(i)->lID);
		}
		// Set column widths
		oListCtrl.SetColumnWidth(0, LVSCW_AUTOSIZE);
		oListCtrl.SetColumnWidth(1, LVSCW_AUTOSIZE);
		oListCtrl.SetColumnWidth(2, LVSCW_AUTOSIZE);
		oListCtrl.SetColumnWidth(3, LVSCW_AUTOSIZE);
		oListCtrl.SetColumnWidth(4, LVSCW_AUTOSIZE);
	}
}

void CPersonsView::OnUpdate(CView* /*pSender*/, LPARAM lHint, CObject* pHint)
{
	CPersonsDoc* pDoc = GetDocument();
	CListCtrl& oListCtrl = GetListCtrl();
	long * lID; //used to point at ID of the item to be deleted, passed by method delete

	PERSONS * oChangedPerson; // used to point at person passed by methods update and insert
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
			oChangedPerson = (PERSONS*)pHint;
			for (int i = 0; i < pDoc->m_oPersonsArray.GetSize(); i++)
			{
				if (oListCtrl.GetItemData(i) == oChangedPerson->lID)
				{
					oListCtrl.SetItem(i, 0, LVIF_TEXT, oChangedPerson->szFirstName, 0, 0, 0, NULL);
					oListCtrl.SetItem(i, 1, LVIF_TEXT, oChangedPerson->szMiddleName, 0, 0, 0, NULL);
					oListCtrl.SetItem(i, 2, LVIF_TEXT, oChangedPerson->szFamilyName, 0, 0, 0, NULL);
					oListCtrl.SetItem(i, 3, LVIF_TEXT, oChangedPerson->szUCN, 0, 0, 0, NULL);
					oListCtrl.SetItem(i, 4, LVIF_TEXT, oChangedPerson->szAddress, 0, 0, 0, NULL);
				}
			}
			break;
		case ON_INSERT_IDENTIFIER:
			oChangedPerson = (PERSONS*)pHint;

			int nIndex;
			nIndex = oListCtrl.InsertItem(LVIF_TEXT, oListCtrl.GetItemCount(), oChangedPerson->szFirstName, 0, 0, 0, NULL);
			oListCtrl.SetItem(nIndex, 1, LVIF_TEXT, oChangedPerson->szMiddleName, 0, 0, 0, NULL);
			oListCtrl.SetItem(nIndex, 2, LVIF_TEXT, oChangedPerson->szFamilyName, 0, 0, 0, NULL);
			oListCtrl.SetItem(nIndex, 3, LVIF_TEXT, oChangedPerson->szUCN, 0, 0, 0, NULL);
			oListCtrl.SetItem(nIndex, 4, LVIF_TEXT, oChangedPerson->szAddress, 0, 0, 0, NULL);
			oListCtrl.SetItemData(nIndex, oChangedPerson->lID);
			break;
		}
	}
}

BOOL CPersonsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return CListView::OnPreparePrinting(pInfo);
}

void CPersonsView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	//CListView::OnBeginPrinting(pDC, pInfo);
}

void CPersonsView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	//CListView::OnEndPrinting(pDC, pInfo);
}

void CPersonsView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CPersonsDoc* pDoc = GetDocument();

	CMenu cm;
	cm.LoadMenuW(IDR_MENU1);
	cm.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);

}

void CPersonsView::OnMenuSelect()
{
	CPersonsDoc* pDoc = GetDocument();
	CListCtrl& oListCtrl = GetListCtrl();

	POSITION oPos = oListCtrl.GetFirstSelectedItemPosition();
	long lSelectedItemPosition = 0;
	long lSelectedItemID = 0;
	if (oPos) // ако реално има избран елемент
	{
		lSelectedItemPosition = oListCtrl.GetSelectionMark(); //selection position
		lSelectedItemID = oListCtrl.GetItemData(lSelectedItemPosition); // selection id

		if (pDoc->ReturnPersonByID(lSelectedItemID) != NULL)
		{
			CPersonsDialog oPersonsDialog(NULL, pDoc->ReturnPersonByID(lSelectedItemID), pDoc->ReturnPhoneNumberByID(lSelectedItemID), Select, pDoc->SelectAllCities(), pDoc->SelectAllPhoneTypes());
			
			if (lSelectedItemPosition >= 0)
			{
				INT_PTR nRet = -1;
				nRet = oPersonsDialog.DoModal();
				if (nRet == IDOK)
				{
					pDoc->SelectWhereID(oPersonsDialog.m_recPerson.lID, oPersonsDialog.m_recPerson);
				}
			}
		}
	}
}

void CPersonsView::OnMenuInsert()
{
	CPersonsDoc* pDoc = GetDocument();
	CListCtrl& oListCtrl = GetListCtrl();

	PERSONS oPersonForDialog;
	PHONE_NUMBERS pPhoneNumber;
	CPersonsDialog oPersonsDialog(NULL, &oPersonForDialog, &pPhoneNumber, Insert, pDoc->SelectAllCities(), pDoc->SelectAllPhoneTypes());

	INT_PTR nRet = -1;
	nRet = oPersonsDialog.DoModal();

	if (nRet == IDOK)
	{
		if (!pDoc->Insert(oPersonsDialog.m_recPerson, oPersonsDialog.m_strSelectedCityName))
		{
			return;
		}
		oPersonsDialog.m_recPhoneNumber.lPersonID = oPersonsDialog.m_recPerson.lID;
		pDoc->Insert(oPersonsDialog.m_recPhoneNumber, oPersonsDialog.m_strSelectedPhoneType);
	}
}
void CPersonsView::OnMenuUpdate()
{
	CPersonsDoc* pDoc = GetDocument();
	CListCtrl& oListCtrl = GetListCtrl();

	POSITION oPos = oListCtrl.GetFirstSelectedItemPosition();
	long lSelectedItemPosition = 0;
	long lSelectedItemID = 0;

	if (oPos)
	{
		lSelectedItemPosition = oListCtrl.GetSelectionMark(); //selection position
		lSelectedItemID = oListCtrl.GetItemData(lSelectedItemPosition); // selection id

		if (pDoc->ReturnPersonByID(lSelectedItemID) != NULL)
		{
			CPersonsDialog oPersonsDialog(NULL, pDoc->ReturnPersonByID(lSelectedItemID), pDoc->ReturnPhoneNumberByID(lSelectedItemID), Update, pDoc->SelectAllCities(), pDoc->SelectAllPhoneTypes());
			if (lSelectedItemPosition >= 0)
			{
				INT_PTR nRet = -1;
				nRet = oPersonsDialog.DoModal();
				if (nRet == IDOK)
				{
					oPersonsDialog.m_recPerson.lCityID = oPersonsDialog.m_lSelectedCityID;
					oPersonsDialog.m_recPhoneNumber.lPhoneTypeID = oPersonsDialog.m_lSelectedPhoneTypeID;

					pDoc->UpdateWhereID(oPersonsDialog.m_recPerson.lID, oPersonsDialog.m_recPerson);
					pDoc->UpdateWhereID(oPersonsDialog.m_recPhoneNumber.lID, oPersonsDialog.m_recPhoneNumber);
				}
			}
		}
	}
}


void CPersonsView::OnMenuDelete()
{
	CPersonsDoc* pDoc = GetDocument();
	CListCtrl& oListCtrl = GetListCtrl();

	POSITION oPos = oListCtrl.GetFirstSelectedItemPosition();
	long lSelectedItemPosition = 0;
	long lSelectedItemID = 0;
	if (oPos)
	{
		lSelectedItemPosition = oListCtrl.GetSelectionMark(); // selection position
		lSelectedItemID = oListCtrl.GetItemData(lSelectedItemPosition); // selection id

		if (pDoc->ReturnPersonByID(lSelectedItemID) != NULL)
		{
			CPersonsDialog oPersonsDialog(NULL, pDoc->ReturnPersonByID(lSelectedItemID), pDoc->ReturnPhoneNumberByID(lSelectedItemID), Delete, pDoc->SelectAllCities(), pDoc->SelectAllPhoneTypes()); //entity to pass data to console 
			if (lSelectedItemPosition >= 0)
			{
				INT_PTR nRet = -1;
				nRet = oPersonsDialog.DoModal();
				if (nRet == IDOK)
				{
					pDoc->DeleteWhereID(oPersonsDialog.m_recPerson.lID, lSelectedItemPosition);
				}
			}
		}
	}
}