// CCitiesDialog.cpp : implementation file
//

#include "stdafx.h"
#include "PhoneBook.h"
#include "CitiesDialog.h"
#include "afxdialogex.h"


// CCitiesDialog dialog

IMPLEMENT_DYNAMIC(CCitiesDialog, CDialog)

BEGIN_MESSAGE_MAP(CCitiesDialog, CDialog)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CCitiesDialog::CCitiesDialog(CWnd* pParent /*=nullptr*/, CITIES * recCities, DialogOptionSelectedEnum eOptionSelected)
	: CDialog(IDD_DIALOG_CITIES, pParent), m_recCity(*recCities), m_eOptionSelected(eOptionSelected)
{
}

CCitiesDialog::~CCitiesDialog()
{
}

// MFC Overrides
// ----------------
void CCitiesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_CITIES_NAME, m_edbName);
	DDX_Control(pDX, IDC_STT_CITIES_NAME, m_sttName);
	DDX_Control(pDX, IDC_EDB_CITIES_REGION, m_edbRegion);
	DDX_Control(pDX, IDC_STT_CITIES_REGION, m_sttRegion);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}

// MFC Message Handlers
// ----------------
BOOL CCitiesDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_edbName.SetWindowText(_T(""));
	m_edbName.SetLimitText(CITY_NAME_SIZE);

	m_edbRegion.SetWindowText(_T(""));
	m_edbRegion.SetLimitText(CITY_REGION_SIZE);
	CString strText;
	switch (m_eOptionSelected)
	{
	case Select:
		strText = m_recCity.szName;
		strText.Trim();
		m_edbName.SetWindowText(strText);

		strText = m_recCity.szRegion;
		strText.Trim();
		m_edbRegion.SetWindowText(strText);

		m_edbName.SetReadOnly(true);
		m_edbRegion.SetReadOnly(true);
		break;
	case Update:
		m_btnOK.SetWindowTextW(_T("Промени данни"));
		
		strText = m_recCity.szName;
		strText.Trim();
		m_edbName.SetWindowText(strText);

		strText = m_recCity.szRegion;
		strText.Trim();
		m_edbRegion.SetWindowText(strText);
		break;
	case Insert:
		m_btnOK.SetWindowTextW(_T("Добави"));
		break;
	case Delete:
		m_btnOK.SetWindowTextW(_T("Изтрий данни"));

		m_edbName.SetWindowText(m_recCity.szName);
		m_edbRegion.SetWindowText(m_recCity.szRegion);

		m_edbName.EnableWindow(FALSE);
		m_edbRegion.EnableWindow(FALSE);
		break;
	}
	m_btnCancel.SetWindowTextW(_T("Отмени"));
	return TRUE;
}

void CCitiesDialog::OnOK()
{
	if (m_eOptionSelected != Delete && m_eOptionSelected != Select)
	{
		CString strText;

		//проверка на въведено име на град
		m_edbName.GetWindowText(strText);
		_tcscpy_s(m_recCity.szName, strText);
		long lInputLength = strText.GetLength();

		CString strUserInput = strText.SpanIncluding(_T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZабвгдежзийклмнопрстуфхцчшщъьюяАБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЬЮЯ "));
		long lUpdateInputLength = strUserInput.GetLength();

		if (strUserInput.IsEmpty() || lInputLength != lUpdateInputLength) // валидация на диалогово поле за име на град, проверка дали е празно или с грешни символи
		{
			AfxMessageBox(_T("Моля въведете правилни данни за име на града."));
			return;
		}
		//проверка на въведен регион на град
		m_edbRegion.GetWindowText(strText);
		_tcscpy_s(m_recCity.szRegion, strText);
		lInputLength = strText.GetLength();

		strUserInput = strText.SpanIncluding(_T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZабвгдежзийклмнопрстуфхцчшщъьюяАБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЬЮЯ "));
		lUpdateInputLength = strUserInput.GetLength();

		if (strUserInput.IsEmpty() || lInputLength != lUpdateInputLength) // валидация на диалогово поле за регион на град, проверка дали е празно или с грешни символи
		{
			AfxMessageBox(_T("Моля въведете правилни данни за име на регион."));
			return;
		}
	}
	CDialog::OnOK();
}

void CCitiesDialog::OnCancel()
{
	CDialog::OnCancel();
}