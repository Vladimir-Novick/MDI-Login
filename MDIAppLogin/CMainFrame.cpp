// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MDIAppView.h"

#include "CMainFrame.h"
#include "CLoginDialog.h"

#ifdef _DEBUG
#undef DEBUG_NEW
#define DEBUG_NEW new(__FILE__, __LINE__)
#define _CRTDBG_MAP_ALLOC
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#else
#undef _CRTDBG_MAP_ALLOC
#define DEBUG_NEW new
#endif

const UINT WM_PAINTMYCAPTION = WM_USER + 5;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
	ON_WM_ERASEBKGND()
	ON_MESSAGE(WM_PAINTMYCAPTION, OnPaintMyCaption)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	NotLoginExit = false;
}

CMainFrame::~CMainFrame()
{
}

#pragma region updateTitle ---

void CMainFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	if (m_capp != NULL )
	   m_capp->UpdateFrameTitle(m_hWnd, m_strTitle);
}


LRESULT CMainFrame::OnPaintMyCaption(WPARAM bActive, LPARAM lParam)
{
	if (m_capp != NULL)
	    m_capp->PaintMyCaption(bActive, lParam, m_strTitle);
	return 0;
}

#pragma endregion 

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

#pragma region custom close button

	ModifyStyle(WS_SYSMENU, 0); // Remove standard system menu

#pragma endregion
	m_capp = new CCaptionPainter();
	m_capp->Install(this, WM_PAINTMYCAPTION);

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs



	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers



void CMainFrame::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CMDIFrameWnd::OnShowWindow(bShow, nStatus);

	// show login screen  
	if (bShow) {
		loginDialog = RUNTIME_CLASS(CLoginDialog); // Create login dialog
		AfxBeginThread(loginDialog);				// show login dialog
	}

	// TODO: Add your message handler code here
}


void CMainFrame::OnClose()
{
	if (NotLoginExit) {
		m_capp->Uninstall();
		delete m_capp;
		m_Client.UnsubclassWindow();
		CMDIFrameWnd::OnClose();  //  close message from login screen
	}
	else {
		
		if (AfxMessageBox(L"Are you Sure to quit?", MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			m_capp->Uninstall();
			delete m_capp;
			m_Client.UnsubclassWindow();
			CMDIFrameWnd::OnClose();
		}
	}

}


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	if (CMDIFrameWnd::OnCreateClient(lpcs, pContext))
	{
		m_Client.SubclassWindow(m_hWndMDIClient);
		return TRUE;
	}

	return CMDIFrameWnd::OnCreateClient(lpcs, pContext);
}



