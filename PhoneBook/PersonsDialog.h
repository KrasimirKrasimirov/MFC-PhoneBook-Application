#pragma once

#include "PersonsView.h"
// CPersonsDialog dialog

class CPersonsDialog : public CDialog
{
// Macros
// ----------------
	DECLARE_DYNAMIC(CPersonsDialog)
	DECLARE_MESSAGE_MAP()
public:
	CPersonsDialog(CWnd* pParent /*== nullptr*/, PERSONS * recPersons, PHONE_NUMBERS * recPhoneNumber, DialogOptionSelectedEnum eOptionSelected, CCitiesArray * oCitiesArray, CPhoneTypesArray * oPhoneTypesArray);   // standard constructor
	virtual ~CPersonsDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PERSONS};
#endif

// MFC Overrides
// ----------------
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
// Members
// ----------------
public:
	PERSONS & m_recPerson;
	PHONE_NUMBERS & m_recPhoneNumber;
	DialogOptionSelectedEnum m_eOptionSelected;
	CCitiesArray & m_oCitiesArray;
	CPhoneTypesArray & m_oPhoneTypesArray;

	CString m_strSelectedCityName;
	CString m_strSelectedPhoneType;

	long m_lSelectedCityID;
	long m_lSelectedPhoneTypeID;

	CEdit m_edbFirstName;
	CStatic m_sttFirstName;

	CEdit m_edbMiddleName;
	CStatic m_sttMiddleName;

	CEdit m_edbFamilyName;
	CStatic m_sttFamilyName;

	CEdit m_edbUCN;
	CStatic m_sttUCN;

	CEdit m_edbAddress;
	CStatic m_sttAddress;

	CButton m_btnOK;
	CButton m_btnCancel;

	CComboBox m_cmbCityList;
	CStatic m_sttCityList;

	CEdit m_edbPhoneNumber;
	CStatic m_sttPhoneNumber;

	CComboBox m_cmbPhoneTypesList;
	CStatic m_sttPhoneTypesList;
// Methods
// ----------------
	void DisplayCurrentCityInComboBox();
	void DisplayCurrentPhoneTypeInComboBox();
	void DisplayCurrentPersonData();
	void InitializeDialogTextFields();
	void GetSelectedCityID();
	void GetSelectedPhoneTypeID();
};