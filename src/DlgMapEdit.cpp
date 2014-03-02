


//Unicode

#include "stdafx.h"
#include "DlgMapEdit.h"
#include "Det.h"
#include "Bgm.h"
#include "Foe.h"
#include "DlgObj.h"
#include "DlgResize.h"


IMPLEMENT_DYNAMIC(CDlgMapEdit, CDialog)

CDlgMapEdit::CDlgMapEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMapEdit::IDD, pParent)
{

}

CDlgMapEdit::~CDlgMapEdit()
{
}

void CDlgMapEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAP_HSCROLL, m_HScroll);
	DDX_Control(pDX, IDC_MAP_VSCROLL, m_VScroll);
	DDX_Control(pDX, IDC_CHECK_MAP_PLANE2, m_CheckPlane2);
	DDX_Control(pDX, IDC_CHECK_MAP_PLANE0, m_CheckPlane0);
	DDX_Control(pDX, IDC_CHECK_MAP_DET, m_CheckDet);
	DDX_Control(pDX, IDC_MAP_STOCK_SCROLL, m_VScrollStock);
	DDX_Control(pDX, IDC_MAP_STOCK_HSCROLL, m_HScrollStock);
	DDX_Control(pDX, IDC_STATIC_MAP_CUR_COORD, m_StaticCurCoord);
	DDX_Control(pDX, IDC_EDIT_MAP_CUR_GRID0, m_EditCurGrid0);
	DDX_Control(pDX, IDC_EDIT_MAP_CUR_GRID1, m_EditCurGrid1);
	DDX_Control(pDX, IDC_EDIT_MAP_CUR_GRID2, m_EditCurGrid2);
	DDX_Control(pDX, IDC_COMBO_BGM, m_ComboBgm);
	DDX_Control(pDX, IDC_COMBO_BOSS, m_ComboBoss);
	DDX_Control(pDX, IDC_CHECK_MAP_ANI, m_CheckMapAni);
	DDX_Control(pDX, IDC_LIST_MAP_OBJ, m_ListObj);
	DDX_Control(pDX, IDC_EDIT_MAP_CUR_GRID_BOSS, m_EditCurGridBoss);
	DDX_Control(pDX, IDC_CHECK_HIDE_FOE, m_CheckHideFoe);
	DDX_Control(pDX, IDC_CHECK_HIDE_SUP, m_CheckHideSup);
	DDX_Control(pDX, IDC_CHECK_HIDE_DOOR, m_CheckHideDoor);
	DDX_Control(pDX, IDC_CHECK_HIDE_MCTRL, m_CheckHideMctrl);
	DDX_Control(pDX, IDC_CHECK_OBJ_MOVING_ALIGN, m_CheckObjMovingAlign);
	DDX_Control(pDX, IDC_BUTTON_OBJ_UP, m_ButtonObjUp);
	DDX_Control(pDX, IDC_BUTTON_OBJ_DOWN, m_ButtonObjDown);
	DDX_Control(pDX, IDC_BUTTON_OBJ_NEW, m_ButtonObjNew);
	DDX_Control(pDX, IDC_BUTTON_OBJ_DELETE, m_ButtonObjDelete);
	DDX_Control(pDX, IDC_BUTTON_OBJ_PROPERTY, m_ButtonObjProperty);
}


BEGIN_MESSAGE_MAP(CDlgMapEdit, CDialog)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_CHECK_MAP_PLANE2, &CDlgMapEdit::OnBnClickedCheckMapPlane2)
	ON_BN_CLICKED(IDC_CHECK_MAP_PLANE0, &CDlgMapEdit::OnBnClickedCheckMapPlane0)
	ON_BN_CLICKED(IDC_CHECK_MAP_DET, &CDlgMapEdit::OnBnClickedCheckMapDet)

	ON_WM_SETCURSOR()
	ON_STN_DBLCLK(IDC_STATIC_MAP,&CDlgMapEdit::OnMapDbClick)
	ON_CBN_SELCHANGE(IDC_COMBO_BGM, &CDlgMapEdit::OnCbnSelchangeComboBgm)
	ON_CBN_SELCHANGE(IDC_COMBO_BOSS, &CDlgMapEdit::OnCbnSelchangeComboBoss)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_MAP_ANI, &CDlgMapEdit::OnBnClickedCheckMapAni)
	ON_BN_CLICKED(IDC_RADIO_MAP_PT_GRID, &CDlgMapEdit::OnBnClickedRadioMapPtGrid)
	ON_BN_CLICKED(IDC_RADIO_MAP_PT_OBJ, &CDlgMapEdit::OnBnClickedRadioMapPtObj)
	ON_BN_CLICKED(IDC_RADIO_MAP_PT_BOSS, &CDlgMapEdit::OnBnClickedRadioMapPtBoss)
	ON_BN_CLICKED(IDC_CHECK_HIDE_FOE, &CDlgMapEdit::OnBnClickedCheckHideObj)
	ON_BN_CLICKED(IDC_CHECK_HIDE_SUP, &CDlgMapEdit::OnBnClickedCheckHideObj)
	ON_BN_CLICKED(IDC_CHECK_HIDE_DOOR, &CDlgMapEdit::OnBnClickedCheckHideObj)
	ON_BN_CLICKED(IDC_CHECK_HIDE_MCTRL, &CDlgMapEdit::OnBnClickedCheckHideObj)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_MAP_OBJ, &CDlgMapEdit::OnLvnItemchangedListMapObj)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_OBJ_UP, &CDlgMapEdit::OnBnClickedButtonObjUp)
	ON_BN_CLICKED(IDC_BUTTON_OBJ_DOWN, &CDlgMapEdit::OnBnClickedButtonObjDown)
	ON_BN_CLICKED(IDC_BUTTON_OBJ_NEW, &CDlgMapEdit::OnBnClickedButtonObjNew)
	ON_BN_CLICKED(IDC_BUTTON_OBJ_DELETE, &CDlgMapEdit::OnBnClickedButtonObjDelete)
	ON_BN_CLICKED(IDC_BUTTON_OBJ_PROPERTY, &CDlgMapEdit::OnBnClickedButtonObjProperty)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_MAP_OBJ, &CDlgMapEdit::OnNMDblclkListMapObj)
	ON_COMMAND(ID_NEWOBJ_FOE,&CDlgMapEdit::OnNewFoe)
	ON_COMMAND(ID_NEWOBJ_SUP,&CDlgMapEdit::OnNewSup)
	ON_COMMAND(ID_NEWOBJ_DOOR,&CDlgMapEdit::OnNewDoor)
	ON_COMMAND(ID_NEWOBJ_MCTRL,&CDlgMapEdit::OnNewMctrl)
	ON_BN_CLICKED(IDC_BUTTON_MAP_CANCEL, &CDlgMapEdit::OnBnClickedButtonMapCancel)
	ON_BN_CLICKED(IDC_BUTTON_MAP_RESIZE, &CDlgMapEdit::OnBnClickedButtonMapResize)
	ON_BN_CLICKED(IDC_BUTTON_ZERO_CELL, &CDlgMapEdit::OnBnClickedButtonZeroCell)
END_MESSAGE_MAP()


void CDlgMapEdit::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	OnScroll(nSBCode,nPos,pScrollBar);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	if(pScrollBar==&m_HScroll)
	{
		GetDlgItem(IDC_STATIC_MAP)->RedrawWindow();
		GetDlgItem(IDC_STATIC_MAP_CX)->RedrawWindow();
		GetDlgItem(IDC_STATIC_MAP_CY)->RedrawWindow();
	}
	else if(pScrollBar==&m_HScrollStock)GetDlgItem(IDC_STATIC_STOCK)->RedrawWindow();
}

void CDlgMapEdit::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	OnScroll(nSBCode,nPos,pScrollBar);

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
	if(pScrollBar==&m_VScroll)
	{
		GetDlgItem(IDC_STATIC_MAP)->RedrawWindow();
		GetDlgItem(IDC_STATIC_MAP_CX)->RedrawWindow();
		GetDlgItem(IDC_STATIC_MAP_CY)->RedrawWindow();
	}
	else if(pScrollBar==&m_VScrollStock)GetDlgItem(IDC_STATIC_STOCK)->RedrawWindow();
}

