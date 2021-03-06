﻿
//UTF8♔

#include "stdafx.h"
#include "DlgObj.h"
#include "DlgMapEdit.h"
#include "Evc.h"
#include "Foe.h"
#include "Door.h"
#include "Treasure.h"
#include "SqDe.h"

const TCHAR hextran[]=_T("0123456789ABCDEF");

#define FORMAT_OBJ _T("%d:%s")

void MctrlParamEnum_ComboBox(CComboBox& cb,const MCTRL_PARAM_ENUM* mpe)
{
	CString str;
	while(mpe->value!=MCTRL_PARAM_ENUM_END)
	{
		str=mpe->name;
		cb.AddString(str);
		++mpe;
	}
}


IMPLEMENT_DYNAMIC(CDlgObj, CDialog)

CDlgObj::CDlgObj(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgObj::IDD, pParent)
{

}

CDlgObj::~CDlgObj()
{
	
}

void CDlgObj::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_OBJ_PARAM, m_EditObjParam);
	DDX_Control(pDX, IDC_EDIT_OBJ_X, m_EditObjX);
	DDX_Control(pDX, IDC_EDIT_OBJ_XP, m_EditObjXp);
	DDX_Control(pDX, IDC_EDIT_OBJ_Y, m_EditObjY);
	DDX_Control(pDX, IDC_EDIT_OBJ_YP, m_EditObjYp);
	DDX_Control(pDX, IDC_COMBO_OBJ_CLASS, m_ComboClass);
	DDX_Control(pDX, IDC_TAB_PARAM, m_TabParam);
	DDX_Control(pDX, IDC_EDIT_OBJ_MCTRL1, m_EditMctrl1);
	DDX_Control(pDX, IDC_CHECK_OBJ_MCTRL2, m_CheckMctrl2);
}


BEGIN_MESSAGE_MAP(CDlgObj, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_OBJ_CLASS, &CDlgObj::OnCbnSelchangeComboObjClass)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_PARAM, &CDlgObj::OnTcnSelchangeTabParam)

	ON_BN_CLICKED(IDC_CHECK_OP_S_INVISIBLE, &CDlgObj::OnBnClicked_S_Invisivle)
	ON_BN_CLICKED(IDC_CHECK_OP_S_BUBBLE, &CDlgObj::OnBnClicked_S_Bubble)
	ON_BN_CLICKED(IDC_CHECK_OP_S_SQNOW, &CDlgObj::OnBnClicked_S_Sqnow)
	ON_BN_CLICKED(IDC_CHECK_OP_S_FF, &CDlgObj::OnBnClicked_S_FF)
	ON_BN_CLICKED(IDC_CHECK_OP_S_TREASURE, &CDlgObj::OnBnClicked_S_Treasure)
	ON_CBN_SELCHANGE(IDC_COMBO_OP_S_TREASURE,  &CDlgObj::OnCbnSelchange_S_Treasure)

	ON_EN_CHANGE(IDC_EDIT_OP_D_STEP, &CDlgObj::OnEnChange_D_Step)
	ON_EN_CHANGE(IDC_EDIT_OP_D_DOOR, &CDlgObj::OnEnChange_D_Door)

	ON_COMMAND_RANGE(IDC_BUTTON_OP_M_REL_BASE,IDC_BUTTON_OP_M_REL_BASE+20, &CDlgObj::OnBnClicked_M_Rel)
	ON_COMMAND_RANGE(ID_MENU_OP_M_REL_BASE,ID_MENU_OP_M_REL_BASE+300, &CDlgObj::OnMenu_M_Rel)

	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_OP_M_0_COUNT, &CDlgObj::OnTcnSelchange_M_0_Count)
	ON_EN_CHANGE(IDC_EDIT_OP_M_0_REL0, &CDlgObj::OnEnChange_M_0_Rel0)
	ON_EN_CHANGE(IDC_EDIT_OP_M_0_REL1, &CDlgObj::OnEnChange_M_0_Rel1)
	ON_EN_CHANGE(IDC_EDIT_OP_M_0_REL2, &CDlgObj::OnEnChange_M_0_Rel2)

	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_OP_M_1_COUNT, &CDlgObj::OnTcnSelchange_M_1_Count)
	ON_EN_CHANGE(IDC_EDIT_OP_M_1_REL0, &CDlgObj::OnEnChange_M_1_Rel0)
	ON_EN_CHANGE(IDC_EDIT_OP_M_1_REL1, &CDlgObj::OnEnChange_M_1_Rel1)
	ON_EN_CHANGE(IDC_EDIT_OP_M_1_ROPELENGTH, &CDlgObj::OnEnChange_M_1_RopeLength)
	ON_CBN_SELCHANGE(IDC_COMBO_OP_M_1_STYLE, &CDlgObj::OnCbnSelchange_M_1_Style)

	ON_BN_CLICKED(IDC_CHECK_OP_M_2_REVERSE, &CDlgObj::OnBnClicked_M_2_Reverse)
	ON_EN_CHANGE(IDC_EDIT_OP_M_2_HOLDTIME, &CDlgObj::OnEnChange_M_2_HoldTime)
	ON_CBN_SELCHANGE(IDC_COMBO_OP_M_2_STYLE_MAIN, &CDlgObj::OnCbnSelchange_M_2_StyleMain)
	ON_CBN_SELCHANGE(IDC_COMBO_OP_M_2_STYLE_EX, &CDlgObj::OnCbnSelchange_M_2_StyleEx)

	ON_BN_CLICKED(IDC_CHECK_OP_M_3_FALL, &CDlgObj::OnBnClicked_M_3_Fall)
	ON_BN_CLICKED(IDC_CHECK_OP_M_3_UNK, &CDlgObj::OnBnClicked_M_3_Unk)

	ON_CBN_SELCHANGE(IDC_COMBO_OP_M_5_MAIN, &CDlgObj::OnCbnSelchange_M_5_Style)
	ON_CBN_SELCHANGE(IDC_COMBO_OP_M_5_SUB, &CDlgObj::OnCbnSelchange_M_5_SubStyle)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_OP_M_5_COUNT, &CDlgObj::OnTcnSelchange_M_5_Count)
	ON_EN_CHANGE(IDC_EDIT_OP_M_5_DX0, &CDlgObj::OnEnChange_M_5_DX0)
	ON_EN_CHANGE(IDC_EDIT_OP_M_5_DY0, &CDlgObj::OnEnChange_M_5_DY0)
	ON_EN_CHANGE(IDC_EDIT_OP_M_5_DX1, &CDlgObj::OnEnChange_M_5_DX1)
	ON_EN_CHANGE(IDC_EDIT_OP_M_5_DY1, &CDlgObj::OnEnChange_M_5_DY1)
	ON_EN_CHANGE(IDC_EDIT_OP_M_5_DX2, &CDlgObj::OnEnChange_M_5_DX2)
	ON_EN_CHANGE(IDC_EDIT_OP_M_5_DY2, &CDlgObj::OnEnChange_M_5_DY2)

	ON_CBN_SELCHANGE(IDC_COMBO_OP_M_10_STYLE, &CDlgObj::OnCbnSelchange_M_10_Style)
	ON_EN_CHANGE(IDC_EDIT_OP_M_10_TIME, &CDlgObj::OnEnChange_M_10_Time)

	ON_CBN_SELCHANGE(IDC_COMBO_OP_M_14_STYLE, &CDlgObj::OnCbnSelchange_M_14_Style)
	ON_BN_CLICKED(IDC_CHECK_OP_M_14_SUP, &CDlgObj::OnBnClicked_M_14_Sup)
	ON_EN_CHANGE(IDC_EDIT_OP_M_14_REL, &CDlgObj::OnEnChange_M_14_Rel)

	ON_BN_CLICKED(IDC_CHECK_OP_M_15_SUP, &CDlgObj::OnBnClicked_M_15_Sup)
	ON_EN_CHANGE(IDC_EDIT_OP_M_15_REL, &CDlgObj::OnEnChange_M_15_Rel)

	ON_BN_CLICKED(IDC_CHECK_OP_M_17_SUP, &CDlgObj::OnBnClicked_M_17_Sup)
	ON_BN_CLICKED(IDC_CHECK_OP_M_17_DUST, &CDlgObj::OnBnClicked_M_17_Dust)
	ON_EN_CHANGE(IDC_EDIT_OP_M_17_REL, &CDlgObj::OnEnChange_M_17_Rel)

	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_OP_M_22_COUNT, &CDlgObj::OnTcnSelchange_M_22_Count)
	ON_EN_CHANGE(IDC_EDIT_OP_M_22_REL0, &CDlgObj::OnEnChange_M_22_Rel0)
	ON_EN_CHANGE(IDC_EDIT_OP_M_22_REL1, &CDlgObj::OnEnChange_M_22_Rel1)
	ON_EN_CHANGE(IDC_EDIT_OP_M_22_REL2, &CDlgObj::OnEnChange_M_22_Rel2)
	ON_EN_CHANGE(IDC_EDIT_OP_M_22_REL3, &CDlgObj::OnEnChange_M_22_Rel3)
	ON_EN_CHANGE(IDC_EDIT_OP_M_22_REL4, &CDlgObj::OnEnChange_M_22_Rel4)
	ON_EN_CHANGE(IDC_EDIT_OP_M_22_TIME0, &CDlgObj::OnEnChange_M_22_Time0)
	ON_EN_CHANGE(IDC_EDIT_OP_M_22_TIME1, &CDlgObj::OnEnChange_M_22_Time1)
	ON_EN_CHANGE(IDC_EDIT_OP_M_22_TIME2, &CDlgObj::OnEnChange_M_22_Time2)
	ON_EN_CHANGE(IDC_EDIT_OP_M_22_TIME3, &CDlgObj::OnEnChange_M_22_Time3)
	ON_EN_CHANGE(IDC_EDIT_OP_M_22_TIME4, &CDlgObj::OnEnChange_M_22_Time4)
	ON_BN_CLICKED(IDC_CHECK_OP_M_22_WAITBOSS, &CDlgObj::OnBnClicked_M_22_WaitBoss)

	ON_EN_CHANGE(IDC_EDIT_OP_M_23_REL0, &CDlgObj::OnEnChange_M_23_Rel0)
	ON_EN_CHANGE(IDC_EDIT_OP_M_23_REL1, &CDlgObj::OnEnChange_M_23_Rel1)
	ON_EN_CHANGE(IDC_EDIT_OP_M_23_REL2, &CDlgObj::OnEnChange_M_23_Rel2)
	ON_EN_CHANGE(IDC_EDIT_OP_M_23_REL3, &CDlgObj::OnEnChange_M_23_Rel3)
	ON_EN_CHANGE(IDC_EDIT_OP_M_23_REL4, &CDlgObj::OnEnChange_M_23_Rel4)
	ON_EN_CHANGE(IDC_EDIT_OP_M_23_REL5, &CDlgObj::OnEnChange_M_23_Rel5)
	ON_EN_CHANGE(IDC_EDIT_OP_M_23_REL6, &CDlgObj::OnEnChange_M_23_Rel6)
	ON_EN_CHANGE(IDC_EDIT_OP_M_23_REL7, &CDlgObj::OnEnChange_M_23_Rel7)

	ON_EN_CHANGE(IDC_EDIT_OP_M_24_WIDTH, &CDlgObj::OnEnChange_M_24_Width)
	ON_EN_CHANGE(IDC_EDIT_OP_M_24_HEIGHT, &CDlgObj::OnEnChange_M_24_Height)
	ON_CBN_SELCHANGE(IDC_COMBO_OP_M_24_STYLE,  &CDlgObj::OnCbnSelchange_M_24_Style)

	ON_CBN_SELCHANGE(IDC_COMBO_OP_M_SINGLE,  &CDlgObj::OnCbnSelchange_M_Single)

	ON_WM_DESTROY()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CHexEdit, CEdit)
	ON_WM_CHAR()
