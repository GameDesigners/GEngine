#ifndef GRTTI_H
#define GRTTI_H
#include <GStrings.h>
#include "GGraphics.h"
namespace GEngine {
	namespace GGraphic {

		class GObject;
		typedef GObject* (*CreateObjectFunc)();

		class GGRAPHIC_API GRtti
		{
		public:
			GRtti(const TCHAR* _className, GRtti* _parent, CreateObjectFunc* cof);
			~GRtti();

			bool operator==(const GRtti& rhs) const;
			bool operator!=(const GRtti& rhs) const;
			bool IsSampleType(const GRtti& rhs) const;
			bool IsDerived(const GRtti& rhs) const;
			const GStl::GTString& Name() const;
			
			inline GObject* Generate()
			{
				if (__cof != nullptr)
					return (*__cof)();
				return nullptr;
			}

		private:
			GStl::GTString m_className;
			GRtti* m_pParent;
			CreateObjectFunc* __cof;
		};

#include "GRtti.marc"
	}
}
#endif // !GRTTI_H