void CDlgMapEdit::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	RECT rc;
	if(nIDCtl==IDC_STATIC_MAP)
	{
		CString str;

		GetDlgItem(IDC_STATIC_MAP)->GetClientRect(&rc);
		m_CanMap.Present(lpDrawItemStruct->hDC,0,0,rc.right,rc.bottom,
			m_HScroll.GetScrollPos(),m_VScroll.GetScrollPos());

		//static CBrush BlackBrush(RGB(0,0,0));
		RECT rcb;
		rcb.top=0;
		rcb.bottom=rc.bottom;
		rcb.left=m_Ma.GetW()*16-m_HScroll.GetScrollPos();
		rcb.right=rc.right;
		FillRect(lpDrawItemStruct->hDC,&rcb,(HBRUSH)GetStockObject(BLACK_BRUSH));
		rcb.right=rcb.left;
		rcb.left=0;
		rcb.top=m_Ma.GetH()*16-m_VScroll.GetScrollPos();
		FillRect(lpDrawItemStruct->hDC,&rcb,(HBRUSH)GetStockObject(BLACK_BRUSH));
		

		CBrush NullBrush,*pOldBrush;
		CPoint pt;
		CPen* pOldPen;
		
		if(mode==MPT_OBJ)
		{
			static CPen PenFoe(PS_SOLID,2,RGB(192,0,0)),
				PenSup(PS_SOLID,2,RGB(0,0,192)),
				PenDoor(PS_SOLID,2,RGB(0,192,0)),
				PenEp(PS_SOLID,2,RGB(192,0,192)),
				PenCur(PS_SOLID,2,RGB(255,255,0)),
				PenSel(PS_DOT,1,RGB(255,0,0));
			bool hitcur=false;
			
			
			NullBrush.CreateStockObject(NULL_BRUSH);
			pOldBrush=dc.SelectObject(&NullBrush);
			

			dc.SetBkMode(TRANSPARENT);

			//Foe
			pOldPen=dc.SelectObject(&PenFoe);
			if(!m_CheckHideFoe.GetCheck())for(u16 i=0;i<m_De.GetFoeCount();++i)
			{
				pt.x=m_De.Foe(i).x-7-m_HScroll.GetScrollPos();
				pt.y=m_De.Foe(i).y-7-m_VScroll.GetScrollPos();
				if(cur_obj==i && cur_objgroup==FOE)
				{
					dc.SelectObject(&PenCur);
					hitcur=true;
				}
				else if(hitcur)
				{
					dc.SelectObject(&PenFoe);
					hitcur=false;
				}
				dc.Ellipse(pt.x,pt.y,pt.x+14,pt.y+14);
				str.Format(_T("%d %s"),i,FoeDesc[m_De.Foe(i).class_id].name);
				dc.DrawText(str,CRect(pt.x+4,pt.y,0,0),DT_LEFT|DT_TOP|DT_NOCLIP);
			}
			
			//Sup
			dc.SelectObject(&PenSup);
			if(!m_CheckHideSup.GetCheck())for(u16 i=0;i<m_De.GetSupCount();++i)
			{
				pt.x=m_De.Sup(i).x-m_HScroll.GetScrollPos();
				pt.y=m_De.Sup(i).y-9-m_VScroll.GetScrollPos();
				if(cur_obj==i && cur_objgroup==SUP)
				{
					dc.SelectObject(&PenCur);
					hitcur=true;
				}
				else if(hitcur)
				{
					dc.SelectObject(&PenSup);
					hitcur=false;
				}
				dc.MoveTo(pt);
				pt.x-=8;
				pt.y+=13;
				dc.LineTo(pt);
				pt.x+=16;
				dc.LineTo(pt);
				pt.x-=8;
				pt.y-=13;
				dc.LineTo(pt);
				str.Format(_T("%d %s"),i,SupDesc[m_De.Sup(i).class_id].name);
				dc.DrawText(str,CRect(pt.x-2,pt.y+1,0,0),DT_LEFT|DT_TOP|DT_NOCLIP);
			}

			//Door
			dc.SelectObject(&PenDoor);
			if(!m_CheckHideDoor.GetCheck())for(u16 i=0;i<m_Ma.GetDoorCount();++i)
			{
				pt.x=m_Ma.Door(i).x-8-m_HScroll.GetScrollPos();
				pt.y=m_Ma.Door(i).y-8-m_VScroll.GetScrollPos();
				if(cur_obj==i && cur_objgroup==DOOR)
				{
					dc.SelectObject(&PenCur);
					hitcur=true;
				}
				else if(hitcur)
				{
					dc.SelectObject(&PenDoor);
					hitcur=false;
				}
				dc.Rectangle(pt.x,pt.y,pt.x+16,pt.y+16);
				str.Format(_T("%d"),i);
				dc.DrawText(str,CRect(pt.x+2,pt.y,0,0),DT_LEFT|DT_TOP|DT_NOCLIP);
			}
			//Mctrl
			dc.SelectObject(&PenEp);
			if(!m_CheckHideMctrl.GetCheck())for(u8 i=0;i<m_Mctrl.GetMctrlCount();++i)
			{
				pt.x=m_Mctrl[i].x-m_HScroll.GetScrollPos();
				pt.y=m_Mctrl[i].y-9-m_VScroll.GetScrollPos();
				if(cur_obj==i && cur_objgroup==MCTRL)
				{
					dc.SelectObject(&PenCur);
					hitcur=true;
				}
				else if(hitcur)
				{
					dc.SelectObject(&PenEp);
					hitcur=false;
				}
				dc.MoveTo(pt);
				pt.y+=9;
				pt.x-=9;
				dc.LineTo(pt);
				pt.y+=9;
				pt.x+=9;
				dc.LineTo(pt);
				pt.y-=9;
				pt.x+=9;
				dc.LineTo(pt);
				pt.y-=9;
				pt.x-=9;
				dc.LineTo(pt);
				str.Format(_T("%d  %s"),i,EvcDesc[m_Mctrl[i].class_id].Name);
				dc.DrawText(str,CRect(pt.x-3,pt.y+1,0,0),DT_LEFT|DT_TOP|DT_NOCLIP);
			}
			if(cur_sel_obj!=0xFFFF)
			{
				switch(cur_sel_objgroup)
				{
				case FOE:
					pt.x=m_De.Foe(cur_sel_obj).x;
					pt.y=m_De.Foe(cur_sel_obj).y;
					break;
				case SUP:
					pt.x=m_De.Sup(cur_sel_obj).x;
					pt.y=m_De.Sup(cur_sel_obj).y;
					break;
				case DOOR:
					pt.x=m_Ma.Door(cur_sel_obj).x;
					pt.y=m_Ma.Door(cur_sel_obj).y;
					break;
				case MCTRL:
					pt.x=m_Mctrl[(u8)cur_sel_obj].x;
					pt.y=m_Mctrl[(u8)cur_sel_obj].y;
					break;
				}
				dc.SelectObject(&PenSel);
				dc.SetBkMode(OPAQUE);
				pt.x-=m_HScroll.GetScrollPos();
				pt.y-=m_VScroll.GetScrollPos();
				pt.x-=10;
				pt.y-=10;
				dc.Ellipse(pt.x,pt.y,pt.x+20,pt.y+20);
				pt.x-=2;
				pt.y-=2;
				dc.Ellipse(pt.x,pt.y,pt.x+24,pt.y+24);
			}


			dc.SelectObject(pOldPen);
			dc.SelectObject(pOldBrush);
			NullBrush.DeleteObject();
		}
		if(mode==MPT_BOSS)
		{
			static CPen PenGuide(PS_SOLID,2,RGB(192,128,0));
			NullBrush.CreateStockObject(WHITE_BRUSH);
			pOldBrush=dc.SelectObject(&NullBrush);
			dc.SetBkMode(TRANSPARENT);
			pOldPen=dc.SelectObject(&PenGuide);
			for(u16 i=0;i<m_Ma.GetGuideCount();++i)
			{
				pt.x=m_Ma.Guide(i).x-9-m_HScroll.GetScrollPos();
				pt.y=m_Ma.Guide(i).y-9-m_VScroll.GetScrollPos();
				dc.Ellipse(pt.x,pt.y,pt.x+18,pt.y+18);
				str.Format(_T("%d"),m_Ma.Guide(i).id);
				dc.DrawText(str,CRect(pt.x+3,pt.y+1,0,0),DT_LEFT|DT_TOP|DT_NOCLIP);
			}
			dc.SelectObject(pOldPen);
			dc.SelectObject(pOldBrush);
			NullBrush.DeleteObject();
		}
		

		if((mode==MPT_GRID || mode==MPT_BOSS) && cur_grid_x!=0xFF)
		{
			CPen RedPen(PS_DOT,1,RGB(255,0,0));
			HGDIOBJ hOldPen=SelectObject(lpDrawItemStruct->hDC,RedPen.GetSafeHandle());
			SelectObject(lpDrawItemStruct->hDC,GetStockObject(NULL_BRUSH));
			Rectangle(lpDrawItemStruct->hDC,
				(cur_grid_x<<4)-m_HScroll.GetScrollPos(),
				(cur_grid_y<<4)-m_VScroll.GetScrollPos(),
				(cur_grid_x<<4)+16-m_HScroll.GetScrollPos(),
				(cur_grid_y<<4)+16-m_VScroll.GetScrollPos());
			SelectObject(lpDrawItemStruct->hDC,hOldPen);
		}
		
		

	}
	else if(nIDCtl==IDC_STATIC_STOCK)
	{
		GetDlgItem(IDC_STATIC_STOCK)->GetClientRect(&rc);
		m_CanStock.Present(lpDrawItemStruct->hDC,0,0,rc.right,rc.bottom,
			m_HScrollStock.GetScrollPos(),m_VScrollStock.GetScrollPos());

		if(cur_stock_x!=0xFF)
		{
			CPen RedPen(PS_DOT,1,RGB(255,0,0));
			HGDIOBJ hOldPen=SelectObject(lpDrawItemStruct->hDC,RedPen.GetSafeHandle());
			SelectObject(lpDrawItemStruct->hDC,GetStockObject(NULL_BRUSH));
			Rectangle(lpDrawItemStruct->hDC,
				(cur_stock_x<<4)-m_HScrollStock.GetScrollPos(),
				(cur_stock_y<<4)-m_VScrollStock.GetScrollPos(),
				(cur_stock_x<<4)+16-m_HScrollStock.GetScrollPos(),
				(cur_stock_y<<4)+16-m_VScrollStock.GetScrollPos());
			SelectObject(lpDrawItemStruct->hDC,hOldPen);
		}
		if(cursel_stock_x!=0xFF)
		{
			if(m_CheckDet.GetCheck())
			{
				cursel_stock_x2=cursel_stock_x;
				cursel_stock_y2=cursel_stock_y;
			}
			CPen RedPen(PS_SOLID,2,RGB(255,0,0));
			HGDIOBJ hOldPen=SelectObject(lpDrawItemStruct->hDC,RedPen.GetSafeHandle());
			SelectObject(lpDrawItemStruct->hDC,GetStockObject(NULL_BRUSH));
			Rectangle(lpDrawItemStruct->hDC,
				(cursel_stock_x<<4)-m_HScrollStock.GetScrollPos(),
				(cursel_stock_y<<4)-m_VScrollStock.GetScrollPos(),
				(cursel_stock_x2<<4)+16-m_HScrollStock.GetScrollPos(),
				(cursel_stock_y2<<4)+16-m_VScrollStock.GetScrollPos());
			SelectObject(lpDrawItemStruct->hDC,hOldPen);
		}
	}
	else if(nIDCtl==IDC_STATIC_MAP_CUR_GRID)
	{
		m_CanCurGrid.Present(lpDrawItemStruct->hDC,0,0,32,48,0,0);
	}
	else if(nIDCtl==IDC_STATIC_MAP_CX)
	{
		static CBrush bbck(dc.GetBkColor());
		CString str;
		GetDlgItem(IDC_STATIC_MAP_CX)->GetClientRect(&rc);
		int begin,end;
		begin=m_HScroll.GetScrollPos()>>4;
		end=begin+((rc.right-rc.left)>>4)+1;
		for(int i=begin;i<=end;++i)
		{
			str.Format(_T("%d"),i);
			rc.left=(i<<4)-m_HScroll.GetScrollPos();
			rc.top=0;
			rc.bottom=16;
			rc.right=rc.left+16;
			dc.FillRect(&rc,&bbck);
			dc.DrawText(str,-1,&rc,DT_LEFT|DT_TOP|DT_NOCLIP);
		}
	}
	else if(nIDCtl==IDC_STATIC_MAP_CY)
	{
		static CBrush bbck(dc.GetBkColor());
		CString str;
		GetDlgItem(IDC_STATIC_MAP_CY)->GetClientRect(&rc);
		int begin,end;
		begin=m_VScroll.GetScrollPos()>>4;
		end=begin+((rc.bottom-rc.top)>>4)+1;
		for(int i=begin;i<=end;++i)
		{
			str.Format(_T("%d"),i);
			rc.left=0;
			rc.top=(i<<4)-m_VScroll.GetScrollPos();
			rc.bottom=rc.top+16;
			rc.right=16;
			dc.FillRect(&rc,&bbck);
			dc.DrawText(str,-1,&rc,DT_LEFT|DT_TOP|DT_NOCLIP);
		}
	}



	dc.Detach();
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
void CDlgMapEdit::PaintStock()
{
	m_CanStock.Clear(0);
	int CheckPlane0=m_CheckPlane0.GetCheck();
	if(m_CheckDet.GetCheck())
	{
		
		int x=0,y=0;
		if(CheckPlane0) for(int i=0;DetDesc0[i].code!=0xFFFFFFFF;++i)
		{
			if(DetDesc0[i].code==0xFFFFFFFE)
			{
				++y;x=0;
			}
			else
			{
				for(u8 bx=0;bx<16;++bx)for(u8 by=0;by<16;++by)
				{
					m_CanStock.SetPixel((x<<4)|bx,(y<<4)|by,
						Det0Bmp[i].Get(bx,by)?RGB(0,128,0):RGB(255,255,255));
				}
				++x;
			}
		}
		else for(int i=0;Det1List[i]!=0xFFFFFFFF;++i)
		{
			if(Det1List[i]==0xFFFFFFFE)
			{
				++y;x=0;
			}
			else
			{
				for(u8 bx=0;bx<16;++bx)for(u8 by=0;by<16;++by)
				{
					m_CanStock.SetPixel((x<<4)|bx,(y<<4)|by,
						Det1Bmp[i].data[bx][by]);
				}
				++x;
				//if(x==32)x=0,++y;
			}
		}
	}
	else
	{
		Nitro::CharData chardata;
		COLORREF clr;
		u8 plti;
		int dx,dy;
		u16 TexMappingCount=CheckPlane0?
			m_Ma.GetTexMappingCount(TEXM_F):m_Ma.GetTexMappingCount(TEXM_B);
		SqB &sqb=CheckPlane0?m_Fb:m_Bb;
		for(u16 i=0;i<TexMappingCount;++i)
		{
			for(u8 b=0;b<4;++b)
			{
				if(CheckPlane0)chardata=m_Ma.TexMapping(TEXM_F,i).mapping[b];
				else chardata=m_Ma.TexMapping(TEXM_B,i).mapping[b];
				for(u8 bx=0;bx<8;++bx)for(u8 by=0;by<8;++by)
				{
					if(CheckPlane0)
					{
						dx=((i&31)<<4)|bx|((b&1)<<3);
						dy=((i>>5)<<4)|by|((b&2)<<2);
					}
					else
					{
						dx=((i&63)<<4)|bx|((b&1)<<3);
						dy=((i>>6)<<4)|by|((b&2)<<2);
					}

					plti=sqb.Tile(chardata.tile,false,chardata.plt==0xF).Get(chardata.flipx?7-bx:bx,chardata.flipy?7-by:by);
					if(plti)
						clr=Nitro::Color15to24(sqb.Pal[plti|(sqb.PalLine(chardata.tile)<<4)]);
					else clr=RGB(255,255,255);
					m_CanStock.SetPixel(dx,dy,clr);
				}
				
			}
		}
	}
}
inline COLORREF ColorToGrey(COLORREF color)
{
	BYTE gr=(GetRValue(color)+GetGValue(color)+GetBValue(color))/3;
	gr=(gr+765)>>2;
	return RGB(gr,gr,gr);
}
inline COLORREF CDlgMapEdit::ColorToLi(COLORREF color,u8 bosszone)
{
	static bool bosszonecolorinit=false;
	static struct{float r,g,b;} bosszonecolor[100];
	if(!bosszonecolorinit)
	{
		int randoldseed=rand();
		srand(123);
		for(int i=0;i<100;++i)
		{
			
			bosszonecolor[i].r=(float)rand()/RAND_MAX*0.7f+0.2f;
			bosszonecolor[i].g=(float)rand()/RAND_MAX*0.7f+0.2f;
			bosszonecolor[i].b=(float)rand()/RAND_MAX*0.7f+0.2f;
			
		}
		srand(randoldseed);
		bosszonecolorinit=true;
	}

	if(mode==MPT_GRID)return color;
	
	else if(mode==MPT_BOSS)
	{
		BYTE gr=(GetRValue(color)+GetGValue(color)+GetBValue(color))/3;
		return RGB(
			(BYTE)(bosszonecolor[bosszone].r*gr),
			(BYTE)(bosszonecolor[bosszone].g*gr),
			(BYTE)(bosszonecolor[bosszone].b*gr)
			);
	}
	return RGB(
		(GetRValue(color)+765)>>2,
		(GetGValue(color)+765)>>2,
		(GetBValue(color)+765)>>2
		);
}
void CDlgMapEdit::PaintMap(u8 onlyx,u8 onlyy)
{

	Nitro::CharData chardata[3];
	COLORREF clr[3];
	u8 plti[3];
	int dx,dy;

	int CheckPlane2=m_CheckPlane2.GetCheck();
	int CheckPlane0=m_CheckPlane0.GetCheck();
	int CheckDet=m_CheckDet.GetCheck();
	BMP1b16x16* detbmp;
	BMP3216x16* det1bmp,*det2bmp;
	COLORREF detc;
	u8 x0,x1,y0,y1;
	if(onlyx==0xFF)x0=0,x1=m_Ma.GetW();else x0=onlyx,x1=onlyx+1;
	if(onlyy==0xFF)y0=0,y1=m_Ma.GetH();else y0=onlyy,y1=onlyy+1;
	for(u8 y=y0;y<y1;++y)for(u8 x=x0;x<x1;++x)
	{
		GetDet0Desc(m_Ma.Cell(x,y).det[0],&detbmp);
		det1bmp=GetDet1Bmp(m_Ma.Cell(x,y).det[1]);
		det2bmp=GetDet1Bmp(m_Ma.Cell(x,y).det[2]);
		for(u8 b=0;b<4;++b)
		{
			chardata[1]=m_Ma.TexMapping(TEXM_B,m_Ma.Cell(x,y).gra[1],true).mapping[b];
			chardata[2]=m_Ma.TexMapping(TEXM_B,m_Ma.Cell(x,y).gra[2],true).mapping[b];
			chardata[0]=m_Ma.TexMapping(TEXM_F,m_Ma.Cell(x,y).gra[0],true).mapping[b];

			for(u8 bx=0;bx<8;++bx)for(u8 by=0;by<8;++by)
			{
				dx=bx|((b&1)<<3)|(x<<4);
				dy=by|((b&2)<<2)|(y<<4);
				plti[0]=m_Fb.Tile(chardata[0].tile,false,chardata[0].plt==0xF).Get(chardata[0].flipx?7-bx:bx,chardata[0].flipy?7-by:by);
				plti[1]=m_Bb.Tile(chardata[1].tile,true,chardata[1].plt==0xF).Get(chardata[1].flipx?7-bx:bx,chardata[1].flipy?7-by:by);
				plti[2]=m_Bb.Tile(chardata[2].tile,true,chardata[2].plt==0xF).Get(chardata[2].flipx?7-bx:bx,chardata[2].flipy?7-by:by);
				clr[0]=Nitro::Color15to24(m_Fb.Pal[plti[0]|(m_Fb.PalLine(chardata[0].tile)<<4)]);
				if(plti[1])
					clr[1]=Nitro::Color15to24(m_Bb.Pal_Ani(m_Bb.PalLine(chardata[1].tile,true),plti[1]));
				else clr[1]=RGB(255,255,255);
				clr[2]=Nitro::Color15to24(m_Bb.Pal_Ani(m_Bb.PalLine(chardata[2].tile,true),plti[2]));
				if(CheckPlane0)
				{
					if(CheckPlane2)
					{
						m_CanMap.SetPixel(dx,dy,ColorToGrey(clr[1]));
						if(plti[2])m_CanMap.SetPixel(dx,dy,ColorToGrey(clr[2]));
						detc=det2bmp->data[bx|((b&1)<<3)][by|((b&2)<<2)];
					}
					else
					{
						m_CanMap.SetPixel(dx,dy,ColorToGrey(clr[1]));
						detc=det1bmp->data[bx|((b&1)<<3)][by|((b&2)<<2)];
					}
					if(CheckDet)
					{
						if(plti[0])m_CanMap.SetPixel(dx,dy,ColorToGrey(clr[0]));
						if(detc!=RGB(255,255,255))m_CanMap.SetPixel(dx,dy,ColorToGrey(detc));
						if(detbmp->Get(bx|((b&1)<<3),by|((b&2)<<2)))
							m_CanMap.SetPixel(dx,dy,ColorToLi(RGB(0,128,0),m_Ma.Cell(x,y).guide_id));
					}else if(plti[0])m_CanMap.SetPixel(dx,dy,ColorToLi(clr[0],m_Ma.Cell(x,y).guide_id));
				}
				else
				{
					if(CheckPlane2)
					{
						m_CanMap.SetPixel(dx,dy,ColorToGrey(clr[1]));
						if(CheckDet)
						{
							if(plti[2])m_CanMap.SetPixel(dx,dy,ColorToGrey(clr[2]));
							detc=det2bmp->data[bx|((b&1)<<3)][by|((b&2)<<2)];
							if(detc!=RGB(255,255,255))m_CanMap.SetPixel(dx,dy,ColorToLi(detc,m_Ma.Cell(x,y).guide_id));
						}
						else
							if(plti[2])m_CanMap.SetPixel(dx,dy,ColorToLi(clr[2],m_Ma.Cell(x,y).guide_id));
					}
					else
					{
						if(CheckDet)
						{
							COLORREF detc;
							m_CanMap.SetPixel(dx,dy,ColorToGrey(clr[1]));
							detc=det1bmp->data[bx|((b&1)<<3)][by|((b&2)<<2)];
							if(detc!=RGB(255,255,255))m_CanMap.SetPixel(dx,dy,ColorToLi(detc,m_Ma.Cell(x,y).guide_id));

						}
						else m_CanMap.SetPixel(dx,dy,ColorToLi(clr[1],m_Ma.Cell(x,y).guide_id));
					}
				}
			}
		}
	}
	
}
BOOL CDlgMapEdit::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Mctrl.FromMa(m_Ma);

	m_CanMap.Create(m_Ma.GetW()*16,m_Ma.GetH()*16);
	m_CanStock.Create(1024,max(max(
		m_Ma.GetTexMappingCount(TEXM_B)>>6,
		m_Ma.GetTexMappingCount(TEXM_F)>>5),12)<<4);
	m_CanCurGrid.Create(32,48);

	cur_grid_x=cur_grid_y=0xFF;
	cur_stock_x=cur_stock_y=0xFF;
	cursel_stock_x=cursel_stock_y=0xFF;
	cursel_stock=0xFFFFFFFF;
	grid_drawing=false;
	cur_obj=cur_sel_obj=0xFFFF;
	IsListObjChangeFromSoftWare=false;
	obj_moving=false;
	
	m_CheckPlane0.SetCheck(GetPrivateProfileInt(_T("MapEditor"),_T("Plane0"),0,ProfilePath)?TRUE:FALSE);
	m_CheckPlane2.SetCheck(GetPrivateProfileInt(_T("MapEditor"),_T("Plane2"),0,ProfilePath)?TRUE:FALSE);
	m_CheckDet.SetCheck(GetPrivateProfileInt(_T("MapEditor"),_T("Det"),0,ProfilePath)?TRUE:FALSE);
	m_CheckMapAni.SetCheck(GetPrivateProfileInt(_T("MapEditor"),_T("MapAni"),0,ProfilePath)?TRUE:FALSE);

	CString str;
	for(int i=0;i<256;++i)
	{
		str.Format(FORMAT_BGM,i,GetBgmName((u8)i));
		m_ComboBgm.AddString(str);
		if(m_Ma.MapAttribute.Bgm==(u8)i)m_ComboBgm.SelectString(-1,str);
	}
	for(u8 i=0;i<10;++i)
	{
		str.Format(FORMAT_BOSS,i);
		m_ComboBoss.AddString(str);
		if(m_Ma.MapAttribute.Boss==i)m_ComboBoss.SelectString(-1,str);
	}

	SetScroll();
	SetStockScroll();

	CheckRadioButton(0,30000,IDC_RADIO_MAP_PT_GRID);
	mode=MPT_GRID;

	m_ListObj.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_ListObj.InsertColumn(0,_T("ID"),0,32);
	m_ListObj.InsertColumn(1,_T("类别"),0,64);
	m_ListObj.InsertColumn(2,_T("坐标"),0,128);
	m_ListObj.InsertColumn(3,_T("参数/脚本"),0,256);
	m_ListObj.EnableGroupView(TRUE);
	LVGROUP lvg={0};
	lvg.cbSize=sizeof(LVGROUP);
	lvg.mask=LVGF_ALIGN|LVGF_STATE|LVGF_HEADER|LVGF_GROUPID;
	lvg.state=LVGS_NORMAL; 
	lvg.uAlign=LVGA_HEADER_LEFT;
	lvg.iGroupId=0;
	lvg.pszHeader=_T("敌人");
	m_ListObj.InsertGroup(-1,&lvg);
	lvg.iGroupId=1;
	lvg.pszHeader=_T("补给品");
	m_ListObj.InsertGroup(-1,&lvg);
	lvg.iGroupId=2;
	lvg.pszHeader=_T("传送装置");
	m_ListObj.InsertGroup(-1,&lvg);
	lvg.iGroupId=3;
	lvg.pszHeader=_T("地图组件");
	m_ListObj.InsertGroup(-1,&lvg);
	lvg.iGroupId=4;
	lvg.pszHeader=_T("BOSS引导器");
	m_ListObj.InsertGroup(-1,&lvg);

	UpdateObjList();

	PaintMap();
	PaintStock();

	OnStockLButtonDown(0,0);


	memcpy(&m_Bb.TileTimeDelta,&m_Ma.S12HScript.TileTimeDelta,4);
	OnBnClickedCheckMapAni();
	
	return TRUE;
}
#define OUTSIDE_MARK _T("[出界]")
void CDlgMapEdit::UpdateObjList()
{
	m_ListObj.DeleteAllItems();
	CString str,str2;

	LVITEM lvi={0};
	lvi.mask=LVIF_GROUPID|LVIF_TEXT;

	int ibase=0;

	bool in;

	//Foe
	lvi.iGroupId=0;
	for(u16 i=0;i<m_De.GetFoeCount();++i)
	{
		lvi.iItem=i;
		str.Format(_T("%d"),i);
		lvi.pszText=str.GetBuffer();
		m_ListObj.InsertItem(&lvi);
		str.Format(_T("%s"),FoeDesc[m_De.Foe(i).class_id].name);
		m_ListObj.SetItem(i,1,LVIF_TEXT,str,0,0,0,0);
		in=m_De.Foe(i).x<(m_Ma.GetW()<<4) && m_De.Foe(i).y<(m_Ma.GetH()<<4);
		str.Format(_T("%s(%d.%X,  %d.%X)"),in?_T(""):OUTSIDE_MARK,
			m_De.Foe(i).x>>4,m_De.Foe(i).x&0xF,
			m_De.Foe(i).y>>4,m_De.Foe(i).y&0xF);
		m_ListObj.SetItem(i,2,LVIF_TEXT,str,0,0,0,0);
		str.Format(_T("%02X %02X %02X %02X %02X %02X %02X %02X"),
			m_De.Foe(i).pa,m_De.Foe(i).pb,
			m_De.Foe(i).pc,m_De.Foe(i).pd,
			m_De.Foe(i).pe,m_De.Foe(i).pf,
			m_De.Foe(i).pg,m_De.Foe(i).ph);
		m_ListObj.SetItem(i,3,LVIF_TEXT,str.GetBuffer(),0,0,0,0);
	}
	ibase+=m_De.GetFoeCount();

	//Sup
	lvi.iGroupId=1;
	for(u16 i=0;i<m_De.GetSupCount();++i)
	{
		lvi.iItem=i+ibase;
		str.Format(_T("%d"),i);
		lvi.pszText=str.GetBuffer();
		m_ListObj.InsertItem(&lvi);
		str.Format(_T("%s"),SupDesc[m_De.Sup(i).class_id].name);
		m_ListObj.SetItem(i+ibase,1,LVIF_TEXT,str,0,0,0,0);
		in=m_De.Sup(i).x<(m_Ma.GetW()<<4) && m_De.Sup(i).y<(m_Ma.GetH()<<4);
		str.Format(_T("%s(%d.%X,  %d.%X)"),in?_T(""):OUTSIDE_MARK,
			m_De.Sup(i).x>>4,m_De.Sup(i).x&0xF,
			m_De.Sup(i).y>>4,m_De.Sup(i).y&0xF);
		m_ListObj.SetItem(i+ibase,2,LVIF_TEXT,str,0,0,0,0);
		str.Format(_T("%02X %02X %02X %02X %02X %02X %02X %02X"),
			m_De.Sup(i).pa,m_De.Sup(i).pb,
			m_De.Sup(i).pc,m_De.Sup(i).pd,
			m_De.Sup(i).pe,m_De.Sup(i).pf,
			m_De.Sup(i).pg,m_De.Sup(i).ph);
		m_ListObj.SetItem(i+ibase,3,LVIF_TEXT,str.GetBuffer(),0,0,0,0);
	}
	ibase+=m_De.GetSupCount();

	//Door
	lvi.iGroupId=2;
	for(u16 i=0;i<m_Ma.GetDoorCount();++i)
	{
		lvi.iItem=i+ibase;
		str.Format(_T("%d"),i);
		lvi.pszText=str.GetBuffer();
		m_ListObj.InsertItem(&lvi);
		str.Format(_T("%d"),m_Ma.Door(i).class_id);
		m_ListObj.SetItem(i+ibase,1,LVIF_TEXT,str,0,0,0,0);
		in=m_Ma.Door(i).x<(m_Ma.GetW()<<4) && m_Ma.Door(i).y<(m_Ma.GetH()<<4);
		str.Format(_T("%s(%d,  %d)"),in?_T(""):OUTSIDE_MARK,
			m_Ma.Door(i).x>>4,m_Ma.Door(i).y>>4);
		m_ListObj.SetItem(i+ibase,2,LVIF_TEXT,str,0,0,0,0);
		if(m_Ma.Door(i).dst_step!=0xFF)
			str.Format(_T("To Step%02d,Door%d"),m_Ma.Door(i).dst_step,m_Ma.Door(i).dst_door);
		else if(m_Ma.Door(i).dst_door)
			str.Format(_T("%d"),m_Ma.Door(i).dst_door);
		else
			str=_T("void");
		m_ListObj.SetItem(i+ibase,3,LVIF_TEXT,str.GetBuffer(),0,0,0,0);
	}
	ibase+=m_Ma.GetDoorCount();

	//Mctrl
	lvi.iGroupId=3;
	for(u8 i=0;i<m_Mctrl.GetMctrlCount();++i)
	{
		lvi.iItem=i+ibase;
		str.Format(_T("%d"),i);
		lvi.pszText=str.GetBuffer();
		m_ListObj.InsertItem(&lvi);
		str.Format(_T("%s"),EvcDesc[m_Mctrl[i].class_id].Name);
		m_ListObj.SetItem(i+ibase,1,LVIF_TEXT,str,0,0,0,0);
		in=m_Mctrl[i].x<(m_Ma.GetW()<<4) && m_Mctrl[i].y<(m_Ma.GetH()<<4);
		str.Format(_T("%s(%d.%X,  %d.%X)"),in?_T(""):OUTSIDE_MARK,
			m_Mctrl[i].x>>4,m_Mctrl[i].x&0xF,
			m_Mctrl[i].y>>4,m_Mctrl[i].y&0xF);
		m_ListObj.SetItem(i+ibase,2,LVIF_TEXT,str,0,0,0,0);
		str.Format(_T("%02X %02X|"),m_Mctrl[i].param&0xFF,m_Mctrl[i].param>>8);
		for(u16 j=0;j<EvcDesc[m_Mctrl[i].class_id].DataLen;++j)
		{
			str2.Format(_T("%02X "),m_Mctrl[i].pExtData[j]);
			str+=str2;
		}
		m_ListObj.SetItem(i+ibase,3,LVIF_TEXT,str.GetBuffer(),0,0,0,0);
	}

}
void CDlgMapEdit::UpdateGuideList()
{
	m_ListObj.DeleteAllItems();
	CString str,str2;

	LVITEM lvi={0};
	lvi.mask=LVIF_GROUPID|LVIF_TEXT;

	bool in;

	//Guide
	lvi.iGroupId=4;
	for(u16 i=0;i<m_Ma.GetGuideCount();++i)
	{
		lvi.iItem=i;
		str.Format(_T("%d"),m_Ma.Guide(i).id);
		lvi.pszText=str.GetBuffer();
		m_ListObj.InsertItem(&lvi);
		str=_T("-");
		m_ListObj.SetItem(i,1,LVIF_TEXT,str,0,0,0,0);
		in=m_Ma.Guide(i).x<(m_Ma.GetW()<<4) && m_Ma.Guide(i).y<(m_Ma.GetH()<<4);
		str.Format(_T("%s(%d.%X,  %d.%X)"),in?_T(""):OUTSIDE_MARK,
			m_Ma.Guide(i).x>>4,m_Ma.Guide(i).y&0xF,
			m_Ma.Guide(i).y>>4,m_Ma.Guide(i).y&0xF);
		m_ListObj.SetItem(i,2,LVIF_TEXT,str,0,0,0,0);
		str.Format(_T("%04X"),m_Ma.Guide(i).U);
		m_ListObj.SetItem(i,3,LVIF_TEXT,str.GetBuffer(),0,0,0,0);
	}


}
void CDlgMapEdit::SetScroll()
{
	RECT rc;
	int hsrg,vsrg;
	GetDlgItem(IDC_STATIC_MAP)->GetClientRect(&rc);
	hsrg=m_Ma.GetW()*16-rc.right;
	if(hsrg<1)hsrg=1;
	vsrg=m_Ma.GetH()*16-rc.bottom;
	if(vsrg<1)vsrg=1;
	SCROLLINFO scrinfo={0};
	scrinfo.cbSize=sizeof(SCROLLINFO);
	scrinfo.fMask=SIF_PAGE|SIF_RANGE|SIF_POS;
	scrinfo.nPage=rc.right;
	scrinfo.nMin=0;scrinfo.nMax=hsrg-1+scrinfo.nPage-1;
	scrinfo.nPos=0;
	m_HScroll.SetScrollInfo(&scrinfo);
	scrinfo.nPage=rc.bottom;
	scrinfo.nMin=0;scrinfo.nMax=vsrg-1+scrinfo.nPage-1;
	scrinfo.nPos=0;
	m_VScroll.SetScrollInfo(&scrinfo);
}
void CDlgMapEdit::SetStockScroll()
{
	u32 W,H;
	if(m_CheckPlane0.GetCheck())
	{
		W=512;
		H=(m_Ma.GetTexMappingCount(TEXM_F)>>5)<<4;
	}
	else
	{
		if(m_CheckDet.GetCheck())
		{
			W=512;
			H=12*16;
			
		}
		else
		{
			W=1024;
			H=(m_Ma.GetTexMappingCount(TEXM_B)>>6)<<4;
		}
	}
	RECT rc;
	int hsrg,vsrg;
	GetDlgItem(IDC_STATIC_STOCK)->GetClientRect(&rc);
	hsrg=W-rc.right;
	if(hsrg<1)hsrg=1;
	vsrg=H-rc.bottom;
	if(vsrg<1)vsrg=1;
	SCROLLINFO scrinfo={0};
	scrinfo.cbSize=sizeof(SCROLLINFO);
	scrinfo.fMask=SIF_PAGE|SIF_RANGE|SIF_POS;
	scrinfo.nPage=rc.right;
	scrinfo.nMin=0;scrinfo.nMax=hsrg-1+scrinfo.nPage-1;
	scrinfo.nPos=0;
	m_HScrollStock.SetScrollInfo(&scrinfo);
	scrinfo.nPage=rc.bottom;
	scrinfo.nMin=0;scrinfo.nMax=vsrg-1+scrinfo.nPage-1;
	scrinfo.nPos=0;
	m_VScrollStock.SetScrollInfo(&scrinfo);
}
void CDlgMapEdit::OnBnClickedCheckMapPlane2()
{
	WritePrivateProfileString(_T("MapEditor"),_T("Plane2"),m_CheckPlane2.GetCheck()?
		_T("1"):_T("0"),ProfilePath);
	PaintMap();
	GetDlgItem(IDC_STATIC_MAP)->RedrawWindow();
}

