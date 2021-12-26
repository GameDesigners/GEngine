#ifndef GREFERENCE_H
#define GREFERENCE_H
#include "GGraphics.h"

namespace GEngine {
	namespace GGraphic {

		class GGRAPHIC_API GReference
		{
		public:
			int GetReferenceCount() const { return m_ref_count; }
			void IncreaseReferenceCount() { GEngine::GSystem::GLockedIncrement((long*)(&m_ref_count)); }
			void DecreaseReferenceCount() 
			{ 
				GEngine::GSystem::GLockedDecrement((long*)(&m_ref_count)); 
				if (m_ref_count == 0)
				{
					GDELETE this;
				}
			}

		private:
			int m_ref_count;
		};



		template<class T>
		class GGRAPHIC_API GObjectSmartPointer
		{
		public:
			typedef T         value_type;
			typedef T*        value_pointer;
			typedef const T*  const_value_pointer;
			typedef T&        value_reference;

		public:
			GObjectSmartPointer(value_pointer pObj = nullptr);
			GObjectSmartPointer(const GObjectSmartPointer& cv);
			~GObjectSmartPointer();
			
			T& operator*() const;
			T* operator->() const;
			operator T* () const;
			GObjectSmartPointer<T>& operator=(value_pointer pObj);
			GObjectSmartPointer<T>& operator=(const GObjectSmartPointer& cv);
			bool operator==(value_pointer pObj) const;
			bool operator!=(value_pointer pObj) const;
			bool operator==(const GObjectSmartPointer& rhs)  const;
			bool operator!=(const GObjectSmartPointer& rhs) const;

		private:
			inline void SetObject(value_pointer pObj) { m_pObject = pObj; }
			inline T* GetObject() { return m_pObject; }
			value_pointer m_pObject;
		};

#include "GReference.inl"
	}
}


#endif // !GREFERENCE_H
