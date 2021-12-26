#include "GReference.h"
template<class T>
inline GEngine::GGraphic::GObjectSmartPointer<T>::GObjectSmartPointer(value_pointer pObj)
{
	m_pObject = pObj;
	if (m_pObject != nullptr)
		m_pObject->IncreaseReferenceCount();
}

template<class T>
inline GEngine::GGraphic::GObjectSmartPointer<T>::GObjectSmartPointer(const GObjectSmartPointer& cv)
{
	m_pObject = cv.m_pObject;
	if (m_pObject != nullptr)
		m_pObject->IncreaseReferenceCount();
}

template<class T>
inline GEngine::GGraphic::GObjectSmartPointer<T>::~GObjectSmartPointer()
{
	if (m_pObject != nullptr)
	{
		m_pObject->DecreaseReferenceCount();
		m_pObject = nullptr;
	}
}

template<class T>
inline T& GEngine::GGraphic::GObjectSmartPointer<T>::operator*() const
{
	return *m_pObject;
}

template<class T>
inline T* GEngine::GGraphic::GObjectSmartPointer<T>::operator->() const
{
	return m_pObject;
}

template<class T>
inline GEngine::GGraphic::GObjectSmartPointer<T>::operator T* () const
{
	return m_pObject;
}

template<class T>
inline GEngine::GGraphic::GObjectSmartPointer<T>& GEngine::GGraphic::GObjectSmartPointer<T>::operator=(value_pointer pObj)
{
	if (m_pObject != nullptr)//释放管理的指针
	{
		m_pObject->DecreaseReferenceCount();
		m_pObject = nullptr;
	}

	m_pObject = pObj;
	if (m_pObject != nullptr)
		m_pObject->IncreaseReferenceCount();
	return *this;
}

template<class T>
inline GEngine::GGraphic::GObjectSmartPointer<T>& GEngine::GGraphic::GObjectSmartPointer<T>::operator=(const GObjectSmartPointer& cv)
{
	if (m_pObject != nullptr)
	{
		m_pObject->DecreaseReferenceCount();
		m_pObject = nullptr;
	}

	m_pObject = cv.m_pObject;
	if (m_pObject != nullptr)
		m_pObject->IncreaseReferenceCount();
	return *this;
}

template<class T>
inline bool GEngine::GGraphic::GObjectSmartPointer<T>::operator==(value_pointer pObj) const
{
	return m_pObject == pObj;
}

template<class T>
inline bool GEngine::GGraphic::GObjectSmartPointer<T>::operator!=(value_pointer pObj) const
{
	return m_pObject != pObj;
}

template<class T>
inline bool GEngine::GGraphic::GObjectSmartPointer<T>::operator==(const GObjectSmartPointer& rhs) const
{
	return m_pObject == rhs.m_pObject;
}

template<class T>
inline bool GEngine::GGraphic::GObjectSmartPointer<T>::operator!=(const GObjectSmartPointer& rhs) const
{
	return m_pObject != rhs.m_pObject;
}
