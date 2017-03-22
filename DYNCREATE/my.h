#ifndef __MY__H__
#define __MY__H__
#include "mfc.h"

class CMyFrameWnd;


//CMyFrameWnd
class CMyFrameWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CMyFrameWnd)
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
public:
	virtual void SayHello()
	{
		TRACE_FUCTION_AND_LINE("Hello!");
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
public:
	virtual void SayHello()
	{
		TRACE_FUCTION_AND_LINE("Hello!");
	}
};
//CMyDoc
class CMyDoc : public CDocument
{
	DECLARE_DYNCREATE(CMyDoc)
public:
	CMyDoc()
	{
		TRACE_FUCTION_AND_LINE("");
	}
	~CMyDoc()
	{
		TRACE_FUCTION_AND_LINE("");
	}
public:
	virtual void SayHello()
	{
		TRACE_FUCTION_AND_LINE("Hello!");
	}
};
//CMyView
class CMyView : public CView
{
	DECLARE_DYNCREATE(CMyView)
public:
	CMyView()
	{
		TRACE_FUCTION_AND_LINE("");
	}
	~CMyView()
	{
		TRACE_FUCTION_AND_LINE("");
	}
public:
	virtual void SayHello()
	{
		TRACE_FUCTION_AND_LINE("Hello!");
	}
};
#endif//__MY__H__
