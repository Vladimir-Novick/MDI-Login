// ClientWnd.cpp : implementation file
//

#include "stdafx.h"
#include "ClientWnd.h"


// CClientWnd

IMPLEMENT_DYNAMIC(CClientWnd, CWnd)
CClientWnd::CClientWnd()
{
}

CClientWnd::~CClientWnd()
{
}


BEGIN_MESSAGE_MAP(CClientWnd, CWnd)
   ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


BOOL CClientWnd::OnEraseBkgnd(CDC* pDC)
{
   CRect Rect;
   GetClientRect(&Rect);
   pDC->FillSolidRect(&Rect,RGB(168, 178, 198));

   return TRUE;
}