void CDlgMapEdit::OnBnClickedCheckMapPlane0()
{
	WritePrivateProfileString(_T("MapEditor"),_T("Plane0"),m_CheckPlane0.GetCheck()?
		_T("1"):_T("0"),ProfilePath);
	SetStockScroll();
	OnStockLButtonDown(0,0);
	PaintMap();
	PaintStock();
	GetDlgItem(IDC_STATIC_MAP)->RedrawWindow();
	GetDlgItem(IDC_STATIC_STOCK)->RedrawWindow();
}

void CDlgMapEdit::OnBnClickedCheckMapDet()
{
	WritePrivateProfileString(_T("MapEditor"),_T("Det"),m_CheckDet.GetCheck()?
		_T("1"):_T("0"),ProfilePath);
	SetStockScroll();
	OnStockLButtonDown(0,0);
	PaintMap();
	PaintStock();
	GetDlgItem(IDC_STATIC_MAP)->RedrawWindow();
	GetDlgItem(IDC_STATIC_STOCK)->RedrawWindow();
}

void CDlgMapEdit::OnMapLButtonDown(u8 x,u8 y)
{
	if(mode==MPT_BOSS)return;
	grid_drawing=true;
	OnMapMouseMove(x,y);
}
void CDlgMapEdit::OnMapLButtonUp(u8 x,u8 y)
{
	if(mode==MPT_BOSS)return;
	grid_drawing=false;

}
void CDlgMapEdit::OnMapLButtonUp_Obj()
{
	obj_moving=false;
}
void CDlgMapEdit::OnMapDraw(u8 x,u8 y)
{
	if(mode==MPT_BOSS)return;
	if(m_CheckDet.GetCheck())
	{
		if(m_CheckPlane0.GetCheck())m_Ma.Cell(x,y).det[0]=cursel_stock;
		else
			if(m_CheckPlane2.GetCheck())m_Ma.Cell(x,y).det[2]=cursel_stock;
			else m_Ma.Cell(x,y).det[1]=cursel_stock;
		PaintMap(x,y);
	}
	else
		if(m_CheckPlane0.GetCheck())
		{
			//m_Ma.Cell(x,y).gra[0]=(u16)cursel_stock;
			for(u8 dx=cursel_stock_x;dx<=cursel_stock_x2;++dx)
				for(u8 dy=cursel_stock_y;dy<=cursel_stock_y2;++dy)
				{
					if(x+dx-cursel_stock_x < m_Ma.GetW() && 
						y+dy-cursel_stock_y < m_Ma.GetH())
					{
						m_Ma.Cell(x+dx-cursel_stock_x,y+dy-cursel_stock_y)
							.gra[0]=dx+dy*32;
						PaintMap(x+dx-cursel_stock_x,y+dy-cursel_stock_y);
					}
				}
		}
		else
		{
			int plane=m_CheckPlane2.GetCheck()?2:1;
			//m_Ma.Cell(x,y).gra[plane]=(u16)cursel_stock;
			for(u8 dx=cursel_stock_x;dx<=cursel_stock_x2;++dx)
				for(u8 dy=cursel_stock_y;dy<=cursel_stock_y2;++dy)
				{
					if(x+dx-cursel_stock_x < m_Ma.GetW() && 
						y+dy-cursel_stock_y < m_Ma.GetH())
					{
						m_Ma.Cell(x+dx-cursel_stock_x,y+dy-cursel_stock_y)
							.gra[plane]=dx+dy*64;
						PaintMap(x+dx-cursel_stock_x,y+dy-cursel_stock_y);
					}
				}
		}
	
}
void CDlgMapEdit::OnMapMouseMove(u8 x,u8 y)
{
	if(x>=m_Ma.GetW() || y>=m_Ma.GetH())
	{
		grid_drawing=false;
		m_StaticCurCoord.SetWindowText(_T(""));
		m_EditCurGrid0.SetWindowText(_T(""));
		m_EditCurGrid1.SetWindowText(_T(""));
		m_EditCurGrid2.SetWindowText(_T(""));
		m_EditCurGridBoss.SetWindowText(_T(""));
		m_CanCurGrid.Clear(RGB(255,255,255));
		GetDlgItem(IDC_STATIC_MAP_CUR_GRID)->RedrawWindow();
		cur_grid_x=0xFF;
		cur_grid_y=0xFF;
		GetDlgItem(IDC_STATIC_MAP)->RedrawWindow();
		return;
	}
	if(grid_drawing)
	{
		OnMapDraw(x,y);
	}

	CString str;
	str.Format(_T("(%d,%d)"),x,y);
	m_StaticCurCoord.SetWindowText(str);

	str.Format(_T("%04X|%08X"),m_Ma.Cell(x,y).gra[0],m_Ma.Cell(x,y).det[0]);
	m_EditCurGrid0.SetWindowText(str);
	str.Format(_T("%04X|%08X"),m_Ma.Cell(x,y).gra[1],m_Ma.Cell(x,y).det[1]);
	m_EditCurGrid1.SetWindowText(str);
	str.Format(_T("%04X|%08X"),m_Ma.Cell(x,y).gra[2],m_Ma.Cell(x,y).det[2]);
	m_EditCurGrid2.SetWindowText(str);
	str.Format(_T("%d"),m_Ma.Cell(x,y).guide_id);
	m_EditCurGridBoss.SetWindowText(str);

	//Paint the grid data
	Nitro::CharData chardata[3];
	COLORREF clr[3];
	u8 plti[3];
	int dx,dy;
	BMP1b16x16* detbmp;
	BMP3216x16* det1bmp,*det2bmp;
	GetDet0Desc(m_Ma.Cell(x,y).det[0],&detbmp);
	det1bmp=GetDet1Bmp(m_Ma.Cell(x,y).det[1]);
	det2bmp=GetDet1Bmp(m_Ma.Cell(x,y).det[2]);
	for(u8 b=0;b<4;++b)
	{
		chardata[1]=m_Ma.TexMapping(TEXM_B,m_Ma.Cell(x,y).gra[1]).mapping[b];
		chardata[2]=m_Ma.TexMapping(TEXM_B,m_Ma.Cell(x,y).gra[2]).mapping[b];
		chardata[0]=m_Ma.TexMapping(TEXM_F,m_Ma.Cell(x,y).gra[0]).mapping[b];
		for(u8 bx=0;bx<8;++bx)for(u8 by=0;by<8;++by)
		{
			dx=bx|((b&1)<<3);
			dy=by|((b&2)<<2);
			plti[0]=m_Fb.Tile(chardata[0].tile).Get(chardata[0].flipx?7-bx:bx,chardata[0].flipy?7-by:by);
			plti[1]=m_Bb.Tile(chardata[1].tile).Get(chardata[1].flipx?7-bx:bx,chardata[1].flipy?7-by:by);
			plti[2]=m_Bb.Tile(chardata[2].tile).Get(chardata[2].flipx?7-bx:bx,chardata[2].flipy?7-by:by);
			if(plti[0])
				clr[0]=Nitro::Color15to24(m_Fb.Pal[plti[0]|(m_Fb.PalLine(chardata[0].tile)<<4)]);
			else clr[0]=RGB(255,255,255);
			if(plti[1])
				clr[1]=Nitro::Color15to24(m_Bb.Pal[plti[1]|(m_Bb.PalLine(chardata[1].tile)<<4)]);
			else clr[1]=RGB(255,255,255);
			if(plti[2]) 
				clr[2]=Nitro::Color15to24(m_Bb.Pal[plti[2]|(m_Bb.PalLine(chardata[2].tile)<<4)]);
			else clr[2]=RGB(255,255,255);
			
			m_CanCurGrid.SetPixel(dx,dy,clr[0]);
			m_CanCurGrid.SetPixel(dx,dy+16,clr[1]);
			m_CanCurGrid.SetPixel(dx,dy+32,clr[2]);
			m_CanCurGrid.SetPixel(dx+16,dy,detbmp->Get(dx,dy)?RGB(0,128,0):RGB(255,255,255));
			m_CanCurGrid.SetPixel(dx+16,dy+16,det1bmp->data[dx][dy]);
			m_CanCurGrid.SetPixel(dx+16,dy+32,det2bmp->data[dx][dy]);
		}
	}
	GetDlgItem(IDC_STATIC_MAP_CUR_GRID)->RedrawWindow();

	cur_grid_x=x;
	cur_grid_y=y;
	GetDlgItem(IDC_STATIC_MAP)->RedrawWindow();
}
void CDlgMapEdit::OnStockMouseMove(u8 x,u8 y)
{
	if(mode!=MPT_GRID)return;
	CString str;
	if(m_CheckDet.GetCheck())
	{
		if(m_CheckPlane0.GetCheck())
		{
			const DetDesc* ddesc=GetDet0Desc(x,y);
			if(ddesc)
			{
				cur_stock_x=x;
				cur_stock_y=y;
				str=ddesc->name;
			}
			else
			{
				cur_stock_x=cur_stock_y=0xFF;
				str=_T("");
			}
		}
		else
		{
			u32 det1code=GetDet1CodeByStockCoord(x,y);
			if(det1code!=0xFFFFFFFF)
			{
				cur_stock_x=x;
				cur_stock_y=y;
				GetDet1Desc(det1code,str);
			}
			else
			{
				cur_stock_x=cur_stock_y=0xFF;
				str=_T("");
			}
		}
	}
	else
	{
		if(m_CheckPlane0.GetCheck())
		{
			if(x>=32 || y>m_Ma.GetTexMappingCount(TEXM_F)>>5)
			{
				cur_stock_x=cur_stock_y=0xFF;
				str=_T("");
			}
			else
			{
				cur_stock_x=x;
				cur_stock_y=y;
				str.Format(_T("%02X"),x+y*32);
			}
		}
		else
		{
			if(x>=64 || y>m_Ma.GetTexMappingCount(TEXM_B)>>6)
			{
				cur_stock_x=cur_stock_y=0xFF;
				str=_T("");
			}
			else
			{
				cur_stock_x=x;
				cur_stock_y=y;
				str.Format(_T("%02X"),x+y*64);
			}
		}
	}
	m_StaticCurCoord.SetWindowText(str);
	GetDlgItem(IDC_STATIC_STOCK)->RedrawWindow();
}
void CDlgMapEdit::OnStockRButtonDown(u8 x,u8 y)
{
	if(mode!=MPT_GRID)return;
	if(m_CheckDet.GetCheck())return;
	if(m_CheckPlane0.GetCheck())
	{
		if(x>=32|| y>m_Ma.GetTexMappingCount(TEXM_F)>>5) return;
		else if(x>=cursel_stock_x && y>=cursel_stock_y)
		{
			cursel_stock_x2=x;
			cursel_stock_y2=y;
			cursel_stock2=x+y*32;
		}
	}
	else
	{
		if(x>=64|| y>m_Ma.GetTexMappingCount(TEXM_B)>>6) return;
		else if(x>=cursel_stock_x && y>=cursel_stock_y)
		{
			cursel_stock_x2=x;
			cursel_stock_y2=y;
			cursel_stock2=x+y*64;
		}
	}
	GetDlgItem(IDC_STATIC_STOCK)->RedrawWindow();
}
void CDlgMapEdit::OnStockLButtonDown(u8 x,u8 y)
{
	if(mode!=MPT_GRID)return;
	if(m_CheckDet.GetCheck())
	{
		if(m_CheckPlane0.GetCheck())
		{
			const DetDesc* ddesc=GetDet0Desc(x,y);
			if(ddesc)
			{
				cursel_stock_x=x;
				cursel_stock_y=y;
				cursel_stock=ddesc->code;
			}
			else return;
		}
		else
		{
			u32 det1code=GetDet1CodeByStockCoord(x,y);
			if(det1code!=0xFFFFFFFF)
			{
				cursel_stock_x=x;
				cursel_stock_y=y;
				cursel_stock=det1code;
			}
			else return;
		}
	}
	else
	{
		if(m_CheckPlane0.GetCheck())
		{
			if(x>=32|| y>m_Ma.GetTexMappingCount(TEXM_F)>>5) return;
			else
			{
				cursel_stock_x2=cursel_stock_x=x;
				cursel_stock_y2=cursel_stock_y=y;
				cursel_stock2=cursel_stock=x+y*32;
			}
		}
		else
		{
			if(x>=64|| y>m_Ma.GetTexMappingCount(TEXM_B)>>6) return;
			else
			{
				cursel_stock_x2=cursel_stock_x=x;
				cursel_stock_y2=cursel_stock_y=y;
				cursel_stock2=cursel_stock=x+y*64;
			}
		}
	}
	GetDlgItem(IDC_STATIC_STOCK)->RedrawWindow();
}
void CDlgMapEdit::OnMapMouseMove_Obj(u16 x,u16 y)
{
	if(x==0xFFFF)
	{
		cur_obj=0xFFFF;
		obj_moving=false;
	}
	else if(obj_moving)
	{
		int fx=x-obj_moving_dx;
		int fy=y-obj_moving_dy;
		if(abs(obj_moving_ox-fx)+abs(obj_moving_oy-fy)>3)
		{
			u16 ix=min(max(fx,0),m_Ma.GetW()*16-1);
			u16 iy=min(max(fy,0),m_Ma.GetH()*16-1);
			if(m_CheckObjMovingAlign.GetCheck())
			{
				ix&=0xFFF8;
				iy&=0xFFF8;
			}
			switch(cur_sel_objgroup)
			{
			case FOE:
				m_De.Foe(cur_sel_obj).x=ix;
				m_De.Foe(cur_sel_obj).y=iy;
				break;
			case SUP:
				m_De.Sup(cur_sel_obj).x=ix;
				m_De.Sup(cur_sel_obj).y=iy;
				break;
			case DOOR:
				ix=(ix&0xFFF0)|8;
				iy=(iy&0xFFF0)|8;
				m_Ma.Door(cur_sel_obj).x=ix;
				m_Ma.Door(cur_sel_obj).y=iy;
				break;
			case MCTRL:
				m_Mctrl[(u8)cur_sel_obj].x=ix;
				m_Mctrl[(u8)cur_sel_obj].y=iy;
				break;
			}
			CString str;
			if(cur_sel_objgroup==DOOR)
			{
				str.Format(_T("(%d,  %d)"),ix>>4,iy>>4);
			}
			else
			{
				str.Format(_T("(%d.%X,  %d.%X)"),
					ix>>4,ix&0xF,
					iy>>4,iy&0xF);
			}
			m_ListObj.SetItemText(Obj_GameIdtoListId(cur_sel_obj,cur_sel_objgroup),2,str);
			GetDlgItem(IDC_STATIC_MAP)->RedrawWindow();
		}
	}
	else
	{
		PICKOBJ_GROUP n_cur_objgroup;
		u16 n_cur_obj;
		n_cur_obj=PickObj(x,y,&n_cur_objgroup);
		if(n_cur_obj!=cur_obj || n_cur_objgroup!=cur_objgroup)
		{
			cur_obj=n_cur_obj;
			cur_objgroup=n_cur_objgroup;
			GetDlgItem(IDC_STATIC_MAP)->RedrawWindow();
		}
	}
}
int CDlgMapEdit::Obj_GameIdtoListId(u16 id,PICKOBJ_GROUP group)
{
	int nItem=id;
	switch(group)
	{
	case MCTRL:nItem+=m_Ma.GetDoorCount();
	case DOOR:nItem+=m_De.GetSupCount();
	case SUP:nItem+=m_De.GetFoeCount();
	case FOE:break;
	default:ASSERT(FALSE);
	}
	return nItem;
}
void CDlgMapEdit::OnMapLButtonDown_Obj(u16 x,u16 y)
{
	u16 tcur_sel_obj;
	PICKOBJ_GROUP tgroup;
	tcur_sel_obj=PickObj(x,y,&tgroup);
	if(tcur_sel_obj!=0xFFFF)
	{
		cur_sel_obj=tcur_sel_obj;
		cur_sel_objgroup=tgroup;
		int nItem=Obj_GameIdtoListId(cur_sel_obj,cur_sel_objgroup);

		IsListObjChangeFromSoftWare=true;
		m_ListObj.SetItemState(nItem,
			LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
		m_ListObj.EnsureVisible(nItem,TRUE);
		m_ListObj.SetFocus();
		IsListObjChangeFromSoftWare=false;
		GetDlgItem(IDC_STATIC_MAP)->RedrawWindow();

		switch(cur_sel_objgroup)
		{
		case FOE:
			obj_moving_ox=m_De.Foe(cur_sel_obj).x;
			obj_moving_oy=m_De.Foe(cur_sel_obj).y;
			break;
		case SUP:
			obj_moving_ox=m_De.Sup(cur_sel_obj).x;
			obj_moving_oy=m_De.Sup(cur_sel_obj).y;
			break;
		case DOOR:
			obj_moving_ox=m_Ma.Door(cur_sel_obj).x;
			obj_moving_oy=m_Ma.Door(cur_sel_obj).y;
			break;
		case MCTRL:
			obj_moving_ox=m_Mctrl[(u8)cur_sel_obj].x;
			obj_moving_oy=m_Mctrl[(u8)cur_sel_obj].y;
			break;
		}
		obj_moving_dx=x-obj_moving_ox;
		obj_moving_dy=y-obj_moving_oy;
		obj_moving=true;
	}
}
BOOL CDlgMapEdit::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{

	LONG Id=GetWindowLong(pWnd->GetSafeHwnd(),GWL_ID);
	CPoint pt;
	CRect rc;
	GetCursorPos(&pt);
	pWnd->GetWindowRect(&rc);
	pt-=rc.TopLeft();
	if(mode==MPT_OBJ)
	{
		if(message==WM_LBUTTONUP)
		{
			OnMapLButtonUp_Obj();
		}
		else if(Id==IDC_STATIC_MAP)
		{
			pt.x+=m_HScroll.GetScrollPos();
			pt.y+=m_VScroll.GetScrollPos();
			switch(message)
			{
			case WM_MOUSEMOVE:OnMapMouseMove_Obj((u16)pt.x,(u16)pt.y);break;
			case WM_LBUTTONDOWN:OnMapLButtonDown_Obj((u16)pt.x,(u16)pt.y);break;
			//case WM_LBUTTONUP:OnMapLButtonUp((u8)(pt.x>>4),(u8)(pt.y>>4));break;
			}
		}
		else OnMapMouseMove_Obj(0xFFFF,0xFFFF);
	}
	else if(mode==MPT_GRID || mode==MPT_BOSS)
	{
		if(message==WM_LBUTTONUP)
		{
			OnMapLButtonUp(0xFF,0xFF);
		}
		else if(Id==IDC_STATIC_MAP)
		{
			pt.x+=m_HScroll.GetScrollPos();
			pt.y+=m_VScroll.GetScrollPos();
			switch(message)
			{
			case WM_MOUSEMOVE:OnMapMouseMove((u8)(pt.x>>4),(u8)(pt.y>>4));break;
			case WM_LBUTTONDOWN:OnMapLButtonDown((u8)(pt.x>>4),(u8)(pt.y>>4));break;
			//case WM_LBUTTONUP:OnMapLButtonUp((u8)(pt.x>>4),(u8)(pt.y>>4));break;
			}

		}
		else if(Id==IDC_STATIC_STOCK)
		{
			pt.x+=m_HScrollStock.GetScrollPos();
			pt.y+=m_VScrollStock.GetScrollPos();
			switch(message)
			{
			case WM_MOUSEMOVE:OnStockMouseMove((u8)(pt.x>>4),(u8)(pt.y>>4));break;
			case WM_LBUTTONDOWN:OnStockLButtonDown((u8)(pt.x>>4),(u8)(pt.y>>4));break;
			case WM_RBUTTONDOWN:OnStockRButtonDown((u8)(pt.x>>4),(u8)(pt.y>>4));break;
			//case WM_LBUTTONUP:OnStockLButtonUp((u8)(pt.x>>4),(u8)(pt.y>>4));break;
			}
		}
		else
		{
			OnMapMouseMove(0xFF,0xFF);
		}
	}

	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

void CDlgMapEdit::OnCbnSelchangeComboBgm()
{
	CString str;
	m_ComboBgm.GetWindowText(str);
	int bgm;
	TCHAR dummybuf[100];
	_stscanf(str,FORMAT_BGM,&bgm,dummybuf);
	m_Ma.MapAttribute.Bgm=(u8)bgm;
}

void CDlgMapEdit::OnCbnSelchangeComboBoss()
{
	CString str;
	m_ComboBoss.GetWindowText(str);
	int bgm;
	TCHAR dummybuf[100];
	_stscanf(str,FORMAT_BOSS,&bgm,dummybuf);
	m_Ma.MapAttribute.Boss=(u8)bgm;
}

void CDlgMapEdit::OnTimer(UINT_PTR nIDEvent)
{
	bool needredraw=false;
	if(nIDEvent==ID_TIMER_REDRAW_MAP)
	{
		needredraw=m_Ma.TicketIn()||needredraw;
		needredraw=m_Bb.TicketIn()||needredraw;
		if(needredraw)
		{
			PaintMap();
			GetDlgItem(IDC_STATIC_MAP)->RedrawWindow();
		}
	}

	CDialog::OnTimer(nIDEvent);
}

void CDlgMapEdit::OnBnClickedCheckMapAni()
{
	WritePrivateProfileString(_T("MapEditor"),_T("MapAni"),m_CheckMapAni.GetCheck()?
		_T("1"):_T("0"),ProfilePath);
	if(m_CheckMapAni.GetCheck())
	{
		SetTimer(ID_TIMER_REDRAW_MAP,20,0);
	}
	else
	{
		KillTimer(ID_TIMER_REDRAW_MAP);
		m_Ma.TicketClear();
		m_Bb.TicketClear();
		if(m_Bb.pSqPl1)m_Bb.pSqPl1->TickedClear();
		PaintMap();
		GetDlgItem(IDC_STATIC_MAP)->RedrawWindow();
	}
}

void CDlgMapEdit::OnBnClickedRadioMapPtGrid()
{
	mode=MPT_GRID;
	m_ListObj.ShowWindow(SW_HIDE);
	m_CheckHideFoe.ShowWindow(SW_HIDE);
	m_CheckHideSup.ShowWindow(SW_HIDE);
	m_CheckHideDoor.ShowWindow(SW_HIDE);
	m_CheckHideMctrl.ShowWindow(SW_HIDE);
	m_CheckObjMovingAlign.ShowWindow(SW_HIDE);
	m_ButtonObjUp.ShowWindow(SW_HIDE);
	m_ButtonObjDown.ShowWindow(SW_HIDE);
	m_ButtonObjNew.ShowWindow(SW_HIDE);
	m_ButtonObjDelete.ShowWindow(SW_HIDE);
	m_ButtonObjProperty.ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_STOCK)->ShowWindow(SW_SHOW);
	m_HScrollStock.ShowWindow(SW_SHOW);
	m_VScrollStock.ShowWindow(SW_SHOW);
	PaintMap();
	GetDlgItem(IDC_STATIC_MAP)->RedrawWindow();
}

void CDlgMapEdit::OnBnClickedRadioMapPtObj()
{
	mode=MPT_OBJ;
	UpdateObjList();
	m_ListObj.ShowWindow(SW_SHOW);
	m_CheckHideFoe.ShowWindow(SW_SHOW);
	m_CheckHideSup.ShowWindow(SW_SHOW);
	m_CheckHideDoor.ShowWindow(SW_SHOW);
	m_CheckHideMctrl.ShowWindow(SW_SHOW);
	m_CheckObjMovingAlign.ShowWindow(SW_SHOW);
	m_ButtonObjUp.ShowWindow(SW_SHOW);
	m_ButtonObjDown.ShowWindow(SW_SHOW);
	m_ButtonObjNew.ShowWindow(SW_SHOW);
	m_ButtonObjDelete.ShowWindow(SW_SHOW);
	m_ButtonObjProperty.ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_STOCK)->ShowWindow(SW_HIDE);
	m_HScrollStock.ShowWindow(SW_HIDE);
	m_VScrollStock.ShowWindow(SW_HIDE);
	cur_obj=cur_sel_obj=0xFFFF;
	PaintMap();
	GetDlgItem(IDC_STATIC_MAP)->RedrawWindow();
}

