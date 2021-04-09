#pragma once

#include "CitiesView.h"
// CCitiesDialog dialog

class CCitiesDialog : public CDialog
{
	// Macros
	// ----------------
	DECLARE_DYNAMIC(CCitiesDialog)
	DECLARE_MESSAGE_MAP()
public:
	CCitiesDialog(CWnd* pParent /*= nullptr*/, CITIES * recCities, DialogOptionSelectedEnum nOptionSelected);   // standard constructor
	virtual ~CCitiesDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CITIES };
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
private:
	
	// Members
	// ----------------
public:
	CITIES & m_recCity;
	CEdit m_edbName;
	CStatic m_sttName;
	CEdit m_edbRegion;
	CStatic m_sttRegion;
	CButton m_btnOK;
	CButton m_btnCancel;
	DialogOptionSelectedEnum m_eOptionSelected;
};