END_MESSAGE_MAP()


BOOL CDlgObj::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetWindowText(title);

	m_ComboClass.SetImageList(&ImageList_ObjIcon);

	m_BarParamDecode.Create(this,IDDB_OBJ_PARAM_NULL,
			CBRS_NOALIGN,IDDB_OBJ_PARAM_NULL);
	InitBarParamDecode();

	m_TabParam.InsertItem(0,_T("解码后"));
	m_TabParam.InsertItem(1,_T("解码前"));
	OnTcnSelchangeTabParam(0,0);
	

	CString str;
	str.Format(_T("%d"),x>>4);
	m_EditObjX.SetWindowText(str);
	m_EditObjX.SetLimitText(3);
	str.Format(_T("%c"),hextran[x&0xF]);
	m_EditObjXp.SetWindowText(str);
	m_EditObjXp.SetLimitText(1);
	str.Format(_T("%d"),y>>4);
	m_EditObjY.SetWindowText(str);
	m_EditObjY.SetLimitText(3);
	str.Format(_T("%c"),hextran[y&0xF]);
	m_EditObjYp.SetWindowText(str);
	m_EditObjYp.SetLimitText(1);
	m_EditObjParam.Init();
	m_EditObjParam.m_pAttach=param;

	COMBOBOXEXITEM cbei;
	cbei.mask=CBEIF_TEXT|CBEIF_IMAGE|CBEIF_SELECTEDIMAGE|CBEIF_LPARAM;
	if(objgroup==FOE)
	{
		m_EditMctrl1.EnableWindow(FALSE);
		m_CheckMctrl2.EnableWindow(FALSE);
		for(u16 i=0;FoeDesc[i].name;++i)
		{
			str.Format(FORMAT_OBJ,i,FoeDesc[i].name);
			cbei.iItem=i;
			cbei.pszText=str.GetBuffer();
			cbei.iSelectedImage=cbei.iImage=ImageList_ObjIcon.GetFoeIconId(i);
			cbei.lParam=i;
			m_ComboClass.InsertItem(&cbei);
		}
		m_ComboClass.SetCurSel(class_id);
		m_EditObjParam.m_DataLen=8;
	}
	else if(objgroup==SUP)
	{
		m_EditMctrl1.EnableWindow(FALSE);
		m_CheckMctrl2.EnableWindow(FALSE);
		for(u16 i=0;SupDesc[i].name;++i)
		{
			str.Format(FORMAT_OBJ,i,SupDesc[i].name);
			cbei.iItem=i;
			cbei.pszText=str.GetBuffer();
			cbei.iSelectedImage=cbei.iImage=ImageList_ObjIcon.GetSupIconId(i);
			cbei.lParam=i;
			m_ComboClass.InsertItem(&cbei);
		}
		m_ComboClass.SetCurSel(class_id);
		m_EditObjParam.m_DataLen=8;
	}
	else if(objgroup==DOOR)
	{
		m_EditMctrl1.EnableWindow(FALSE);
		m_CheckMctrl2.EnableWindow(FALSE);
		m_EditObjXp.EnableWindow(FALSE);
		m_EditObjYp.EnableWindow(FALSE);
		for(u16 i=0;DoorDesc[i].name;++i)
		{
			str.Format(FORMAT_OBJ,DoorDesc[i].class_id,DoorDesc[i].name);
			cbei.iItem=i;
			cbei.pszText=str.GetBuffer();
			cbei.iSelectedImage=cbei.iImage=ImageList_ObjIcon.GetDoorIconId(i);
			cbei.lParam=DoorDesc[i].class_id;
			m_ComboClass.InsertItem(&cbei);
			if(DoorDesc[i].class_id==class_id)m_ComboClass.SetCurSel(i);
		}
		m_EditObjParam.m_DataLen=2;
	}
	else if(objgroup==MCTRL)
	{
		for(u8 i=0;EvcDesc[i].DataLen;++i)
		{
			str.Format(FORMAT_OBJ,i,EvcDesc[i].Name);
			cbei.iItem=i;
			cbei.pszText=str.GetBuffer();
			cbei.iSelectedImage=cbei.iImage=ImageList_ObjIcon.GetMctrlIconId(i);
			cbei.lParam=i;
			m_ComboClass.InsertItem(&cbei);
		}
		m_ComboClass.SetCurSel(class_id);
		m_EditObjParam.m_DataLen=/*2+*/GetEvcDataLen((u8)class_id);
		//m_EditObjParam.m_charBreak=_T(" |");
		str.Format(_T("%d"),mctrl_param[0]);
		m_EditMctrl1.SetWindowText(str);
		m_EditMctrl1.SetLimitText(3);
		m_CheckMctrl2.SetCheck(mctrl_param[1]?TRUE:FALSE);
	}
	m_EditObjParam.UpdateText();

	return FALSE;
}

void CDlgObj::OnOK()
{
	CString str;
	m_EditObjX.GetWindowText(str);
	x=_ttoi(str)<<4;
	m_EditObjXp.GetWindowText(str);
	if(str[0]>=(UINT)'0' && str[0]<=(UINT)'9')
	{
		x|=str[0]-'0';
	}
	else if(str[0]>=(UINT)'A' && str[0]<=(UINT)'F')
	{
		x|=str[0]-(UINT)'A'+10;
	}
	else if(str[0]>=(UINT)'a' && str[0]<=(UINT)'f')
	{
		x|=str[0]-(UINT)'a'+10;
	}
	else
	{
		m_EditObjXp.SetFocus();
		m_EditObjXp.SetSel(0,-1);
		MessageBeep(MB_OK);
		return;
	}
	m_EditObjY.GetWindowText(str);
	y=_ttoi(str)<<4;
	m_EditObjYp.GetWindowText(str);
	if(str[0]>=(UINT)'0' && str[0]<=(UINT)'9')
	{
		y|=str[0]-'0';
	}
	else if(str[0]>=(UINT)'A' && str[0]<=(UINT)'F')
	{
		y|=str[0]-(UINT)'A'+10;
	}
	else if(str[0]>=(UINT)'a' && str[0]<=(UINT)'f')
	{
		y|=str[0]-(UINT)'a'+10;
	}
	else
	{
		m_EditObjYp.SetFocus();
		m_EditObjYp.SetSel(0,-1);
		MessageBeep(MB_OK);
		return;
	}
	if(objgroup==MCTRL)
	{
		m_EditMctrl1.GetWindowText(str);
		mctrl_param[0]=(u8)min(255,_ttoi(str));
		mctrl_param[1]=m_CheckMctrl2.GetCheck()?1:0;
	}
	CDialog::OnOK();
}