void CDlgMapEdit::OnBnClickedRadioMapPtBoss()
{
	mode=MPT_BOSS;
	UpdateGuideList();
	m_ListObj.ShowWindow(SW_SHOW);
	m_CheckHideFoe.ShowWindow(SW_HIDE);
	m_CheckHideSup.ShowWindow(SW_HIDE);
	m_CheckHideDoor.ShowWindow(SW_HIDE);
	m_CheckHideMctrl.ShowWindow(SW_HIDE);
	m_CheckObjMovingAlign.ShowWindow(SW_HIDE);
	m_ButtonObjUp.ShowWindow(SW_HIDE);
	m_ButtonObjDown.ShowWindow(SW_HIDE);
	m_ButtonObjNew.ShowWindow(SW_HIDE);
	m_ButtonObjDelete.ShowWindow(SW_HIDE);
	m_ButtonObjProperty.ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_STOCK)->ShowWindow(SW_HIDE);
	m_HScrollStock.ShowWindow(SW_HIDE);
	m_VScrollStock.ShowWindow(SW_HIDE);
	PaintMap();
	GetDlgItem(IDC_STATIC_MAP)->RedrawWindow();
}

void CDlgMapEdit::OnBnClickedCheckHideObj()
{
	GetDlgItem(IDC_STATIC_MAP)->RedrawWindow();
}

