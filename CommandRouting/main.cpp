#include "my.h"

int main()
{
	CWinApp* pApp = AfxGetApp();

	pApp->InitApplication();
	pApp->InitInstance();
	pApp->Run();

	CMyDoc* pMyDoc = new CMyDoc;
	CMyView* pMyView = new CMyView;
	CFrameWnd* pMyFrame = (CFrameWnd*)pApp->m_pMainWnd;
	pMyFrame->m_pViewActive = pMyView;
	pMyView->m_pDocument = pMyDoc;

	// test Message Routing
	cout << endl << "pMyFrame received a WM_CREATE, routing path :" << endl;
	AfxWndProc(0, WM_CREATE, 0, 0, pMyFrame);

	cout << endl << "pMyView received a WM_PAINT, routing path :" << endl;
	AfxWndProc(0, WM_PAINT, 0, 0, pMyView);

	cout << endl << "pMyView received a WM_COMMAND, routing path :" << endl;
	AfxWndProc(0, WM_COMMAND, 0, 0, pMyView);

	cout << endl << "pMyFrame received a WM_COMMAND, routing path :" << endl;
	AfxWndProc(0, WM_COMMAND, 0, 0, pMyFrame);
	return 0;
}