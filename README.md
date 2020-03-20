# MDI-Login. Basic skeleton project
Multiple-Document Interface (MDI) 

# Applications with Login Modal Dialog

 ![login](/images/screen.png)

 The modal window is a child of one of the main windows.
 However, it is blocking all the top-level windows once it is open. 

 Submitted app solves this problem. Describes how to use standard dialogs in an MDI application.

#  Design Components Library ( NDC )

Components for MFC WinForm help developers execute Design with modular and customizable UI components. 
These components enable a reliable development workflow to build beautiful and functional user experiences for C++ MFC Desktop application.

## Custom MDI Frame color


CMainFrame :

            protected:
                 CClientWnd  m_Client;

OnCreateClient action :

            BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
            {
	            if (CMDIFrameWnd::OnCreateClient(lpcs, pContext))
	            {
		            m_Client.SubclassWindow(m_hWndMDIClient);
		            return TRUE;
	            }

	            return CMDIFrameWnd::OnCreateClient(lpcs, pContext);
            }

OnClose action:

            void CMainFrame::OnClose(){
                .....
                m_Client.UnsubclassWindow();
                CMDIFrameWnd::OnClose();
            }


## Custom Dialogs

Dialogs inform users about a task and can contain critical information, require decisions, or involve multiple tasks.

Using:
  change reference from
      CDialog to CDesignDialog
      CModalDialog to CModalDesignDialog

         include: CDesignDialog.h

##  Create Resource DLLs and Language Support
  
### Create Satellite DLL ( resource-only DLL )

1) Create Empty Dynamic Link Library project with Windows Desktop Wizard.

2) Create a new resource ( .rc file )

3) Specify the /NOENTRY linker option. ( Project Properties -> Linker -> Advanced -> No Entry Point -> Select Yes option )

### Use a Satellite DLL

1) set all application resource into Satellite DLL

2) Load satellite DLL into your application initialization:

for example:

            //////////////////////////////////////////////
            // CMDIAppViewApp initialization

            BOOL CMDIAppViewApp::InitInstance()
            {

	            hResourceDLL = LoadLibrary(L"ResourceDLL.Dll");
	            AfxSetResourceHandle(hResourceDLL);

	            AfxEnableControlContainer();
                ....

You can select resources DLL file depending on your application configuration

3) Unload your sattelite DLL

for example:

            int CMDIAppViewApp::ExitInstance()
            {
                // Restores the EXE as the resource container.
                //
	            AfxSetResourceHandle(AfxGetApp()->m_hInstance); 
	            FreeLibrary(hResourceDLL);
	            hResourceDLL = NULL;

	            return CWinApp::ExitInstance();
            }