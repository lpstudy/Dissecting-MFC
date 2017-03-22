#ifndef __BASE__CLASS_H
#define __BASE__CLASS_H
#include "mfc.h"
#include "my.h"
#include <fstream>
#include <iostream>

class CObject;
class CSize
{
public:
	CSize()
	{
		m_width =0;
		m_height =0;
	}
	CSize(int w, int h) : m_width(w), m_height(h)
	{}
	void set(int w, int h)
	{
		m_width = w;
		m_height = h;
	}
protected:
private:
	int m_width;
	int m_height;
};

class CPoint
{
public:
	CPoint(){}
	CPoint(int cx, int cy);

	void Set(int cx, int cy)
	{
		m_x = cx;
		m_y = cy;
	}
protected:
private:
public:
	int m_x;
	int m_y;
};

class CRect
{
public:
	CRect(){}
	// from left, top, right, and bottom
	CRect(int l, int t, int r, int b) :m_left(l),
		m_top(t),
		m_right(r),
		m_bottom(b)
	{}
	int Width() {return m_right-m_left;}
	int Height(){return m_bottom-m_top;}

	void Set(int l, int t, int r, int b)
	{
		m_left = l;
		m_top = t;
		m_right = r;
		m_bottom = b;
	}
protected:
private:
public:
	int m_left;
	int m_top;
	int m_right;
	int m_bottom;
};

//
class CArchive
{

public:
	
public:
	//写入到文件中
	friend CArchive& AFXAPI operator<<(CArchive& ar, const CObject* pOb)
	{
		ar.WriteObject(pOb);
		return ar;
	}

	//读取到对象中
	friend CArchive& AFXAPI operator>>(CArchive& ar, CObject*& pOb)
	{
		//根据类名，获取到CRuntimeClass,传给ReadObject
		UINT schemaNum;
		CRuntimeClass* pClass = CRuntimeClass::Load(ar, &schemaNum);
		if(pClass){
			pOb = ar.ReadObject(pClass);
		}
		return ar;
	}

	friend CArchive& AFXAPI operator>>(CArchive& ar, const CObject*& pOb)
	{
		//根据类名，获取到CRuntimeClass,传给ReadObject
		UINT schemaNum;
		CRuntimeClass* pClass = CRuntimeClass::Load(ar, &schemaNum);
		if(pClass){
			pOb = ar.ReadObject(pClass);
		}
		return ar;
	}
public:
	CArchive& operator<<(DWORD dw)
	{
		Write(&dw, sizeof(DWORD));
		return *this;
	}
	CArchive& operator<<(WORD w)
	{
		Write(&w, sizeof(WORD));
		return *this;
	}
	CArchive& operator<<(int i)
	{
		Write(&i, sizeof(int));
		return *this;
	}
	CArchive& operator<<(short s)
	{
		Write(&s, sizeof(short));
		return *this;
	}
	CArchive& operator<<(char c)
	{
		Write(&c, sizeof(char));
		return *this;
	}
public://从文件读取
	CArchive& operator>>(DWORD &dw)
	{
		Read(&dw, sizeof(DWORD));
		return *this;
	}
	CArchive& operator>>(WORD &w)
	{
		Read(&w, sizeof(WORD));
		return *this;
	}
	CArchive& operator>>(int &i)
	{
		Read(&i, sizeof(int));
		return *this;
	}
	CArchive& operator>>(short &s)
	{
		Read(&s, sizeof(short));
		return *this;
	}
	CArchive& operator>>(char &c)
	{
		Read(&c, sizeof(char));
		return *this;
	}
public:
	void WriteObject(const CObject* pCOb)
	{
		CObject* pOb = (CObject*)pCOb;
		CRuntimeClass* pClass = pOb->GetRuntimeClass();
		m_bIsStore = TRUE;
		pClass->Store(*this);//保存runtimeclass变量
		pOb->Serialize(*this);//保存
	}
	CObject* ReadObject(const CRuntimeClass* pCClass)
	{
		CRuntimeClass* pClass = (CRuntimeClass*)pCClass;
		m_bIsStore = FALSE;
		CObject* pObj = pClass->CreateObject();
		pObj->Serialize(*this);
		return pObj;
	}
public:
	BOOL IsStoring() const
	{
		return m_bIsStore;
	}
public:
	void SetStoring(BOOL storing)
	{
		m_bIsStore = storing;
	}
public:
	UINT Read(void* lpBuf, UINT nMax)
	{
		 m_fstream.read((char*)lpBuf, nMax);
		 return m_fstream.gcount();
	}
	void Write(const void* lpBuf, UINT nMax)
	{
		m_fstream.write((const char*)lpBuf,nMax);
	}
	void Flush()
	{
		m_fstream.flush();
	}
	void Close()
	{
		m_fstream.close();
	}
public:
	fstream m_fstream;
private:
	BOOL m_bIsStore;
};

//感觉无用，有DECLARE_SERIAL，它自己搞定自己，搞定自己的serialize，搞定自己的<<,>>

	//写入到文件

	
#endif