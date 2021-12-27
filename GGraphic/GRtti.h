#ifndef GRTTI_H
#define GRTTI_H
#include <GStrings.h>
#include "GGraphics.h"
namespace GEngine {
	namespace GGraphic {

		class GObject;
		class GProperty;
		typedef GObject* (*FactoryFunction)();

		class GGRAPHIC_API GRtti
		{
		public:
			GRtti(const TCHAR* _className, GRtti* _parent, FactoryFunction* cof);
			~GRtti();

			bool operator==(const GRtti& rhs) const;
			bool operator!=(const GRtti& rhs) const;
			bool IsSampleType(const GRtti& rhs) const;
			bool IsDerived(const GRtti& rhs) const;
			const GStl::GTString& Name() const;
			
			void InitialGenerateFun(FactoryFunction* cof);
			inline GObject* Generate()
			{
				if (__cof != nullptr)
					return (*__cof)();
				return nullptr;
			}

			GProperty* GetProperty(unsigned int uiIndex) const;
			unsigned int GetPropertyNum() const;
			void AddProperty(GProperty* pProperty);
			void AddProperty(GRtti& rtti);
			void ClearProperty();


		private:
			GStl::GTString m_className;
			GRtti* m_pParent;
			FactoryFunction* __cof;

			GStl::GVector<GProperty*> m_PropertyArray;
		};

#include "GRtti.marc"
	}
}
#endif // !GRTTI_H
