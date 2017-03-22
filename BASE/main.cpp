#include "my.h"

int main()
{
	CWinApp* pApp = AfxGetApp();

	pApp->InitApplication();
	pApp->InitInstance();
	pApp->Run();
	return 0;
}
//全局对象CMyWinApp在创建的时候调用CWinApp的构造函数给m_pCurrentWinApp成员变量赋值，赋值为自身的地址，这样可以通过AfxGetApp获取全局对象。
//调用CWinApp的InitApplication
//然后调用CMyWinApp的InitInstance
//然后初始化CMyFrameWnd
