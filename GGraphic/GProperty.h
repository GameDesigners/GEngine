#ifndef GPROPERTY_H
#define GPROPERTY_H
#include "GGraphics.h"
#include "GRtti.h"
namespace GEngine {
	namespace GGraphic {

		typedef GStl::GTString GUserdName;
		class GGRAPHIC_API GProperty
		{
		protected:
			enum
			{
				F_SAVE_LOAD       = 0X01,
				F_CLONE           = 0X02,
				F_COPY            = 0X04,
				F_SAVE_LOAD_CLONE = 0X03,
				F_SAVE_LOAD_COPY  = 0X05,
				F_REFLECT_NAME    = 0X08,
				F_MAX
			};

			GProperty(GRtti& owner, const GUserdName& name, unsigned int uiElementOffset, unsigned int uiFlags);

			virtual void* GetValueAddress(void* pObj) const;
			virtual void Clone(GProperty* p);

		private:
			GRtti* m_pOwner;
			GUserdName m_Name;
			unsigned int m_uiFlag;
			unsigned int m_uiElementOffset;
		};

		template<typename T>
		class GGRAPHIC_API GEnumProperty : public GProperty
		{
			GEnumProperty(GRtti& owner, const GUserdName& name, const GUserdName& enumName, unsigned int uiElementOffset, unsigned int uiFlags);
			virtual void Clone(GProperty* p);
			virtual bool SetValue(void* pObj, T& dataSrc) const;
			virtual bool GetValue(void* pObj, T& dataDest) const;
			virtual bool GetValue(const void* pObj, T& dataDest) const;
			virtual T& Value(void* pObj) const;
			virtual GProperty* GetInstance();

			GUserdName m_EnumName;
		};

		template<typename T>
		class GGRAPHIC_API GDataProperty : public GProperty
		{
			GDataProperty(GRtti& owner, const GUserdName& name, unsigned int uiElementOffset, unsigned int uiDataNum, bool bDynamicCreate);

			virtual void Clone(GProperty* p);
			virtual GProperty* GetInstance();

		private:
			bool m_bDynamicCreate;
			unsigned int m_uiDataNum;
			unsigned int m_uiElementOffset;

			
		};

#include "GProperty.inl"
	}
}
#endif // !GFAST_OBJECT_MANAGER_H
