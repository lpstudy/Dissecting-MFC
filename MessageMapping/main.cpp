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

	// output Message Map construction
	AFX_MSGMAP* pMessageMap = pMyView->GetMessageMap();
	cout << endl << "CMyView Message Map : " << endl;
	MsgMapPrinting(pMessageMap);

	pMessageMap = pMyDoc->GetMessageMap();
	cout << endl << "CMyDoc Message Map : " << endl;
	MsgMapPrinting(pMessageMap);

	pMessageMap = pMyFrame->GetMessageMap();
	cout << endl << "CMyFrameWnd Message Map : " << endl;
	MsgMapPrinting(pMessageMap);

	pMessageMap = pApp->GetMessageMap();
	cout << endl << "CMyWinApp Message Map : " << endl;
	MsgMapPrinting(pMessageMap);
	return 0;
}