void CDlgObj::OnCbnSelchangeComboObjClass()
{
	/*CString str;
	m_ComboClass.GetWindowText(str);
	int c;
	TCHAR dummybuf[100];
	_stscanf(str,FORMAT_OBJ,&c,dummybuf);*/
	COMBOBOXEXITEM cbei;
	cbei.mask=CBEIF_LPARAM;
	cbei.iItem=m_ComboClass.GetCurSel();
	m_ComboClass.GetItem(&cbei);
	class_id=(u16)cbei.lParam;
	if(objgroup==MCTRL)
	{
		m_EditObjParam.m_DataLen=GetEvcDataLen((u8)class_id);
		//ZeroMemory(param,GetEvcDataLen((u8)class_id));
		memcpy(param,MctrlDefault[class_id],GetEvcDataLen((u8)class_id));
		m_EditObjParam.UpdateText();
		InitBarParamDecode();
		OnTcnSelchangeTabParam(0,0);
	}
}

void CDlgObj::OnTcnSelchangeTabParam(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(m_TabParam.GetCurSel()==0)
	{
		ParamDecode();
		RECT rc;
		m_EditObjParam.GetWindowRect(&rc);
		ScreenToClient(&rc);
		m_EditObjParam.ShowWindow(SW_HIDE);
		m_BarParamDecode.MoveWindow(&rc);
	}
	else
	{
		m_EditObjParam.UpdateText();
		m_EditObjParam.ShowWindow(SW_SHOW);
		m_BarParamDecode.MoveWindow(0,0,0,0);
	}
	if(pResult)*pResult = 0;
}
void CDlgObj::OnBnClicked_M_Rel(UINT ButtonId)
{
	int ibutton=ButtonId-IDC_BUTTON_OP_M_REL_BASE;
	RelMctrlPreset_Binding binding=
		RelMctrlPresetListEntry.GetAt(RelMctrlPresetListEntry.FindIndex(ibutton));
	if(m_BarParamDecode.GetDlgItem(binding.EditId)->IsWindowEnabled())
	{
		CurEditId=binding.EditId;
		CMenu menu;
		menu.CreatePopupMenu();

		CString str;
		for(u8 i=0;i<pMa->MctrlPack.GetMctrlCount();++i)
		{
			str.Format(_T("%d %s"),i,EvcDesc[pMa->MctrlPack[i].class_id].Name);
			menu.AppendMenu(0,ID_MENU_OP_M_REL_BASE+i,str);
			menu.SetMenuItemBitmaps(i,MF_BYPOSITION,
				&ImageList_ObjIcon.MctrlIcon[pMa->MctrlPack[i].class_id],0);
		
		}

		CRect rc;
		binding.pButton->GetWindowRect(&rc);
		menu.TrackPopupMenu(
			GetSystemMetrics(SM_MENUDROPALIGNMENT)?
			TPM_RIGHTALIGN:TPM_LEFTALIGN,
			rc.left,rc.bottom,this);
		menu.DestroyMenu();
	}
}
void CDlgObj::OnMenu_M_Rel(UINT MenuId)
{
	int i=MenuId-ID_MENU_OP_M_REL_BASE;
	CString str;
	str.Format(_T("%d"),i);
	m_BarParamDecode.GetDlgItem(CurEditId)->SetWindowText(str);
}
void CDlgObj::BindRelMctrlPreset(int EditId)
{
	RECT rc;
	m_BarParamDecode.GetDlgItem(EditId)->GetWindowRect(&rc);
	m_BarParamDecode.ScreenToClient(&rc);
	rc.left=rc.right;
	rc.right+=16;

	RelMctrlPreset_Binding binding;
	binding.EditId=EditId;
	binding.pButton=new CButton;
	binding.pButton->Create(_T("."),WS_CHILD|WS_VISIBLE,rc,&m_BarParamDecode,
		IDC_BUTTON_OP_M_REL_BASE+RelMctrlPresetListEntry.GetCount());
	RelMctrlPresetListEntry.AddTail(binding);

}
void CDlgObj::CleanRelMctrlPreset()
{
	while(!RelMctrlPresetListEntry.IsEmpty())
	{
		delete RelMctrlPresetListEntry.GetHead().pButton;
		RelMctrlPresetListEntry.RemoveHead();
	}
}
void CDlgObj::InitBarParamDecode()
{
	

	m_BarParamDecode.DestroyWindow();
	CString str;
	switch(objgroup)
	{
	case SUP:
		m_BarParamDecode.Create(this,IDDB_OBJ_PARAM_SUP,
			CBRS_NOALIGN,IDDB_OBJ_PARAM_SUP);
		for(u8 i=0;i<=120;++i)
		{
			GetTreasureName(i,str);
			((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_S_TREASURE))
				->AddString(str);
		}
		break;
	case DOOR:
		m_BarParamDecode.Create(this,IDDB_OBJ_PARAM_DOOR,
			CBRS_NOALIGN,IDDB_OBJ_PARAM_DOOR);
		((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_D_STEP))->SetLimitText(3);
		((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_D_DOOR))->SetLimitText(3);
		break;
	case MCTRL:
		switch(class_id)
		{
		case 0:
			m_BarParamDecode.Create(this,IDDB_OBJ_PARAM_MCTRL_0,
				CBRS_NOALIGN,IDDB_OBJ_PARAM_MCTRL_0);
			((CTabCtrl*)m_BarParamDecode.GetDlgItem(IDC_TAB_OP_M_0_COUNT))
				->InsertItem(0,_T("1"));
			((CTabCtrl*)m_BarParamDecode.GetDlgItem(IDC_TAB_OP_M_0_COUNT))
				->InsertItem(1,_T("2"));
			((CTabCtrl*)m_BarParamDecode.GetDlgItem(IDC_TAB_OP_M_0_COUNT))
				->InsertItem(2,_T("3"));
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_0_REL0))
				->SetLimitText(3);
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_0_REL1))
				->SetLimitText(3);
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_0_REL2))
				->SetLimitText(3);
			BindRelMctrlPreset(IDC_EDIT_OP_M_0_REL0);
			BindRelMctrlPreset(IDC_EDIT_OP_M_0_REL1);
			BindRelMctrlPreset(IDC_EDIT_OP_M_0_REL2);
			break;
		case 1:
			m_BarParamDecode.Create(this,IDDB_OBJ_PARAM_MCTRL_1,
				CBRS_NOALIGN,IDDB_OBJ_PARAM_MCTRL_1);
			((CTabCtrl*)m_BarParamDecode.GetDlgItem(IDC_TAB_OP_M_1_COUNT))
				->InsertItem(0,_T("0"));
			((CTabCtrl*)m_BarParamDecode.GetDlgItem(IDC_TAB_OP_M_1_COUNT))
				->InsertItem(1,_T("1"));
			((CTabCtrl*)m_BarParamDecode.GetDlgItem(IDC_TAB_OP_M_1_COUNT))
				->InsertItem(2,_T("2"));
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_1_REL0))
				->SetLimitText(3);
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_1_REL1))
				->SetLimitText(3);
			BindRelMctrlPreset(IDC_EDIT_OP_M_1_REL0);
			BindRelMctrlPreset(IDC_EDIT_OP_M_1_REL1);
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_1_ROPELENGTH))
				->SetLimitText(2);
			MctrlParamEnum_ComboBox(
				*(CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_1_STYLE),
				MCTRL_EXT_1_STYLE);
			break;
		case 2:
			m_BarParamDecode.Create(this,IDDB_OBJ_PARAM_MCTRL_2,
				CBRS_NOALIGN,IDDB_OBJ_PARAM_MCTRL_2);
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_2_HOLDTIME))
				->SetLimitText(3);
			MctrlParamEnum_ComboBox(*(CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_2_STYLE_MAIN),
				MCTRL_EXT_2_MAIN_STYLE);
			MctrlParamEnum_ComboBox(*(CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_2_STYLE_EX),
				MCTRL_EXT_2_EX_STYLE);
			break;
		case 3:
			m_BarParamDecode.Create(this,IDDB_OBJ_PARAM_MCTRL_3,
				CBRS_NOALIGN,IDDB_OBJ_PARAM_MCTRL_3);
			break;
		case 5:
			m_BarParamDecode.Create(this,IDDB_OBJ_PARAM_MCTRL_5,
				CBRS_NOALIGN,IDDB_OBJ_PARAM_MCTRL_5);
			((CTabCtrl*)m_BarParamDecode.GetDlgItem(IDC_TAB_OP_M_5_COUNT))
				->InsertItem(0,_T("0"));
			((CTabCtrl*)m_BarParamDecode.GetDlgItem(IDC_TAB_OP_M_5_COUNT))
				->InsertItem(1,_T("1"));
			((CTabCtrl*)m_BarParamDecode.GetDlgItem(IDC_TAB_OP_M_5_COUNT))
				->InsertItem(2,_T("2"));
			((CTabCtrl*)m_BarParamDecode.GetDlgItem(IDC_TAB_OP_M_5_COUNT))
				->InsertItem(3,_T("3"));
			MctrlParamEnum_ComboBox(*(CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_5_MAIN),
				MCTRL_EXT_5_STYLE);
			MctrlParamEnum_ComboBox(*(CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_5_SUB),
				MCTRL_EXT_5_SUB_STYLE);
			break;
		case 6:
			m_BarParamDecode.Create(this,IDDB_OBJ_PARAM_MCTRL_SINGLE,
				CBRS_NOALIGN,IDDB_OBJ_PARAM_MCTRL_SINGLE);
			MctrlParamEnum_ComboBox(*(CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_SINGLE),
				MCTRL_EXT_6_STYLE);
			break;
		case 10:
			m_BarParamDecode.Create(this,IDDB_OBJ_PARAM_MCTRL_10,
				CBRS_NOALIGN,IDDB_OBJ_PARAM_MCTRL_10);
			MctrlParamEnum_ComboBox(*(CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_10_STYLE),
				MCTRL_EXT_10_STYLE);
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_10_TIME))->SetLimitText(3);
			break;
		case 11:
			m_BarParamDecode.Create(this,IDDB_OBJ_PARAM_MCTRL_SINGLE,
				CBRS_NOALIGN,IDDB_OBJ_PARAM_MCTRL_SINGLE);
			((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_SINGLE))
				->AddString(_T("任意方向"));
			((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_SINGLE))
				->AddString(_T("↑"));
			((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_SINGLE))
				->AddString(_T("↗"));
			((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_SINGLE))
				->AddString(_T("→"));
			((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_SINGLE))
				->AddString(_T("↘"));
			((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_SINGLE))
				->AddString(_T("↓"));
			((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_SINGLE))
				->AddString(_T("↙"));
			((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_SINGLE))
				->AddString(_T("←"));
			((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_SINGLE))
				->AddString(_T("↖"));
			break;
		case 12:
			m_BarParamDecode.Create(this,IDDB_OBJ_PARAM_DOOR,
				CBRS_NOALIGN,IDDB_OBJ_PARAM_DOOR);
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_D_STEP))->SetLimitText(3);
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_D_DOOR))->SetLimitText(3);
			break;
		case 14:
			m_BarParamDecode.Create(this,IDDB_OBJ_PARAM_MCTRL_14,
				CBRS_NOALIGN,IDDB_OBJ_PARAM_MCTRL_14);
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_14_REL))->SetLimitText(3);
			MctrlParamEnum_ComboBox(
				*(CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_14_STYLE),
				MCTRL_EXT_14_STYLE);
			break;
		case 15:
			m_BarParamDecode.Create(this,IDDB_OBJ_PARAM_MCTRL_15,
				CBRS_NOALIGN,IDDB_OBJ_PARAM_MCTRL_15);
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_15_REL))->SetLimitText(3);
			break;
		case 16:
		case 9:
			m_BarParamDecode.Create(this,IDDB_OBJ_PARAM_MCTRL_16,
				CBRS_NOALIGN,IDDB_OBJ_PARAM_MCTRL_16);
			break;
		case 17:
			m_BarParamDecode.Create(this,IDDB_OBJ_PARAM_MCTRL_17,
				CBRS_NOALIGN,IDDB_OBJ_PARAM_MCTRL_17);
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_17_REL))->SetLimitText(3);
			break;
		case 22:
			m_BarParamDecode.Create(this,IDDB_OBJ_PARAM_MCTRL_22,
				CBRS_NOALIGN,IDDB_OBJ_PARAM_MCTRL_22);
			((CTabCtrl*)m_BarParamDecode.GetDlgItem(IDC_TAB_OP_M_22_COUNT))
				->InsertItem(0,_T("1"));
			((CTabCtrl*)m_BarParamDecode.GetDlgItem(IDC_TAB_OP_M_22_COUNT))
				->InsertItem(1,_T("2"));
			((CTabCtrl*)m_BarParamDecode.GetDlgItem(IDC_TAB_OP_M_22_COUNT))
				->InsertItem(2,_T("3"));
			((CTabCtrl*)m_BarParamDecode.GetDlgItem(IDC_TAB_OP_M_22_COUNT))
				->InsertItem(3,_T("4"));
			((CTabCtrl*)m_BarParamDecode.GetDlgItem(IDC_TAB_OP_M_22_COUNT))
				->InsertItem(4,_T("5"));
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_REL0))
				->SetLimitText(3);
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_REL1))
				->SetLimitText(3);
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_REL2))
				->SetLimitText(3);
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_REL3))
				->SetLimitText(3);
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_REL4))
				->SetLimitText(3);
			BindRelMctrlPreset(IDC_EDIT_OP_M_22_REL0);
			BindRelMctrlPreset(IDC_EDIT_OP_M_22_REL1);
			BindRelMctrlPreset(IDC_EDIT_OP_M_22_REL2);
			BindRelMctrlPreset(IDC_EDIT_OP_M_22_REL3);
			BindRelMctrlPreset(IDC_EDIT_OP_M_22_REL4);
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_TIME0))
				->SetLimitText(5);
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_TIME1))
				->SetLimitText(5);
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_TIME2))
				->SetLimitText(5);
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_TIME3))
				->SetLimitText(5);
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_TIME4))
				->SetLimitText(5);
			break;
		case 23:
			m_BarParamDecode.Create(this,IDDB_OBJ_PARAM_MCTRL_23,
				CBRS_NOALIGN,IDDB_OBJ_PARAM_MCTRL_23);
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_23_REL0))
				->SetLimitText(3);
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_23_REL1))
				->SetLimitText(3);
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_23_REL2))
				->SetLimitText(3);
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_23_REL3))
				->SetLimitText(3);
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_23_REL4))
				->SetLimitText(3);
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_23_REL5))
				->SetLimitText(3);
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_23_REL6))
				->SetLimitText(3);
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_23_REL7))
				->SetLimitText(3);
			BindRelMctrlPreset(IDC_EDIT_OP_M_23_REL0);
			BindRelMctrlPreset(IDC_EDIT_OP_M_23_REL1);
			BindRelMctrlPreset(IDC_EDIT_OP_M_23_REL2);
			BindRelMctrlPreset(IDC_EDIT_OP_M_23_REL3);
			BindRelMctrlPreset(IDC_EDIT_OP_M_23_REL4);
			BindRelMctrlPreset(IDC_EDIT_OP_M_23_REL5);
			BindRelMctrlPreset(IDC_EDIT_OP_M_23_REL6);
			BindRelMctrlPreset(IDC_EDIT_OP_M_23_REL7);
			break;
		case 24:
			m_BarParamDecode.Create(this,IDDB_OBJ_PARAM_MCTRL_24,
				CBRS_NOALIGN,IDDB_OBJ_PARAM_MCTRL_24);
			MctrlParamEnum_ComboBox(
				*(CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_24_STYLE),
				MCTRL_EXT_24_STYLE);
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_24_WIDTH))
				->SetLimitText(3);
			((CEdit*)m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_24_HEIGHT))
				->SetLimitText(3);
			break;
		case 25:
			m_BarParamDecode.Create(this,IDDB_OBJ_PARAM_MCTRL_SINGLE,
				CBRS_NOALIGN,IDDB_OBJ_PARAM_MCTRL_SINGLE);
			((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_SINGLE))
				->AddString(_T("气泡"));
			((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_SINGLE))
				->AddString(_T("火花"));
			break;
		default:
			m_BarParamDecode.Create(this,IDDB_OBJ_PARAM_NULL,
				CBRS_NOALIGN,IDDB_OBJ_PARAM_NULL);
		}
		break;
	default:
		m_BarParamDecode.Create(this,IDDB_OBJ_PARAM_NULL,
			CBRS_NOALIGN,IDDB_OBJ_PARAM_NULL);
		break;
	}
}
void CDlgObj::ParamDecode()
{
	CString str;
	switch(objgroup)
	{
	case SUP:
		((CButton*)m_BarParamDecode.GetDlgItem(IDC_CHECK_OP_S_INVISIBLE))
			->SetCheck( param[3]&SQ_ITEM_SUP_FLAG_INVISIBLE ?TRUE:FALSE);
		((CButton*)m_BarParamDecode.GetDlgItem(IDC_CHECK_OP_S_BUBBLE))
			->SetCheck( param[3]&SQ_ITEM_SUP_FLAG_BUBBLE ?TRUE:FALSE);
		((CButton*)m_BarParamDecode.GetDlgItem(IDC_CHECK_OP_S_SQNOW))
			->SetCheck( param[3]&SQ_ITEM_SUP_FLAG_SQNOW ?TRUE:FALSE);
		((CButton*)m_BarParamDecode.GetDlgItem(IDC_CHECK_OP_S_FF))
			->SetCheck( param[4]  ?TRUE:FALSE);
		((CButton*)m_BarParamDecode.GetDlgItem(IDC_CHECK_OP_S_TREASURE))
			->SetCheck( param[6]  ?TRUE:FALSE);
		((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_S_TREASURE))
			->SetCurSel(min(param[5],120));
		m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_S_TREASURE)
			->EnableWindow(param[6]?TRUE:FALSE);
		break;
	case DOOR:
		str.Format(_T("%d"),param[0]);
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_D_STEP)->SetWindowText(str);
		str.Format(_T("%d"),param[1]);
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_D_DOOR)->SetWindowText(str);
		break;
	case MCTRL:
		switch(class_id)
		{
		case 0:{
			int count=((MCTRL_EXT_0*)param)->RelMctrlCount;
			count=max(1,min(3,count));
			((CTabCtrl*)m_BarParamDecode.GetDlgItem(IDC_TAB_OP_M_0_COUNT))
				->SetCurSel(count-1);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_0_REL1)
				->EnableWindow(count>1?TRUE:FALSE);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_0_REL2)
				->EnableWindow(count>2?TRUE:FALSE);
			str.Format(_T("%d"),((MCTRL_EXT_0*)param)->RelMctrlIndex[0]);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_0_REL0)
				->SetWindowText(str);
			str.Format(_T("%d"),((MCTRL_EXT_0*)param)->RelMctrlIndex[1]);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_0_REL1)
				->SetWindowText(str);
			str.Format(_T("%d"),((MCTRL_EXT_0*)param)->RelMctrlIndex[2]);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_0_REL2)
				->SetWindowText(str);
			break;}
		case 1:{
			((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_1_STYLE))
				->SetCurSel(
				MpeV2I(((MCTRL_EXT_1*)param)->Style,MCTRL_EXT_1_STYLE)
				);
			int count=((MCTRL_EXT_1*)param)->RelMctrlCount;
			count=min(2,count);
			((CTabCtrl*)m_BarParamDecode.GetDlgItem(IDC_TAB_OP_M_1_COUNT))
				->SetCurSel(count);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_1_REL0)
				->EnableWindow(count>0?TRUE:FALSE);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_1_REL1)
				->EnableWindow(count>1?TRUE:FALSE);
			str.Format(_T("%d"),((MCTRL_EXT_1*)param)->RelMctrlIndex[0]);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_1_REL0)
				->SetWindowText(str);
			str.Format(_T("%d"),((MCTRL_EXT_1*)param)->RelMctrlIndex[1]);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_1_REL1)
				->SetWindowText(str);
			str.Format(_T("%d"),((MCTRL_EXT_1*)param)->RopeLength);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_1_ROPELENGTH)
				->SetWindowText(str);
			break;}
		case 2:
			str.Format(_T("%d"),((MCTRL_EXT_2*)param)->HoldTime);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_2_HOLDTIME)
				->SetWindowText(str);
			((CButton*)m_BarParamDecode.GetDlgItem(IDC_CHECK_OP_M_2_REVERSE))
				->SetCheck(((MCTRL_EXT_2*)param)->Reverse?TRUE:FALSE);
			((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_2_STYLE_MAIN))
				->SetCurSel(MpeV2I(((MCTRL_EXT_2*)param)->MainStyle,MCTRL_EXT_2_MAIN_STYLE));
			((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_2_STYLE_EX))
				->SetCurSel(MpeV2I(((MCTRL_EXT_2*)param)->ExStyle,MCTRL_EXT_2_EX_STYLE));
			
			break;
		case 3:
			((CButton*)m_BarParamDecode.GetDlgItem(IDC_CHECK_OP_M_3_FALL))
				->SetCheck(((MCTRL_EXT_3*)param)->Flag_Fall?TRUE:FALSE);
			((CButton*)m_BarParamDecode.GetDlgItem(IDC_CHECK_OP_M_3_UNK))
				->SetCheck(((MCTRL_EXT_3*)param)->Flag_Unk?TRUE:FALSE);
			break;
		case 5:{
			((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_5_MAIN))
				->SetCurSel(MpeV2I(((MCTRL_EXT_5*)param)->Style,MCTRL_EXT_5_STYLE));
			((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_5_SUB))
				->SetCurSel(MpeV2I(((MCTRL_EXT_5*)param)->SubStyle,MCTRL_EXT_5_SUB_STYLE));
			int count=((MCTRL_EXT_5*)param)->NodeCount;
			count=min(3,count);
			((CTabCtrl*)m_BarParamDecode.GetDlgItem(IDC_TAB_OP_M_5_COUNT))
				->SetCurSel(count);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_5_DX0)
				->EnableWindow(count>0?TRUE:FALSE);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_5_DX1)
				->EnableWindow(count>1?TRUE:FALSE);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_5_DX2)
				->EnableWindow(count>2?TRUE:FALSE);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_5_DY0)
				->EnableWindow(count>0?TRUE:FALSE);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_5_DY1)
				->EnableWindow(count>1?TRUE:FALSE);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_5_DY2)
				->EnableWindow(count>2?TRUE:FALSE);
			str.Format(_T("%d"),((MCTRL_EXT_5*)param)->Node[0].dx);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_5_DX0)
				->SetWindowText(str);
			str.Format(_T("%d"),((MCTRL_EXT_5*)param)->Node[1].dx);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_5_DX1)
				->SetWindowText(str);
			str.Format(_T("%d"),((MCTRL_EXT_5*)param)->Node[2].dx);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_5_DX2)
				->SetWindowText(str);
			str.Format(_T("%d"),((MCTRL_EXT_5*)param)->Node[0].dy);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_5_DY0)
				->SetWindowText(str);
			str.Format(_T("%d"),((MCTRL_EXT_5*)param)->Node[1].dy);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_5_DY1)
				->SetWindowText(str);
			str.Format(_T("%d"),((MCTRL_EXT_5*)param)->Node[2].dy);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_5_DY2)
				->SetWindowText(str);
			break;}
		case 6:
			((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_SINGLE))
				->SetCurSel(MpeV2I(((MCTRL_EXT_6*)param)->Style,MCTRL_EXT_6_STYLE));
			break;
		case 10:
			((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_10_STYLE))
				->SetCurSel(MpeV2I(((MCTRL_EXT_10*)param)->Style,MCTRL_EXT_10_STYLE));
			str.Format(_T("%d"),((MCTRL_EXT_10*)param)->Time);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_10_TIME)->SetWindowText(str);
			break;
		case 11:
			if(((MCTRL_EXT_11*)param)->Style==1)
			{
				((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_SINGLE))
					->SetCurSel(0);
			}
			else
			{
				int k=((MCTRL_EXT_11*)param)->Style/36;
				if(k>7)k=0;
				((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_SINGLE))
					->SetCurSel(k+1);
			}
			break;
		case 12:
			str.Format(_T("%d"),param[0]);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_D_STEP)->SetWindowText(str);
			str.Format(_T("%d"),param[1]);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_D_DOOR)->SetWindowText(str);
			break;
		case 14:
			((CButton*)m_BarParamDecode.GetDlgItem(IDC_CHECK_OP_M_14_SUP))
				->SetCheck(((MCTRL_EXT_14*)param)->IsSup?TRUE:FALSE);
			str.Format(_T("%d"),((MCTRL_EXT_14*)param)->RelFoeSupIndex);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_14_REL)->SetWindowText(str);
			((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_14_STYLE))
				->SetCurSel(((MCTRL_EXT_14*)param)->Style);
			break;
		case 15:
			((CButton*)m_BarParamDecode.GetDlgItem(IDC_CHECK_OP_M_15_SUP))
				->SetCheck(((MCTRL_EXT_15*)param)->IsSup_LSL4&MCTRL_EXT_15_ISSUP?TRUE:FALSE);
			str.Format(_T("%d"),((MCTRL_EXT_15*)param)->RelFoeSupIndex);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_15_REL)->SetWindowText(str);
			break;
		case 17:
			((CButton*)m_BarParamDecode.GetDlgItem(IDC_CHECK_OP_M_17_SUP))
				->SetCheck(((MCTRL_EXT_17*)param)->IsSup?TRUE:FALSE);
			((CButton*)m_BarParamDecode.GetDlgItem(IDC_CHECK_OP_M_17_DUST))
				->SetCheck(((MCTRL_EXT_17*)param)->Dust?TRUE:FALSE);
			str.Format(_T("%d"),((MCTRL_EXT_17*)param)->RelFoeSupIndex);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_17_REL)->SetWindowText(str);
			break;
		case 22:{
			int count=((MCTRL_EXT_22*)param)->RelMctrlCount;
			count=max(1,min(5,count));
			((CTabCtrl*)m_BarParamDecode.GetDlgItem(IDC_TAB_OP_M_22_COUNT))
				->SetCurSel(count-1);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_REL1)
				->EnableWindow(count>1?TRUE:FALSE);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_REL2)
				->EnableWindow(count>2?TRUE:FALSE);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_REL3)
				->EnableWindow(count>3?TRUE:FALSE);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_REL4)
				->EnableWindow(count>4?TRUE:FALSE);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_TIME1)
				->EnableWindow(count>1?TRUE:FALSE);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_TIME2)
				->EnableWindow(count>2?TRUE:FALSE);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_TIME3)
				->EnableWindow(count>3?TRUE:FALSE);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_TIME4)
				->EnableWindow(count>4?TRUE:FALSE);
			str.Format(_T("%d"),((MCTRL_EXT_22*)param)->RelMctrlIndex[0]);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_REL0)
				->SetWindowText(str);
			str.Format(_T("%d"),((MCTRL_EXT_22*)param)->RelMctrlIndex[1]);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_REL1)
				->SetWindowText(str);
			str.Format(_T("%d"),((MCTRL_EXT_22*)param)->RelMctrlIndex[2]);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_REL2)
				->SetWindowText(str);
			str.Format(_T("%d"),((MCTRL_EXT_22*)param)->RelMctrlIndex[3]);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_REL3)
				->SetWindowText(str);
			str.Format(_T("%d"),((MCTRL_EXT_22*)param)->RelMctrlIndex[4]);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_REL4)
				->SetWindowText(str);
			str.Format(_T("%d"),((MCTRL_EXT_22*)param)->TimeDelta[0]);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_TIME0)
				->SetWindowText(str);
			str.Format(_T("%d"),((MCTRL_EXT_22*)param)->TimeDelta[1]);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_TIME1)
				->SetWindowText(str);
			str.Format(_T("%d"),((MCTRL_EXT_22*)param)->TimeDelta[2]);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_TIME2)
				->SetWindowText(str);
			str.Format(_T("%d"),((MCTRL_EXT_22*)param)->TimeDelta[3]);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_TIME3)
				->SetWindowText(str);
			str.Format(_T("%d"),((MCTRL_EXT_22*)param)->TimeDelta[4]);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_TIME4)
				->SetWindowText(str);
			((CButton*)m_BarParamDecode.GetDlgItem(IDC_CHECK_OP_M_22_WAITBOSS))
				->SetCheck(((MCTRL_EXT_22*)param)->WaitBoss);
			break;}
		case 23:
			str.Format(_T("%d"),((MCTRL_EXT_23*)param)->RelMctrlIndex[0]);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_23_REL0)
				->SetWindowText(str);
			str.Format(_T("%d"),((MCTRL_EXT_23*)param)->RelMctrlIndex[1]);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_23_REL1)
				->SetWindowText(str);
			str.Format(_T("%d"),((MCTRL_EXT_23*)param)->RelMctrlIndex[2]);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_23_REL2)
				->SetWindowText(str);
			str.Format(_T("%d"),((MCTRL_EXT_23*)param)->RelMctrlIndex[3]);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_23_REL3)
				->SetWindowText(str);
			str.Format(_T("%d"),((MCTRL_EXT_23*)param)->RelMctrlIndex[4]);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_23_REL4)
				->SetWindowText(str);
			str.Format(_T("%d"),((MCTRL_EXT_23*)param)->RelMctrlIndex[5]);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_23_REL5)
				->SetWindowText(str);
			str.Format(_T("%d"),((MCTRL_EXT_23*)param)->RelMctrlIndex[6]);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_23_REL6)
				->SetWindowText(str);
			str.Format(_T("%d"),((MCTRL_EXT_23*)param)->RelMctrlIndex[7]);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_23_REL7)
				->SetWindowText(str);
			break;
		case 24:
			((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_24_STYLE))
					->SetCurSel(MpeV2I(((MCTRL_EXT_24*)param)->Style,MCTRL_EXT_24_STYLE));
			str.Format(_T("%d"),((MCTRL_EXT_24*)param)->Width);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_24_WIDTH)
				->SetWindowText(str);
			str.Format(_T("%d"),((MCTRL_EXT_24*)param)->Height);
			m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_24_HEIGHT)
				->SetWindowText(str);
			break;

		case 25:
			((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_SINGLE))
				->SetCurSel(((MCTRL_EXT_25*)param)->Style?1:0);
			break;
		}
		break;
	}
}

