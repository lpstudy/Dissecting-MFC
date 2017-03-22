#include "my.h"

int main()
{
	//����pDoc��
	CMyDoc* pDoc = new CMyDoc;
	pDoc->m_sizeDoc = 1000;

	CObList oblist;
//5 5 5 5 5 CStroke
	CStroke stroke;
	for(int i = 0; i < 5; ++i)
		stroke.m_ptArray.push_back(5);
	oblist.push_back(&stroke);
//10 10 10 10 CRectangle
	CRectangle rectang;
	rectang.m_rect.Set(10, 10, 10, 10);
	oblist.push_back(&rectang);
//20 20 2 CCircle
	CCircle circle;
	circle.m_center.Set(20, 20);
	circle.m_radius = 2;
	oblist.push_back(&circle);

	pDoc->m_graphList = oblist;

	//��pDoc���󱣴浽�ļ�class.txt��
	CArchive ar;
	ar.m_fstream.open(".\\class.txt", ios::in | ios::binary | ios::out | ios::trunc);
	if(!ar.m_fstream.is_open()){
		TRACE_FUCTION_AND_LINE("open file failed");
		return -1;
	}

	ar << pDoc;
	ar.Close();
	

	//���¶�ȡclass.txt���ڴ棬�ָ�����pDocToRead
	ar.m_fstream.open(".\\class.txt", ios::in | ios::binary | ios::out);
	if(!ar.m_fstream.is_open()){
		TRACE_FUCTION_AND_LINE("open file failed");
		return -1;
	}
	CObject* pDocToRead;
	ar >> pDocToRead;
	ar.Close();


	//pDocToRead��ʼд�뵽��һ���ļ�class2.txt��
	ar.m_fstream.open(".\\class2.txt", ios::in | ios::binary | ios::out | ios::trunc);
	if(!ar.m_fstream.is_open()){
		TRACE_FUCTION_AND_LINE("open file failed");
		return -1;
	}
	ar << pDocToRead;

	//test write or read object only(not runtime information)

	ar << circle;
	ar >> circle;
	ar.Close();
	return 0;
}