#pragma once

class SqMa
{
private:
	struct GridData
	{
		u16 gra[3];
		u32 det[3];
	};
	enum{
		MAGIC=0x614D,//"Ma"
	};
public:
	struct BLOCK_MAPPING
	{
		u16 mapping[4];
	};
	
	struct Header
	{
		u16 Magic;
		u16 HeaderSize;//=0x44
		u8 LevelD;
		u8 StageD;
		u16 x06;//=0x0101
		u8 Boss;
		u8 x09;//?
		u8 x0A;//?
		u8 Bgm;
		u32 SectionOff[13];
		u32 x40;//=0
	};
	SqMa(void);
	~SqMa(void);
	
	bool Load(const u8* psrc);
	bool IsLoaded();
	void Unload();

	GridData & Grid(u8 x,u8 y);
	u8 GetW();
	u8 GetH();
	BLOCK_MAPPING & BlockMappingA(u16 i);
	BLOCK_MAPPING & BlockMappingB(u16 i);
private:
	u8 w,h;
	GridData *pGrid;
	u16 BlockMappingCountA,BlockMappingCountB;
	BLOCK_MAPPING *pBlockMappingA,*pBlockMappingB;
	
};