void CDlgObj::OnBnClicked_S_Invisivle()
{
	if(((CButton*)m_BarParamDecode.GetDlgItem(IDC_CHECK_OP_S_INVISIBLE))->GetCheck())
	{
		param[3]|=SQ_ITEM_SUP_FLAG_INVISIBLE;
	}
	else
	{
		param[3]&=~SQ_ITEM_SUP_FLAG_INVISIBLE;
	}
}
void CDlgObj::OnBnClicked_S_Bubble()
{
	if(((CButton*)m_BarParamDecode.GetDlgItem(IDC_CHECK_OP_S_BUBBLE))->GetCheck())
	{
		param[3]|=SQ_ITEM_SUP_FLAG_BUBBLE;
	}
	else
	{
		param[3]&=~SQ_ITEM_SUP_FLAG_BUBBLE;
	}
}
void CDlgObj::OnBnClicked_S_Sqnow()
{
	if(((CButton*)m_BarParamDecode.GetDlgItem(IDC_CHECK_OP_S_SQNOW))->GetCheck())
	{
		param[3]|=SQ_ITEM_SUP_FLAG_SQNOW;
	}
	else
	{
		param[3]&=~SQ_ITEM_SUP_FLAG_SQNOW;
	}
}
void CDlgObj::OnBnClicked_S_FF()
{
	param[4]=((CButton*)m_BarParamDecode.GetDlgItem(IDC_CHECK_OP_S_FF))
		->GetCheck()?0xFF:0;
}
void CDlgObj::OnBnClicked_S_Treasure()
{
	if(((CButton*)m_BarParamDecode.GetDlgItem(IDC_CHECK_OP_S_TREASURE))->GetCheck())
	{
		param[6]=1;
		m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_S_TREASURE)
			->EnableWindow(TRUE);
	}
	else
	{
		param[6]=0;
		param[5]=0;
		m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_S_TREASURE)
			->EnableWindow(FALSE);
	}
}
void CDlgObj::OnCbnSelchange_S_Treasure()
{
	param[5]=((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_S_TREASURE))
		->GetCurSel();
}

