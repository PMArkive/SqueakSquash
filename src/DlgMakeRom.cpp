﻿
//UTF8♔


#include "stdafx.h"
#include "DlgMakeRom.h"




IMPLEMENT_DYNAMIC(CDlgMakeRom, CDialog)

CDlgMakeRom::CDlgMakeRom(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMakeRom::IDD, pParent)
{

}

CDlgMakeRom::~CDlgMakeRom()
{
}

void CDlgMakeRom::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MR_ROM, m_EditRom);
	DDX_Control(pDX, IDC_EDIT_MR_NEWROM, m_EditNewRom);
	DDX_Control(pDX, IDC_EDIT_MR_MAPSET, m_EditMapSet);
	DDX_Control(pDX, IDC_EDIT_NDSEMU, m_EditNdsEmu);
	DDX_Control(pDX, IDC_STATIC_NDSEMU, m_StaticNdsEmu);
	DDX_Control(pDX, IDC_BUTTON_BEGINEMU, m_ButtonBeginEmu);
	DDX_Control(pDX, IDC_CHECK_MAKEROM_V2, m_CheckV2);
}


BEGIN_MESSAGE_MAP(CDlgMakeRom, CDialog)
	ON_COMMAND(IDC_BUTTON_MR_ROM, &CDlgMakeRom::OnMrRom)
	ON_COMMAND(IDC_BUTTON_MR_NEWROM, &CDlgMakeRom::OnMrNewrom)
	ON_COMMAND(IDC_BUTTON_MAKEROM, &CDlgMakeRom::OnMakeRom)
	ON_BN_CLICKED(IDC_BUTTON_NDSEMU, &CDlgMakeRom::OnBnClickedButtonNdsemu)
	ON_BN_CLICKED(IDC_BUTTON_BEGINEMU, &CDlgMakeRom::OnBnClickedButtonBeginemu)
END_MESSAGE_MAP()



void CDlgMakeRom::OnMrRom()
{
	TCHAR strPath[1000]={0};
	GetPrivateProfileString(_T("FILE"),_T("RomPath"),0,strPath,999,ProfilePath);
	
	CFileDialog filedlg(TRUE,0,0,0,
		_T("Nitro ROM(*.nds;*.bin)|*.nds;*.bin|")
		_T("All files(*.*)|*.*|")
		_T("|"),this);
	filedlg.GetOFN().lpstrInitialDir=strPath;
	filedlg.GetOFN().lpstrTitle=_T("选择模板ROM");
	if(filedlg.DoModal()==IDCANCEL)return;
	CString strFileName=filedlg.GetPathName(),strFOName=filedlg.GetFileName();
	WritePrivateProfileString(_T("FILE"),_T("RomPath"),
		strFileName.Left(strFileName.GetLength()-strFOName.GetLength()),ProfilePath);
	m_EditRom.SetWindowText(strFileName);
	
}

void CDlgMakeRom::OnMrNewrom()
{
	TCHAR strPath[1000]={0};
	GetPrivateProfileString(_T("FILE"),_T("NewRomPath"),0,strPath,999,ProfilePath);
	CFileDialog filedlg(FALSE,_T("nds"),_T("NewKirby.nds"),OFN_OVERWRITEPROMPT,
		_T("Nitro ROM(*.nds)|*.nds|")_T("|"),this);
	filedlg.GetOFN().lpstrInitialDir=strPath;
	filedlg.GetOFN().lpstrTitle=_T("生成新ROM到...");
	if(filedlg.DoModal()==IDCANCEL)return;
	CString strFileName=filedlg.GetPathName(),strFOName=filedlg.GetFileName();
	WritePrivateProfileString(_T("FILE"),_T("NewRomPath"),
		strFileName.Left(strFileName.GetLength()-strFOName.GetLength()),ProfilePath);
	m_EditNewRom.SetWindowText(strFileName);
}

