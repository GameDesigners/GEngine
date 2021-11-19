#ifndef GTIMER_H
#define GTIMER_H
#include "GSystem.h"
namespace GEngine
{
	namespace GSystem
	{
		class GSYSTEM_API GTimer
		{
		public:
			static GTimer& GetTimer();

			void UpdateFps();
			void Reset();
			void Start();
			void Pause();
			double GetFPS(); 
			double GetDeltaTime();
			double GetRuningTime();
			double GetTotalTime();

		public:
			GTimer(const GTimer& timer) = delete;
			GTimer operator=(const GTimer& timer) = delete;
		private:

			GTimer();
			~GTimer();
			void InitGameTimer();

			int      m_iFrameCount;
			double   m_dFps;
			double   m_dPreRecordPointTime;
			double   m_dDeltaTime;
			double   m_dPreUpdateFpsTime;
			bool     m_bIsStop = true;
			bool     m_bUseLargeTime;

			/*使用大时间标记的变量*/
			__int64  m_i64OneSecondTicks;
			__int64  m_i64TimeTickStartCount;
			__int64  m_i64PauseTimeAccumulation;
			__int64  m_i64PrePauseTime;

			/*使用常规事件计数*/
			unsigned long m_ulStartTime;
			unsigned long m_ulPasueTimeAccumulation;
			unsigned long m_ulPrePauseTime;
		};
	}
}
#endif // !GTIMER_H