void CDlgObj::OnEnChange_D_Step()
{
	CString str;
	int i;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_D_STEP)
		->GetWindowText(str);
	i=_ttoi(str);
	param[0]=(u8)min(max(0,i),255);
}
void CDlgObj::OnEnChange_D_Door()
{
	CString str;
	int i;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_D_DOOR)
		->GetWindowText(str);
	i=_ttoi(str);
	param[1]=(u8)min(max(0,i),255);
}



void CDlgObj::OnTcnSelchange_M_0_Count(NMHDR *pNMHDR, LRESULT *pResult)
{
	int i=((CTabCtrl*)m_BarParamDecode.GetDlgItem(IDC_TAB_OP_M_0_COUNT))
		->GetCurSel();
	((MCTRL_EXT_0*)param)->RelMctrlCount=i+1;
	if(i>0)
	{
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_0_REL1)
			->EnableWindow(TRUE);
		OnEnChange_M_0_Rel1();
	}
	else
	{
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_0_REL1)
			->EnableWindow(FALSE);
		((MCTRL_EXT_0*)param)->RelMctrlIndex[1]=0xFF;
	}
	if(i>1)
	{
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_0_REL2)
			->EnableWindow(TRUE);
		OnEnChange_M_0_Rel2();
	}
	else
	{
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_0_REL2)
			->EnableWindow(FALSE);
		((MCTRL_EXT_0*)param)->RelMctrlIndex[2]=0xFF;
	}
	*pResult=0;
}

