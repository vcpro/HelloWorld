#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
#define LOG_BUFFER_SIZE 2048*2048

#define LOG(tag,...) Trace(tag,0,__FILE__,__LINE__,__FUNCTION__,__VA_ARGS__)
#define LOGI(tag,...) Trace(tag,0,__FILE__,__LINE__,__FUNCTION__,__VA_ARGS__)
#define LOGD(tag,...) Trace(tag,1,__FILE__,__LINE__,__FUNCTION__,__VA_ARGS__)
#define LOGW(tag,...) Trace(tag,2,__FILE__,__LINE__,__FUNCTION__,__VA_ARGS__)
#define LOGE(tag,...) Trace(tag,3,__FILE__,__LINE__,__FUNCTION__,__VA_ARGS__)


void Trace(const char* target, int level, const char* file, int line, const char* function, const char* fmt, ...);