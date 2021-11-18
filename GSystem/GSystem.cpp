#include "GSystem.h"
using namespace GEngine::GSystem;

TCHAR GSystem::ms_logBuffer[GSYSTEM_LOG_BUFFER_SIZE];
DWORD GSystem::ms_dwMainThreadID;

TCHAR* GSystem::GetLogBuffer()
{
	return ms_logBuffer;
}

DWORD GSystem::GetMainThreadID()
{
	ms_dwMainThreadID = GetCurrentThreadId();
	return ms_dwMainThreadID;
}