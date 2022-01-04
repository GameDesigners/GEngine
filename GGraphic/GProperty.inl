#include "GProperty.h"
template<class T>
inline GEngine::GGraphic::GEnumProperty<T>::GEnumProperty(GRtti& owner, const GUserdName& name, const GUserdName& enumName, unsigned int uiElementOffset, unsigned int uiFlags)
	: GProperty(owner,name, uiElementOffset, uiFlags)
{
	m_EnumName = enumName;
}

template<typename T>
inline void GEngine::GGraphic::GEnumProperty<T>::Clone(GProperty* p)
{
	GEnumProperty* pTemp = p;
	GProperty::Clone(pTemp);
	m_EnumName = pTemp->m_EnumName;
}

template<typename T>
inline bool GEngine::GGraphic::GEnumProperty<T>::SetValue(void* pObj, T& dataSrc) const
{
	*((T*)((unsigned char*)(pObj)+this->m_uiElementOffset)) = dataSrc;

}

template<typename T>
inline bool GEngine::GGraphic::GEnumProperty<T>::GetValue(void* pObj, T& dataDest) const
{
	dataDest = *((T*)((unsigned char*)(pObj)+this->m_uiElementOffset));
	return true;
}

template<typename T>
inline bool GEngine::GGraphic::GEnumProperty<T>::GetValue(const void* pObj, T& dataDest) const
{
	dataDest = *((T*)((const char*)(pObj)+this->m_uiElementOffset));
	return true;
}

template<typename T>
inline T& GEngine::GGraphic::GEnumProperty<T>::Value(void* pObj) const
{
	return *((T*)((const char*)(pObj)+this->m_uiElementOffset));
}

template<typename T>
inline GEngine::GGraphic::GProperty* GEngine::GGraphic::GEnumProperty<T>::GetInstance()
{
	return GNEW GEnumProperty<T>();
}


template<typename T>
GEngine::GGraphic::GDataProperty<T>::GDataProperty(GRtti& owner, const GUserdName& name, unsigned int uiElementOffset, unsigned int uiDataNum, bool bDynamicCreate)
	: GProperty(owner, name, uiElementOffset, F_SAVE_LOAD_CLONE)
{
	m_bDynamicCreate = bDynamicCreate;
	m_uiDataNum = uiDataNum;
	m_uiElementOffset = uiElementOffset;
}

template<typename T>
inline void GEngine::GGraphic::GDataProperty<T>::Clone(GProperty* p)
{

}

template<typename T>
inline GEngine::GGraphic::GProperty* GEngine::GGraphic::GDataProperty<T>::GetInstance()
{
	return nullptr;
}
