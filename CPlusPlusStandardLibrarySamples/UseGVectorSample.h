#ifndef USE_GVECTOR_SAMPLE_H
#define USE_GVECTOR_SAMPLE_H
#include <iostream>
#include <string>
#include <GArray.h>
#include <GVector.h>

#include <array>
#include <vector>
using namespace GEngine::GSystem;
using namespace GEngine::GStl;

void GVectorSample()
{
	SamplesElem temp(520, 13.14);
	GVector<SamplesElem> vector1;
	for (int idx = 0; idx < 5; idx++)
		vector1.push_back(SamplesElem(idx, 20.2));
	
	GVector<SamplesElem> vector2(vector1);
	GVector<SamplesElem> vector3(g_move(vector2));
	GVector<SamplesElem> vector4(10);
	GVector<SamplesElem> vector5(10, temp);
	//GVector<SamplesElem> vector6(vector5.begin(),vector5.end());

	std::cout << "vector5 size:" << vector5.size() << " capcity:" << vector5.capcity() << std::endl;

	for (auto p = vector5.begin(); p != vector5.end(); p++)
		p->to_string();
	std::cout << std::endl;
	/*for (auto p = vector2.begin(); p != vector2.end(); p++)
		p->to_string();*/
}

#endif // !USE_GVECTOR_SAMPLE_H
