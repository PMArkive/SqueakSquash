﻿//UTF8♔

#include "stdafx.h"
#include "DlgGuide.h"
#include "DlgGuideResize.h"



IMPLEMENT_DYNAMIC(CDlgGuide, CDialog)

CDlgGuide::CDlgGuide(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGuide::IDD, pParent)
{

}

CDlgGuide::~CDlgGuide()
{
}

void CDlgGuide::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(CDlgGuide, CDialog)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_GUIDE_RESIZE,CDlgGuide::OnGuideResize)
END_MESSAGE_MAP()

/*

[WIDTH_L]      [WIDTH_R*GuideCount]
#################################################
#           #$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$# [HEIGHT_T]
#################################################
#***********#...................................# [HEIGHT_B*GuideCount]
#***********#...................................#
#***********#...................................#
#***Guide***#............Distance...............#
#****Info***#..............Matrix...............#
#***********#...................................#
#***********#...................................#
#################################################

*/
#define WIDTH_L 192
#define WIDTH_R 24
#define HEIGHT_T 24
#define HEIGHT_B 24
#define GX_OID 0
#define GX_IID 24
#define GX_X 48
#define GX_Y 96
#define GX_U 144



void CDlgGuide::SetScroll()
{
	RECT rc;
	rc.left=0;
	rc.top=0;
	rc.right=max(WIDTH_L+WIDTH_R*m_pMa->GetGuideCount()+6,500);
	rc.bottom=HEIGHT_T+HEIGHT_B*m_pMa->GetGuideCount()+6;
	m_pGuideTable->MoveWindow(&rc);
	m_pGuideTable->m_cur=CGuideTable::N;
	m_pGuideTable->m_Edit.ShowWindow(SW_HIDE);

	RECT wrc;
	int hsrg,vsrg;
	GetClientRect(&wrc);
	hsrg=rc.right-wrc.right+16;
	if(hsrg<1)hsrg=1;
	vsrg=rc.bottom-wrc.bottom+16;
	if(vsrg<1)vsrg=1;
	SCROLLINFO scrinfo={0};
	scrinfo.cbSize=sizeof(SCROLLINFO);
	scrinfo.fMask=SIF_PAGE|SIF_RANGE|SIF_POS;
	scrinfo.nPage=wrc.right;
	scrinfo.nMin=0;scrinfo.nMax=hsrg-1+scrinfo.nPage-1;
	scrinfo.nPos=0;
	SetScrollInfo(SB_HORZ,&scrinfo);
	scrinfo.nPage=wrc.bottom;
	scrinfo.nMin=0;scrinfo.nMax=vsrg-1+scrinfo.nPage-1;
	scrinfo.nPos=0;
	SetScrollInfo(SB_VERT,&scrinfo);
}
BOOL CDlgGuide::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_pGuideTable=new CGuideTable;
	m_pGuideTable->m_pMa=m_pMa;
	m_pGuideTable->Create(0,0,WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this);

	SetScroll();
	return TRUE;
}
void CDlgGuide::OnWndScroll(UINT nSBCode, UINT nPos,int nBar)
{
	// Get the minimum and maximum scroll-bar positions.
   int minpos;
   int maxpos;
   GetScrollRange(nBar, &minpos, &maxpos); 
   maxpos = GetScrollLimit(nBar);

   // Get the current position of scroll box.
   int curpos = GetScrollPos(nBar);

   // Determine the new position of scroll box.
   switch (nSBCode)
   {
   case SB_LEFT:      // Scroll to far left.
      curpos = minpos;
      break;

   case SB_RIGHT:      // Scroll to far right.
      curpos = maxpos;
      break;

   case SB_ENDSCROLL:   // End scroll.
      break;

   case SB_LINELEFT:      // Scroll left.
      if (curpos > minpos)
         curpos--;
      break;

   case SB_LINERIGHT:   // Scroll right.
      if (curpos < maxpos)
         curpos++;
      break;

   case SB_PAGELEFT:    // Scroll one page left.
   {
      // Get the page size. 
      SCROLLINFO   info;
      GetScrollInfo(nBar, &info, SIF_ALL);

      if (curpos > minpos)
      curpos = max(minpos, curpos - (int) info.nPage);
   }
      break;

   case SB_PAGERIGHT:      // Scroll one page right.
   {
      // Get the page size. 
      SCROLLINFO   info;
      GetScrollInfo(nBar, &info, SIF_ALL);

      if (curpos < maxpos)
         curpos = min(maxpos, curpos + (int) info.nPage);
   }
      break;

   case SB_THUMBPOSITION: // Scroll to absolute position. nPos is the position
      curpos = nPos;      // of the scroll box at the end of the drag operation.
      break;

   case SB_THUMBTRACK:   // Drag scroll box to specified position. nPos is the
      curpos = nPos;     // position that the scroll box has been dragged to.
      break;
   }

   // Set the new position of the thumb (scroll box).
   SetScrollPos(nBar, curpos);


   CRect rc;
   m_pGuideTable->GetWindowRect(&rc);
   rc-=rc.TopLeft();
   rc-=CPoint(GetScrollPos(SB_HORZ),GetScrollPos(SB_VERT));
   m_pGuideTable->MoveWindow(&rc);

}

