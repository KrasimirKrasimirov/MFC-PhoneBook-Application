// PhoneTypesDialog.cpp : implementation file
//

#include "stdafx.h"
#include "PhoneBook.h"
#include "PhoneTypesDialog.h"
#include "afxdialogex.h"


// CPhoneTypesDialog dialog

IMPLEMENT_DYNAMIC(CPhoneTypesDialog, CDialog)

BEGIN_MESSAGE_MAP(CPhoneTypesDialog, CDialog)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CPhoneTypesDialog::CPhoneTypesDialog(CWnd* pParent /*=nullptr*/, PHONE_TYPES * recPhoneTypes, DialogOptionSelectedEnum eOptionSelected)
	: CDialog(IDD_DIALOG_PHONE_TYPES, pParent), m_recPhoneType(*recPhoneTypes), m_eOptionSelected(eOptionSelected)
{
}

CPhoneTypesDialog::~CPhoneTypesDialog()
{
}

// MFC Overrides
// ----------------
void CPhoneTypesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_PHONE_TYPES_TYPE, m_edbPhoneType);
	DDX_Control(pDX, IDC_STT_PHONE_TYPES_TYPE, m_sttPhoneType);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}

// MFC Message Handlers
// ----------------
BOOL CPhoneTypesDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_edbPhoneType.SetWindowText(_T(""));
	m_edbPhoneType.SetLimitText(PHONE_TYPE_TYPE_SIZE);

	CString strText;

	switch (m_eOptionSelected)
	{
	case Select:
		strText = m_recPhoneType.szType;
		strText.Trim();
		m_edbPhoneType.SetWindowText(strText);

		m_edbPhoneType.SetReadOnly(true);
		break;
	case Update:
		m_btnOK.SetWindowTextW(_T("Промени данни"));
		
		strText = m_recPhoneType.szType;
		strText.Trim();
		m_edbPhoneType.SetWindowText(strText);
		break;
	case Insert:
		m_btnOK.SetWindowTextW(_T("Добави"));
		break;
	case Delete:
		m_btnOK.SetWindowTextW(_T("Изтрий данни"));

		m_edbPhoneType.SetWindowText(m_recPhoneType.szType);
		m_edbPhoneType.EnableWindow(FALSE);
		break;
	}
	m_btnCancel.SetWindowTextW(_T("Отмени"));
	return TRUE;
}


void CPhoneTypesDialog::OnOK()
{
	if (m_eOptionSelected != Delete && m_eOptionSelected != Select)
	{
		CString strText;

		//проверка на въведен тип телефон
		m_edbPhoneType.GetWindowText(strText);
		_tcscpy_s(m_recPhoneType.szType, strText);
		long lInputLength = strText.GetLength();

		CString strUserInput = strText.SpanIncluding(_T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZабвгдежзийклмнопрстуфхцчшщъьюяАБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЬЮЯ "));
		long lUpdateInputLength = strUserInput.GetLength();

		if (strUserInput.IsEmpty() || lInputLength != lUpdateInputLength) // валидация на диалогово поле за име на град, проверка дали е празно или с грешни символи
		{
			AfxMessageBox(_T("Моля въведете правилни данни за тип телефон."));
			return;
		}
	}
	CDialog::OnOK();
}

void CPhoneTypesDialog::OnCancel()
{
	CDialog::OnCancel();
}