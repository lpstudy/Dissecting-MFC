#include <string.h>
#include <iostream>
#include "my.h"
using namespace std;
extern CMyWinApp theApp;

CRuntimeClass* CRuntimeClass::pFirstClass = NULL;
//AFX_ASSINIT这个对象一个类会有一个静态对象，不过它的作用域却不是位于类中，而是位于文件的，通过这个静态对象自身调用其构造函数来完成链表的连接过程
AFX_CLASSINIT::AFX_CLASSINIT(CRuntimeClass* pNewClass)
{
	pNewClass->m_pNextClass = CRuntimeClass::pFirstClass;
	CRuntimeClass::pFirstClass = pNewClass;
}

//CObject的头部需要特殊处理，
static char szCObject[] = "CObject";
struct CRuntimeClass CObject::classCObject =
{ szCObject, sizeof(CObject), 0xffff, NULL, NULL };
static AFX_CLASSINIT _init_CObject(&CObject::classCObject);
CRuntimeClass* CObject::GetRuntimeClass() const
{
	return &CObject::classCObject;
}

IMPLEMENT_DYNAMIC(CCmdTarget, CObject)
IMPLEMENT_DYNAMIC(CWinThread, CCmdTarget)
IMPLEMENT_DYNAMIC(CWinApp, CWinThread)
IMPLEMENT_DYNCREATE(CWnd, CCmdTarget) // 其实在MFC 它是IMPLEMENT_DYNCREATE()，见节。
IMPLEMENT_DYNCREATE(CFrameWnd, CWnd) // 其实在MFC 它是IMPLEMENT_DYNCREATE()，见节。
IMPLEMENT_DYNAMIC(CDocument, CCmdTarget)
IMPLEMENT_DYNAMIC(CView, CWnd)

// in implementation file
BOOL CObject::IsKindOf(const CRuntimeClass* pClass) const
{
	CRuntimeClass* pClassThis = GetRuntimeClass();
	while (pClassThis != NULL)
	{
		if (pClassThis == pClass)
			return TRUE;
		pClassThis = pClassThis->m_pBaseClass;
	}
	return FALSE; // walked to the top, no match
}
void PrintAllClasses()
{
	CRuntimeClass* pClass;
	// just walk through the simple list of registered classes
	for (pClass = CRuntimeClass::pFirstClass; pClass != NULL;
		pClass = pClass->m_pNextClass)
	{
		TRACE_FUCTION_AND_LINE("%s", pClass->m_lpszClassName);
		TRACE_FUCTION_AND_LINE("%d", pClass->m_nObjectSize);
		TRACE_FUCTION_AND_LINE("%d", pClass->m_wSchema);
	}
}
// in implementation file
CObject* CRuntimeClass::CreateObject()
{
	if (m_pfnCreateObject == NULL)
	{
		TRACE_FUCTION_AND_LINE("Error: Trying to create object which is not "
			"DECLARE_DYNCREATE \nor DECLARE_SERIAL: %s.\n",
			m_lpszClassName);
		return NULL;
	}
	CObject* pObject = NULL;
	pObject = (*m_pfnCreateObject)();
	return pObject;
}
//从文件中load
CRuntimeClass* PASCAL CRuntimeClass::Load(CArchive& ar, UINT* pwSchemaNum)
{
	WORD nLen = 0;
	char szClassName[64];
	CRuntimeClass* pClass;
	char c = '|';
	int SchemaNum = 0;
	ar >> (WORD&)SchemaNum >>  c >> nLen >> c;//类标识,类名长度

	*pwSchemaNum = SchemaNum;
	if (nLen >= sizeof(szClassName) || ar.Read(szClassName, nLen) != nLen)//类名称
		return NULL;
	szClassName[nLen] = '\0';
	for (pClass = pFirstClass; pClass != NULL; pClass = pClass->m_pNextClass)
	{
		if (strcmp(szClassName, pClass->m_lpszClassName) == 0)//获取类名称对应的 CRuntimeClass
		{
			ar >> c;
			return pClass;
		}
	}
	ar >> c;
	return NULL; // not found
}
//保存类描述
void CRuntimeClass::Store(CArchive& ar) const
// stores a runtime class description
{
	WORD nLen = (WORD)strlen(m_lpszClassName);
	char c= '|';
	ar << (WORD)m_wSchema <<c<< nLen<<c;
	ar.Write(m_lpszClassName, nLen*sizeof(char));
	ar << c;
}

CWinApp* AfxGetApp()
{
	return theApp.m_pCurrentWinApp;
}

BEGIN_MESSAGE_MAP(CWnd, CCmdTarget)
	ON_COMMAND(CWndid, 0)
END_MESSAGE_MAP()
BEGIN_MESSAGE_MAP(CFrameWnd, CWnd)
	ON_COMMAND(CFrameWndid, 0)
END_MESSAGE_MAP()
BEGIN_MESSAGE_MAP(CDocument, CCmdTarget)
	ON_COMMAND(CDocumentid, 0)
END_MESSAGE_MAP()
BEGIN_MESSAGE_MAP(CView, CWnd)
	ON_COMMAND(CViewid, 0)
	ON_NON_COMMAND(WM_PAINT, 0, &CView::OnPaint)
END_MESSAGE_MAP()
BEGIN_MESSAGE_MAP(CWinApp, CCmdTarget)
	ON_COMMAND(CWinAppid, 0)
END_MESSAGE_MAP()

AFX_MSGMAP* CCmdTarget::GetMessageMap() const
{
	return &CCmdTarget::messageMap;
}
AFX_MSGMAP CCmdTarget::messageMap =
{
	NULL,
	&CCmdTarget::_messageEntries[0]
};
AFX_MSGMAP_ENTRY CCmdTarget::_messageEntries[] =
{
	{ 0, 0, CCmdTargetid, 0, AfxSig_end, 0 }
};

//command routing
LRESULT AfxWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam,
				   CWnd *pWnd) // last param. pWnd is added by JJHou.
{
	TRACE_FUCTION_AND_LINE("AfxWndProc()");
	return AfxCallWndProc(pWnd, hWnd, nMsg, wParam, lParam);
}
LRESULT AfxCallWndProc(CWnd* pWnd, HWND hWnd, UINT nMsg,
					   WPARAM wParam, LPARAM lParam)
{
	TRACE_FUCTION_AND_LINE("AfxCallWndProc()");
	LRESULT lResult = pWnd->WindowProc(nMsg, wParam, lParam);
	return lResult;
}