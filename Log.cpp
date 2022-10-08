#include "Log.h"
#include <mutex>

std::mutex g_MutexLog;
const char* g_levelStr[] =
{
	"INFO",
	"DEBUG",
	"WARNING",
	"ERROR"
};
const DWORD color[] = {
	FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED,
	FOREGROUND_GREEN,
	FOREGROUND_GREEN | FOREGROUND_BLUE,
	FOREGROUND_RED
};
LOGLEVEL g_Level = LOGLEVEL::LEV_NORMAL;
string g_FileBuf;
void SetLogMode(LOGLEVEL level)
{
	g_MutexLog.lock();
	g_Level = level;
	g_MutexLog.unlock();
}
void Trace(bool bInfoOnly, int InternalLevel, const char* File, int Line, const char* Function, const char* Fmt, ...)
{
	g_MutexLog.lock();
	//对于非DEBUG模式来说，不输出DEBUG信息，对于FATAL模式来说，不输出DEBUG和INFO信息
	if ((g_Level != LOGLEVEL::LEV_DEBUG&&InternalLevel == LOG_DEBUG)||
		(g_Level == LOGLEVEL::LEV_FATAL&&(InternalLevel == LOG_DEBUG|| InternalLevel == LOG_INFO))
		)
	{
		g_MutexLog.unlock();
		return;
	}
	static vector<char> Buffer;
	
	if (Buffer.size() <= 0)
	{
		Buffer.resize(LOG_BUFFER_SIZE / 2);
	}


	if (InternalLevel < LOG_INFO)InternalLevel = LOG_INFO;
	if (InternalLevel > LOG_ERROR)InternalLevel = LOG_ERROR;

	va_list ap;
	va_start(ap, Fmt);


	char* pBuffer = Buffer.data();
	int ret = 0;
	if (!bInfoOnly)
	{
		snprintf(pBuffer, Buffer.size(), "\r\n%s(%d)<%s> [%s]",
			File, Line, g_levelStr[InternalLevel], Function);
	}
	size_t len = strlen(pBuffer);
	ret = _vsnprintf(pBuffer + len, Buffer.size() - len, Fmt, ap);
	if (ret < 0)
	{
		// Error
		std::cout << "Buffer filling Failed" << std::endl;
		Buffer.clear();
		g_MutexLog.unlock();
		return;
	}
	OutputDebugStringA(pBuffer);
	if (!bInfoOnly)
	{
		OutputDebugStringA("\n");
	}
	//Console
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wAttributes = color[InternalLevel];
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hConsole, &info);
	SetConsoleTextAttribute(hConsole, wAttributes);
	if (!bInfoOnly)
	{
		std::cout << pBuffer << std::endl;
	}
	else
	{
		//no cr lf
		std::cout << pBuffer;
	}
	SetConsoleTextAttribute(hConsole,info.wAttributes);

	//File
	g_FileBuf.append(pBuffer);
	if (!bInfoOnly)
	{
		g_FileBuf.append(" ").append(__TIMESTAMP__).append("\n");
	}
	if (g_FileBuf.size() >= LOG_BUFFER_SIZE/2)
	{
		WriteLogFile(g_FileBuf.data());
		g_FileBuf.clear();
	}
	Buffer.clear();
	g_MutexLog.unlock();
}

void WriteLogFile(const char* LogStr)
{
	std::string FilePath = std::string(BASE_LOGDIR).append(__DATE__).append(".Log");
	if (_access(BASE_LOGDIR, 0) == -1)
	{
		CreateDirectoryA(BASE_LOGDIR, 0);
	}
	if (_access(FilePath.c_str(), 0) == -1)
	{
		ofstream ofs(FilePath, ios::ios_base::app);
		ofs << "-----------------Log Start On[" << __TIMESTAMP__ << "]-----------------"<<endl;
		ofs << LogStr;
		ofs.close();
	}
	else
	{
		ofstream ofs(FilePath, ios::ios_base::app);
		ofs << LogStr;
		ofs.close();
	}


}

void FlushAllLogBufData()
{
	g_MutexLog.lock();
	if (g_FileBuf.size() > 0)
	{
		WriteLogFile(g_FileBuf.data());
		g_FileBuf.clear();
		WriteLogFile("\r\n-----------------Log End On[");
		WriteLogFile(__TIMESTAMP__);
		WriteLogFile("]----------------\r\n");
	}
	g_MutexLog.unlock();
}