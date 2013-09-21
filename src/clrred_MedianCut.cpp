
#include "stdafx.h"
#include <list>
#include "Nitro.h"

class RGBVec
{
public:
	u8 r,g,b;
	RGBVec():r(0),g(0),b(0){}
	RGBVec(u8 _r,u8 _g,u8 _b):r(_r),g(_g),b(_b){}
	RGBVec(COLORREF rgb):r(GetRValue(rgb)),g(GetGValue(rgb)),b(GetBValue(rgb)){}
	RGBVec(Nitro::Color15 c):r(c.r),g(c.g),b(c.b){}
	static enum CMPMODE{CMPMODE_ALL,CMPMODE_R,CMPMODE_G,CMPMODE_B}CmpMode;
	u32 GetCmpValue()const
	{
		switch(CmpMode)
		{
		case CMPMODE_ALL:return (r<<16)|(g<<8)|b;
		case CMPMODE_R:return r;
		case CMPMODE_G:return g;
		case CMPMODE_B:return b;
		default:return r;
		}
	}
	inline bool operator > (const RGBVec& c)const{return GetCmpValue()> c.GetCmpValue();}
	inline bool operator < (const RGBVec& c)const{return GetCmpValue()< c.GetCmpValue();}
	inline bool operator >=(const RGBVec& c)const{return GetCmpValue()>=c.GetCmpValue();}
	inline bool operator <=(const RGBVec& c)const{return GetCmpValue()<=c.GetCmpValue();}
	inline bool operator ==(const RGBVec& c)const{return r==c.r&&g==c.g&&b==c.b;}
	//inline bool operator !=(const RGBVec& c)const{return GetCmpValue()!=c.GetCmpValue();}
	u32 GetDistanceSquare(const RGBVec& c)const
	{
		return (r-c.r)*(r-c.r)+
			(g-c.g)*(g-c.g)+
			(b-c.b)*(b-c.b);
	}
};
RGBVec::CMPMODE RGBVec::CmpMode(CMPMODE_R);
typedef std::list<RGBVec> rvlist;
bool clrred_MedianCut(
	rvlist &ColorIn,
	RGBVec ColorOut[/*256*/],

	CWnd* pWndUpdate,
	CProgressCtrl *pProgress
	)
{
	rvlist::iterator iter,iter2;
	if(ColorIn.size()<256)
	{
		u8 i=1;
		for(iter=ColorIn.begin();iter!=ColorIn.end();iter++)
		{
			ColorOut[i]=*iter;
			++i;
		}
		pProgress->SetPos(10);pWndUpdate->UpdateData(FALSE);
		return false;
	}

	std::list<rvlist> rvlq,//��������
		rvlt;//����������
	std::list<rvlist>::iterator iterq;
	rvlist rva,rvb;
	rvlq.push_front(ColorIn);//��������Ϊ��һ����������
	u8 rmax,rmin,gmax,gmin,bmax,bmin;
	for(int i=0;i<8;++i)//���������ܼƽ������1�ݷָ��2^8=256��
	{
		for(iterq=rvlq.begin();iterq!=rvlq.end();iterq++)
		{
			//����rgb����ֵ
			rmax=gmax=bmax=0;
			rmin=gmin=bmin=31;
			for(iter=iterq->begin();iter!=iterq->end();iter++)
			{
				if(iter->r>rmax)rmax=iter->r;
				if(iter->g>gmax)gmax=iter->g;
				if(iter->b>rmax)bmax=iter->b;
				if(iter->r<rmin)rmin=iter->r;
				if(iter->g<gmin)gmin=iter->g;
				if(iter->b<rmin)bmin=iter->b;
			}
			//���ݺ��ӳߴ�ѡ������ʽ
			if(rmax-rmin>gmax-gmin && 
				rmax-rmin>bmax-bmin)RGBVec::CmpMode=RGBVec::CMPMODE_R;
			else if(gmax-gmin>bmax-bmin)RGBVec::CmpMode=RGBVec::CMPMODE_G;
			else RGBVec::CmpMode=RGBVec::CMPMODE_B;

			//����
			iterq->sort();

			//������ָ����������rva,rvb
			iter=iterq->begin();
			for(u32 j=0;j<iterq->size()/2;++j)++iter;//�õ�����Ԫ�صĵ�����
			rva.insert(rva.begin(),iterq->begin(),iter);
			rvb.insert(rvb.begin(),iter,iterq->end());
			
			//����������������������
			rvlt.push_front(rva);
			rvlt.push_front(rvb);
			rva.clear();rvb.clear();
		}
		//�������������滻ԭ������
		rvlq=rvlt;
		rvlt.clear();
		pProgress->SetPos(i+3);pWndUpdate->UpdateData(FALSE);
	}

	ASSERT(rvlq.size()==256);

	//���ɵ�ɫ��
	u8 i=0;
	u32 rs,gs,bs;
	for(iterq=rvlq.begin();iterq!=rvlq.end();iterq++)
	{
		rs=gs=bs=0;
		for(iter=iterq->begin();iter!=iterq->end();iter++)
		{
			rs+=iter->r;
			gs+=iter->g;
			bs+=iter->b;
		}
		ColorOut[i].r=u8(rs/iterq->size());
		ColorOut[i].g=u8(gs/iterq->size());
		ColorOut[i].b=u8(bs/iterq->size());
		++i;
	}
	pProgress->SetPos(11);pWndUpdate->UpdateData(FALSE);
	return true;
}