void CDlgObj::OnEnChange_M_0_Rel0()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_0_REL0)
		->GetWindowText(str);
	((MCTRL_EXT_0*)param)->RelMctrlIndex[0]=min(255,_ttoi(str));
}
void CDlgObj::OnEnChange_M_0_Rel1()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_0_REL1)
		->GetWindowText(str);
	((MCTRL_EXT_0*)param)->RelMctrlIndex[1]=min(255,_ttoi(str));
}
void CDlgObj::OnEnChange_M_0_Rel2()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_0_REL2)
		->GetWindowText(str);
	((MCTRL_EXT_0*)param)->RelMctrlIndex[2]=min(255,_ttoi(str));
}
void CDlgObj::OnCbnSelchange_M_1_Style()
{
	((MCTRL_EXT_1*)param)->Style=MCTRL_EXT_1_STYLE[
		((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_1_STYLE))
		->GetCurSel()].value;
}
void CDlgObj::OnTcnSelchange_M_1_Count(NMHDR *pNMHDR, LRESULT *pResult)
{
	int i=((CTabCtrl*)m_BarParamDecode.GetDlgItem(IDC_TAB_OP_M_1_COUNT))
		->GetCurSel();
	((MCTRL_EXT_1*)param)->RelMctrlCount=i;
	if(i>0)
	{
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_1_REL0)
			->EnableWindow(TRUE);
		OnEnChange_M_1_Rel0();
	}
	else
	{
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_1_REL0)
			->EnableWindow(FALSE);
		((MCTRL_EXT_1*)param)->RelMctrlIndex[0]=0xFF;
	}
	if(i>1)
	{
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_1_REL1)
			->EnableWindow(TRUE);
		OnEnChange_M_1_Rel1();
	}
	else
	{
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_1_REL1)
			->EnableWindow(FALSE);
		((MCTRL_EXT_1*)param)->RelMctrlIndex[1]=0xFF;
	}
	*pResult=0;
}

