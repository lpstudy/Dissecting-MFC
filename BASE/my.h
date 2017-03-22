#ifndef __MY__H__
#define __MY__H__
#include "mfc.h"

class CMyFrameWnd;


//CMyFrameWnd
class CMyFrameWnd : public CFrameWnd
{
public:
	CMyFrameWnd()
	{
		TRACE_FUCTION_AND_LINE("");
		Create();
	}
	~CMyFrameWnd()
	{
		TRACE_FUCTION_AND_LINE("");
	}
};

//CMyWinApp
class CMyWinApp : public CWinApp
{
public:
	CMyWinApp()
	{
		TRACE_FUCTION_AND_LINE("0x%p", this);
	}
	~CMyWinApp()
	{
		TRACE_FUCTION_AND_LINE("");
	}

public:
	virtual BOOL InitInstance()
	{
		TRACE_FUCTION_AND_LINE("");
		m_pMainWnd = new CMyFrameWnd;
		return TRUE;
	}
};
#endif//__MY__H__
