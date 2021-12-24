#ifndef GMAIN_H
#define GMAIN_H
#include "GPriority.h"
#include "GVector.h"
#include "GAlgorithm.h"

namespace GEngine {
	namespace GGraphic {


		typedef bool (*Function)();
		class GRtti;
		typedef bool (*FunctionProperty)(GRtti*);

		class GGRAPHIC_API GMain
		{
		public:
			static void AddInitialPropertyFunction(FunctionProperty Func);
			static void AddTerminalPropertyFunction(Function Func);
			static void AddInitialFunction(Function Func);
			static void AddInitialFunction(Function Func, GPriority* pPriority);
			static bool Initialize();
			static void AddTerminalFuntion(Function Func);
			static void AddTerminalFuntion(Function Func, GPriority* pPriority);
			static bool Terminate();

		public:
			GMain();
			~GMain();

			class GGRAPHIC_API Element
			{
			public:
				Element() {}
				Element(const Function fun, GPriority* p) : __fun(fun), __pPriority(p) {}
				void operator=(const Element& e)
				{
					__fun = e.__fun;
					__pPriority = e.__pPriority;
				}

			public:
				Function   __fun;
				GPriority* __pPriority;
			};

		private:
			class ElementLessThan
			{
			public:
				bool operator()(const Element& elem1, const Element& elem2) const
				{
					unsigned int priority1 = elem1.__pPriority->GetPriorityNum();
					unsigned int priority2 = elem1.__pPriority->GetPriorityNum();
					return priority1 < priority2;
				}
			};

			static GStl::GVector<Element>* ms_pInitialVector;
			static GStl::GVector<FunctionProperty>* ms_pInitialPropertyVector;
			static GStl::GVector<Element>* ms_pTerminalVector;
			static GStl::GVector<Function>* ms_pTerminalPropertyVector;
			static unsigned int ms_uiInitialObject;
			static unsigned int ms_uiTerminalObject;
		};
	}
}
#endif // !GMAIN_H
