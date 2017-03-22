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
			TRACE_FUCTION_AND_LINE("%d-%s", lpEntry->nID,  classinfo[i].classname);
			break;
		}
	}
}
BOOL calllpEntries(AFX_MSGMAP_ENTRY* lpEntry, UINT nMessage, UINT nId, CCmdTarget* handle)
{
	TRACE_FUCTION_AND_LINE("");
	int i;
	for(i = 0; lpEntry[i].nMessage != 0 && (lpEntry[i].nMessage != nMessage || lpEntry[i].nID != nId); ++i)
		;
	if (lpEntry[i].nMessage == 0)
	{
		return FALSE;//cannot handle
	}

	//������ֱ�ӵ��ã�mfc���õ�ͨ�û��ƣ�����union�������п��ܵĺ����Ͳ������Ͷ��ŵ�һ��union���棬�ڴ�����Ϣ��ʱ��ͬʱ����Ҫ���õĺ�������
	//��Ҫ����ʱ�����ݲ�ͬ�����Ĳ�������ֱ�ӵ���union�ṹ��Ĳ�ͬ����ָ�룬���ö�pfn���е�ǿת(union�����ˡ�)��������ֱ��ģ��CView::OnPaint
	/*
	union MessageMapFunctions
	{
		AFX_PMSG pfn;   // generic member function pointer
		BOOL (AFX_MSG_CALL CCmdTarget::*pfn_b_b)(BOOL);
		BOOL (AFX_MSG_CALL CCmdTarget::*pfn_b_u)(UINT);
		BOOL (AFX_MSG_CALL CWnd::*pfn_b_v)();
		void (AFX_MSG_CALL CWnd::*pfn_v_u)(UINT);
		void (AFX_MSG_CALL CWnd::*pfn_v_u_u)(UINT, UINT);
		void (AFX_MSG_CALL CWnd::*pfn_v_i_i)(int, int);
		void (AFX_MSG_CALL CWnd::*pfn_v_u_u_u)(UINT, UINT, UINT);
		void (AFX_MSG_CALL CWnd::*pfn_v_u_i_i)(UINT, int, int);
		void (AFX_MSG_CALL CWnd::*pfn_v_w_l)(WPARAM, LPARAM);
		void (AFX_MSG_CALL CWnd::*pfn_v_b_W_W)(BOOL, CWnd*, CWnd*);
	}
	//��Ҫ���ú�����ʱ��
	union MessageMapFunctions mmf;
	mmf.pfn = lpEntry->pfn;

	switch (lpEntry->nSig)
	{
	default:
		ASSERT(FALSE);
		break;
	case AfxSig_l_p:
		{
			CPoint point(lParam);		
			lResult = (this->*mmf.pfn_l_p)(point);
			break;
		}		
	case AfxSig_b_D_v:
		lResult = (this->*mmf.pfn_b_D)(CDC::FromHandle(reinterpret_cast<HDC>(wParam)));
		break;

	case AfxSig_b_b_v:
		lResult = (this->*mmf.pfn_b_b)(static_cast<BOOL>(wParam));
		break;
	}
	*/
	typedef void (CView::*CVIEW_ONPAINT)(void);
	CVIEW_ONPAINT pfn = (CVIEW_ONPAINT)(lpEntry[i].pfn);
	CView* currentView = (CView*)handle;
	(currentView->*pfn)();//call handle func
	return TRUE;
}
void MsgMapPrinting(AFX_MSGMAP* pMessageMap)
{
	for(; pMessageMap != NULL; pMessageMap = pMessageMap->pBaseMessageMap) {
		AFX_MSGMAP_ENTRY* lpEntry = pMessageMap->lpEntries;
		printlpEntries(lpEntry);
	}
}