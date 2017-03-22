#include "log.h"
#include "typedef.h"


//CObject
class CObject
{
public:
	CObject()
	{
		TRACE_FUCTION_AND_LINE("");
	}
	~CObject()
	{
		TRACE_FUCTION_AND_LINE("");
	}
};

//CCmdTarget
class CCmdTarget : public CObject
{
public:
	CCmdTarget()
	{
		TRACE_FUCTION_AND_LINE("");
	}
	~CCmdTarget()
	{
		TRACE_FUCTION_AND_LINE("");
	}
};

//CWinThread
class CWinThread : public CCmdTarget
{
public:
	CWinThread()
	{
		TRACE_FUCTION_AND_LINE("");
	}
	~CWinThread()
	{
		TRACE_FUCTION_AND_LINE("");
	}

public:
	virtual BOOL InitInstance()
	{
		TRACE_FUCTION_AND_LINE("");
		return true;
	}
	virtual int Run()
	{
		TRACE_FUCTION_AND_LINE("");
		return 1;
	}
};

class CWnd;

//CWinApp
class CWinApp : public CWinThread
{
public:
	CWinApp* m_pCurrentWinApp;
	CWnd*    m_pMainWnd;
public:
	CWinApp()
	{
		m_pCurrentWinApp = this;
		TRACE_FUCTION_AND_LINE("");
	}
	~CWinApp()
	{
		TRACE_FUCTION_AND_LINE("");
	}

public:
	virtual BOOL InitInstance()
	{
		TRACE_FUCTION_AND_LINE("");
		return true;
	}
	virtual BOOL InitApplication()
	{
		TRACE_FUCTION_AND_LINE("");
		return true;
	}
	virtual int Run()
	{
		TRACE_FUCTION_AND_LINE("");
		CWinThread::Run();
		return 1;
	}
};
//CObject->CCmdTarget->CWinThread->CWinApp

//CDocument
class CDocument : public CCmdTarget
{
public:
	CDocument()
	{
		TRACE_FUCTION_AND_LINE("");
	}
	~CDocument()
	{
		TRACE_FUCTION_AND_LINE("");
	}
};
//CObject->CCmdTarget->CDocument

//CWnd
class CWnd : public CCmdTarget
{
public:
	CWnd()
	{
		TRACE_FUCTION_AND_LINE("");
	}
	~CWnd()
	{
		TRACE_FUCTION_AND_LINE("");
	}

public:
	virtual BOOL Create()
	{
		TRACE_FUCTION_AND_LINE("");
		return 1;
	}
	BOOL CreateEx()
	{
		TRACE_FUCTION_AND_LINE("");
		PreCreateWindow();
		return true;
	}
	virtual BOOL PreCreateWindow()
	{
		TRACE_FUCTION_AND_LINE("");
		return true;
	}
};

//CFrameWnd
class CFrameWnd : public CWnd
{
public:
	CFrameWnd()
	{
		TRACE_FUCTION_AND_LINE("");
	}
	~CFrameWnd()
	{
		TRACE_FUCTION_AND_LINE("");
	}

public:
	BOOL Create()
	{
		TRACE_FUCTION_AND_LINE("");
		CreateEx();
		return TRUE;
	}
	virtual BOOL PreCreateWindow()
	{
		TRACE_FUCTION_AND_LINE("");
		return true;
	}
};

//CView
class CView : public CWnd
{
public:
	CView()
	{
		TRACE_FUCTION_AND_LINE("");
	}
	~CView()
	{
		TRACE_FUCTION_AND_LINE("");
	}
};
//CObject->CCmdTarget->CWnd->(CFrameWnd,CView)

CWinApp* AfxGetApp();