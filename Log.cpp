#include "Log.h"
#include <mutex>

std::mutex g_MutexLog;

void Trace(const char* target, int level, const char* file, int line, const char* function, const char* fmt, ...)
{
	g_MutexLog.lock();
	static vector<char> buffer;
	if (buffer.size() <= 0)
	{
		buffer.resize(LOG_BUFFER_SIZE);
	}
	const char* slevel[] =
	{
		"INFO",
		"DEBUG",
		"WARNING",
		"ERROR"
	};

	if (level < 0)level = 0;
	if (level > 3)level = 3;

	va_list ap;
	va_start(ap, fmt);


	char* pBuffer = buffer.data();
	int ret = snprintf(pBuffer, buffer.size(), "%s(%d)<%s>-<%s> [%s]",
		file, line, slevel[level], target, function);
	size_t len = strlen(pBuffer);
	ret = _vsnprintf(pBuffer + len, buffer.size() - len, fmt, ap);
	if (ret < 0)
	{
		// Error
	}
	OutputDebugStringA(pBuffer);
	OutputDebugStringA("\r\n");
	//Console
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD color[] = {
		FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED,
		FOREGROUND_GREEN,
		FOREGROUND_GREEN | FOREGROUND_BLUE,
		FOREGROUND_RED
	};
	WORD wAttributes = color[level];
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hConsole, &info);
	SetConsoleTextAttribute(hConsole, wAttributes);
	std::cout << pBuffer << std::endl;
	SetConsoleTextAttribute(hConsole,info.wAttributes);
	g_MutexLog.unlock();
}