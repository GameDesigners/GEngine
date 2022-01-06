#include "GTimer.h"
using namespace GEngine::GSystem;

GTimer& GTimer::GetTimer()
{
	static GTimer m_gTimer;
	return m_gTimer;
}

GTimer::GTimer()
{
	InitGameTimer();
}

GTimer::~GTimer() {}

void GTimer::InitGameTimer()
{
	m_iFrameCount = 0;
	m_dFps = 0;
	m_dPreRecordPointTime = 0;
	m_dDeltaTime = 0;
	m_dPreUpdateFpsTime = 0;
	m_bIsStop = false;

	m_i64OneSecondTicks = 0;
	m_i64TimeTickStartCount = 0;
	m_i64PauseTimeAccumulation = 0;
	m_i64PrePauseTime = 0;

	m_ulStartTime = 0;
	m_ulPasueTimeAccumulation = 0;
	m_ulPrePauseTime = 0;

	//判断时间计数方式
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&m_i64OneSecondTicks))
	{
		m_bUseLargeTime = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&m_i64TimeTickStartCount);//起始时间
	}
	else
	{
		m_bUseLargeTime = false;
		m_ulStartTime = timeGetTime();
	}
}

void GTimer::Tick()
{
	if (!m_bIsStop)
	{
		//计算当前的时间点
		double currentTime = 0;
		if (m_bUseLargeTime)
		{
			__int64 now = 0;
			QueryPerformanceCounter((LARGE_INTEGER*)&now);
			currentTime = (now - m_i64TimeTickStartCount) * ((1.0 / m_i64OneSecondTicks) * 1000);  //单位：微秒
		}
		else
			currentTime = timeGetTime() - m_ulStartTime;

		//计算Call Function: <UpdateFps> 的时间差
		m_dDeltaTime = currentTime - m_dPreUpdateFpsTime;
		m_dPreUpdateFpsTime = currentTime;
		//计算FPS
		if (currentTime - m_dPreRecordPointTime > 1000.0f)
		{
			m_dFps = m_iFrameCount;
			m_dPreRecordPointTime = currentTime;
			m_iFrameCount = 0;
		}
		else
			m_iFrameCount++;

	}
	else
	{
		m_dDeltaTime = 0;
	}
}

void GTimer::Reset()
{
	InitGameTimer();
}

void GTimer::Start()
{
	if (!m_bIsStop) return;

	if (m_bUseLargeTime)
	{
		__int64 now = 0;
		QueryPerformanceCounter((LARGE_INTEGER*)&now);
		m_i64PauseTimeAccumulation += now - m_i64PrePauseTime;
		m_i64PrePauseTime = now;
	}
	else 
	{
		double now = timeGetTime();
		m_ulPasueTimeAccumulation += now - m_ulPrePauseTime;
		m_ulPrePauseTime = now;
	}
	m_bIsStop = false;
}

void GTimer::Pause()
{
	if (m_bIsStop) return;

	if (m_bUseLargeTime)
	{
		__int64 now = 0;
		QueryPerformanceCounter((LARGE_INTEGER*)&now);
		m_i64PrePauseTime = now;
	}
	else
	{
		m_ulPrePauseTime = timeGetTime();
	}
	m_bIsStop = true;
}

double GTimer::GetFPS()
{
	return m_dFps;
}

double GTimer::GetDeltaTime()
{
	return m_dDeltaTime;
}

double GTimer::GetRuningTime()
{
	if (m_bUseLargeTime)
	{
		__int64 now = 0;
		QueryPerformanceCounter((LARGE_INTEGER*)&now);
		m_i64PrePauseTime = now;
		__int64 lastest = m_bIsStop ? m_i64PrePauseTime : now;
		return (lastest - m_i64PauseTimeAccumulation - m_i64TimeTickStartCount) * (1.0 / m_i64OneSecondTicks) * 1000;
	}
	else
	{
		DWORD lastest = m_bIsStop ? m_ulPrePauseTime : timeGetTime();
		return lastest - m_ulStartTime - m_ulPasueTimeAccumulation;
	}
}

double GTimer::GetTotalTime()
{
	if (m_bUseLargeTime)
	{
		__int64 now = 0;
		QueryPerformanceCounter((LARGE_INTEGER*)&now);
		return (now - m_i64TimeTickStartCount) * (1.0 / m_i64OneSecondTicks) * 1000;
	}
	else
		return timeGetTime() - m_ulStartTime;
}