#include "my.h"

int main()
{
	CWinApp* pApp = AfxGetApp();

	pApp->InitApplication();
	pApp->InitInstance();
	pApp->Run();
	PrintAllClasses();


	//以下isKindOf利用的是类继承的特性，传进去类的静态数据成员RunTimeClass指针，然后判定this一直到最高的父类是否等于此RunTimeClass指针。
	CMyDoc* pMyDoc   = new CMyDoc;
	TRACE_FUCTION_AND_LINE("pMyDoc------");
	TRACE_FUCTION_AND_LINE("CMyDoc:%d", pMyDoc->IsKindOf(RUNTIME_CLASS(CMyDoc))); //1
	TRACE_FUCTION_AND_LINE("CDocument:%d",pMyDoc->IsKindOf(RUNTIME_CLASS(CDocument)));//1
	TRACE_FUCTION_AND_LINE("CCmdTarget:%d",pMyDoc->IsKindOf(RUNTIME_CLASS(CCmdTarget)));//1
	TRACE_FUCTION_AND_LINE("CObject:%d", pMyDoc->IsKindOf(RUNTIME_CLASS(CObject)));//1
	TRACE_FUCTION_AND_LINE("CWinApp:%d",pMyDoc->IsKindOf(RUNTIME_CLASS(CWinApp)));// 0
	TRACE_FUCTION_AND_LINE("CView:%d",pMyDoc->IsKindOf(RUNTIME_CLASS(CView)));// 0
	CMyView* pMyView = new CMyView;
	TRACE_FUCTION_AND_LINE("pMyView------");
	TRACE_FUCTION_AND_LINE("CView:%d",pMyView->IsKindOf(RUNTIME_CLASS(CView)));// 1
	TRACE_FUCTION_AND_LINE("CObject:%d",pMyView->IsKindOf(RUNTIME_CLASS(CObject)));// 1
	TRACE_FUCTION_AND_LINE("CWnd:%d",pMyView->IsKindOf(RUNTIME_CLASS(CWnd)));//1
	TRACE_FUCTION_AND_LINE("CFrameWnd:%d",pMyView->IsKindOf(RUNTIME_CLASS(CFrameWnd)));// 0
	CMyFrameWnd* pMyWnd = new CMyFrameWnd;
	TRACE_FUCTION_AND_LINE("pMyFrameWnd------");
	TRACE_FUCTION_AND_LINE("CFrameWnd:%d",pMyWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd)));// 1
	return 0;
}