#pragma once

#include "PhoneTypesView.h"
// CPhoneTypesDialog dialog

class CPhoneTypesDialog : public CDialog
{
	// Macros
	// ----------------
	DECLARE_DYNAMIC(CPhoneTypesDialog)
	DECLARE_MESSAGE_MAP()

public:
	CPhoneTypesDialog(CWnd* pParent /*= nullptr*/, PHONE_TYPES * recPhoneTypes, DialogOptionSelectedEnum eOptionSelected);   // standard constructor
	virtual ~CPhoneTypesDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PHONE_TYPES };
#endif
// MFC Overrides
// ----------------
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Overrides
// ----------------
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();

	// Members
	// ----------------
public:
	PHONE_TYPES & m_recPhoneType;
	CEdit m_edbPhoneType;
	CStatic m_sttPhoneType;
	CButton m_btnOK;
	CButton m_btnCancel;

	DialogOptionSelectedEnum m_eOptionSelected;
};
