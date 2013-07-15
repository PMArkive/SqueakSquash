#pragma once



class CWndWait : public CFrameWnd
{
	DECLARE_DYNCREATE(CWndWait)
protected:
	CWndWait();          
	virtual ~CWndWait();
	static CWndWait WndWait;
	static bool wwshowed;
	static DWORD WINAPI WndWaitThread(LPVOID lpThreadParameter);
public:
	static void InitWndWait();
	static void ShowWndWait();
	static void HideWndWait();

protected:
	DECLARE_MESSAGE_MAP()
};

