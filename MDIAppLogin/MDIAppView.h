
#pragma once


#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMDIAppViewApp:
// See MDIAppView.cpp for the implementation of this class
//

class CMDIAppViewApp : public CWinApp
{

public:
	CMDIAppViewApp();
	HINSTANCE hResourceDLL;



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDIAppViewApp)

	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMDIAppViewApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	virtual HINSTANCE LoadAppLangResourceDLL();
	virtual int ExitInstance();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

