#ifndef GOBJECT_SYSTEM_SAMPLES_H
#define GOBJECT_SYSTEM_SAMPLES_H
#include <GReference.h>
#include "CommonData.h"
using namespace GEngine::GGraphic;

class A : public GReference
{
public:
	void to_string()
	{
		cout << "hello world!" << endl;
	}
};

void GObjectSmartPointerSample()
{
	GObjectSmartPointer<A> a(GNEW A());
	a->to_string();
}

#endif // !GOBJECT_SYSTEM_SAMPLES_H
