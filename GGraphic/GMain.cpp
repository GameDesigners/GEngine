#include "GMain.h"
using namespace GEngine::GGraphic;

GEngine::GStl::GVector<GMain::Element>*   GMain::ms_pInitialVector = nullptr;
GEngine::GStl::GVector<FunctionProperty>* GMain::ms_pInitialPropertyVector = nullptr;
GEngine::GStl::GVector<GMain::Element>*   GMain::ms_pTerminalVector = nullptr;
GEngine::GStl::GVector<Function>*         GMain::ms_pTerminalPropertyVector = nullptr;
unsigned int                              GMain::ms_uiInitialObject = 0;
unsigned int                              GMain::ms_uiTerminalObject = 0;

void GEngine::GGraphic::GMain::AddInitialPropertyFunction(FunctionProperty Func)
{
	if (Func == nullptr)
		return;

	if (ms_pInitialPropertyVector == nullptr)
		ms_pInitialPropertyVector = GNEW GStl::GVector<FunctionProperty>;

	ms_pInitialPropertyVector->push_back(Func);
}

void GEngine::GGraphic::GMain::AddTerminalPropertyFunction(Function Func)
{
	if (Func == nullptr)
		return;

	if (ms_pTerminalPropertyVector == nullptr);
	ms_pTerminalPropertyVector = GNEW GStl::GVector<Function>;

	ms_pTerminalPropertyVector->push_back(Func);
}

void GEngine::GGraphic::GMain::AddInitialFunction(Function Func)
{
	AddInitialFunction(Func, nullptr);
}

void GEngine::GGraphic::GMain::AddInitialFunction(Function Func, GPriority* pPriority)
{
	if (Func == nullptr)
		return;

	if (ms_pInitialVector == nullptr)
		ms_pInitialVector = GNEW GStl::GVector<Element>;

	Element e;
	e.__fun = Func;
	e.__pPriority = pPriority;
	ms_pInitialVector->push_back(e);
}

bool GEngine::GGraphic::GMain::Initialize()
{
	if (ms_pInitialPropertyVector != nullptr)
	{
		for (int index = 0; index < ms_pInitialPropertyVector->size(); index++)
		{
			if (!(*(*ms_pInitialPropertyVector)[index])(nullptr))
			{
				GASSERT(0);
				return false;
			}
		}
		ms_pInitialPropertyVector->clear();
	}

	if (ms_pInitialVector != nullptr)
	{
		GStl::sort(ms_pInitialVector->begin(), ms_pInitialVector->end(), ElementLessThan());
		for (int index = 0; index < ms_pInitialVector->size(); index++)
		{
			if (!(*ms_pInitialVector)[index].__fun())
			{
				GASSERT(0);
				return false;
			}
		}
		ms_pInitialVector->clear();
	}

	GSAFE_DELETE(ms_pInitialPropertyVector);
	GSAFE_DELETE(ms_pInitialVector);
	return true;
}

void GEngine::GGraphic::GMain::AddTerminalFuntion(Function Func)
{
	AddTerminalFuntion(Func, nullptr);
}

void GEngine::GGraphic::GMain::AddTerminalFuntion(Function Func, GPriority* pPriority)
{
	if (Func == nullptr)
		return;

	if (ms_pTerminalVector == nullptr)
		ms_pTerminalVector = GNEW GStl::GVector<GMain::Element>;

	Element e;
	e.__fun = Func;
	e.__pPriority = pPriority;
	ms_pTerminalVector->push_back(e);
}

bool GEngine::GGraphic::GMain::Terminate()
{
	if (ms_pTerminalPropertyVector!=nullptr)
	{
		for (int index = ms_pTerminalPropertyVector->size() - 1; index >= 0; index--)
		{
			if (!(*(*ms_pTerminalPropertyVector)[index])())
			{
				GASSERT(0);
				return false;
			}
		}
		ms_pTerminalPropertyVector->clear();
	}
	
	if (ms_pTerminalVector != nullptr)
	{
		GStl::sort(ms_pTerminalVector->begin(), ms_pTerminalVector->end(), ElementLessThan());
		for (int index = ms_pTerminalVector->size() - 1; index >= 0; index--)
		{
			if (!(*ms_pTerminalVector)[index].__fun())
			{
				GASSERT(0);
				return false;
			}
		}
		ms_pTerminalVector->clear();
	}
	
	GSAFE_DELETE(ms_pTerminalPropertyVector);
	GSAFE_DELETE(ms_pTerminalVector);
	return true;
}

GEngine::GGraphic::GMain::GMain() {}
GEngine::GGraphic::GMain::~GMain() {}


