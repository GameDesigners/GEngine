#include "GSystem.h"
using namespace GEngine::GSystem;

TCHAR GSystem::ms_logBufferW[GSYSTEM_LOG_BUFFER_SIZE];
CHAR GSystem::ms_logBufferA[GSYSTEM_LOG_BUFFER_SIZE];
DWORD GSystem::ms_dwMainThreadID;

TCHAR* GSystem::GetLogBufferW()
{
	return ms_logBufferW;
}

CHAR* GSystem::GetLogBufferA()
{
	return ms_logBufferA;
}

DWORD GSystem::GetMainThreadID()
{
	ms_dwMainThreadID = GetCurrentThreadId();
	return ms_dwMainThreadID;
}