#include "stdafx.h"
#include "SqPl1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

SqPl1::SqPl1():loaded(false)
{
	ZeroMemory(PlLineList,sizeof(PlLineList));
}

SqPl1::~SqPl1()
{
	Unload();
}
void SqPl1::Unload()
{
	if(!loaded)return;
	for(u8 i=0;i<16;++i)
	{
		if(PlLineList[i].FrameCount)
		{
			delete[] PlLineList[i].FrameList;
		}
	}
	ZeroMemory(PlLineList,sizeof(PlLineList));
}
bool SqPl1::IsLoaded(){return loaded;}
bool SqPl1::Load(const u8* psrc)
{
	if(*(u16*)psrc!=1)return false;
	psrc+=2;
	Unload();
	u16 LineCount=*(u16*)psrc;psrc+=2;
	ASSERT(LineCount<17);
	u8 line,framecount;
	for(u16 l=0;l<LineCount;++l)
	{
		line=*(psrc++);
		framecount=*(psrc++);
		ASSERT(line<16||!PlLineList[line].FrameCount);
		PlLineList[line].FrameCount=framecount;
		//ASSERT(framecount<17);
		PlLineList[line].FrameList=new PlFrame[framecount];
		for(u8 i=0;i<framecount;++i)PlLineList[line].FrameList[i].Time=*(psrc++);
		if(framecount&1)++psrc;
		for(u8 i=0;i<framecount;++i){memcpy(PlLineList[line].FrameList[i].Pl,psrc,32);psrc+=32;}
	}
	loaded=true;
	return true;
}
u8 SqPl1::GetFrameCount(u8 Line)
{
	ASSERT(loaded);
	ASSERT(Line<16);
	return PlLineList[Line].FrameCount;
}
SqPl1::PlFrame& SqPl1::GetFrame(u8 Line,u8 FrameIdx)
{
	ASSERT(loaded);
	ASSERT(Line<16);
	ASSERT(FrameIdx<PlLineList[Line].FrameCount);
	return PlLineList[Line].FrameList[FrameIdx];
}