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

	std::cout << array8.empty() << std::endl;
	std::cout << array8.size() << std::endl;
	std::cout << array8.capcity() << std::endl;

	GArray<int, 8> array9 = { 1,2,53,4,5 };
	GArray<int, 8> array10 = { 5,4,3,8,7,7 };

	std::cout << "array9 == array10=" << (array9 == array10) << std::endl;
	std::cout << "array9 !=array10=" << (array9 != array10) << std::endl;
	std::cout << "array9 < array10=" << (array9 < array10) << std::endl;
	std::cout << "array9 > array10=" << (array9 > array10) << std::endl;
	std::cout << "array9 >=array10=" << (array9 >= array10) << std::endl;
	std::cout << "array9 <=array10=" << (array9 <= array10) << std::endl;

	for (auto p = array9.begin(); p != array9.end(); ++p)
		std::cout << *p << " ";
	std::cout << std::endl;

	for (auto p = array9.cbegin(); p != array9.cend(); ++p)
		std::cout << *p << " ";
	std::cout << std::endl;

	for (auto p = array9.rbegin(); p != array9.rend(); ++p)
		std::cout << *p << " ";
	std::cout << std::endl;

	for (auto p = array9.crbegin(); p != array9.crend(); ++p)
		std::cout << *p << " ";
	std::cout << std::endl;
}


#endif // !GUSE_GARRAY_SAMPLE_H
