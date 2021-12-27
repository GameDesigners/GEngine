#ifndef GOBJECT_H
#define GOBJECT_H
#include <GMap.h>
#include "GReference.h"
#include "GRtti.h"
#include "GMain.h"

namespace GEngine {
	namespace GGraphic {
		using namespace GEngine::GSystem;

		class GFastObjectManager;
		class GObject;

		class GGRAPHIC_API GFastObjectManager
		{
			friend class GObject;

			enum
			{
				MAX_OBJECT_FLAG = 100000,
				MAX_OBJECT_NUM = MAX_OBJECT_FLAG - 1
			};
		public:
			GFastObjectManager();
			~GFastObjectManager();

		private:
			unsigned int AddObject(GObject* p);
			void DeleteObject(GObject* p);
			bool IsClear();
			void PrepareForGC();
			unsigned int GetObjectNum();


			GObject* m_ObjectArray[MAX_OBJECT_FLAG];
			GStl::GVector<unsigned int> m_FreeTable;

		};

		class GGRAPHIC_API GObject : public GReference, public GMemObject
		{
			typedef GStl::GTString  GUserName;

			DECLARE_RTTI(GObject)
			DECLARE_INITIALIZE_TERMINAL_CODE(GObject)

		protected:
			GObject();

		public:
			virtual ~GObject();

			friend class GFastObjectManager;
			GFastObjectManager& GetObjectManager()
			{
				static GFastObjectManager objManager;
				return objManager;
			}

		protected:
			static GStl::GMap<GUserName, FactoryFunction> ms_ClassFactory;
			
		private:
			unsigned int m_uiObjectID;
		};

		GStl::GMap<GStl::GTString, FactoryFunction> GObject::ms_ClassFactory;

		IMPLEMENT_RTTI_NO_PARENT_NO_GENERATE_FUNC(GObject)
		IMPLEMENT_INITIALIZE_TERMINAL_BEGIN(GObject)
		IMPLEMENT_INITIALIZE_TERMINAL_END


		

		//强制类型转换函数
		//**********************************************************************************************************************************************

		template<typename T> inline T* Static_Cas(GObject* pkObj)
		{
			return static_cast<T*>(pkObj);
		}

		template<typename T> inline const T* Static_Cast(const GObject* pkObj)
		{
			return static_cast<const T*>(pkObj);
		}

		template<typename T> inline T* Dynamic_Cast(GObject* pkObj)
		{
			return pkObj && pkObj->IsDerived(T::Type) ? static_cast<T*>(pkObj) : nullptr;
		}

		template<typename T> inline const T* Dynamic_Cast(GObject* pkObj)
		{
			return pkObj && pkObj->IsDerived(T::Type) ? static_cast<const T*>(pkObj) : nullptr;
		}

#include "GObject.marc"
	}
}
#endif // !GOBJECT_H
