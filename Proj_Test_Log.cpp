// Proj_Test_Log.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "Log.h"
int main()
{
	//非debug模式下不输出debug信息
	//Debug模式下输出debug信息
	//bDebugData用于控制是否需要添加时间戳，换行以及显示前置信息
	//SetLogMode(LOGLEVEL::LEV_NORMAL);
	//LOGI(0,"INFO ");
	//LOGI(1, "INFO ");
	//LOGD(0, "Debug ");
	//LOGD(1, "Debug ");
	//LOGW(0, "WARNING ");
	//LOGW(1, "WARNING ");
	//LOGE(0, "ERROR ");
	//LOGE(1, "ERROR ");
	//SetLogMode(LOGLEVEL::LEV_FATAL);
	//LOGI(0, "INFO ");
	//LOGI(1, "INFO ");
	//LOGD(0, "Debug ");
	//LOGD(1, "Debug ");
	//LOGW(0, "WARNING ");
	//LOGW(1, "WARNING ");
	//LOGE(0, "ERROR ");
	//LOGE(1, "ERROR ");
	SetLogMode(LOGLEVEL::LEV_DEBUG);
	LOGI(0, "INFO ");
	LOGI(1, "INFO ");
	LOGD(0, "Debug ");
	LOGD(1, "Debug ");
	LOGW(0, "WARNING ");
	LOGW(1, "WARNING ");
	LOGE(0, "ERROR ");
	LOGE(1, "ERROR ");
    //std::cout << "Hello World!\n";
	FlushAllLogBufData();
	system("pause");
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
