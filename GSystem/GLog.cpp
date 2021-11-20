#include "GLog.h"
using namespace GEngine::GSystem;

GLog::GLog(TCHAR* filePath)
{
	GASSERT(filePath != nullptr);
	m_bIsInited = m_logFile.Open(filePath, GFile::FileAccess::ReadWriteCreate, GFile::FileMode::BINARY);
}