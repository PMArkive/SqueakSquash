﻿//UTF8♔
#include "stdafx.h"

void GetTreasureName(u8 code,CString &str)
{
	if(code==120)
	{
		str=_T("[Crash]");
	}
	else if(code==119)
	{
		str=_T("蛋糕");
	}
	else if(code>97)
	{
		str.Format(_T("拼图%d"),code-97);
	}
	else if(code>92)
	{
		str.Format(_T("地图%d"),code-92);
	}
	else if(code>87)
	{
		str.Format(_T("背景%d"),code-87);
	}
	else if(code>69)
	{
		str.Format(_T("喷漆%d"),code-69);
	}
	else if(code>61)
	{
		str.Format(_T("过关证明%d"),code-61);
	}
	else if(code>50)
	{
		str.Format(_T("乐谱%d"),code-50);
	}
	else if(code>27)
	{
		str.Format(_T("卷轴%d"),code-27);
	}
	else if(code>20)
	{
		str.Format(_T("幽灵%d"),code-20);
	}
	else if(code>13)
	{
		str.Format(_T("钥匙%d"),code-13);
	}
	else if(code>5)
	{
		str.Format(_T("生命之心%d"),code-5);
	}
	else if(code==5)
	{
		str=_T("CD");
	}
	else
	{
		str.Format(_T("封印之心%d"),code+1);
	}
}