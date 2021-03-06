﻿
//UTF8♔



#include "stdafx.h"
#include "SqMa.h"
#include "SqDe.h"
#include "Evc.h"
#include <list>




const EVC_DESC EvcDesc[]={

	//0
	{4,		_T("按钮"),		1,3},
	{6,		_T("绳索顶"),	2,2},
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
	{2,		_T("雷管")},
	{2,		_T("敌人/补给品出现")},
	{8,		_T("背景变色触发器")},
	{8,		_T("一次性红外线触发器?[19]")	,4,3},

	//20
	{14,	_T("BOSS引擎?")},
	{6,		_T("红外线触发器?[21]"),	2,3},
	{16,	_T("延时触发簇")	,1,5},
	{12,	_T("金属BOSS-落石循环触发器")	,4,8},
	{4,		_T("大画面特效")},
	{2,		_T("火花/气泡")},
	{4,		_T("二十六")},
	{0,0}
};

const u8 MctrlDefault[64][27]=
{
	//0
	{0x10,0x00,0xFF,0xFF},//OK

	//1
	{0x00,0x30,0x00,0x00,0xFF,0x00},//OK

	//2
	{0x00,0x00},//OK

	//3
	{0x00,0x00},//OK
	{0x00},

	//5
	{0x00,0x00,0x1E,0x00,0x1E,0x00,0x00,0x00,0x00,0x00,0x00,0x00},//OK

	//6
	{0x00,0x00},//OK
	{0x00},
	{0x00},

	//9
	{0x00,0x00},//OK

	//10
	{0x00,0x64},//OK

	//11
	{0x01,0x00},//OK

	//12
	{0x00,0x00},//OK
	{0x00},

	//14
	{0x00,0xFF},//OK

	//15
	{0x00,0xFF},//OK

	//16
	{0xCC,0xCC},//OK

	//17
	{0x00,0x00},//OK
	{0x00},
	{0x00},

	//20
	{0x00},
	{0x00},

	//22
	{0x01,0x00,0xFF,0xFF,0xFF,0xFF
		,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},//OK

	//23
	{0x00,0x00,0x1E,0x00,
		0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},//OK

	//24
	{0x01,0x00,0x0A,0x0A},//OK

	//25
	{0x00,0x00},//OK
	{0x00},
};
int MpeV2I(u16 value,const MCTRL_PARAM_ENUM* mpe)
{
	int i=0;
	while(mpe->value!=MCTRL_PARAM_ENUM_END)
	{
		if(mpe->value==value)
		{
			return i;
		}
		++mpe;
		++i;
	}
	return 0;
}
const MCTRL_PARAM_ENUM MCTRL_EXT_1_STYLE[]=
{
	{0,_T("绳子")},
	{1,_T("绳子?")},
	{2,_T("钢缆")},
	{MCTRL_PARAM_ENUM_END}
};
const MCTRL_PARAM_ENUM MCTRL_EXT_2_MAIN_STYLE[]=
{
	{0,_T("门↑")},
	{1,_T("门→")},
	{2,_T("门←")},
	{3,_T("刺↑")},
	{4,_T("刺↓")},
	{5,_T("刺→")},
	{6,_T("刺←")},
	{7,_T("?")},
	{MCTRL_PARAM_ENUM_END}
};
const MCTRL_PARAM_ENUM MCTRL_EXT_2_EX_STYLE[]=
{
	{0x0,_T("0")},
	{0x1,_T("1")},
	{0x4,_T("4")},
	{0x8,_T("8")},
	{0xC,_T("C")},
	{0xE,_T("E")},
	{MCTRL_PARAM_ENUM_END}
};
const MCTRL_PARAM_ENUM MCTRL_EXT_5_STYLE[]=
{
	{0x00,_T("静止")},
	{0x10,_T("踏上启动")},
	{0x90,_T("踏上损坏")},
	{0xA0,_T("自动")},
	{MCTRL_PARAM_ENUM_END}
};
const MCTRL_PARAM_ENUM MCTRL_EXT_5_SUB_STYLE[]=
{
	{0x0,_T("普通")},
	{0x1,_T("循环")},
	{0x5,_T("终点损坏")},
	{MCTRL_PARAM_ENUM_END}
};

