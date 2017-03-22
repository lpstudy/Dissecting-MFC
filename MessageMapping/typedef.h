#ifndef __TYPEDEFINE_H__
#define __TYPEDEFINE_H__

/*
 * ϵͳ��֧�ֵ���Ҫ�ⲿ����ĺ�
 * �����ϵͳ���: _LINUX��_AIX��_HPUNIX��_SOLARIS
 * ��Щ����Ҫ���ⲿǿ�ƶ��壬���δ���壬��ֱ�ӱ���ʧ��
 * �����ɴ������жϳ����ĺ궨�岿��
 * _WINDOWS: ����ϵͳ��_WIN32��_WIN64�Զ����壬��ʾwindows����ϵͳ
 * __64bit: ���ݲ���ϵͳ�����뻷�����ֳ��Զ�����
 * __GNUC__: gcc�������Ժ����
 * _MSC_VER: vc�������Զ����
 * __INTEL_COMPILER: intel�������Զ����
 */

#include <stddef.h>

#if defined(_WIN32) || defined(_WIN64)
#	undef _WINDOWS
#	define _WINDOWS
#endif

/*�жϲ���ϵͳ�����Ƿ�֧��*/
#if !defined(_WINDOWS) && !defined(_LINUX) && !defined(_AIX) && !defined(_HPUNIX) && !defined(_SOLARIS)
#	error "unknow operating system!!!"
#endif

/*�ж�֧�ֵı���������*/
#if !defined(_MSC_VER) && !defined(__GNUC__) && !defined(__INTEL_COMPILER)
#	error "unkown compiler !!!"
#endif

#if defined(_WIN64) || defined(__x86_64__) || defined (__64BIT__)
#	define __64bit
#endif

/**************/
#if defined(_LINUX) || defined(_AIX) || defined(_HPUNIX) || defined(_SOLARIS)
#	include <stdint.h>

#else /*_WINDOWS*/
#ifndef __int8_t_defined
#define __int8_t_defined
	typedef char int8_t;
	typedef unsigned char uint8_t;
	typedef short int16_t;
	typedef unsigned short uint16_t;
	typedef int int32_t;
	typedef unsigned int uint32_t;

# ifdef __64bit
	typedef long int64_t;
	typedef unsigned long uint64_t;
# else
#	ifdef _MSC_VER
	typedef __int64 int64_t;
	typedef unsigned __int64 uint64_t;
#	else
	typedef long long int64_t;
	typedef unsigned long long uint64_t;
#	endif /*_MSC_VER*/
# endif /*__64bit*/


/* 7.18.1.4  Integer types capable of holding object pointers */
#	ifdef __64bit
	typedef long intptr_t;
	typedef unsigned long uintptr_t;
#	else
	typedef int intptr_t;
	typedef unsigned uintptr_t;
#	endif
	
#endif /*end __int8_t_defined*/
#endif /*end _WINDOWS*/

	typedef float  float32_t;
	typedef double float64_t;
	typedef long double float128_t;


#if !defined(_SIZE_T) && !defined(_SIZE_T_DEFINED)
#define _SIZE_T
#define _SIZE_T_DEFINED
	typedef unsigned long   size_t;
#endif

/* �Բ����ͱ������� */
#ifndef __bool_t_defined
#define __bool_t_defined
	typedef uint8_t bool_t;
#	ifndef TRUE
#	define TRUE (bool_t)(1)
#	endif
#	ifndef FALSE
#	define FALSE (bool_t)(0)
#	endif
#endif

/* 7.18.2.1  Limits of exact-width integer types */
#ifndef _H_STDINT
#define INT8_MIN (-128) 
#define INT16_MIN (-32768)
#define INT32_MIN (-2147483647 - 1)
#ifdef __GNUC__
	#define INT64_MIN  (-9223372036854775807LL - 1)
#else
	#define INT64_MIN  (-9223372036854775807i64 - 1)
#endif

#define INT8_MAX 127
#define INT16_MAX 32767
#define INT32_MAX 2147483647
#ifdef __GNUC__
	#define INT64_MAX 9223372036854775807LL
#else
	#define INT64_MAX 9223372036854775807i64
#endif

#define UINT8_MAX 0xff /* 255U */
#define UINT16_MAX 0xffff /* 65535U */
#define UINT32_MAX 0xffffffff  /* 4294967295U */
#ifdef __GNUC__
	#define UINT64_MAX 0xffffffffffffffffULL /* 18446744073709551615ULL */
#else
	#define UINT64_MAX 0xffffffffffffffffui64 /* 18446744073709551615ULL */
#endif

#ifndef INT64_C
#   if defined(__GNUC__)
#       define INT64_C(c)     (c ## LL)
#       define UINT64_C(c)    (c ## ULL)
#   else
#       define INT64_C(c)     (c ## i64)
#       define UINT64_C(c)    (c ## ui64)
#   endif
#endif /*INT64_C*/
#endif /*_H_STDINT*/

/*�޸�FET�����ֵ������SELECT����Linux��Ч*/
#undef FD_SETSIZE
#define FD_SETSIZE 256 

/*ͳһ����ͷ�ļ��İ���*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <errno.h>
#include <assert.h>

#include <time.h>
#include <memory.h>
//#include <string.h>
	
#include <sys/stat.h>

#ifdef _LINUX
#define __FUNCDNAME__ __func__
#endif

#ifdef _WINDOWS  
#	ifndef _WIN32_WINNT
#	define _WIN32_WINNT 0x0500
#	endif
//#	include <windows.h>
#else
#	include <unistd.h>
#	include <sys/time.h>
	//typedef void* HANDLE;
#endif
	
/*FIXME: should be comment out on VC9.0(1500)*/
#if (defined(_MSC_VER) && (_MSC_VER>=1500))
#	define snprintf _snprintf
#	define vsnprintf _vsnprintf
#endif
	
/*MAX_PATH*/
#ifndef MAX_PATH
#	define MAX_PATH 260
#endif

#define	CTboolTRUE			1
#define CTboolFALSE			0

/*ָ��ɾ���궨��*/	
#define SAFE_DELETE_POINT(p) do{delete (p); (p) = NULL;} while(0)
#define SAFE_DELETE_ARRAY(p) do{delete [] (p); (p) = NULL;} while(0)

/*�ӿ��������������궨��*/
#define DECLARE_PURE_INTERFACE(name) public: virtual ~name() {};
	
/*����VC�ı���澯*/
#if (defined(_MSC_VER) )/*&& defined(_DEBUG))*/
#	pragma warning(disable:4786)	/*warning C4786: identifier was truncated to '255' characters in the browser information*/
#	pragma warning(disable:4355) /*warning C4355: 'this' : used in base member initializer list*/
#endif

#ifndef BOOL
#define  BOOL int
#endif
#ifndef LPCSTR
#define LPCSTR LPSTR
#endif
#ifndef LPSTR
typedef char* LPSTR;
#endif
#ifndef UINT
#define UINT int
#endif
#ifndef PASCAL
#define PASCAL //_stdcall
#endif
#ifndef WORD
#define WORD uint16_t
#endif
#ifndef DWORD
#define DWORD uint64_t
#endif
#ifndef AFXAPI
#define AFXAPI
#endif

#ifndef WPARAM
#define WPARAM uint32_t 
#endif
#ifndef LPARAM
#define LPARAM int32_t 
#endif
#ifndef LRESULT
#define LRESULT int32_t 
#endif
#ifndef HWND
#define HWND int32_t 
#endif
#endif //__TYPEDEFINE_H__