void CDlgGuide::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	OnWndScroll(nSBCode,nPos,SB_VERT);
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CDlgGuide::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	OnWndScroll(nSBCode,nPos,SB_HORZ);
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

BEGIN_MESSAGE_MAP(CGuideTable, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_EN_CHANGE(IDC_EDIT_GUIDE,CGuideTable::OnEditChange)
	ON_BN_CLICKED(IDC_BUTTON_GUIDE_RESIZE,CGuideTable::OnGuideResize)
END_MESSAGE_MAP()

void CGuideTable::OnEditChange()
{
	CString str;
	m_Edit.GetWindowText(str);
	int i,j;
	switch(m_cur)
	{
	case I:
		i=_ttoi(str);
		m_pMa->Guide(m_curi).index=(u16)max(min(i,65535),0);
		break;
	case X:
		if(str.Find(_T('.'))==-1)
		{
			i=_ttoi(str);
			i*=16;
		}
		else
		{
			_stscanf(str,_T("%d.%x"),&i,&j);
			i=i*16+j;
		}
		m_pMa->Guide(m_curi).x=(u16)i;
		break;
	case Y:
		if(str.Find(_T('.'))==-1)
		{
			i=_ttoi(str);
			i*=16;
		}
		else
		{
			_stscanf(str,_T("%d.%x"),&i,&j);
			i=i*16+j;
		}
		m_pMa->Guide(m_curi).y=(u16)i;
		break;
	case U:
		i=_ttoi(str);
		m_pMa->Guide(m_curi).U=(u16)max(min(i,65535),0);
		break;
	case M:
		i=_ttoi(str);
		m_pMa->GuideMatrix(m_curi*m_pMa->GetGuideCount()+m_curj)=(u8)max(min(i,255),0);
		break;
	default:
		ASSERT(FALSE);
	}
}

void CGuideTable::OnPaint()
{
	CPaintDC dc(this);
	CString str;
	str=_T("表");
	dc.TextOut(GX_OID,0,str,str.GetLength());
	str=_T("里");
	dc.TextOut(GX_IID,0,str,str.GetLength());
	str=_T("X");
	dc.TextOut(GX_X,0,str,str.GetLength());
	str=_T("Y");
	dc.TextOut(GX_Y,0,str,str.GetLength());
	str=_T("?");
	dc.TextOut(GX_U,0,str,str.GetLength());
	str=_T("距离矩阵");
	dc.TextOut(WIDTH_L,0,str,str.GetLength());
	for(u16 i=0;i<m_pMa->GetGuideCount();++i)
	{
		str.Format(_T("%d"),i);
		dc.TextOut(GX_OID,
			HEIGHT_T+HEIGHT_B*i,str,str.GetLength());
		if(i==m_pMa->Guide(i).index)
		{
			str=_T("~");
		}
		else
		{
			str.Format(_T("%d"),m_pMa->Guide(i).index);
		}
		dc.TextOut(GX_IID,
			HEIGHT_T+HEIGHT_B*i,str,str.GetLength());
		str.Format(_T("%d.%X"),m_pMa->Guide(i).x>>4,m_pMa->Guide(i).x&0xF);
		dc.TextOut(GX_X,
			HEIGHT_T+HEIGHT_B*i,str,str.GetLength());
		str.Format(_T("%d.%X"),m_pMa->Guide(i).y>>4,m_pMa->Guide(i).y&0xF);
		dc.TextOut(GX_Y,
			HEIGHT_T+HEIGHT_B*i,str,str.GetLength());
		str.Format(_T("%d"),m_pMa->Guide(i).U);
		dc.TextOut(GX_U,
			HEIGHT_T+HEIGHT_B*i,str,str.GetLength());
		for(u16 j=0;j<m_pMa->GetGuideCount();++j)
		{
			str.Format(_T("%d"),
				m_pMa->GuideMatrix(i*m_pMa->GetGuideCount()+j));
			dc.TextOut(WIDTH_L+WIDTH_R*j,
				HEIGHT_T+HEIGHT_B*i,str,str.GetLength());
		}
		
	}
	for(u16 i=0;i<=m_pMa->GetGuideCount();++i)
	{
		dc.MoveTo(WIDTH_L+WIDTH_R*i,HEIGHT_T);
		dc.LineTo(WIDTH_L+WIDTH_R*i,HEIGHT_T+HEIGHT_B*m_pMa->GetGuideCount());
		dc.MoveTo(WIDTH_L,HEIGHT_T+HEIGHT_B*i);
		dc.LineTo(WIDTH_L+WIDTH_R*m_pMa->GetGuideCount(),HEIGHT_T+HEIGHT_B*i);
	}
}


void CGuideTable::OnLButtonDown(UINT nFlags, CPoint point)
{

	CString str;
	if(point.y>HEIGHT_T && point.y<HEIGHT_T+HEIGHT_B*m_pMa->GetGuideCount()
		&& point.x>GX_IID && point.x<WIDTH_L+WIDTH_R*m_pMa->GetGuideCount())
	{
		int y;
		y=(point.y-HEIGHT_T)/HEIGHT_B;
		m_curi=y;
		if(point.x>WIDTH_L)
		{
			int x;
			x=(point.x-WIDTH_L)/WIDTH_R;
			str.Format(_T("%d"),m_pMa->GuideMatrix(x+y*m_pMa->GetGuideCount()));
			m_Edit.MoveWindow(WIDTH_L+x*WIDTH_R,HEIGHT_T+y*HEIGHT_B,
				WIDTH_R,HEIGHT_B);
			m_cur=M;
			m_curj=x;
			
		}
		else if(point.x>GX_U)
		{
			str.Format(_T("%d"),m_pMa->Guide(y).U);
			m_Edit.MoveWindow(GX_U,HEIGHT_T+y*HEIGHT_B,
				WIDTH_L-GX_U,HEIGHT_B);
			m_cur=U;
		}
		else if(point.x>GX_Y)
		{
			str.Format(_T("%d.%X"),m_pMa->Guide(y).y>>4,m_pMa->Guide(y).y&0xF);
			m_Edit.MoveWindow(GX_Y,HEIGHT_T+y*HEIGHT_B,
				GX_U-GX_Y,HEIGHT_B);
			m_cur=Y;
		}
		else if(point.x>GX_X)
		{
			str.Format(_T("%d.%X"),m_pMa->Guide(y).x>>4,m_pMa->Guide(y).x&0xF);
			m_Edit.MoveWindow(GX_X,HEIGHT_T+y*HEIGHT_B,
				GX_Y-GX_X,HEIGHT_B);
			m_cur=X;
		}
		else //if(point.x>GX_IID)
		{
			str.Format(_T("%d"),m_pMa->Guide(y).index);
			m_Edit.MoveWindow(GX_IID,HEIGHT_T+y*HEIGHT_B,
				GX_X-GX_IID,HEIGHT_B);
			m_cur=I;
		}
		m_Edit.SetWindowText(str);
		m_Edit.ShowWindow(SW_SHOW);
		m_Edit.SetFocus();
		m_Edit.SetSel(0,-1,0);
		if(m_cur==M)
		{
			str.Format(_T("(%d,%d)"),m_curi,m_curj);
#ifdef _UNICODE
			m_Edit.ShowBalloonTip(0,str);
#endif
		}
		else
		{
#ifdef _UNICODE
			m_Edit.HideBalloonTip();
#endif
		}
		RedrawWindow();
	}
	else
	{
		m_Edit.ShowWindow(SW_HIDE);
		m_cur=N;
		RedrawWindow();
	}

	CFrameWnd::OnLButtonDown(nFlags, point);
}

int CGuideTable::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_Edit.Create(WS_CHILD|ES_AUTOHSCROLL,CRect(0,0,0,0),this,IDC_EDIT_GUIDE);
	m_cur=N;

	m_ButtomResize.Create(_T("更改引导器数量"),WS_CHILD|WS_VISIBLE,
		CRect(WIDTH_L+128,0,WIDTH_L+256,HEIGHT_T),this,IDC_BUTTON_GUIDE_RESIZE);

	return 0;
}
void CGuideTable::OnGuideResize()
{

	::PostMessage(GetParent()->GetSafeHwnd(),WM_COMMAND,
		MAKELONG(IDC_BUTTON_GUIDE_RESIZE,BN_CLICKED),(LPARAM)m_ButtomResize.GetSafeHwnd());
}
void CDlgGuide::OnGuideResize()
{

	CDlgGuideResize dlg;
	dlg.m_GuideCount=m_pMa->GetGuideCount();
	if(dlg.DoModal()==IDOK)
	{
		m_pMa->ResizeGuide(dlg.m_GuideCount);
		SetScroll();
		m_pGuideTable->RedrawWindow();
	}
}