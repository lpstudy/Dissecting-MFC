#ifndef __LOG__H__
#define __LOG__H__

#include <stdio.h>
#define TRACE_FUCTION_AND_LINE(fmt, ...) printf("[%30s:%4d] "fmt"\n",__FUNCTION__, __LINE__, ##__VA_ARGS__)

#endif