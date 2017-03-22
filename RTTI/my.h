#ifndef __MY__H__
#define __MY__H__
#include "mfc.h"

class CMyFrameWnd;


//CMyFrameWnd
class CMyFrameWnd : public CFrameWnd
{
	DECLARE_DYNAMIC(CMyFrameWnd)
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
//CMyDoc
class CMyDoc : public CDocument
{
	DECLARE_DYNAMIC(CMyDoc)
public:
	CMyDoc()
	{
		TRACE_FUCTION_AND_LINE("");
	}
	~CMyDoc()
	{
		TRACE_FUCTION_AND_LINE("");
	}

};
//CMyView
class CMyView : public CView
{
	DECLARE_DYNAMIC(CMyView)
public:
	CMyView()
	{
		TRACE_FUCTION_AND_LINE("");
	}
	~CMyView()
	{
		TRACE_FUCTION_AND_LINE("");
	}

};
#endif//__MY__H__
