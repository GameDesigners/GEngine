#ifndef USE_GDEQUE_SAMPLE_H
#define USE_GDEQUE_SAMPLE_H
#include "GDeque.h"
using namespace GEngine::GSystem;
using namespace GEngine::GStl;
void GDeuqeSample()
{
	GDeque<SamplesElem> deque1;
	GDeque<SamplesElem> deque2(28);
	GDeque<SamplesElem> deque3(24, SamplesElem(12, 25.3));
}
#endif // !USE_GDEQUE_SAMPLE_H
