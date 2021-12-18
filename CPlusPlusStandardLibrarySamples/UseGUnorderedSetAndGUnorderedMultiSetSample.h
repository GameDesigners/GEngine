#ifndef GUNORDEREDSET_AND_GUNORDEREDMULTISET_SAMPLE_H
#define GUNORDEREDSET_AND_GUNORDEREDMULTISET_SAMPLE_H
#include <GUnorderedSet.h>
#include "CommonData.h"
using namespace GEngine::GSystem;
using namespace GEngine::GStl;

HASH_FUNC_TEMPLATE_TITLE struct __extract_key_fun<SamplesElem>
{
	//哈希桶处理碰撞的函数
	size_t operator()(const SamplesElem& val) const
	{
		return *(val.i);
	}
};


ostream& operator<<(ostream& os,GUnorderedSet<int>& set)
{
	os << "set 's size: " << set.size();
	os << "| is empty? " << set.empty();
	os << "| load_factor: " << set.load_factor();
	os << endl << "**********************************" << endl;
	for (GUnorderedSet<int>::iterator_type p = set.begin(); p != set.end(); p++)
		cout << *p << " ";
	os << endl;
	return os;
}

void GUnorderedSetSample()
{
	GUnorderedSet<int> uset1;
	for (int index = 0; index < 10; index++)
		uset1.insert(index);

	cout << uset1;
}


#endif // !GUNORDEREDSET_AND_GUNORDEREDMULTISET_SAMPLE_H
