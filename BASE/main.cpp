#include "my.h"

int main()
{
	CWinApp* pApp = AfxGetApp();

	pApp->InitApplication();
	pApp->InitInstance();
	pApp->Run();
	return 0;
}
//ȫ�ֶ���CMyWinApp�ڴ�����ʱ�����CWinApp�Ĺ��캯����m_pCurrentWinApp��Ա������ֵ����ֵΪ����ĵ�ַ����������ͨ��AfxGetApp��ȡȫ�ֶ���
//����CWinApp��InitApplication
//Ȼ�����CMyWinApp��InitInstance
//Ȼ���ʼ��CMyFrameWnd
