#pragma once
#include <afxwin.h>

// all CModalDialog functionality is now in CDialog
#define CModalDesignDialog    CDesignDialog

class CDesignDialog : public CDialog
{

	DECLARE_DYNAMIC(CDesignDialog)

private:
	HBRUSH m_hBkgndBrush;

	void Init();

public:


	CDesignDialog() :CDialog() {
		Init();
	}

	explicit CDesignDialog(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL):CDialog(lpszTemplateName, pParentWnd) {
		Init();
	};
	explicit CDesignDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL) : CDialog(nIDTemplate, pParentWnd) {
		Init();
	};

	virtual ~CDesignDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

