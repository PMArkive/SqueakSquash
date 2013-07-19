#include "stdafx.h"

#include "Det.h"

const DetDesc DetDesc0[]=
{
	{0x00000000,_T("Air"),				0,0},	

	{0x00810000,_T("Fuse←"),			2,1},
	{0x00820000,_T("Fuse→"),			3,1},		
	{0x00830000,_T("Fuse─"),			7,1},
	{0x00840000,_T("Fuse↑"),			0,1},
	{0x00850000,_T("Fuse┌"),			5,1},
	{0x00860000,_T("Fuse┐"),			6,1},
	{0x00880000,_T("Fuse↓"),			1,1},
	{0x00890000,_T("Fuse└"),			8,1},
	{0x008A0000,_T("Fuse┘"),			9,1},
	{0x008C0000,_T("Fuse│"),			4,1},

	{0x03000000,_T("Walk"),				0,2},
	{0x19000000,_T("Snow cover"),		5,2},
	{0x29000000,_T("Ice Block?"),		5,0},

	{0x38400000,_T("Rop"),				1,3},
	{0x38410000,_T("Rop Bottom"),		2,3},
	{0x38420000,_T("Rop Top"),			0,3},
	{0x38440000,_T("Steel rop"),		4,3},
	{0x38450000,_T("Steel rop Bottom"),	5,3},
	{0x38460000,_T("Steel rop Top"),	3,3},
	{0x38480000,_T("?Organ rop"),		7,3},
	{0x38490000,_T("?Organ rop Bottom"),8,3},
	{0x384A0000,_T("?Organ rop Top"),	6,3},

	{0x42000000,_T("Spark"),			0,4},
	{0x80000000,_T("Flame"),			5,4},
	{0x00000400,_T("?"),				0,5},

	{0x38000800,_T("Chain fire"),		5,5},
	{0x38001000,_T("Chain bomb"),		6,5},
	{0x38004800,_T("Fire block"),		7,5},
	{0x38005000,_T("Bomb block"),		8,5},

	{0x00004000,_T("Soil block"),		0,6},
	{0x01004000,_T("Hard block"),		1,6},
	{0x02004000,_T("Steel block"),		2,6},
	{0x03004000,_T("Steel block///"),	3,6},
	{0x04004000,_T("Star block"),		4,6},
	{0x05004000,_T("Big star block 0"),	5,6},
	{0x05104000,_T("Big star block 1"),	6,6},
	{0x05204000,_T("Big star block 2"),	7,6},
	{0x05304000,_T("Big star block 3"),	8,6},
	{0x08004000,_T("Soil"),				0,7},
	{0x10004000,_T("Sand"),				1,7},
	{0x18004000,_T("Snow"),				2,7},
	{0x20004000,_T("Cloud"),			3,7},
	{0x28004000,_T("2-hit Ice Block"),	4,7},
	{0x30004000,_T("2-hit Block"),		5,7},
	{0x39004000,_T("Pile"),				6,7},
	{0x3A004000,_T("?Elechain"),		7,7},

	{0x2000C028,_T("Cloud 0"),0,8},
	{0x2000C068,_T("Cloud 1"),1,8},
	{0x2000C0A8,_T("Cloud 2"),2,8},
	{0x2000C0E8,_T("Cloud 3"),3,8},



	{0xFFFFFFFF}
};


const DetDesc* GetDet0Desc(u32 code)
{
	for(int i=0;DetDesc0[i].code!=0xFFFFFFFF;++i)
	{
		if(DetDesc0[i].code==code){
			return &DetDesc0[i];
		}
	}
	return 0;
}