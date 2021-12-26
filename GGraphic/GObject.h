#ifndef GOBJECT_H
#define GOBJECT_H
#include "GReference.h"

namespace GEngine {
	namespace GGraphic {
		using namespace GEngine::GSystem;

		class GGRAPHIC_API GObject : public GReference, public GMemObject
		{

		};
	}
}
#endif // !GOBJECT_H
