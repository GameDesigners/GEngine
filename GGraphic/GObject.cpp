#include "GObject.h"

GEngine::GGraphic::GFastObjectManager::GFastObjectManager()
{
	m_FreeTable.assign(MAX_OBJECT_FLAG, 0);
	for (unsigned int index = 0; index < MAX_OBJECT_NUM; index++)
	{
		m_ObjectArray[index] = nullptr;
		m_FreeTable[index] = index;
	}
	m_ObjectArray[MAX_OBJECT_NUM] = nullptr;
}

GEngine::GGraphic::GFastObjectManager::~GFastObjectManager() {}

unsigned int GEngine::GGraphic::GFastObjectManager::AddObject(GObject* p)
{
	unsigned int ID = m_FreeTable[m_FreeTable.size() - 1];
	m_ObjectArray[ID] = p;
	m_FreeTable.pop_back();
	return ID;
}

void GEngine::GGraphic::GFastObjectManager::DeleteObject(GObject* p)
{
	if (m_ObjectArray[p->m_uiObjectID] != nullptr)
	{
		m_ObjectArray[p->m_uiObjectID] = nullptr;
		m_FreeTable.push_back(p->m_uiObjectID);
		p->m_uiObjectID = MAX_OBJECT_FLAG;
	}
}

unsigned int GEngine::GGraphic::GFastObjectManager::GetObjectNum()
{
	return MAX_OBJECT_FLAG - m_FreeTable.size();
}








GEngine::GGraphic::GObject::GObject()
{
	m_uiObjectID = GetObjectManager().AddObject(this);
}


GEngine::GGraphic::GObject::~GObject()
{
	GetObjectManager().DeleteObject(this);
}
