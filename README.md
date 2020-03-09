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

## Dialogs

Dialogs inform users about a task and can contain critical information, require decisions, or involve multiple tasks.

Using:
  change reference from
      CDialog to CDesignDialog
      CModalDialog to CModalDesignDialog

         include: CDesignDialog.h
  