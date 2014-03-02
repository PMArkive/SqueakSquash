
//Unicode


#include "stdafx.h"
#include "Evc.h"
#include <list>




const EVC_DESC EvcDesc[]={

	//0
	{4,		_T("按钮")},
	{6,		_T("绳索顶")},
	{2,		_T("活动机关")},
	{2,		_T("悬挂平台")},
	{8,		_T("活动平台")},
	{12,	_T("云平台")},
	{2,		_T("滚石")},
	{4,		_T("火柱")},
	{2,		_T("落石")},
	{2,		_T("冰锥")},

	//10
	{2,		_T("蜡烛")},
	{2,		_T("大炮")},
	{2,		_T("点火大炮")},
	{64,	_T("传送星")},
	{2,		_T("草丛")},
	{2,		_T("木桶")},
	{2,		_T("雷管?")},
	{2,		_T("FOE/SUP出现")},
	{8,		_T("背景变色触发器")},
	{8,		_T("一次性红外线触发器?[19]")},

	//20
	{14,	_T("BOSS引擎?")},
	{6,		_T("红外线触发器?[21]")},
	{16,	_T("延时触发簇")},
	{12,	_T("金属BOSS-落石循环触发器")},
	{4,		_T("大画面特效")},
	{2,		_T("小画面特效")},
	{4,		_T("二十六")},
	{0,0}
};

u16 GetEvcDataLen(u8 class_id)
{
	return EvcDesc[class_id].DataLen;
}

SqMctrlPack::SqMctrlPack():pMctrl(0),MctrlCount(0)
{
}
SqMctrlPack::~SqMctrlPack()
{
	Unload();
}
void SqMctrlPack::ToMa(SqMa& sqma)
{
	ASSERT(sqma.IsLoaded());

	//Clear old data
	if(sqma.pMctrl){delete[] sqma.pMctrl;sqma.pMctrl=0;}
	if(sqma.pMctrlGroup){
		for(u8 i=0;i<sqma.MctrlGroupCount;++i)delete[] sqma.pMctrlGroup[i].pData;
		delete[] sqma.pMctrlGroup;sqma.pMctrlGroup=0;
	}
	sqma.MctrlGroupCount=0;

	struct EVCTB
	{
		u8 class_id;
		std::list<u8*> ext_data_pl;
	};
	std::list<EVCTB> evctbl;
	EVCTB evctbt;

	bool needp;
	if(sqma.MctrlCount=MctrlCount)
	{

		//EvpIn;
		sqma.pMctrl=new SqMa::MctrlData[MctrlCount];
		for(u8 i=0;i<MctrlCount;++i)
		{
			sqma.pMctrl[i].class_id=pMctrl[i].class_id;
			sqma.pMctrl[i].x=pMctrl[i].x;
			sqma.pMctrl[i].y=pMctrl[i].y;
			sqma.pMctrl[i].param=pMctrl[i].param;

			//apply for id
			needp=true;
			for(std::list<EVCTB>::iterator iter=evctbl.begin();
				iter!=evctbl.end();iter++)
			{
				if(iter->class_id==pMctrl[i].class_id)
				{
					sqma.pMctrl[i].id=(u8)iter->ext_data_pl.size();
					iter->ext_data_pl.push_back(pMctrl[i].pExtData);
					needp=false;
					break;
				}
			}
			if(needp)
			{
				evctbt.class_id=pMctrl[i].class_id;
				evctbl.push_back(evctbt);
				evctbl.back().ext_data_pl.push_back(pMctrl[i].pExtData);
				sqma.pMctrl[i].id=0;
			}

		}

		//EvcIn
		sqma.MctrlGroupCount=(u8)evctbl.size();
		sqma.pMctrlGroup=new SqMa::MctrlGroupData[sqma.MctrlGroupCount];
		u8 i=0,j;
		for(std::list<EVCTB>::iterator iter=evctbl.begin();
				iter!=evctbl.end();iter++,++i)
		{
			sqma.pMctrlGroup[i].Header.class_id=iter->class_id;
			sqma.pMctrlGroup[i].Header.data_len=GetEvcDataLen(iter->class_id);
			sqma.pMctrlGroup[i].Header.count=(u8)iter->ext_data_pl.size();
			sqma.pMctrlGroup[i].pData=new u8[sqma.pMctrlGroup[i].Header.data_len*
				sqma.pMctrlGroup[i].Header.count];
			j=0;
			for(std::list<u8*>::iterator jter=iter->ext_data_pl.begin();
				jter!=iter->ext_data_pl.end();jter++,++j)
				memcpy(sqma.pMctrlGroup[i].pData+sqma.pMctrlGroup[i].Header.data_len*j,*jter,
					sqma.pMctrlGroup[i].Header.data_len);
		}	
	}
}
void SqMctrlPack::FromMa(SqMa& sqma)
{
	ASSERT(sqma.IsLoaded());
	Unload();

	MctrlCount=sqma.MctrlCount;
	if(MctrlCount)
	{
		pMctrl=new MctrlNote[MctrlCount];
		for(u8 i=0;i<MctrlCount;++i)
		{
			pMctrl[i].class_id=sqma.pMctrl[i].class_id;
			pMctrl[i].x=sqma.pMctrl[i].x;
			pMctrl[i].y=sqma.pMctrl[i].y;
			pMctrl[i].param=sqma.pMctrl[i].param;
			pMctrl[i].pExtData=new u8[GetEvcDataLen(pMctrl[i].class_id)];
			for(u8 j=0;;++j)
			{
				ASSERT(j<sqma.MctrlGroupCount);
				if(sqma.pMctrlGroup[j].Header.class_id==pMctrl[i].class_id)
				{
					ASSERT(GetEvcDataLen(pMctrl[i].class_id)==sqma.pMctrlGroup[j].Header.data_len);
					ASSERT(sqma.pMctrl[i].id<sqma.pMctrlGroup[j].Header.count);
					memcpy(pMctrl[i].pExtData,
						sqma.pMctrlGroup[j].pData+sqma.pMctrl[i].id*sqma.pMctrlGroup[j].Header.data_len,
						sqma.pMctrlGroup[j].Header.data_len);
					break;
				}
			}
			
		}
	}
}
void SqMctrlPack::Unload()
{
	if(pMctrl)
	{
		for(u8 i=0;i<MctrlCount;++i)delete[] pMctrl[i].pExtData;
		delete[] pMctrl;
		pMctrl=0;
	}
	MctrlCount=0;
}
void SqMctrlPack::RemoveMctrl(u8 i)
{
	ASSERT(i<MctrlCount);
	delete[] pMctrl[i].pExtData;
	if(MctrlCount==1)
	{
		MctrlCount=0;
		delete[] pMctrl;
		pMctrl=0;
	}
	else
	{
		MctrlNote *newData=new MctrlNote[--MctrlCount];
		memcpy(newData,pMctrl,i*sizeof(MctrlNote));
		memcpy(newData+i,pMctrl+i+1,(MctrlCount-i)*sizeof(MctrlNote));
		delete[] pMctrl;
		pMctrl=newData;
	}
}
u8 SqMctrlPack::NewMctrl()
{
	MctrlNote *newData=new MctrlNote[++MctrlCount];
	if(MctrlCount!=1)
	{
		memcpy(newData,pMctrl,(MctrlCount-1)*sizeof(MctrlNote));
		delete[]pMctrl;
	}
	pMctrl=newData;
	memset(&pMctrl[MctrlCount-1],0,sizeof(MctrlNote));
	return MctrlCount-1;
}