#ifndef __MFC__H__
#define __MFC__H__
#include "log.h"
#include "typedef.h"
//每一个类有一个CRuntimeClass静态对象，于是又多少个类，就有多少个CRuntimeClass对象
//所有类的CRuntimeClass对象组成一个链表，链表的头部又是一个静态指针对象。
//于是整个mfc就只有一个链表头部静态指针对象,pFirstClass
struct CRuntimeClass;
class CObject;

struct AFX_CLASSINIT
{ AFX_CLASSINIT(CRuntimeClass* pNewClass); };

struct CRuntimeClass
{
	// Attributes
	LPCSTR m_lpszClassName;
	int m_nObjectSize;
	UINT m_wSchema; // schema number of the loaded class
	CObject* (PASCAL* m_pfnCreateObject)(); // NULL => abstract class
	CRuntimeClass* m_pBaseClass;
	// CRuntimeClass objects linked together in simple list
	static CRuntimeClass* pFirstClass; // start of class list
	CRuntimeClass* m_pNextClass; // linked list of registered classes
};

#define DECLARE_DYNAMIC(class_name) \
public: \
	static CRuntimeClass class##class_name; \
	virtual CRuntimeClass* GetRuntimeClass() const;

#define RUNTIME_CLASS(class_name) \
	(&class_name::class##class_name)

#define IMPLEMENT_DYNAMIC(class_name, base_class_name) \
	_IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, NULL)

#define _IMPLEMENT_RUNTIMECLASS(class_name, base_class_name,wSchema,pfnNew) \
	static char _lpsz##class_name[] = #class_name; \
	CRuntimeClass class_name::class##class_name = { \
	_lpsz##class_name, sizeof(class_name), wSchema, pfnNew, \
	RUNTIME_CLASS(base_class_name), NULL }; \
	static AFX_CLASSINIT _init_##class_name(&class_name::class##class_name); \
	CRuntimeClass* class_name::GetRuntimeClass() const \
	{ return &class_name::class##class_name; } \


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
public:
	virtual CRuntimeClass* GetRuntimeClass() const;
	BOOL IsKindOf(const CRuntimeClass* pClass) const;
public:
	static CRuntimeClass classCObject;
};

//CCmdTarget
class CCmdTarget : public CObject
{
	DECLARE_DYNAMIC(CCmdTarget)
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
	DECLARE_DYNAMIC(CWinThread)
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
	DECLARE_DYNAMIC(CWinApp)
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
	DECLARE_DYNAMIC(CDocument)
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
	DECLARE_DYNAMIC(CWnd)
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
	DECLARE_DYNAMIC(CFrameWnd)
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
	DECLARE_DYNAMIC(CView)
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

void PrintAllClasses();
CWinApp* AfxGetApp();

#endif//__MFC__H__