void CDlgMakeRom::OnMakeRom()
{
	CString strRom,strNewRom;
	m_EditRom.GetWindowText(strRom);
	m_EditNewRom.GetWindowText(strNewRom);
	if(!CopyFile(strRom,strNewRom,FALSE))
	{
		MessageBox(_T("未能创建新ROM"),
			_T("失败"),MB_ICONERROR);
		return;
	}
	CFile file;
	if(!file.Open(strNewRom,CFile::modeReadWrite))
	{
		MessageBox(_T("未能创建新ROM"),
			_T("失败"),MB_ICONERROR);
		return;
	}
	CWndWait::ShowWndWait();
	BeginWaitCursor();
	if(!m_pMapSet->MakeRom(file,m_CheckV2.GetCheck()?true:false))
	{
		CWndWait::HideWndWait();
		EndWaitCursor();
		MessageBox(_T("生成ROM失败，导致失败的原因可能如下\n")
			_T(" - 模板ROM并非有效的呐喊团游戏ROM\n")
			_T(" - 地图集内文件过多"),
			_T("失败"),MB_ICONERROR);
		file.Close();
		return;
	}
	CWndWait::HideWndWait();
	EndWaitCursor();

	CString str;
	m_EditRom.GetWindowText(str);
	WritePrivateProfileString(_T("FILE"),_T("RomPathAndFile"),str,ProfilePath);
	m_EditNewRom.GetWindowText(str);
	WritePrivateProfileString(_T("FILE"),_T("NewRomPathAndFile"),str,ProfilePath);

	MessageBox(_T("成功生成ROM"),_T("成功"),0);
	m_ButtonBeginEmu.EnableWindow();
	file.Close();
}

BOOL CDlgMakeRom::OnInitDialog()
{
	CDialog::OnInitDialog();

	TCHAR strPath[1000]={0};
	GetPrivateProfileString(_T("FILE"),_T("RomPathAndFile"),_T(""),strPath,999,ProfilePath);
	m_EditRom.SetWindowText(strPath);
	GetPrivateProfileString(_T("FILE"),_T("NewRomPathAndFile"),_T(""),strPath,999,ProfilePath);
	m_EditNewRom.SetWindowText(strPath);

	GetPrivateProfileString(_T("FILE"),_T("NdsEmu"),_T(""),strPath,999,ProfilePath);
	m_EditNdsEmu.SetWindowText(strPath);
	HICON hIcon;
	if(ExtractIconEx(strPath,0,&hIcon,0,1))
		m_StaticNdsEmu.SetIcon(hIcon);

	m_EditMapSet.SetWindowText(_T("This map set."));

	m_CheckV2.SetCheck(TRUE);

	return TRUE;
}

void CDlgMakeRom::OnBnClickedButtonNdsemu()
{
	//TCHAR strPath[1000]={0};
	//GetPrivateProfileString(_T("FILE"),_T(""),0,strPath,999,ProfilePath);
	CFileDialog filedlg(TRUE,0,0,0,
		_T("Executable file(*.exe)|*.exe|")_T("|"),this);
	filedlg.GetOFN().lpstrTitle=_T("选择模拟器");
	if(filedlg.DoModal()==IDCANCEL)return;
	CString strFileName=filedlg.GetPathName();
	WritePrivateProfileString(_T("FILE"),_T("NdsEmu"),strFileName,ProfilePath);
	m_EditNdsEmu.SetWindowText(strFileName);
	HICON hIcon;
	if(ExtractIconEx(strFileName,0,&hIcon,0,1))
		m_StaticNdsEmu.SetIcon(hIcon);
}

void CDlgMakeRom::OnBnClickedButtonBeginemu()
{
	CString strEmu,strRom;
	m_EditNewRom.GetWindowText(strRom);
	m_EditNdsEmu.GetWindowText(strEmu);

	strEmu=strEmu+_T(" \"")+strRom+_T(" \"");
	TCHAR *str_t=new TCHAR[strEmu.GetLength()+1];
	_tcscpy(str_t,strEmu);

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&pi,sizeof(pi));
	ZeroMemory(&si,sizeof(si));
	si.cb=sizeof(si);
	
	CreateProcess(0,str_t,0,0,0,0,0,0,&si,&pi);
	delete []str_t;
}
