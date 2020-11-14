#pragma once

/// <summary>
///   Client Window for MDI Frame. Support erase backgrownd to custom color 
/// </summary>
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

class CMainFrameInterface {
protected:
	static CFont* AppDefaultFont;
public:
	static CFont* GetAppDefaultFont();
	static void SetAppDefaultFont(CFont* font);
};