u16 CDlgMapEdit::PickObj(u16 x,u16 y,PICKOBJ_GROUP *retPickGroup)
{
#define DISTANCE_F1(OBJ) (abs(OBJ.x-x)+abs(OBJ.y-y))
	if(!m_CheckHideFoe.GetCheck())for(u16 i=0;i<m_De.GetFoeCount();++i)
	{
		if(DISTANCE_F1(m_De.Foe(i))<16)
		{
			if(retPickGroup)*retPickGroup=FOE;
			return i;
		}
	}
	if(!m_CheckHideSup.GetCheck())for(u16 i=0;i<m_De.GetSupCount();++i)
	{
		if(DISTANCE_F1(m_De.Sup(i))<16)
		{
			if(retPickGroup)*retPickGroup=SUP;
			return i;
		}
	}
	if(!m_CheckHideDoor.GetCheck())for(u16 i=0;i<m_Ma.GetDoorCount();++i)
	{
		if(DISTANCE_F1(m_Ma.Door(i))<16)
		{
			if(retPickGroup)*retPickGroup=DOOR;
			return i;
		}
	}
	if(!m_CheckHideMctrl.GetCheck())for(u8 i=0;i<m_Mctrl.GetMctrlCount();++i)
	{
		if(DISTANCE_F1(m_Mctrl[i])<16)
		{
			if(retPickGroup)*retPickGroup=MCTRL;
			return i;
		}
	}
	return 0xFFFF;
#undef DISTANCE_F1
}
void CDlgMapEdit::OnLvnItemchangedListMapObj(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	if(!IsListObjChangeFromSoftWare)
	{
		cur_sel_obj=pNMLV->iItem;
		cur_sel_objgroup=FOE;
		u16 x,y;
		if(cur_sel_obj>=m_De.GetFoeCount())
		{
			cur_sel_obj-=m_De.GetFoeCount();
			cur_sel_objgroup=SUP;
			if(cur_sel_obj>=m_De.GetSupCount())
			{
				cur_sel_obj-=m_De.GetSupCount();
				cur_sel_objgroup=DOOR;
				if(cur_sel_obj>=m_Ma.GetDoorCount())
				{
					cur_sel_obj-=m_Ma.GetDoorCount();
					cur_sel_objgroup=MCTRL;
					x=m_Mctrl[(u8)cur_sel_obj].x;
					y=m_Mctrl[(u8)cur_sel_obj].y;
				}
				else{
					x=m_Ma.Door(cur_sel_obj).x;
					y=m_Ma.Door(cur_sel_obj).y;
				}
				
			}
			else{
				x=m_De.Sup(cur_sel_obj).x;
				y=m_De.Sup(cur_sel_obj).y;
			}
			
		}
		else{
			x=m_De.Foe(cur_sel_obj).x;
			y=m_De.Foe(cur_sel_obj).y;
		}
		RECT rc;
		GetDlgItem(IDC_STATIC_MAP)->GetClientRect(&rc);
		m_HScroll.SetScrollPos(x-(rc.right-rc.left)/2);
		m_VScroll.SetScrollPos(y-(rc.bottom-rc.top)/2);
		GetDlgItem(IDC_STATIC_MAP)->RedrawWindow();
		GetDlgItem(IDC_STATIC_MAP_CX)->RedrawWindow();
		GetDlgItem(IDC_STATIC_MAP_CY)->RedrawWindow();
	}

	*pResult = 0;
}

