// PersonsDialog.cpp : implementation file
//
#include "stdafx.h"
#include "PhoneBook.h"
#include "PersonsDialog.h"
#include "afxdialogex.h"

// CPersonsDialog dialog
IMPLEMENT_DYNAMIC(CPersonsDialog, CDialog)

BEGIN_MESSAGE_MAP(CPersonsDialog, CDialog)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CPersonsDialog::CPersonsDialog(CWnd* pParent /*=nullptr*/, PERSONS * recPersons, PHONE_NUMBERS * recPhoneNumber,  DialogOptionSelectedEnum eOptionSelected, CCitiesArray * oCitiesArray, CPhoneTypesArray * oPhoneTypesArray)   // standard constructor
	: CDialog(IDD_DIALOG_PERSONS, pParent), m_recPerson(*recPersons), m_recPhoneNumber(*recPhoneNumber), m_eOptionSelected(eOptionSelected), m_oCitiesArray(*oCitiesArray), m_oPhoneTypesArray(*oPhoneTypesArray)
{
}

CPersonsDialog::~CPersonsDialog()
{
}

// MFC Overrides
// ----------------
void CPersonsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_PERSONS_FIRST_NAME, m_edbFirstName);
	DDX_Control(pDX, IDC_STT_PERSONS_FIRST_NAME, m_sttFirstName);
	DDX_Control(pDX, IDC_EDB_PERSONS_MIDDLE_NAME, m_edbMiddleName);
	DDX_Control(pDX, IDC_STT_PERSONS_MIDDLE_NAME, m_sttMiddleName);
	DDX_Control(pDX, IDC_EDB_PERSONS_FAMILY_NAME, m_edbFamilyName);
	DDX_Control(pDX, IDC_STT_PERSONS_FAMILY_NAME, m_sttFamilyName);
	DDX_Control(pDX, IDC_EDB_PERSONS_UCN, m_edbUCN);
	DDX_Control(pDX, IDC_STT_PERSONS_UCN, m_sttUCN);
	DDX_Control(pDX, IDC_EDB_PERSONS_ADDRESS, m_edbAddress);
	DDX_Control(pDX, IDC_STT_PERSONS_ADDRESS, m_sttAddress);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_CMB_PERSONS_CITY_LIST, m_cmbCityList);
	DDX_Control(pDX, IDC_STT_PERSONS_CITY_LIST, m_sttCityList);
	DDX_Control(pDX, IDC_EDB_PERSONS_PHONE_NUMBER, m_edbPhoneNumber);
	DDX_Control(pDX, IDC_STT_PERSONS_PHONE_NUMBER, m_sttPhoneNumber);
	DDX_Control(pDX, IDC_CMB_PERSONS_PHONE_TYPES_LIST, m_cmbPhoneTypesList);
	DDX_Control(pDX, IDC_STT_PERSONS_PHONE_TYPES_LIST, m_sttPhoneTypesList);
}

// CPersonsDialog message handlers
BOOL CPersonsDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitializeDialogTextFields();

	switch (m_eOptionSelected)
	{
	case Select:
		DisplayCurrentCityInComboBox();
		DisplayCurrentPhoneTypeInComboBox();
		DisplayCurrentPersonData();

		m_edbFirstName.SetReadOnly(true);
		m_edbMiddleName.SetReadOnly(true);
		m_edbFamilyName.SetReadOnly(true);
		m_edbUCN.SetReadOnly(true);
		m_edbAddress.SetReadOnly(true);
		m_cmbCityList.EnableWindow(FALSE);
		m_cmbPhoneTypesList.EnableWindow(FALSE);
		m_edbPhoneNumber.SetReadOnly(true);
		break;
	case Update:
		m_btnOK.SetWindowTextW(_T("Промени данни"));

		DisplayCurrentCityInComboBox();
		DisplayCurrentPhoneTypeInComboBox();
		DisplayCurrentPersonData();
		break;
	case Insert:
		m_btnOK.SetWindowTextW(_T("Добави"));
		break;
	case Delete:
		m_btnOK.SetWindowTextW(_T("Изтрий данни"));

		DisplayCurrentCityInComboBox();
		DisplayCurrentPhoneTypeInComboBox();
		DisplayCurrentPersonData();

		m_edbFirstName.EnableWindow(FALSE);
		m_edbMiddleName.EnableWindow(FALSE);
		m_edbFamilyName.EnableWindow(FALSE);
		m_edbUCN.EnableWindow(FALSE);
		m_edbAddress.EnableWindow(FALSE);
		m_cmbCityList.EnableWindow(FALSE);
		m_cmbPhoneTypesList.EnableWindow(FALSE);
		m_edbPhoneNumber.EnableWindow(FALSE);
		break;
	}
	m_btnCancel.SetWindowTextW(_T("Отмени"));
	return TRUE;
}

