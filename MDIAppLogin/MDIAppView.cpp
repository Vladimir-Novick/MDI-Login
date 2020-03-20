// MDIAppView.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MDIAppView.h"

#include "CMainFrame.h"
#include "CChildFrame.h"
#include "MDIAppViewDoc.h"
#include "MDIAppViewView.h"
#include "CDialogAbout.h"

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

/////////////////////////////////////////////////////////////////////////////
// CMDIAppViewApp

BEGIN_MESSAGE_MAP(CMDIAppViewApp, CWinApp)
	//{{AFX_MSG_MAP(CMDIAppViewApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMDIAppViewApp construction

CMDIAppViewApp::CMDIAppViewApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMDIAppViewApp object

CMDIAppViewApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMDIAppViewApp initialization

BOOL CMDIAppViewApp::InitInstance()
{

	hResourceDLL = LoadLibrary(L"ResourceDLL.Dll");
	AfxSetResourceHandle(hResourceDLL);

	AfxEnableControlContainer();


	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("MDIAppLogin_Application"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_MYMDIATYPE,
		RUNTIME_CLASS(CMDIAppViewDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CMDIAppViewView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

// App command to run the dialog
void CMDIAppViewApp::OnAppAbout()
{
	AfxBeginThread(RUNTIME_CLASS(CDialogAbout));
}

/////////////////////////////////////////////////////////////////////////////
// CMDIAppViewApp message handlers



HINSTANCE CMDIAppViewApp::LoadAppLangResourceDLL()
{
	// TODO: Add your specialized code here and/or call the base class

	return CWinApp::LoadAppLangResourceDLL();
}


int CMDIAppViewApp::ExitInstance()
{
	AfxSetResourceHandle(AfxGetApp()->m_hInstance); // Restores the EXE as the resource container.
	FreeLibrary(hResourceDLL);
	hResourceDLL = NULL;

	return CWinApp::ExitInstance();
}
