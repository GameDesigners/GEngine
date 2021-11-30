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

template<class T>
class Array
{
private:
	T arr[10] = {};
};

void GVectorSample()
{
	GArray<SamplesElem,2> sample_array;
	sample_array[0] = SamplesElem(1, 0);
	for (int index = 0; index < 2; index++)
		sample_array[index].to_string();

	GVector<GArray<SamplesElem, 2>> sample_elms;
	sample_elms.reserve(5);
	sample_elms.push_back(sample_array);
	
	for (int index = 0; index < sample_elms.size(); index++)
		sample_elms[index][0].to_string();
}

#endif // !USE_GVECTOR_SAMPLE_H