void CPersonsDialog::OnOK()
{
	if (m_eOptionSelected != Delete && m_eOptionSelected != Select)
	{
		CString strText;

		m_cmbCityList.GetWindowText(strText);
		m_strSelectedCityName = strText;
		GetSelectedCityID();
		
		m_cmbPhoneTypesList.GetWindowText(strText);
		m_strSelectedPhoneType = strText;
		GetSelectedPhoneTypeID();

		//проверка на въведено име на абонат
		m_edbFirstName.GetWindowText(strText);
		_tcscpy_s(m_recPerson.szFirstName, strText);
		long lInputLength = strText.GetLength();

		CString strUserInput = strText.SpanIncluding(_T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZабвгдежзийклмнопрстуфхцчшщъьюяАБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЬЮЯ "));
		long lUpdateInputLength = strUserInput.GetLength();

		if (strUserInput.IsEmpty() || lInputLength != lUpdateInputLength) // валидация на диалогово поле за име на абоната, проверка дали е празно или с грешни символи
		{
			AfxMessageBox(_T("Моля въведете правилни данни за име на абоната."));
			return;
		}

		//проверка на въведено презиме на абонат
		m_edbMiddleName.GetWindowText(strText);
		_tcscpy_s(m_recPerson.szMiddleName, strText);
		lInputLength = strText.GetLength();

		strUserInput = strText.SpanIncluding(_T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZабвгдежзийклмнопрстуфхцчшщъьюяАБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЬЮЯ "));
		lUpdateInputLength = strUserInput.GetLength();

		if (strUserInput.IsEmpty() || lInputLength != lUpdateInputLength) // валидация на диалогово поле за презиме на абоната, проверка дали е празно или с грешни символи
		{
			AfxMessageBox(_T("Моля въведете правилни данни за презиме на абоната."));
			return;
		}

		//проверка на въведена фамилия на абонат
		m_edbFamilyName.GetWindowText(strText);
		_tcscpy_s(m_recPerson.szFamilyName, strText);
		lInputLength = strText.GetLength();

		strUserInput = strText.SpanIncluding(_T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZабвгдежзийклмнопрстуфхцчшщъьюяАБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЬЮЯ "));
		lUpdateInputLength = strUserInput.GetLength();

		if (strUserInput.IsEmpty() || lInputLength != lUpdateInputLength) // валидация на диалогово поле за фамилия на абоната, проверка дали е празно или с грешни символи
		{
			AfxMessageBox(_T("Моля въведете правилни данни за фамилия на абоната."));
			return;
		}

		//проверка на въведено ЕГН на абонат
		m_edbUCN.GetWindowText(strText);
		_tcscpy_s(m_recPerson.szUCN, strText);
		lInputLength = strText.GetLength();

		strUserInput = strText.SpanIncluding(_T("0123456789"));
		lUpdateInputLength = strUserInput.GetLength();

		if (strUserInput.IsEmpty() || lInputLength != lUpdateInputLength) // валидация на диалогово поле за ЕГН на абоната, проверка дали е празно или с грешни символи
		{
			AfxMessageBox(_T("Моля въведете правилни данни за ЕГН на абоната."));
			return;
		}

		//проверка на въведен адрес на абонат
		m_edbAddress.GetWindowText(strText);
		_tcscpy_s(m_recPerson.szAddress, strText);
		lInputLength = strText.GetLength();

		strUserInput = strText.SpanIncluding(_T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZабвгдежзийклмнопрстуфхцчшщъьюяАБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЬЮЯ0123456789. "));
		lUpdateInputLength = strUserInput.GetLength();

		if (strUserInput.IsEmpty() || lInputLength != lUpdateInputLength) // валидация на диалогово поле за адрес на абоната, проверка дали е празно или с грешни символи
		{
			AfxMessageBox(_T("Моля въведете правилни данни за адрес на абоната."));
			return;
		}

		//проверка на въведен телефонен номер на абонат
		m_edbPhoneNumber.GetWindowText(strText);
		_tcscpy_s(m_recPhoneNumber.szPhoneNumber, strText);
		lInputLength = strText.GetLength();

		strUserInput = strText.SpanIncluding(_T("0123456789+ "));
		lUpdateInputLength = strUserInput.GetLength();

		if (strUserInput.IsEmpty() || lInputLength != lUpdateInputLength) // валидация на диалогово поле за телефонен номер на абоната, проверка дали е празно или с грешни символи
		{
			AfxMessageBox(_T("Моля въведете правилни данни за телефонен номер на абоната."));
			return;
		}
	}
	CDialog::OnOK();
}

void CPersonsDialog::OnCancel()
{
	CDialog::OnCancel();
}

void CPersonsDialog::DisplayCurrentCityInComboBox()
{
	for (int i = 0; i < m_oCitiesArray.GetSize(); i++)
	{
		if (m_recPerson.lCityID == m_oCitiesArray.GetAt(i)->lID)
		{
			m_cmbCityList.SetCurSel(i);
		}
	}
}

void CPersonsDialog::DisplayCurrentPhoneTypeInComboBox()
{
	for (int i = 0; i < m_oPhoneTypesArray.GetSize(); i++)
	{
		if (m_recPhoneNumber.lPhoneTypeID == m_oPhoneTypesArray.GetAt(i)->lID)
		{
			m_cmbPhoneTypesList.SetCurSel(i);
		}
	}
}

void CPersonsDialog::DisplayCurrentPersonData()
{
	CString strText;

	strText = m_recPerson.szFirstName;
	strText.Trim();
	m_edbFirstName.SetWindowText(strText);

	strText = m_recPerson.szMiddleName;
	strText.Trim();
	m_edbMiddleName.SetWindowText(strText);

	strText = m_recPerson.szFamilyName;
	strText.Trim();
	m_edbFamilyName.SetWindowText(strText);

	strText = m_recPerson.szUCN;
	strText.Trim();
	m_edbUCN.SetWindowText(strText);

	strText = m_recPerson.szAddress;
	strText.Trim();
	m_edbAddress.SetWindowText(strText);

	strText = m_recPhoneNumber.szPhoneNumber;
	strText.Trim();
	m_edbPhoneNumber.SetWindowText(strText);
}

void CPersonsDialog::InitializeDialogTextFields()
{
	for (int i = 0; i < m_oCitiesArray.GetSize(); i++)
	{
		m_cmbCityList.AddString(m_oCitiesArray.GetAt(i)->szName);
	}
	m_cmbCityList.SetCurSel(0);

	for (int i = 0; i < m_oPhoneTypesArray.GetSize(); i++)
	{
		m_cmbPhoneTypesList.AddString(m_oPhoneTypesArray.GetAt(i)->szType);
	}
	m_cmbPhoneTypesList.SetCurSel(0);

	m_edbPhoneNumber.SetWindowText(_T(""));
	m_edbPhoneNumber.SetLimitText(PHONE_NUMBER_SIZE);

	m_edbFirstName.SetWindowText(_T(""));
	m_edbFirstName.SetLimitText(PERSON_FIRST_NAME_SIZE);

	m_edbMiddleName.SetWindowText(_T(""));
	m_edbMiddleName.SetLimitText(PERSON_MIDDLE_NAME_SIZE);

	m_edbFamilyName.SetWindowText(_T(""));
	m_edbFamilyName.SetLimitText(PERSON_FAMILY_NAME_SIZE);

	m_edbUCN.SetWindowText(_T(""));
	m_edbUCN.SetLimitText(UCN_SIZE);

	m_edbAddress.SetWindowText(_T(""));
	m_edbAddress.SetLimitText(ADDRESS_SIZE);
}

void CPersonsDialog::GetSelectedCityID()
{
	for (int i = 0; i < m_oCitiesArray.GetSize(); i++)
	{
		if (m_strSelectedCityName == m_oCitiesArray.GetAt(i)->szName)
		{
			m_lSelectedCityID = m_oCitiesArray.GetAt(i)->lID;
		}
	}
}

void CPersonsDialog::GetSelectedPhoneTypeID()
{
	for (int i = 0; i < m_oPhoneTypesArray.GetSize(); i++)
	{
		if (m_strSelectedPhoneType == m_oPhoneTypesArray.GetAt(i)->szType)
		{
			m_lSelectedPhoneTypeID = m_oPhoneTypesArray.GetAt(i)->lID;
		}
	}
}