﻿

//UTF8♔

#include "stdafx.h"
#include "Bgm.h"

TCHAR* GetBgmName(u8 code)
{
	switch(code)
	{
	case 0:return _T("Music#04 (主菜单)");
	case 1:return _T("Music#06 (主地图)");
	case 2:return _T("Music#24 (Vegetable Valley)");
	case 3:return _T("Music#25 (Icecream Island)");
	case 4:return _T("Music#08 (Nature Area)");
	case 5:return _T("Music#26 (卷心菜洞穴 Cabbage Cavern)");
	case 6:return _T("Music#27 (糖果星宿 Candy Constellation)");
	case 7:return _T("Music#28 (小萝卜遗迹 Radish Ruins)");
	case 8:return _T("Music#29 (Butter Building)");
	case 9:return _T("Music#15 (Green Greens)");
	case 10:return _T("Music#16");
	case 11:return _T("Music#17");
	case 12:return _T("Music#10");
	case 13:return _T("Music#11 (传送星)");
	case 14:return _T("[无编号]胜利1");
	case 15:return _T("[无编号]胜利2");
	case 16:return _T("[无编号]失败");
	case 17:return _T("Music#09 (无敌)");
	case 18:return _T("Music#09 (无敌2)");
	case 19:return _T("Music#34");
	case 20:return _T("Music#19");
	case 21:return _T("Music#20 (VS Dedede)");
	case 22:return _T("Music#12 (卡比舞)");
	case 23:return _T("Music#13 (卡比舞2)");
	case 24:return _T("Music#22 (呐喊团主题)");
	case 25:return _T("Music#07 (子地图)");
	case 26:return _T("Music#14 (第一关)");
	case 27:return _T("Music#18");
	case 28:return _T("Music#31");
	case 29:return _T("[无编号]Level8");
	case 30:return _T("Music#30 (飞天赛车某曲)");
	case 31:return _T("Music#35 (黑星1)");
	case 32:return _T("Music#05 (标题页)");
	case 33:return _T("Music#21");
	case 34:return _T("Music#23");
	case 35:return _T("Music#01 (小游戏)");
	case 36:return _T("Music#02 (Float Islands)");
	case 37:return _T("Music#36 (黑星2)");
	case 38:return _T("Music#32 (The End)");
	case 39:return _T("Music#03 ");
	case 40:return _T("[无编号]Level3-Stage5");
	case 41:return _T("Music#33 (死亡)");
	case 42:return _T("Music#00");
	case 43:return _T("[后面的似乎都是音效]");
	case 255:return _T("无");
	default:return _T("?");
	}
}