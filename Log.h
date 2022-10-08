#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <direct.h>
#include <fstream>
#include <io.h>
using namespace std;
#define LOG_BUFFER_SIZE 1*256
#define BASE_LOGDIR		"./Log/"
enum LOGLEVEL
{
	LEV_NORMAL,//打印基本信息，含消息，警告，错误
	LEV_FATAL,//打印错误信息，含错误，警告
	LEV_DEBUG,//打印所有信息
};
#define LOG_INFO	0
#define LOG_DEBUG	1
#define LOG_WARNING	2
#define LOG_ERROR	3
#define LOG(...) Trace(0,LOG_INFO,__FILE__,__LINE__,__FUNCTION__,__VA_ARGS__)
#define LOGI(...) Trace(0,LOG_INFO,__FILE__,__LINE__,__FUNCTION__,__VA_ARGS__)
#define LOGD(...) Trace(0,LOG_DEBUG,__FILE__,__LINE__,__FUNCTION__,__VA_ARGS__)
#define LOGW(...) Trace(0,LOG_WARNING,__FILE__,__LINE__,__FUNCTION__,__VA_ARGS__)
#define LOGE(...) Trace(0,LOG_ERROR,__FILE__,__LINE__,__FUNCTION__,__VA_ARGS__)
#define LOG(bInfoOnly,...) Trace(bInfoOnly,LOG_INFO,__FILE__,__LINE__,__FUNCTION__,__VA_ARGS__)
#define LOGI(bInfoOnly,...) Trace(bInfoOnly,LOG_INFO,__FILE__,__LINE__,__FUNCTION__,__VA_ARGS__)
#define LOGD(bInfoOnly,...) Trace(bInfoOnly,LOG_DEBUG,__FILE__,__LINE__,__FUNCTION__,__VA_ARGS__)
#define LOGW(bInfoOnly,...) Trace(bInfoOnly,LOG_WARNING,__FILE__,__LINE__,__FUNCTION__,__VA_ARGS__)
#define LOGE(bInfoOnly,...) Trace(bInfoOnly,LOG_ERROR,__FILE__,__LINE__,__FUNCTION__,__VA_ARGS__)

void SetLogMode(LOGLEVEL level);
void Trace(bool bInfoOnly,int InternalLevel, const char* file, int line, const char* function, const char* fmt, ...);
void WriteLogFile(const char* LogStr);
void FlushAllLogBufData();