void CDlgObj::OnEnChange_M_1_Rel0()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_1_REL0)
		->GetWindowText(str);
	((MCTRL_EXT_1*)param)->RelMctrlIndex[0]=min(255,_ttoi(str));
}
void CDlgObj::OnEnChange_M_1_Rel1()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_1_REL1)
		->GetWindowText(str);
	((MCTRL_EXT_1*)param)->RelMctrlIndex[1]=min(255,_ttoi(str));
}
void CDlgObj::OnEnChange_M_1_RopeLength()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_1_ROPELENGTH)
		->GetWindowText(str);
	((MCTRL_EXT_1*)param)->RopeLength=min(15,_ttoi(str));
}
void CDlgObj::OnBnClicked_M_2_Reverse()
{

	((MCTRL_EXT_2*)param)->Reverse
		=((CButton*)m_BarParamDecode.GetDlgItem(IDC_CHECK_OP_M_2_REVERSE))->GetCheck()?
		1:0;
}
void CDlgObj::OnEnChange_M_2_HoldTime()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_2_HOLDTIME)
		->GetWindowText(str);
	((MCTRL_EXT_2*)param)->HoldTime=min(255,_ttoi(str));
}
void CDlgObj::OnCbnSelchange_M_2_StyleMain()
{
	((MCTRL_EXT_2*)param)->MainStyle=MCTRL_EXT_2_MAIN_STYLE[
		((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_2_STYLE_MAIN))->GetCurSel()
			].value;
}
void CDlgObj::OnCbnSelchange_M_2_StyleEx()
{
	((MCTRL_EXT_2*)param)->ExStyle=MCTRL_EXT_2_EX_STYLE[
		((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_2_STYLE_EX))->GetCurSel()
		].value;
}
void CDlgObj::OnBnClicked_M_3_Fall()
{
	((MCTRL_EXT_3*)param)->Flag_Fall=((CButton*)m_BarParamDecode.GetDlgItem(IDC_CHECK_OP_M_3_FALL))->GetCheck()?
		1:0;
}
void CDlgObj::OnBnClicked_M_3_Unk()
{
	((MCTRL_EXT_3*)param)->Flag_Unk=((CButton*)m_BarParamDecode.GetDlgItem(IDC_CHECK_OP_M_3_UNK))->GetCheck()?
		1:0;
}
void CDlgObj::OnCbnSelchange_M_5_Style()
{
	((MCTRL_EXT_5*)param)->Style=MCTRL_EXT_5_STYLE[
		((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_5_MAIN))->GetCurSel()
		].value;
}
void CDlgObj::OnCbnSelchange_M_5_SubStyle()
{
	((MCTRL_EXT_5*)param)->SubStyle=MCTRL_EXT_5_SUB_STYLE[
		((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_5_SUB))->GetCurSel()
		].value;
}
void CDlgObj::OnTcnSelchange_M_5_Count(NMHDR *pNMHDR, LRESULT *pResult)
{
	int i=((CTabCtrl*)m_BarParamDecode.GetDlgItem(IDC_TAB_OP_M_5_COUNT))
		->GetCurSel();
	((MCTRL_EXT_5*)param)->NodeCount=i;
	if(i>0)
	{
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_5_DX0)
			->EnableWindow(TRUE);
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_5_DY0)
			->EnableWindow(TRUE);
		OnEnChange_M_5_DX0();
		OnEnChange_M_5_DY0();
	}
	else
	{
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_5_DX0)
			->EnableWindow(FALSE);
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_5_DY0)
			->EnableWindow(FALSE);
		((MCTRL_EXT_5*)param)->Node[0].dx=0;
		((MCTRL_EXT_5*)param)->Node[0].dy=0;
	}
	if(i>1)
	{
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_5_DX1)
			->EnableWindow(TRUE);
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_5_DY1)
			->EnableWindow(TRUE);
		OnEnChange_M_5_DX1();
		OnEnChange_M_5_DY1();
	}
	else
	{
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_5_DX1)
			->EnableWindow(FALSE);
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_5_DY1)
			->EnableWindow(FALSE);
		((MCTRL_EXT_5*)param)->Node[1].dx=0;
		((MCTRL_EXT_5*)param)->Node[1].dy=0;
	}
	if(i>2)
	{
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_5_DX2)
			->EnableWindow(TRUE);
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_5_DY2)
			->EnableWindow(TRUE);
		OnEnChange_M_5_DX2();
		OnEnChange_M_5_DY2();
	}
	else
	{
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_5_DX2)
			->EnableWindow(FALSE);
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_5_DY2)
			->EnableWindow(FALSE);
		((MCTRL_EXT_5*)param)->Node[2].dx=0;
		((MCTRL_EXT_5*)param)->Node[2].dy=0;
	}
	*pResult=0;
}
void CDlgObj::OnEnChange_M_5_DX0()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_5_DX0)
		->GetWindowText(str);
	((MCTRL_EXT_5*)param)->Node[0].dx=_ttoi(str);
}
void CDlgObj::OnEnChange_M_5_DY0()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_5_DY0)
		->GetWindowText(str);
	((MCTRL_EXT_5*)param)->Node[0].dy=_ttoi(str);
}
void CDlgObj::OnEnChange_M_5_DX1()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_5_DX1)
		->GetWindowText(str);
	((MCTRL_EXT_5*)param)->Node[1].dx=_ttoi(str);
}
void CDlgObj::OnEnChange_M_5_DY1()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_5_DY1)
		->GetWindowText(str);
	((MCTRL_EXT_5*)param)->Node[1].dy=_ttoi(str);
}
void CDlgObj::OnEnChange_M_5_DX2()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_5_DX2)
		->GetWindowText(str);
	((MCTRL_EXT_5*)param)->Node[2].dx=_ttoi(str);
}
void CDlgObj::OnEnChange_M_5_DY2()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_5_DY2)
		->GetWindowText(str);
	((MCTRL_EXT_5*)param)->Node[2].dy=_ttoi(str);
}
void CDlgObj::OnCbnSelchange_M_10_Style()
{
	((MCTRL_EXT_10*)param)->Style=(u8)MCTRL_EXT_10_STYLE[
		((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_10_STYLE))->GetCurSel()
		].value;
}
void CDlgObj::OnEnChange_M_10_Time()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_10_TIME)
		->GetWindowText(str);
	((MCTRL_EXT_10*)param)->Time=min(255,_ttoi(str));
}
void CDlgObj::OnCbnSelchange_M_14_Style()
{
	((MCTRL_EXT_14*)param)->Style
		=((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_14_STYLE))->GetCurSel();
}
void CDlgObj::OnBnClicked_M_14_Sup()
{
	((MCTRL_EXT_14*)param)->IsSup=
		((CButton*)m_BarParamDecode.GetDlgItem(IDC_CHECK_OP_M_14_SUP))->GetCheck()
		?1:0;
}
void CDlgObj::OnEnChange_M_14_Rel()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_14_REL)
		->GetWindowText(str);
	((MCTRL_EXT_14*)param)->RelFoeSupIndex=min(255,_ttoi(str));
}
void CDlgObj::OnBnClicked_M_15_Sup()
{
	if(((CButton*)m_BarParamDecode.GetDlgItem(IDC_CHECK_OP_M_15_SUP))->GetCheck())
	{
		((MCTRL_EXT_15*)param)->IsSup_LSL4=MCTRL_EXT_15_ISSUP;
	}
	else
	{
		((MCTRL_EXT_15*)param)->IsSup_LSL4=0;
	}
}
void CDlgObj::OnEnChange_M_15_Rel()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_15_REL)
		->GetWindowText(str);
	((MCTRL_EXT_15*)param)->RelFoeSupIndex=min(255,_ttoi(str));
}
void CDlgObj::OnBnClicked_M_17_Sup()
{
	((MCTRL_EXT_17*)param)->IsSup=
		((CButton*)m_BarParamDecode.GetDlgItem(IDC_CHECK_OP_M_17_SUP))->GetCheck()?
		1:0;
}
void CDlgObj::OnBnClicked_M_17_Dust()
{
	((MCTRL_EXT_17*)param)->Dust=
		((CButton*)m_BarParamDecode.GetDlgItem(IDC_CHECK_OP_M_17_DUST))->GetCheck()?
		1:0;
}
void CDlgObj::OnEnChange_M_17_Rel()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_17_REL)
		->GetWindowText(str);
	((MCTRL_EXT_17*)param)->RelFoeSupIndex=min(255,_ttoi(str));
}
void CDlgObj::OnTcnSelchange_M_22_Count(NMHDR *pNMHDR, LRESULT *pResult)
{
	int i=((CTabCtrl*)m_BarParamDecode.GetDlgItem(IDC_TAB_OP_M_22_COUNT))
		->GetCurSel();
	((MCTRL_EXT_22*)param)->RelMctrlCount=(i+1);
	if(i>0)
	{
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_REL1)
			->EnableWindow(TRUE);
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_TIME1)
			->EnableWindow(TRUE);
		OnEnChange_M_22_Rel1();
		OnEnChange_M_22_Time1();
	}
	else
	{
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_REL1)
			->EnableWindow(FALSE);
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_TIME1)
			->EnableWindow(FALSE);
		((MCTRL_EXT_22*)param)->RelMctrlIndex[1]=0xFF;
		((MCTRL_EXT_22*)param)->TimeDelta[1]=0;
	}
	if(i>1)
	{
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_REL2)
			->EnableWindow(TRUE);
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_TIME2)
			->EnableWindow(TRUE);
		OnEnChange_M_22_Rel2();
		OnEnChange_M_22_Time2();
	}
	else
	{
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_REL2)
			->EnableWindow(FALSE);
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_TIME2)
			->EnableWindow(FALSE);
		((MCTRL_EXT_22*)param)->RelMctrlIndex[2]=0xFF;
		((MCTRL_EXT_22*)param)->TimeDelta[2]=0;
	}
	if(i>2)
	{
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_REL3)
			->EnableWindow(TRUE);
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_TIME3)
			->EnableWindow(TRUE);
		OnEnChange_M_22_Rel3();
		OnEnChange_M_22_Time3();
	}
	else
	{
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_REL3)
			->EnableWindow(FALSE);
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_TIME3)
			->EnableWindow(FALSE);
		((MCTRL_EXT_22*)param)->RelMctrlIndex[3]=0xFF;
		((MCTRL_EXT_22*)param)->TimeDelta[3]=0;
	}
	if(i>3)
	{
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_REL4)
			->EnableWindow(TRUE);
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_TIME4)
			->EnableWindow(TRUE);
		OnEnChange_M_22_Rel4();
		OnEnChange_M_22_Time4();
	}
	else
	{
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_REL4)
			->EnableWindow(FALSE);
		m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_TIME4)
			->EnableWindow(FALSE);
		((MCTRL_EXT_22*)param)->RelMctrlIndex[4]=0xFF;
		((MCTRL_EXT_22*)param)->TimeDelta[4]=0;
	}
	*pResult=0;
}
void CDlgObj::OnEnChange_M_22_Rel0()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_REL0)
		->GetWindowText(str);
	((MCTRL_EXT_22*)param)->RelMctrlIndex[0]=min(255,_ttoi(str));
}
void CDlgObj::OnEnChange_M_22_Rel1()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_REL1)
		->GetWindowText(str);
	((MCTRL_EXT_22*)param)->RelMctrlIndex[1]=min(255,_ttoi(str));
}
void CDlgObj::OnEnChange_M_22_Rel2()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_REL2)
		->GetWindowText(str);
	((MCTRL_EXT_22*)param)->RelMctrlIndex[2]=min(255,_ttoi(str));
}
void CDlgObj::OnEnChange_M_22_Rel3()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_REL3)
		->GetWindowText(str);
	((MCTRL_EXT_22*)param)->RelMctrlIndex[3]=min(255,_ttoi(str));
}
void CDlgObj::OnEnChange_M_22_Rel4()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_REL4)
		->GetWindowText(str);
	((MCTRL_EXT_22*)param)->RelMctrlIndex[4]=min(255,_ttoi(str));
}
void CDlgObj::OnEnChange_M_22_Time0()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_TIME0)
		->GetWindowText(str);
	((MCTRL_EXT_22*)param)->TimeDelta[0]=min(65535,_ttoi(str));
}
void CDlgObj::OnEnChange_M_22_Time1()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_TIME1)
		->GetWindowText(str);
	((MCTRL_EXT_22*)param)->TimeDelta[1]=min(65535,_ttoi(str));
}
void CDlgObj::OnEnChange_M_22_Time2()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_TIME2)
		->GetWindowText(str);
	((MCTRL_EXT_22*)param)->TimeDelta[2]=min(65535,_ttoi(str));
}
void CDlgObj::OnEnChange_M_22_Time3()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_TIME3)
		->GetWindowText(str);
	((MCTRL_EXT_22*)param)->TimeDelta[3]=min(65535,_ttoi(str));
}
void CDlgObj::OnEnChange_M_22_Time4()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_22_TIME4)
		->GetWindowText(str);
	((MCTRL_EXT_22*)param)->TimeDelta[4]=min(65535,_ttoi(str));
}
void CDlgObj::OnBnClicked_M_22_WaitBoss()
{
	((MCTRL_EXT_22*)param)->WaitBoss=
		((CButton*)m_BarParamDecode.GetDlgItem(IDC_CHECK_OP_M_22_WAITBOSS))->GetCheck()?
		1:0;
}
void CDlgObj::OnEnChange_M_23_Rel0()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_23_REL0)
		->GetWindowText(str);
	((MCTRL_EXT_23*)param)->RelMctrlIndex[0]=min(255,_ttoi(str));
}
void CDlgObj::OnEnChange_M_23_Rel1()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_23_REL1)
		->GetWindowText(str);
	((MCTRL_EXT_23*)param)->RelMctrlIndex[1]=min(255,_ttoi(str));
}
void CDlgObj::OnEnChange_M_23_Rel2()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_23_REL2)
		->GetWindowText(str);
	((MCTRL_EXT_23*)param)->RelMctrlIndex[2]=min(255,_ttoi(str));
}
void CDlgObj::OnEnChange_M_23_Rel3()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_23_REL3)
		->GetWindowText(str);
	((MCTRL_EXT_23*)param)->RelMctrlIndex[3]=min(255,_ttoi(str));
}
void CDlgObj::OnEnChange_M_23_Rel4()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_23_REL4)
		->GetWindowText(str);
	((MCTRL_EXT_23*)param)->RelMctrlIndex[4]=min(255,_ttoi(str));
}
void CDlgObj::OnEnChange_M_23_Rel5()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_23_REL5)
		->GetWindowText(str);
	((MCTRL_EXT_23*)param)->RelMctrlIndex[5]=min(255,_ttoi(str));
}
void CDlgObj::OnEnChange_M_23_Rel6()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_23_REL6)
		->GetWindowText(str);
	((MCTRL_EXT_23*)param)->RelMctrlIndex[6]=min(255,_ttoi(str));
}
void CDlgObj::OnEnChange_M_23_Rel7()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_23_REL7)
		->GetWindowText(str);
	((MCTRL_EXT_23*)param)->RelMctrlIndex[7]=min(255,_ttoi(str));
}
void CDlgObj::OnEnChange_M_24_Width()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_24_WIDTH)
		->GetWindowText(str);
	((MCTRL_EXT_24*)param)->Width=min(255,_ttoi(str));
}
void CDlgObj::OnEnChange_M_24_Height()
{
	CString str;
	m_BarParamDecode.GetDlgItem(IDC_EDIT_OP_M_24_HEIGHT)
		->GetWindowText(str);
	((MCTRL_EXT_24*)param)->Height=min(255,_ttoi(str));
}
void CDlgObj::OnCbnSelchange_M_24_Style()
{
	((MCTRL_EXT_24*)param)->Style=MCTRL_EXT_24_STYLE[
		((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_24_STYLE))->GetCurSel()
		].value;
}

void CDlgObj::OnCbnSelchange_M_Single()
{
	switch(class_id)
	{
	case 6:
		((MCTRL_EXT_6*)param)->Style=MCTRL_EXT_6_STYLE[
			((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_SINGLE))->GetCurSel()
			].value;
		break;
	case 11:{
		int i=((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_SINGLE))
			->GetCurSel();
		if(i==0)((MCTRL_EXT_25*)param)->Style=1;
		else ((MCTRL_EXT_25*)param)->Style=(i-1)*36;
		break;}
	case 25:
		((MCTRL_EXT_25*)param)->Style=
			((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_SINGLE))
			->GetCurSel();
		break;
	}
}
void CDlgObj::OnDestroy()
{
	CDialog::OnDestroy();

	CleanRelMctrlPreset();
}

