#include "GProperty.h"
GEngine::GGraphic::GProperty::GProperty(GRtti& owner, const GUserdName& name, unsigned int uiElementOffset, unsigned int uiFlags)
{
	m_pOwner = &owner;
	m_Name = name;
	m_uiElementOffset = uiElementOffset;
	m_uiFlag = uiFlags;
}

void* GEngine::GGraphic::GProperty::GetValueAddress(void* pObj) const
{
	return (void*)(((unsigned char*)pObj) + m_uiElementOffset);
}

void GEngine::GGraphic::GProperty::Clone(GProperty* p)
{
}
