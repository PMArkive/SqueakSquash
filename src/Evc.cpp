
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
	{2,		_T("FOE/SUP出现?")},
	{8,		_T("背景变色触发器")},
	{8,		_T("红外线触发器?[19]")},

	//20
	{14,	_T("屏幕锁定")},
	{6,		_T("红外线触发器?[21]")},
	{16,	_T("触发簇?")},
	{12,	_T("循环触发器？")},
	{4,		_T("大画面特效")},
	{2,		_T("小画面特效")},
	{4,		_T("二十六")},
};

u16 GetEvcDataLen(u8 class_id)
{
	return EvcDesc[class_id].DataLen;
}

SqComponentPack::SqComponentPack():pComponent(0),ComponentCount(0)
{
}
SqComponentPack::~SqComponentPack()
{
	Unload();
}
void SqComponentPack::ToMa(SqMa& sqma)
{
	ASSERT(sqma.IsLoaded());

	//Clear old data
	if(sqma.pComponent){delete[] sqma.pComponent;sqma.pComponent=0;}
	if(sqma.pComponentGroup){
		for(u8 i=0;i<sqma.ComponentGroupCount;++i)delete[] sqma.pComponentGroup[i].pData;
		delete[] sqma.pComponentGroup;sqma.pComponentGroup=0;
	}
	sqma.ComponentGroupCount=0;

	struct EVCTB
	{
		u8 class_id;
		std::list<u8*> ext_data_pl;
	};
	std::list<EVCTB> evctbl;
	EVCTB evctbt;

	bool needp;
	if(sqma.ComponentCount=ComponentCount)
	{

		//EvpIn;
		sqma.pComponent=new SqMa::ComponentData[ComponentCount];
		for(u8 i=0;i<ComponentCount;++i)
		{
			sqma.pComponent[i].class_id=pComponent[i].class_id;
			sqma.pComponent[i].x=pComponent[i].x;
			sqma.pComponent[i].y=pComponent[i].y;
			sqma.pComponent[i].param=pComponent[i].param;

			//apply for id
			needp=true;
			for(std::list<EVCTB>::iterator iter=evctbl.begin();
				iter!=evctbl.end();iter++)
			{
				if(iter->class_id==pComponent[i].class_id)
				{
					sqma.pComponent[i].id=(u8)iter->ext_data_pl.size();
					iter->ext_data_pl.push_back(pComponent[i].pExtData);
					needp=false;
					break;
				}
			}
			if(needp)
			{
				evctbt.class_id=pComponent[i].class_id;
				evctbl.push_back(evctbt);
				evctbl.back().ext_data_pl.push_back(pComponent[i].pExtData);
				sqma.pComponent[i].id=0;
			}

		}

		//EvcIn
		sqma.ComponentGroupCount=(u8)evctbl.size();
		sqma.pComponentGroup=new SqMa::ComponentGroupData[sqma.ComponentGroupCount];
		u8 i=0,j;
		for(std::list<EVCTB>::iterator iter=evctbl.begin();
				iter!=evctbl.end();iter++,++i)
		{
			sqma.pComponentGroup[i].Header.class_id=iter->class_id;
			sqma.pComponentGroup[i].Header.data_len=GetEvcDataLen(iter->class_id);
			sqma.pComponentGroup[i].Header.count=(u8)iter->ext_data_pl.size();
			sqma.pComponentGroup[i].pData=new u8[sqma.pComponentGroup[i].Header.data_len*
				sqma.pComponentGroup[i].Header.count];
			j=0;
			for(std::list<u8*>::iterator jter=iter->ext_data_pl.begin();
				jter!=iter->ext_data_pl.end();jter++,++j)
				memcpy(sqma.pComponentGroup[i].pData+sqma.pComponentGroup[i].Header.data_len*j,*jter,
					sqma.pComponentGroup[i].Header.data_len);
		}	
	}
}
void SqComponentPack::FromMa(SqMa& sqma)
{
	ASSERT(sqma.IsLoaded());
	Unload();

	ComponentCount=sqma.ComponentCount;
	if(ComponentCount)
	{
		pComponent=new ComponentNote[ComponentCount];
		for(u8 i=0;i<ComponentCount;++i)
		{
			pComponent[i].class_id=sqma.pComponent[i].class_id;
			pComponent[i].x=sqma.pComponent[i].x;
			pComponent[i].y=sqma.pComponent[i].y;
			pComponent[i].param=sqma.pComponent[i].param;
			pComponent[i].pExtData=new u8[GetEvcDataLen(pComponent[i].class_id)];
			for(u8 j=0;;++j)
			{
				ASSERT(j<sqma.ComponentGroupCount);
				if(sqma.pComponentGroup[j].Header.class_id==pComponent[i].class_id)
				{
					ASSERT(GetEvcDataLen(pComponent[i].class_id)==sqma.pComponentGroup[j].Header.data_len);
					ASSERT(sqma.pComponent[i].id<sqma.pComponentGroup[j].Header.count);
					memcpy(pComponent[i].pExtData,
						sqma.pComponentGroup[j].pData+sqma.pComponent[i].id*sqma.pComponentGroup[j].Header.data_len,
						sqma.pComponentGroup[j].Header.data_len);
					break;
				}
			}
			
		}
	}
}
void SqComponentPack::Unload()
{
	if(pComponent)
	{
		for(u8 i=0;i<ComponentCount;++i)delete[] pComponent[i].pExtData;
		delete[] pComponent;
		pComponent=0;
	}
	ComponentCount=0;
}