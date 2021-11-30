#ifndef USE_GARRAY_SAMPLE_H
#define USE_GARRAY_SAMPLE_H
#include <GArray.h>
using namespace GEngine::GStl;


void GArraySample()
{
	//使用默认构造函数
	GArray<SamplesElem,10> array1;    

	for (int idx = 0; idx < 10; idx++)
		array1[idx] = SamplesElem(idx + 1, 10.5);

	//赋值构造函数
	GArray <SamplesElem, 10> array2(array1);

	//移动构造函数
	GArray<SamplesElem, 10> array3(g_move(array2));

	GArray<SamplesElem, 10> array4{
		SamplesElem(1, 10.5),
		SamplesElem(2, 10.5),
		SamplesElem(3, 10.5),
	};

	GArray<SamplesElem, 3> array5(array4.begin(), array4.begin() + 3);

	GArray<SamplesElem, 3> array6;
	array6 = array5;

	GArray<SamplesElem, 3> array7;
	array7 = g_move(array6);


	array7 = {
		SamplesElem(5, 10.5),
		SamplesElem(7, 10.5),
		SamplesElem(2, 10.5),
	};

	GArray<SamplesElem, 3> array8;
	array8.fill(SamplesElem(122, 10.5));

	array8.swap(array7);

	for (auto p = array7.begin(); p != array7.end(); p++)
		p->to_string();
	for (auto p = array8.begin(); p != array8.end(); p++)
		p->to_string();
	std::cout << std::endl;


}


#endif // !GUSE_GARRAY_SAMPLE_H
