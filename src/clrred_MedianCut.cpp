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
	static enum CMPMODE{CMPMODE_R,CMPMODE_G,CMPMODE_B}CmpMode;
	u8 GetCmpValue()const
	{
		switch(CmpMode)
		{
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
	inline bool operator ==(const RGBVec& c)const{return GetCmpValue()==c.GetCmpValue();}
	inline bool operator !=(const RGBVec& c)const{return GetCmpValue()!=c.GetCmpValue();}
	u32 GetDistanceSquare(const RGBVec& c)const
	{
		return(r*c.r+g*c.g+b*c.b);
	}
};
RGBVec::CMPMODE RGBVec::CmpMode(CMPMODE_R);
typedef std::list<RGBVec> rvlist;
void clrred_MedianCut(
	rvlist &ColorIn,
	RGBVec ColorOut[/*256*/]//ColorOut[0]�������������ɫԤ��
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
		return;
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
			rmin=gmin=bmin=255;
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
	}

	//�Ե���һ�����У���������Ϊ255
	iterq=rvlq.begin();
	iterq++;
	iterq->insert(iterq->begin(),rvlq.begin()->begin(),rvlq.begin()->end());
	rvlq.pop_front();

	ASSERT(rvlq.size()==255);

	//���ɵ�ɫ��
	u8 i=1;
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
}

void BmpToNitroPlt256(
	const COLORREF BmpIn[],
	u32 Size,
	COLORREF BackColor,
	u8 BmpOut[],
	Nitro::Color15 PltOut[/*256*/])
{
	RGBVec rgbt;
	rvlist rvl;

	u32* ColorMap=new u32[Size];
	
	//ɨ����ɫ
	for(u32 i=0;i<Size;++i)
	{
		rgbt=RGBVec(BmpIn[i]);
		rvl.push_front(rgbt);
	}
	rvl.unique();

	//���ɵ�ɫ��
	RGBVec ColorOut[256];
	ColorOut[0]=RGBVec(BackColor);
	clrred_MedianCut(rvl,ColorOut);
	


	delete[]ColorMap;
}