void CDlgMapEdit::OnDestroy()
{
	CDialog::OnDestroy();

	m_Mctrl.ToMa(m_Ma);
}

void CDlgMapEdit::OnBnClickedButtonObjUp()
{
	if(cur_sel_obj==0xFFFF)return;
	if(cur_sel_obj==0)return;
	switch(cur_sel_objgroup)
	{
	case FOE:{
		SqDe::SqItem t;
		t=m_De.Foe(cur_sel_obj);
		m_De.Foe(cur_sel_obj)=m_De.Foe(cur_sel_obj-1);
		m_De.Foe(cur_sel_obj-1)=t;
		break;}
	case SUP:{
		SqDe::SqItem t;
		t=m_De.Sup(cur_sel_obj);
		m_De.Sup(cur_sel_obj)=m_De.Sup(cur_sel_obj-1);
		m_De.Sup(cur_sel_obj-1)=t;
		break;}
	case DOOR:{
		SqMa::SqDoor t;
		t=m_Ma.Door(cur_sel_obj);
		m_Ma.Door(cur_sel_obj)=m_Ma.Door(cur_sel_obj-1);
		m_Ma.Door(cur_sel_obj-1)=t;
		break;}
	case MCTRL:{
		SqMctrlPack::MctrlNote t;
		t=m_Mctrl[(u8)cur_sel_obj];
		m_Mctrl[(u8)cur_sel_obj]=m_Mctrl[(u8)cur_sel_obj-1];
		m_Mctrl[(u8)cur_sel_obj-1]=t;
		break;}
	}

	CString cts,lts;
	int nItem=Obj_GameIdtoListId(cur_sel_obj,cur_sel_objgroup);
	for(int coli=1;coli<m_ListObj.GetHeaderCtrl()->GetItemCount();coli++)
	{
		cts=m_ListObj.GetItemText(nItem,coli);
		lts=m_ListObj.GetItemText(nItem-1,coli);
		m_ListObj.SetItemText(nItem,coli,lts);
		m_ListObj.SetItemText(nItem-1,coli,cts);
	}
	IsListObjChangeFromSoftWare=true;
	m_ListObj.SetItemState(nItem-1,
		LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
	m_ListObj.EnsureVisible(nItem-1,TRUE);
	m_ListObj.SetFocus();
	IsListObjChangeFromSoftWare=false;

	--cur_sel_obj;
	GetDlgItem(IDC_STATIC_MAP)->RedrawWindow();
}

void CDlgMapEdit::OnBnClickedButtonObjDown()
{
	if(cur_sel_obj==0xFFFF)return;
	switch(cur_sel_objgroup)
	{
	case FOE:{
		if(cur_sel_obj==m_De.GetFoeCount()-1)return;
		SqDe::SqItem t;
		t=m_De.Foe(cur_sel_obj);
		m_De.Foe(cur_sel_obj)=m_De.Foe(cur_sel_obj+1);
		m_De.Foe(cur_sel_obj+1)=t;
		break;}
	case SUP:{
		if(cur_sel_obj==m_De.GetSupCount()-1)return;
		SqDe::SqItem t;
		t=m_De.Sup(cur_sel_obj);
		m_De.Sup(cur_sel_obj)=m_De.Sup(cur_sel_obj+1);
		m_De.Sup(cur_sel_obj+1)=t;
		break;}
	case DOOR:{
		if(cur_sel_obj==m_Ma.GetDoorCount()-1)return;
		SqMa::SqDoor t;
		t=m_Ma.Door(cur_sel_obj);
		m_Ma.Door(cur_sel_obj)=m_Ma.Door(cur_sel_obj+1);
		m_Ma.Door(cur_sel_obj+1)=t;
		break;}
	case MCTRL:{
		if(cur_sel_obj==m_Mctrl.GetMctrlCount()-1)return;
		SqMctrlPack::MctrlNote t;
		t=m_Mctrl[(u8)cur_sel_obj];
		m_Mctrl[(u8)cur_sel_obj]=m_Mctrl[(u8)cur_sel_obj+1];
		m_Mctrl[(u8)cur_sel_obj+1]=t;
		break;}
	}

	CString cts,lts;
	int nItem=Obj_GameIdtoListId(cur_sel_obj,cur_sel_objgroup);
	for(int coli=1;coli<m_ListObj.GetHeaderCtrl()->GetItemCount();coli++)
	{
		cts=m_ListObj.GetItemText(nItem,coli);
		lts=m_ListObj.GetItemText(nItem+1,coli);
		m_ListObj.SetItemText(nItem,coli,lts);
		m_ListObj.SetItemText(nItem+1,coli,cts);
	}
	IsListObjChangeFromSoftWare=true;
	m_ListObj.SetItemState(nItem+1,
		LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
	m_ListObj.EnsureVisible(nItem+1,TRUE);
	m_ListObj.SetFocus();
	IsListObjChangeFromSoftWare=false;

	++cur_sel_obj;
	GetDlgItem(IDC_STATIC_MAP)->RedrawWindow();
}
void CDlgMapEdit::OnBnClickedButtonObjNew()
{
	CMenu menu;
	menu.CreatePopupMenu();
	menu.AppendMenu(0,ID_NEWOBJ_FOE,_T("新敌人"));
	menu.AppendMenu(0,ID_NEWOBJ_SUP,_T("新补给品"));
	menu.AppendMenu(0,ID_NEWOBJ_DOOR,_T("新传送装置"));
	menu.AppendMenu(0,ID_NEWOBJ_MCTRL,_T("新地图组件"));
	RECT rc;
	m_ButtonObjNew.GetWindowRect(&rc);
	menu.TrackPopupMenu(
		GetSystemMetrics(SM_MENUDROPALIGNMENT)?
		TPM_RIGHTALIGN:TPM_LEFTALIGN,
		rc.right,rc.top,this);
}

void CDlgMapEdit::OnBnClickedButtonObjDelete()
{
	if(cur_sel_obj==0xFFFF)return;
	switch(cur_sel_objgroup)
	{
	case FOE:
		m_De.RemoveFoe(cur_sel_obj);
		break;
	case SUP:
		m_De.RemoveSup(cur_sel_obj);
		break;
	case DOOR:
		m_Ma.RemoveDoor(cur_sel_obj);
		break;
	case MCTRL:
		m_Mctrl.RemoveMctrl((u8)cur_sel_obj);
		break;
	}
	cur_sel_obj=0xFFFF;
	UpdateObjList();
	GetDlgItem(IDC_STATIC_MAP)->RedrawWindow();
}

void CDlgMapEdit::OnBnClickedButtonObjProperty()
{
	if(cur_sel_obj==0xFFFF)return;
	CDlgObj dlg(this);
	bool change=false;
	if(cur_sel_objgroup==FOE)
	{
		dlg.objgroup=CDlgObj::FOE;
		dlg.title=_T("敌人属性");
		dlg.x=m_De.Foe(cur_sel_obj).x;
		dlg.y=m_De.Foe(cur_sel_obj).y;
		dlg.class_id=m_De.Foe(cur_sel_obj).class_id;
		memcpy(dlg.param,&m_De.Foe(cur_sel_obj).pa,8);
		if(dlg.DoModal()==IDOK)
		{
			m_De.Foe(cur_sel_obj).x=dlg.x;
			m_De.Foe(cur_sel_obj).y=dlg.y;
			m_De.Foe(cur_sel_obj).class_id=dlg.class_id;
			memcpy(&m_De.Foe(cur_sel_obj).pa,dlg.param,8);
			change=true;
		}
	}
	else if(cur_sel_objgroup==SUP)
	{
		dlg.objgroup=CDlgObj::SUP;
		dlg.title=_T("补给品属性");
		dlg.x=m_De.Sup(cur_sel_obj).x;
		dlg.y=m_De.Sup(cur_sel_obj).y;
		dlg.class_id=m_De.Sup(cur_sel_obj).class_id;
		memcpy(dlg.param,&m_De.Sup(cur_sel_obj).pa,8);
		if(dlg.DoModal()==IDOK)
		{
			m_De.Sup(cur_sel_obj).x=dlg.x;
			m_De.Sup(cur_sel_obj).y=dlg.y;
			m_De.Sup(cur_sel_obj).class_id=dlg.class_id;
			memcpy(&m_De.Sup(cur_sel_obj).pa,dlg.param,8);
			change=true;
		}
	}
	else if(cur_sel_objgroup==DOOR)
	{
		dlg.objgroup=CDlgObj::DOOR;
		dlg.title=_T("传送装置属性");
		dlg.x=m_Ma.Door(cur_sel_obj).x;
		dlg.y=m_Ma.Door(cur_sel_obj).y;
		dlg.class_id=m_Ma.Door(cur_sel_obj).class_id;
		memcpy(dlg.param,&m_Ma.Door(cur_sel_obj).dst_step,2);
		if(dlg.DoModal()==IDOK)
		{
			m_Ma.Door(cur_sel_obj).x=dlg.x;
			m_Ma.Door(cur_sel_obj).y=dlg.y;
			m_Ma.Door(cur_sel_obj).class_id=dlg.class_id;
			memcpy(&m_Ma.Door(cur_sel_obj).dst_step,dlg.param,2);
			change=true;
		}
	}
	else if(cur_sel_objgroup==MCTRL)
	{
		dlg.objgroup=CDlgObj::MCTRL;
		dlg.title=_T("地图组件属性");
		dlg.x=m_Mctrl[(u8)cur_sel_obj].x;
		dlg.y=m_Mctrl[(u8)cur_sel_obj].y;
		dlg.class_id=m_Mctrl[(u8)cur_sel_obj].class_id;
		memcpy(dlg.param,&m_Mctrl[(u8)cur_sel_obj].param,2);
		memcpy(dlg.param+2,m_Mctrl[(u8)cur_sel_obj].pExtData,
			GetEvcDataLen(m_Mctrl[(u8)cur_sel_obj].class_id));
		if(dlg.DoModal()==IDOK)
		{
			m_Mctrl[(u8)cur_sel_obj].x=dlg.x;
			m_Mctrl[(u8)cur_sel_obj].y=dlg.y;
			m_Mctrl[(u8)cur_sel_obj].class_id=(u8)dlg.class_id;
			memcpy(&m_Mctrl[(u8)cur_sel_obj].param,dlg.param,2);
			delete[]m_Mctrl[(u8)cur_sel_obj].pExtData;
			m_Mctrl[(u8)cur_sel_obj].pExtData=new u8[
				GetEvcDataLen(m_Mctrl[(u8)cur_sel_obj].class_id)];
			memcpy(m_Mctrl[(u8)cur_sel_obj].pExtData,dlg.param+2,
				GetEvcDataLen(m_Mctrl[(u8)cur_sel_obj].class_id));
			change=true;
		}
	}
	if(change)
	{
		UpdateObjList();
		int nItem=Obj_GameIdtoListId(cur_sel_obj,cur_sel_objgroup);
		m_ListObj.SetItemState(nItem,
			LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
		m_ListObj.EnsureVisible(nItem,TRUE);
	}
}

void CDlgMapEdit::OnNMDblclkListMapObj(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(mode==MPT_OBJ)OnBnClickedButtonObjProperty();
	*pResult = 0;
}
void CDlgMapEdit::OnNewFoe()
{
	RECT rc;
	GetDlgItem(IDC_STATIC_MAP)->GetClientRect(&rc);

	CDlgObj dlg(this);
	dlg.title=_T("新敌人");
	dlg.objgroup=CDlgObj::FOE;
	dlg.x=(u16)min(m_Ma.GetW()*16-8,m_HScroll.GetScrollPos()+(rc.right-rc.left)/2);
	dlg.y=(u16)min(m_Ma.GetH()*16-8,m_VScroll.GetScrollPos()+(rc.bottom-rc.top)/2);
	dlg.class_id=0;
	ZeroMemory(dlg.param,8);

	if(dlg.DoModal()==IDOK)
	{
		u16 i=m_De.NewFoe();
		m_De.Foe(i).class_id=dlg.class_id;
		m_De.Foe(i).x=dlg.x;
		m_De.Foe(i).y=dlg.y;
		memcpy(&m_De.Foe(i).pa,dlg.param,8);

		cur_sel_obj=i;
		cur_sel_objgroup=FOE;

		UpdateObjList();
		int nItem=Obj_GameIdtoListId(cur_sel_obj,cur_sel_objgroup);
		m_ListObj.SetItemState(nItem,
			LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
		m_ListObj.EnsureVisible(nItem,TRUE);
	}
}
void CDlgMapEdit::OnNewSup()
{
	RECT rc;
	GetDlgItem(IDC_STATIC_MAP)->GetClientRect(&rc);

	CDlgObj dlg(this);
	dlg.title=_T("新补给品");
	dlg.objgroup=CDlgObj::SUP;
	dlg.x=(u16)min(m_Ma.GetW()*16-8,m_HScroll.GetScrollPos()+(rc.right-rc.left)/2);
	dlg.y=(u16)min(m_Ma.GetH()*16-8,m_VScroll.GetScrollPos()+(rc.bottom-rc.top)/2);
	dlg.class_id=0;
	ZeroMemory(dlg.param,8);

	if(dlg.DoModal()==IDOK)
	{
		u16 i=m_De.NewSup();
		m_De.Sup(i).class_id=dlg.class_id;
		m_De.Sup(i).x=dlg.x;
		m_De.Sup(i).y=dlg.y;
		memcpy(&m_De.Sup(i).pa,dlg.param,8);

		cur_sel_obj=i;
		cur_sel_objgroup=SUP;

		UpdateObjList();
		int nItem=Obj_GameIdtoListId(cur_sel_obj,cur_sel_objgroup);
		m_ListObj.SetItemState(nItem,
			LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
		m_ListObj.EnsureVisible(nItem,TRUE);
	}
}
void CDlgMapEdit::OnNewDoor()
{
	RECT rc;
	GetDlgItem(IDC_STATIC_MAP)->GetClientRect(&rc);

	CDlgObj dlg(this);
	dlg.title=_T("新传送装置");
	dlg.objgroup=CDlgObj::DOOR;
	dlg.x=(u16)min(m_Ma.GetW()*16-8,m_HScroll.GetScrollPos()+(rc.right-rc.left)/2);
	dlg.x=(dlg.x&0xFFF0)|8;
	dlg.y=(u16)min(m_Ma.GetH()*16-8,m_VScroll.GetScrollPos()+(rc.bottom-rc.top)/2);
	dlg.y=(dlg.y&0xFFF0)|8;
	dlg.class_id=0;
	ZeroMemory(dlg.param,2);

	if(dlg.DoModal()==IDOK)
	{
		u16 i=m_Ma.NewDoor();
		m_Ma.Door(i).class_id=dlg.class_id;
		m_Ma.Door(i).x=dlg.x;
		m_Ma.Door(i).y=dlg.y;
		memcpy(&m_Ma.Door(i).dst_step,dlg.param,2);

		cur_sel_obj=i;
		cur_sel_objgroup=DOOR;

		UpdateObjList();
		int nItem=Obj_GameIdtoListId(cur_sel_obj,cur_sel_objgroup);
		m_ListObj.SetItemState(nItem,
			LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
		m_ListObj.EnsureVisible(nItem,TRUE);
	}
}
void CDlgMapEdit::OnNewMctrl()
{
	RECT rc;
	GetDlgItem(IDC_STATIC_MAP)->GetClientRect(&rc);

	CDlgObj dlg(this);
	dlg.title=_T("新地图组件");
	dlg.objgroup=CDlgObj::MCTRL;
	dlg.x=(u16)min(m_Ma.GetW()*16-8,m_HScroll.GetScrollPos()+(rc.right-rc.left)/2);
	dlg.y=(u16)min(m_Ma.GetH()*16-8,m_VScroll.GetScrollPos()+(rc.bottom-rc.top)/2);
	dlg.class_id=0;
	ZeroMemory(dlg.param,70);

	if(dlg.DoModal()==IDOK)
	{
		u8 i=m_Mctrl.NewMctrl();
		m_Mctrl[i].class_id=(u8)dlg.class_id;
		m_Mctrl[i].x=dlg.x;
		m_Mctrl[i].y=dlg.y;
		memcpy(&m_Mctrl[i].param,dlg.param,2);
		m_Mctrl[i].pExtData=new u8[GetEvcDataLen(m_Mctrl[i].class_id)];
		memcpy(m_Mctrl[i].pExtData,dlg.param+2,
			GetEvcDataLen(m_Mctrl[i].class_id));

		cur_sel_obj=i;
		cur_sel_objgroup=MCTRL;

		UpdateObjList();
		int nItem=Obj_GameIdtoListId(cur_sel_obj,cur_sel_objgroup);
		m_ListObj.SetItemState(nItem,
			LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
		m_ListObj.EnsureVisible(nItem,TRUE);
	}
}
void CDlgMapEdit::OnMapDbClick()
{
	if(mode==MPT_OBJ && cur_obj!=0xFFFF)OnBnClickedButtonObjProperty();
}
void CDlgMapEdit::OnBnClickedButtonMapCancel()
{
	EndDialog(-1);
}

void CDlgMapEdit::OnBnClickedButtonMapResize()
{
	CDlgResize dlg;
	dlg.m_W=m_Ma.GetW();
	dlg.m_H=m_Ma.GetH();
	if(dlg.DoModal()==IDOK)
	{
		m_Ma.ResizeMap(dlg.m_W,dlg.m_H,dlg.m_Ox,dlg.m_Oy);
		for(u16 i=0;i<m_De.GetFoeCount();++i)
		{
			m_De.Foe(i).x=max(0,m_De.Foe(i).x+dlg.m_Ox*16);
			m_De.Foe(i).y=max(0,m_De.Foe(i).y+dlg.m_Oy*16);
		}
		for(u16 i=0;i<m_De.GetSupCount();++i)
		{
			m_De.Sup(i).x=max(0,m_De.Sup(i).x+dlg.m_Ox*16);
			m_De.Sup(i).y=max(0,m_De.Sup(i).y+dlg.m_Oy*16);
		}
		for(u16 i=0;i<m_Ma.GetDoorCount();++i)
		{
			m_Ma.Door(i).x=(max(0,m_Ma.Door(i).x+dlg.m_Ox*16)&0xFFF0)|8;
			m_Ma.Door(i).y=(max(0,m_Ma.Door(i).y+dlg.m_Oy*16)&0xFFF0)|8;
		}
		for(u8 i=0;i<m_Mctrl.GetMctrlCount();++i)
		{
			m_Mctrl[i].x=max(0,m_Mctrl[i].x+dlg.m_Ox*16);
			m_Mctrl[i].y=max(0,m_Mctrl[i].y+dlg.m_Oy*16);
		}
		cur_sel_obj=0xFFFF;
		UpdateObjList();
		m_CanMap.Create(dlg.m_W<<4,dlg.m_H<<4);
		SetScroll();
		PaintMap();
		GetDlgItem(IDC_STATIC_MAP)->RedrawWindow();
	}
}

void CDlgMapEdit::OnBnClickedButtonZeroCell()
{
	if(MessageBox(_T("确定要清空地图?"),0,MB_YESNO|MB_DEFBUTTON2)==IDYES)
	{
		m_Ma.ZeroCell();
		PaintMap();
		GetDlgItem(IDC_STATIC_MAP)->RedrawWindow();
	}
}
