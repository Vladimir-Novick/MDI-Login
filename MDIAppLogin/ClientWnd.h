#pragma once


// CClientWnd

class CClientWnd : public CWnd
{
	DECLARE_DYNAMIC(CClientWnd)

public:
	CClientWnd();
	virtual ~CClientWnd();

protected:
   afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()
};


