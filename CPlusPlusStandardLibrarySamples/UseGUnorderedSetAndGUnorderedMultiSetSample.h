#ifndef GUNORDEREDSET_AND_GUNORDEREDMULTISET_SAMPLE_H
#define GUNORDEREDSET_AND_GUNORDEREDMULTISET_SAMPLE_H
#include <GUnorderedSet.h>
#include "CommonData.h"
using namespace GEngine::GSystem;
using namespace GEngine::GStl;


ostream& operator<<(ostream& os,GUnorderedSet<SamplesElem>& set)
{
	os << endl;
	os << "set 's size: " << set.size();
	os << "| is empty? " << set.empty();
	os << "| bucket_size: " << set.bucket_count();
	os << "| load_factor: " << set.load_factor();
	os << endl << "********************************************************" << endl;
	for (GUnorderedSet<SamplesElem>::iterator_type p = set.begin(); p != set.end(); p++)
		p->to_string();
	os << endl;
	return os;
}

void GUnorderedSetSample()
{
	GUnorderedSet<SamplesElem> uset1;
	for (int index = 0; index < 10; index++)
		uset1.insert(SamplesElem(index, index));

	if (!uset1.insert(SamplesElem(1, 2.1)).second)
		cout << "²åÈëÊ§°Ü" << endl;


	GUnorderedSet<SamplesElem> uset2(97);
	GUnorderedSet<SamplesElem> uset3(uset1);
	GUnorderedSet<SamplesElem> uset4(g_move(uset3));


	GUnorderedSet<SamplesElem>::iterator_type iter = uset4.begin();
	iter++; iter++;
	GUnorderedSet<SamplesElem> uset5(iter, uset4.end());
	iter = uset5.begin();
	GUnorderedSet<SamplesElem> uset6(iter, uset5.end(), 59);
	GUnorderedSet<SamplesElem> uset7 = {
		SamplesElem(62, 60.2),
		SamplesElem(122, 890.88),
		SamplesElem(1846, 8222.3),
		SamplesElem(62, 60.2),
		SamplesElem(122, 890.88),
		SamplesElem(1846, 8222.3)
	};

	uset6 = uset5;
	uset6=g_move(uset7);
	uset7.insert(SamplesElem(1, 1));
	uset6.swap(uset7);
	uset6.insert(uset1.begin(), uset1.end());
	uset6.insert({
		SamplesElem(62, 60.2),
		SamplesElem(122, 890.88),
		SamplesElem(1846, 8222.3),
		SamplesElem(62, 60.2),
		SamplesElem(122, 890.88),
		SamplesElem(1846, 8222.3)
		}
	);

	GUnorderedSet<SamplesElem>::iterator_type pos=uset6.emplace(1, 1.00002).first;
	uset6.earse(uset6.begin());
	iter = uset6.begin(); ++iter;
	uset6.earse(iter, uset6.end());

	cout << uset1;
	cout << uset2;
	cout << uset3;
	cout << uset4;
	cout << uset5;
	cout << uset6;
	cout << uset7;

	for (auto p = uset7.rbegin(); p != uset7.rend(); p++)
		p->to_string();
}


#endif // !GUNORDEREDSET_AND_GUNORDEREDMULTISET_SAMPLE_H
