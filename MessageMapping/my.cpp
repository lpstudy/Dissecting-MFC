#include "my.h"

CMyWinApp theApp;

IMPLEMENT_DYNCREATE(CMyFrameWnd, CFrameWnd)
IMPLEMENT_DYNCREATE(CMyDoc, CDocument)
IMPLEMENT_DYNCREATE(CMyView, CView)
IMPLEMENT_SERIAL(CStroke, CObject, 1000)
IMPLEMENT_SERIAL(CRectangle, CObject, 10000)
IMPLEMENT_SERIAL(CCircle, CObject, 10000)

BEGIN_MESSAGE_MAP(CMyWinApp, CWinApp)
	ON_COMMAND(CMyWinAppid, 0)
END_MESSAGE_MAP()
BEGIN_MESSAGE_MAP(CMyFrameWnd, CFrameWnd)
	ON_COMMAND(CMyFrameWndid, 0)
END_MESSAGE_MAP()
BEGIN_MESSAGE_MAP(CMyDoc, CDocument)
	ON_COMMAND(CMyDocid, 0)
END_MESSAGE_MAP()
BEGIN_MESSAGE_MAP(CMyView, CView)
	ON_COMMAND(CMyViewid, 0)
END_MESSAGE_MAP()


void printlpEntries(AFX_MSGMAP_ENTRY* lpEntry)
{
	struct {
		int classid;
		char* classname;
	} classinfo[] = {
		CCmdTargetid, "CCmdTarget",
		CWinThreadid, "CWinThread",
		CWinAppid, "CWinApp",
		CMyWinAppid, "CMyWinApp",
		CWndid, "CWnd",
		CFrameWndid, "CFrameWnd",
		CMyFrameWndid, "CMyFrameWnd",
		CViewid, "CView",
		CMyViewid, "CMyView",
		CDocumentid, "CDocument",
		CMyDocid, "CMyDoc",
		0, " "
	};

	for (int i=0; classinfo[i].classid != 0; i++)
	{
		if (classinfo[i].classid == lpEntry->nID)
		{
			cout << lpEntry->nID << " ";
			cout << classinfo[i].classname << endl;
			break;
		}
	}
}

void MsgMapPrinting(AFX_MSGMAP* pMessageMap)
{
	for(; pMessageMap != NULL; pMessageMap = pMessageMap->pBaseMessageMap) {
		AFX_MSGMAP_ENTRY* lpEntry = pMessageMap->lpEntries;
		printlpEntries(lpEntry);
	}
}