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

#  Create Resource DLLs and Language Support
  
### Create Satellite DLL ( resource-only DLL )

1) Create Empty Dynamic Link Library project with Windows Desktop Wizard.

2) Create a new resource ( .rc file ).

3) copy all application resource and file resource.h into Satellite DLL.

4) Modify your application resource as your needs.

5) Specify the /NOENTRY linker option. ( Project Properties -> Linker -> Advanced -> No Entry Point -> Select Yes option )

6) Create Satellite DLL for all your application configuration 

### Use a Satellite DLL

Load satellite DLL into your application initialization:

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

#  Adding Icons to Menu Items

This is an easy way to add icons to the menu.

1) Create bitmap image.

If you using GIMP please export with:

			 Compatable Options:
			   - Do not write color space information
			 Advanced Options:  
			  - 24 bits R8 G8 B8

 2) Add to .rc file:

			ID_APP_ABOUT   BITMAP   DISCARDABLE    "res\\bitmap1.bmp"

 where ID_APP_ABOUT - your menu item ID

 3) Add WM_INITMENUPOPUP handler in MainFrame class:

 for example:

 ON_WM_INITMENUPOPUP():
 
			void CMainFrame::OnInitMenuPopup(CMenu* pMenu, UINT nIndex, BOOL bSysMenu)
			{
				CMDIFrameWnd::OnInitMenuPopup(pMenu, nIndex, bSysMenu);

				if (bSysMenu)
				{
					pMenu = GetSystemMenu(FALSE);
				}
				MENUINFO mnfo;
				mnfo.cbSize = sizeof(mnfo);
				mnfo.fMask = MIM_STYLE;
				mnfo.dwStyle = MNS_CHECKORBMP | MNS_AUTODISMISS;
				::SetMenuInfo(pMenu->GetSafeHmenu(), &mnfo);

				MENUITEMINFO minfo;
				minfo.cbSize = sizeof(minfo);
	
				for (UINT pos = 0; pos < pMenu->GetMenuItemCount(); pos++)
				{
					minfo.fMask = MIIM_FTYPE | MIIM_ID ;
					pMenu->GetMenuItemInfo(pos, &minfo, TRUE);

					if (ID_APP_ABOUT == minfo.wID) {
	
						if (hBitmapAbout == NULL) {
							hBitmapAbout = (HBITMAP)::LoadBitmap(::AfxGetResourceHandle(),
								MAKEINTRESOURCE(ID_APP_ABOUT));
						}
						SetMenuItemBitmaps(pMenu->m_hMenu, pos, 
							  MF_BYPOSITION , hBitmapAbout, hBitmapAbout);
					}
				}
			}

Destructor:

			CMainFrame::~CMainFrame()
			{
				if (hBitmapAbout != NULL) {
					DeleteObject(hBitmapAbout);
				}
			}

Constructor:

			CMainFrame::CMainFrame()
			{
				// TODO: add member initialization code here
				NotLoginExit = false;
				hBitmapAbout = NULL;
			}