const MCTRL_PARAM_ENUM MCTRL_EXT_6_STYLE[]=
{
	{0x00,_T("待机")},
	{0x10,_T("滚动")},
	{0x50,_T("后续待机")},
	{0x80,_T("领头待机")},
	{0x90,_T("摇摆?")},
	{MCTRL_PARAM_ENUM_END}
};
const MCTRL_PARAM_ENUM MCTRL_EXT_10_STYLE[]=
{
	{0x00,_T("0?")},
	{0x80,_T("8?")},
	{0xC0,_T("C?")},
	{MCTRL_PARAM_ENUM_END}
};
const MCTRL_PARAM_ENUM MCTRL_EXT_14_STYLE[]=
{
	{0,_T("草丛")},
	{1,_T("大草丛")},
	{2,_T("灌木丛")},
	{3,_T("大灌木丛")},
	{4,_T("宽叶")},
	{5,_T("大宽叶")},
	{MCTRL_PARAM_ENUM_END}
};
const MCTRL_PARAM_ENUM MCTRL_EXT_24_STYLE[]=
{
	{0x0001,_T("雪")},
	{0x0000,_T("风A↓")},
	{0x0010,_T("风A↑")},
	{0x0020,_T("风A→")},
	{0x0030,_T("风A←")},
	{0x0100,_T("风B↓")},
	{0x0110,_T("风B↑")},
	{0x0120,_T("风B→")},
	{0x0130,_T("风B←")},
	{MCTRL_PARAM_ENUM_END}
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
	if(*ppMaDeComm)
	{
		(*ppMaDeComm)->pMa->Notify_Mctrl(N_DELETE,i);
		(*ppMaDeComm)->pDe->Notify_Mctrl(N_DELETE,i);
	}
}
u8 SqMctrlPack::NewMctrl()
{
	if(MctrlCount>=MAX_MCTRL_COUNT)
	{
		return 0xFF;
	}
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
void SqMctrlPack::DownMctrl(u8 i)
{
	ASSERT(i+1<MctrlCount);

	MctrlNote t;
	t=pMctrl[i];
	pMctrl[i]=pMctrl[i+1];
	pMctrl[i+1]=t;

	if(*ppMaDeComm)
	{
		(*ppMaDeComm)->pMa->Notify_Mctrl(N_DOWN,i);
		(*ppMaDeComm)->pDe->Notify_Mctrl(N_DOWN,i);
	}
}
void DecodeMctrlParam(u8 class_id,u8 *param,CString &str)
{
	CString str2;
	str=_T("");
#define CASE_DecodeMctrlParam(cid) case cid:{MCTRL_EXT_##cid &p=*((MCTRL_EXT_##cid*)param);
#define BREAK_DecodeMctrlParam break;}
	switch(class_id)
	{
	CASE_DecodeMctrlParam(0)
		str=_T("关联组件ID:");
		for(int i=0;i<p.RelMctrlCount && i<3;++i)
		{
			str2.Format(_T(" %d"),p.RelMctrlIndex[i]);
			str+=str2;
		}
	BREAK_DecodeMctrlParam

	CASE_DecodeMctrlParam(1)
		str=MCTRL_EXT_1_STYLE[MpeV2I(p.Style,MCTRL_EXT_1_STYLE)].name;
		str+=_T("×");
		str2.Format(_T("%d"),p.RopeLength);
		str+=str2;
		if(p.RelMctrlCount)str+=_T(" 关联组件ID:");
		for(int i=0;i<p.RelMctrlCount && i<2;++i)
		{
			str2.Format(_T(" %d"),p.RelMctrlIndex[i]);
			str+=str2;
		}
	BREAK_DecodeMctrlParam

	CASE_DecodeMctrlParam(2)
		str=MCTRL_EXT_2_MAIN_STYLE[MpeV2I(p.MainStyle,MCTRL_EXT_2_MAIN_STYLE)].name;
		if(p.Reverse)str+=_T("[开关反转]");
		str2.Format(_T(" 保持时间:%d"),p.HoldTime);
		str+=str2;
	BREAK_DecodeMctrlParam

	CASE_DecodeMctrlParam(3)
		if(p.Flag_Unk)str=_T("未知选项 ");
		if(p.Flag_Fall)str+=_T("一踩就掉落");
	BREAK_DecodeMctrlParam

	CASE_DecodeMctrlParam(6)
		str=MCTRL_EXT_6_STYLE[MpeV2I(p.Style,MCTRL_EXT_6_STYLE)].name;
	BREAK_DecodeMctrlParam

	CASE_DecodeMctrlParam(10)
	str.Format(_T("时间:%d"),p.Time);
	BREAK_DecodeMctrlParam
	CASE_DecodeMctrlParam(11)
		switch(p.Style)
		{
		case 1:str=_T("任意方向");break;
		case 0*36:str=_T("↑");break;
		case 1*36:str=_T("↗");break;
		case 2*36:str=_T("→");break;
		case 3*36:str=_T("↘");break;
		case 4*36:str=_T("↓");break;
		case 5*36:str=_T("↙");break;
		case 6*36:str=_T("←");break;
		case 7*36:str=_T("↖");break;
		}
	BREAK_DecodeMctrlParam

	CASE_DecodeMctrlParam(12)
		str.Format(_T("目标Step%02d,Door%d"),p.DestStep,p.DestDoor);
	BREAK_DecodeMctrlParam

	CASE_DecodeMctrlParam(14)
		str=MCTRL_EXT_14_STYLE[MpeV2I(p.Style,MCTRL_EXT_14_STYLE)].name;
		str2.Format(_T(" 关联%sID:%d"),
			p.IsSup?_T("补给品"):_T("敌人"),
			p.RelFoeSupIndex);
		str+=str2;
	BREAK_DecodeMctrlParam
	CASE_DecodeMctrlParam(15)
		str.Format(_T("关联%sID:%d"),
			p.IsSup_LSL4&MCTRL_EXT_15_ISSUP?_T("补给品"):_T("敌人"),
			p.RelFoeSupIndex);
	BREAK_DecodeMctrlParam

	CASE_DecodeMctrlParam(17)
		str.Format(_T("关联%sID:%d"),
			p.IsSup?_T("补给品"):_T("敌人"),
			p.RelFoeSupIndex);
		if(p.Dust)str=_T("[扬尘]")+str;
	BREAK_DecodeMctrlParam
	
	CASE_DecodeMctrlParam(22)
		if(p.WaitBoss)str=_T("等待BOSS死亡 ");
		str+=_T("关联组件ID[时间]:");
		for(int i=0;i<(p.RelMctrlCount)&& i<5;++i)
		{
			str2.Format(_T(" %d[%d]"),p.RelMctrlIndex[i],p.TimeDelta[i]);
			str+=str2;
		}
	BREAK_DecodeMctrlParam

	CASE_DecodeMctrlParam(23)
		str+=_T("关联组件ID:");
		for(int i=0;i<8;++i)
		{
			if(p.RelMctrlIndex[i]!=255)str2.Format(_T(" %d"),p.RelMctrlIndex[i]);
			else str2=_T(" *");
			str+=str2;
		}
	BREAK_DecodeMctrlParam

	CASE_DecodeMctrlParam(24)
		str=MCTRL_EXT_24_STYLE[MpeV2I(p.Style,MCTRL_EXT_24_STYLE)].name;
		str2.Format(_T(" %d*%d"),p.Width,p.Height);
		str+=str2;
	BREAK_DecodeMctrlParam

	CASE_DecodeMctrlParam(25)
		if(p.Style)str=_T("火花");else str=_T("气泡");
	BREAK_DecodeMctrlParam

	default:
		for(int i=0;i<EvcDesc[class_id].DataLen;++i)
		{
			str2.Format(_T("%02X "),param[i]);
			str+=str2;
		}
	}
}