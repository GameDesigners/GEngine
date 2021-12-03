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
	GDeque<SamplesElem> deque4({
		SamplesElem(1314,50.6),
		SamplesElem(3434,3489.7),
		SamplesElem(54645,5768.7),
		SamplesElem(34545,346.7)
		});
	GDeque<SamplesElem> deque5(deque3);
	deque5 = deque4;
	GDeque<SamplesElem> deque6(g_move(deque5));
	GDeque<SamplesElem> deque7= {
		SamplesElem(1314,50.6),
		SamplesElem(3434,3489.7),
		SamplesElem(54645,5768.7),
		SamplesElem(34545,346.7),
		SamplesElem(34545,346.7),
		SamplesElem(34545,346.7),
		SamplesElem(34545,346.7),
		SamplesElem(34545,346.7)
		};
	std::cout << "deque1 size:" << deque1.size() << " is_empty:" << deque1.empty() << std::endl;
	std::cout << "deque2 size:" << deque2.size() << " is_empty:" << deque2.empty() << std::endl;
	std::cout << "deque3 size:" << deque3.size() << " is_empty:" << deque3.empty() << std::endl;
	std::cout << "deque4 size:" << deque4.size() << " is_empty:" << deque4.empty() << std::endl;
	std::cout << "deque5 size:" << deque5.size() << " is_empty:" << deque5.empty() << std::endl;
	std::cout << "deque6 size:" << deque6.size() << " is_empty:" << deque6.empty() << std::endl;
	std::cout << "deque7 size:" << deque7.size() << " is_empty:" << deque7.empty() << std::endl;

	std::cout << std::endl;
	//__deque_memory_buffer_block<SamplesElem>* map= G 
}
#endif // !USE_GDEQUE_SAMPLE_H
