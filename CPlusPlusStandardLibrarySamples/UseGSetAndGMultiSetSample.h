#ifndef USE_GSET_AND_GMULTISET_SAMPLE
#define USE_GSET_AND_GMULTISET_SAMPLE
#include <GSet.h>
#include "CommonData.h"
using namespace GEngine::GSystem;
using namespace GEngine::GStl;

void GSetSample()
{
	GSet<SamplesElem> set1;
	GSet<SamplesElem> set2(g_move(set1));
}

#endif // !USE_GSET_AND_GMULTISET_SAMPLE
