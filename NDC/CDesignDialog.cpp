#include "StdAfx.h"
#include "CDesignDialog.h"

IMPLEMENT_DYNAMIC(CDesignDialog, CObject)
BEGIN_MESSAGE_MAP(CDesignDialog, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

CDesignDialog::~CDesignDialog() {

	if (m_hBkgndBrush){
		DeleteObject(m_hBkgndBrush);
    }
}

void CDesignDialog::Init() {
	m_hBkgndBrush = CreateSolidBrush(RGB(226, 230, 233));
}

HBRUSH CDesignDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC )
	{
		DWORD d = GetSysColor(COLOR_BTNFACE);

		COLORREF normal = RGB(GetRValue(d), GetGValue(d), GetBValue(d));
	
		pDC->SetBkColor(RGB(226, 230, 233));

	}

	return m_hBkgndBrush;
}
