
// PhoneBook.h : main header file for the PhoneBook application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
enum DialogOptionSelectedEnum { Select, Update, Delete, Insert };

// CPhoneBookApp:
// See PhoneBook.cpp for the implementation of this class
//

class CPhoneBookApp : public CWinAppEx
{
public:
	CPhoneBookApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPhoneBookApp theApp;