void BmpToPlt256(
	const Nitro::Color15 BmpIn[],
	u32 Size,
	COLORREF BackColor,
	u8 BmpOut[],
	Nitro::Color15 PltOut[/*256*/],

	CWnd* pWndUpdate,
	CProgressCtrl *pProgress)
{
	RGBVec rgbt;
	rvlist rvl;

	
	//ɨ����ɫ
	for(u32 i=0;i<Size;++i)
	{
		rgbt=RGBVec(BmpIn[i]);
		rvl.push_front(rgbt);
	}
	RGBVec::CmpMode=RGBVec::CMPMODE_ALL;
	pProgress->SetPos(1);pWndUpdate->UpdateData(FALSE);
	rvl.sort();
	rvl.unique();
	pProgress->SetPos(2);pWndUpdate->UpdateData(FALSE);

	//���ɵ�ɫ��
	RGBVec ColorOut[256];

	u32 colord,cd2,plti;
	if(clrred_MedianCut(rvl,ColorOut,pWndUpdate,pProgress))
	{
		//�Ե�һ����ɫ������ɫ������λ
		colord=0xFFFFFFFF;
		for(u32 i=0;i<256;i+=2)
		{
			cd2=ColorOut[i].GetDistanceSquare(ColorOut[i+1]);
			if(cd2<colord)
			{
				plti=i;
				colord=cd2;
			}
		}
		ColorOut[plti+1].r=(ColorOut[plti].r+ColorOut[plti+1].r)/2;
		ColorOut[plti+1].g=(ColorOut[plti].g+ColorOut[plti+1].g)/2;
		ColorOut[plti+1].b=(ColorOut[plti].b+ColorOut[plti+1].b)/2;
		memmove(ColorOut+1,ColorOut,plti*sizeof(RGBVec));
		pProgress->SetPos(12);pWndUpdate->UpdateData(FALSE);
	}
	ColorOut[0]=RGBVec(BackColor);
	
	//����ӳ���
	for(u32 i=0;i<Size;++i)
	{
		//���������ɫ
		colord=0xFFFFFFFF;
		for(u32 j=1;j<256;++j)
		{
			cd2=ColorOut[j].GetDistanceSquare(RGBVec(BmpIn[i]));
			if(cd2<colord)
			{
				colord=cd2;
				plti=j;
			}
		}
		BmpOut[i]=(u8)plti;
	}
	pProgress->SetPos(13);pWndUpdate->UpdateData(FALSE);

	//��ɫ��ת��
	for(u32 i=0;i<256;++i)
	{
		PltOut[i].r=ColorOut[i].r;
		PltOut[i].g=ColorOut[i].g;
		PltOut[i].b=ColorOut[i].b;
		PltOut[i].x=0;
	}
	pProgress->SetPos(14);pWndUpdate->UpdateData(FALSE);

}