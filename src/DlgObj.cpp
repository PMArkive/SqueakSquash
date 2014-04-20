
//UTF16♔

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

	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_OP_M_0_COUNT, &CDlgObj::OnTcnSelchange_M_0_Count)
	ON_EN_CHANGE(IDC_EDIT_OP_M_0_REL0, &CDlgObj::OnEnChange_M_0_Rel0)
	ON_EN_CHANGE(IDC_EDIT_OP_M_0_REL1, &CDlgObj::OnEnChange_M_0_Rel1)
	ON_EN_CHANGE(IDC_EDIT_OP_M_0_REL2, &CDlgObj::OnEnChange_M_0_Rel2)

	ON_BN_CLICKED(IDC_CHECK_OP_M_3_FALL, &CDlgObj::OnBnClicked_M_3_Fall)
	ON_BN_CLICKED(IDC_CHECK_OP_M_3_UNK, &CDlgObj::OnBnClicked_M_3_Unk)

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

	ON_CBN_SELCHANGE(IDC_COMBO_OP_M_SINGLE,  &CDlgObj::OnCbnSelchange_M_Single)

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
			break;
		case 3:
			m_BarParamDecode.Create(this,IDDB_OBJ_PARAM_MCTRL_3,
				CBRS_NOALIGN,IDDB_OBJ_PARAM_MCTRL_3);
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
			break;
		case 25:
			m_BarParamDecode.Create(this,IDDB_OBJ_PARAM_MCTRL_SINGLE,
				CBRS_NOALIGN,IDDB_OBJ_PARAM_MCTRL_SINGLE);
			((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_SINGLE))
				->AddString(_T("火花"));
			((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_SINGLE))
				->AddString(_T("气泡"));
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
			int count=((MCTRL_EXT_0*)param)->RelMctrlCount_LSL4>>4;
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
		case 3:
			((CButton*)m_BarParamDecode.GetDlgItem(IDC_CHECK_OP_M_3_FALL))
				->SetCheck(((MCTRL_EXT_3*)param)->Style&MCTRL_EXT_3_FLAG_FALL?TRUE:FALSE);
			((CButton*)m_BarParamDecode.GetDlgItem(IDC_CHECK_OP_M_3_UNK))
				->SetCheck(((MCTRL_EXT_3*)param)->Style&MCTRL_EXT_3_FLAG_UNK?TRUE:FALSE);
			break;
		case 22:{
			int count=((MCTRL_EXT_22*)param)->RelMctrlCount_OR_WaitBoss
				&MCTRL_EXT_22_RELMCTRLCOUNT_MASK;
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
				->SetCheck(((MCTRL_EXT_22*)param)->RelMctrlCount_OR_WaitBoss
				&MCTRL_EXT_22_WAITBOSS?TRUE:FALSE);
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
	((MCTRL_EXT_0*)param)->RelMctrlCount_LSL4=(i+1)<<4;
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

void CDlgObj::OnBnClicked_M_3_Fall()
{
	if(((CButton*)m_BarParamDecode.GetDlgItem(IDC_CHECK_OP_M_3_FALL))->GetCheck())
	{
		((MCTRL_EXT_3*)param)->Style|=MCTRL_EXT_3_FLAG_FALL;
	}
	else
	{
		((MCTRL_EXT_3*)param)->Style&=~MCTRL_EXT_3_FLAG_FALL;
	}
}
void CDlgObj::OnBnClicked_M_3_Unk()
{
	if(((CButton*)m_BarParamDecode.GetDlgItem(IDC_CHECK_OP_M_3_UNK))->GetCheck())
	{
		((MCTRL_EXT_3*)param)->Style|=MCTRL_EXT_3_FLAG_UNK;
	}
	else
	{
		((MCTRL_EXT_3*)param)->Style&=~MCTRL_EXT_3_FLAG_UNK;
	}
}

void CDlgObj::OnTcnSelchange_M_22_Count(NMHDR *pNMHDR, LRESULT *pResult)
{
	int i=((CTabCtrl*)m_BarParamDecode.GetDlgItem(IDC_TAB_OP_M_22_COUNT))
		->GetCurSel();
	((MCTRL_EXT_22*)param)->RelMctrlCount_OR_WaitBoss
		=(((MCTRL_EXT_22*)param)->RelMctrlCount_OR_WaitBoss&MCTRL_EXT_22_WAITBOSS) |
		(i+1);
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
	if(((CButton*)m_BarParamDecode.GetDlgItem(IDC_CHECK_OP_M_22_WAITBOSS))->GetCheck())
	{
		((MCTRL_EXT_22*)param)->RelMctrlCount_OR_WaitBoss|=MCTRL_EXT_22_WAITBOSS;
	}
	else
	{
		((MCTRL_EXT_22*)param)->RelMctrlCount_OR_WaitBoss&=~MCTRL_EXT_22_WAITBOSS;
	}
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

void CDlgObj::OnCbnSelchange_M_Single()
{
	switch(class_id)
	{
	case 25:
		((MCTRL_EXT_25*)param)->Style=
			((CComboBox*)m_BarParamDecode.GetDlgItem(IDC_COMBO_OP_M_SINGLE))
			->GetCurSel();
		break;
	}
}