#include "my.h"

extern CMyWinApp theApp;

CRuntimeClass* CRuntimeClass::pFirstClass = NULL;
//AFX_ASSINIT�������һ�������һ����̬���󣬲�������������ȴ����λ�����У�����λ���ļ��ģ�ͨ�������̬������������乹�캯���������������ӹ���
AFX_CLASSINIT::AFX_CLASSINIT(CRuntimeClass* pNewClass)
{
	pNewClass->m_pNextClass = CRuntimeClass::pFirstClass;
	CRuntimeClass::pFirstClass = pNewClass;
}

//CObject��ͷ����Ҫ���⴦��
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
IMPLEMENT_DYNAMIC(CWnd, CCmdTarget) // ��ʵ��MFC ����IMPLEMENT_DYNCREATE()�����ڡ�
IMPLEMENT_DYNAMIC(CFrameWnd, CWnd) // ��ʵ��MFC ����IMPLEMENT_DYNCREATE()�����ڡ�
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

CWinApp* AfxGetApp()
{
	return theApp.m_pCurrentWinApp;
}