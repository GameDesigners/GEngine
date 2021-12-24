#include "GPriority.h"
using namespace GEngine::GGraphic;

GEngine::GGraphic::GPriority::GPriority()
{
	m_uiPriorityNum = 0;
}

GEngine::GGraphic::GPriority::GPriority(unsigned int priority)
{
	m_uiPriorityNum = priority;
}

GEngine::GGraphic::GPriority::~GPriority()
{
	m_PriorityThanList.clear();
}

bool GEngine::GGraphic::GPriority::AddPriorityThan(GPriority* pPriority)
{
	if (pPriority == nullptr) 
		return false;

	if (pPriority->__check_is_circle(this))  //检查是否会形成拓扑回路
		return false;

	m_uiPriorityNum = 0;
	m_PriorityThanList.push_back(pPriority);
	return true;
}

unsigned int GEngine::GGraphic::GPriority::GetPriorityNum()
{
	__update_priority_num();
	return m_uiPriorityNum;
}

GPriority& GEngine::GGraphic::GPriority::operator=(GPriority& rv)
{
	rv.__update_priority_num();
	m_uiPriorityNum = rv.m_uiPriorityNum;
	m_PriorityThanList.clear();
	m_PriorityThanList = rv.m_PriorityThanList;
	return *this;
}

bool GEngine::GGraphic::GPriority::operator==(GPriority& rv)
{
	__update_priority_num();
	rv.__update_priority_num();
	return m_uiPriorityNum == rv.m_uiPriorityNum;
}

bool GEngine::GGraphic::GPriority::operator!=(GPriority& rv)
{
	__update_priority_num();
	rv.__update_priority_num();
	return m_uiPriorityNum != rv.m_uiPriorityNum;
}

bool GEngine::GGraphic::GPriority::operator>(GPriority& rv)
{
	__update_priority_num();
	rv.__update_priority_num();
	return m_uiPriorityNum > rv.m_uiPriorityNum;
}

bool GEngine::GGraphic::GPriority::operator<(GPriority& rv)
{
	__update_priority_num();
	rv.__update_priority_num();
	return m_uiPriorityNum < rv.m_uiPriorityNum;
}

bool GEngine::GGraphic::GPriority::operator>=(GPriority& rv)
{
	__update_priority_num();
	rv.__update_priority_num();
	return m_uiPriorityNum >= rv.m_uiPriorityNum;
}

bool GEngine::GGraphic::GPriority::operator<=(GPriority& rv)
{
	__update_priority_num();
	rv.__update_priority_num();
	return m_uiPriorityNum <= rv.m_uiPriorityNum;
}
