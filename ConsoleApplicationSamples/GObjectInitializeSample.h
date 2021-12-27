#ifndef GOBJECT_INITIALIZE_SAMPLE_H
#define GOBJECT_INITIALIZE_SAMPLE_H
#include <GObject.h>
using namespace GEngine::GGraphic;

class GObjectReference_A :public GObject
{
	DECLARE_RTTI(GObjectReference_A)
	DECLARE_INITIALIZE_TERMINAL_CODE(GObjectReference_A)
	DECLARE_DEFAULT_GENERATE_FUNCTION(GObjectReference_A)
};

IMPLEMENT_RTTI_NO_GENERATE_FUNC(GObjectReference_A, GObject)
IMPLEMENT_INITIALIZE_TERMINAL_BEGIN(GObjectReference_A)
ADD_DEFAULT_GENERATE_FUN_TO_CLASS_FACTORY(GObjectReference_A)
IMPLEMENT_INITIALIZE_TERMINAL_END

void GObjectIntializeSample()
{
	//GObject* pA = GObjectReference_A::Type.Generate();
	//GObject* pB = GObject::ms_ClassFactory.at(GObjectReference_A::Type.Name())();
	//GDELETE pB;
}


#endif // !GOBJECT_INITIALIZE_SAMPLE_H
