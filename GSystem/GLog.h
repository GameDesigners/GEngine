#ifndef GLOG_H
#define GLOG_H
#include "GFile.h"
namespace GEngine
{
	namespace GSystem
	{
        //#define G_LOG(Capcity,LogStr) 
		class GLog
		{
		public:
			enum class LogType
			{
				Log,
				Warning,
				Error
			};
		public:
			GLog(TCHAR* filePath);
			
			void Log();
			void Warn();
			void Error();

		private:
			GFile m_logFile;
			bool  m_bIsInited = false;
		};

	}
}

#endif // !GLOG_H

