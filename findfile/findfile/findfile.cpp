// findfile.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "findfile.h"
#include "CMDLine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;
CCMDLine cmdLine;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// 初始化 MFC 并在失败时显示错误
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: 更改错误代码以符合您的需要
		_tprintf(_T("错误: MFC 初始化失败\n"));
		nRetCode = 1;
	}
	else
	{
		theApp.ParseCommandLine (cmdLine);
		if(cmdLine.m_bIsFileDlg) {
			if(cmdLine.m_szFile.GetLength() ==0 || cmdLine.m_szFilter.GetLength() == 0) {
				nRetCode = 1;
			} else {
				CFileDialog dlgFile(cmdLine.m_bIsOpen,0,cmdLine.m_szFile,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,cmdLine.m_szFilter);
				if(dlgFile.DoModal() == IDOK) {
					_tprintf(_T("%s"), dlgFile.GetPathName());
				} else {
					nRetCode = 1;
				}
			}
		} else {
			BROWSEINFO   bi; 
			ZeroMemory(&bi,   sizeof(bi)); 
			TCHAR   szDisplayName[MAX_PATH]; 
			szDisplayName[0]    =   0;  

			bi.hwndOwner        =   NULL; 
			bi.pidlRoot         =   NULL; 
			bi.pszDisplayName   =   szDisplayName; 
			bi.lpszTitle        =   (LPCTSTR)cmdLine.m_szDlgTitle; 
			bi.ulFlags          =   BIF_RETURNONLYFSDIRS|BIF_NEWDIALOGSTYLE;
			bi.lParam           =   NULL; 
			bi.iImage           =   0;  

			LPITEMIDLIST   pidl   =   SHBrowseForFolder(&bi);
			TCHAR   szPathName[MAX_PATH]; 
			if   (NULL   !=   pidl)
			{
				 BOOL bRet = SHGetPathFromIDList(pidl,szPathName);
				 size_t nLen = 0;
				 if(FALSE == bRet) {
					  nRetCode = 1;
				 } else {
					 nRetCode = 0;
					 nLen = _tcslen(szPathName);
					 if(szPathName[nLen - 1] != _T('\\')) {
						szPathName[nLen] = _T('\\');
						szPathName[++nLen] = 0;
					 }
					_tprintf(_T("%s"), szPathName);
				 }
			} else {
				nRetCode = 1;
			}
		}
	}

	return nRetCode;
}
