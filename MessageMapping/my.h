#ifndef __MY__H__
#define __MY__H__
#include <vector>
#include <list>
#include <iostream>
using namespace std;

#include "mfc.h"
#include "baseclass.h"

typedef list<CObject*> CObList;
typedef list<CObject*>::iterator CObListIter;
typedef vector<DWORD> CDWordArray;
typedef vector<DWORD>::iterator CDWordArrayIter;
class CMyFrameWnd;


//CMyFrameWnd
class CMyFrameWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CMyFrameWnd)
	DECLARE_MESSAGE_MAP()
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
public:
	virtual void SayHello()
	{
		TRACE_FUCTION_AND_LINE("Hello!");
	}
};

//CMyWinApp
class CMyWinApp : public CWinApp
{
	DECLARE_MESSAGE_MAP()
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
public:
	virtual void SayHello()
	{
		TRACE_FUCTION_AND_LINE("Hello!");
	}
};
//CMyDoc
class CMyDoc : public CDocument
{
	DECLARE_SERIAL(CMyDoc)
	DECLARE_MESSAGE_MAP()
public:
	CObList m_graphList;//这个暂时不支持Serialize，如果支持可以直接ar>>m_graphList
	WORD m_sizeDoc;
public:
	CMyDoc()
	{
		TRACE_FUCTION_AND_LINE("");
	}
	~CMyDoc()
	{
		TRACE_FUCTION_AND_LINE("");
	}
public:
	virtual void SayHello()
	{
		TRACE_FUCTION_AND_LINE("Hello!");
	}
	virtual void Serialize(CArchive& ar)
	{
		char c = '|';
		if(ar.IsStoring())
		{
			ar<<m_sizeDoc << c; 
		}
		else{
			ar>>m_sizeDoc << c;
		}
		//m_graphList.Serialize(ar);
		if(ar.IsStoring())
		{
			ar<< (WORD)m_graphList.size() << c;
			for (CObListIter iter = m_graphList.begin(); iter != m_graphList.end(); ++iter)
			{
				ar << (*iter);//调用对象的WriteObject
			}
		}
		else{
			WORD nCount;
			ar >> nCount >> c;
			while(nCount > 0 && nCount--)
			{
				CObject* pObj;
				ar >>pObj;
				m_graphList.push_back(pObj);
			}
		}

	}
};
//CMyView
class CMyView : public CView
{
	DECLARE_DYNCREATE(CMyView)
	DECLARE_MESSAGE_MAP()
public:
	CMyView()
	{
		TRACE_FUCTION_AND_LINE("");
	}
	~CMyView()
	{
		TRACE_FUCTION_AND_LINE("");
	}
public:
	virtual void SayHello()
	{
		TRACE_FUCTION_AND_LINE("Hello!");
	}
};

//线是一堆点的集合
class CStroke : public CObject
{
	DECLARE_SERIAL(CStroke)
public:
	CStroke(){}
public:
	virtual void Serialize(CArchive& ar)
	{
		//m_ptArray.Serialize(ar);

		if(ar.IsStoring())
		{
			ar << (WORD)m_ptArray.size();
			for(CDWordArrayIter iter = m_ptArray.begin(); iter != m_ptArray.end(); ++iter)
			{
				ar << (*iter);
			}
		}
		else{
			WORD nCount;
			ar >> nCount;
			while(nCount > 0 && nCount--)
			{
				DWORD obj;
				ar >> obj;
				m_ptArray.push_back(obj);
			}
		}
	}
public:
	CDWordArray m_ptArray; // series of connected points
};
//矩形是
class CRectangle : public CObject
{
	DECLARE_SERIAL(CRectangle)
public:
	CRectangle(){}
public:
	virtual void Serialize(CArchive& ar)
	{
		if(ar.IsStoring())
		{
			ar << m_rect.m_left;
			ar << m_rect.m_top;
			ar << m_rect.m_right;
			ar << m_rect.m_bottom;
		}
		else{
			ar >> m_rect.m_left;
			ar >> m_rect.m_top;
			ar >> m_rect.m_right;
			ar >> m_rect.m_bottom;
		}
	}
public:
	CRect m_rect;//普通数据类型对象
};

//圆进行序列化。
class CCircle : public CObject
{
	DECLARE_SERIAL(CCircle)
public:
	CCircle(){}
public:
	virtual void Serialize(CArchive& ar)
	{
		if(ar.IsStoring())
		{
			ar << m_center.m_x;
			ar << m_center.m_y;
			ar << m_radius;
		}
		else{
			ar >> m_center.m_x;
			ar >> m_center.m_y;
			ar >> m_radius;
		}
	}
public:
	CPoint m_center;
	UINT m_radius;
};
void printlpEntries(AFX_MSGMAP_ENTRY* lpEntry);
void MsgMapPrinting(AFX_MSGMAP* pMessageMap);
#endif//__MY__H__
