#ifndef USE_GSET_AND_GMULTISET_SAMPLE
#define USE_GSET_AND_GMULTISET_SAMPLE
#include <GSet.h>
#include "CommonData.h"
using namespace GEngine::GSystem;
using namespace GEngine::GStl;

ostream& operator<<(ostream& os, GSet<SamplesElem>& set)
{
	os << "set 's count:" << set.size() << endl;
	for (GSet<SamplesElem>::iterator_type p = set.begin(); p != set.end(); p++)
		p->to_string();
	os << endl;
	return os;
}

ostream& operator<<(ostream& os, GMultiSet<SamplesElem>& set)
{
	os << "set 's count:" << set.size() << endl;
	for (GMultiSet<SamplesElem>::iterator_type p = set.begin(); p != set.end(); p++)
		p->to_string();
	os << endl;
	return os;
}

void GSetSample()
{
	GSet<SamplesElem> set1;
	for (int index = 0; index < 10; index++)
		set1.insert(SamplesElem(index, index));
	GSet<SamplesElem> set2(set1);
	GSet<SamplesElem> set3(g_move(set1));
	GSet<SamplesElem> set4(set3.begin(),set3.end());
	GSet<SamplesElem> set5({
		SamplesElem(1314,50.6),
		SamplesElem(3434,3489.7),
		SamplesElem(54645,5768.7),
		SamplesElem(34545,346.7),		
		SamplesElem(54645,5768.7),
		});

	GSet<SamplesElem> set6({
		SamplesElem(1314,50.6),
		SamplesElem(3434,3489.7),
		SamplesElem(54645,5768.7),
		SamplesElem(34545,346.7),
		SamplesElem(54645,5768.7),
		});

	set6 = set2;
	set6 = set5;
	set6 = g_move(set5);
	set6 = {
		SamplesElem(1314,50.6),
		SamplesElem(3434,3489.7),
		SamplesElem(54645,5768.7),
		SamplesElem(34545,346.7),
		SamplesElem(8,8.8),
		SamplesElem(6,6.666)
	};

	set6.swap(set4);
	GSet<SamplesElem>::comparator_type c = set6.value_comparator();
	GSet<SamplesElem> set7(set6);
	set7.insert(set4.begin(), set4.end());
	set7.insert({
		SamplesElem(1314, 50.6),
		SamplesElem(3434, 3489.7),
		SamplesElem(1,1.1111),
		SamplesElem(2,1.1111),
		SamplesElem(3,1.1111),
		SamplesElem(8, 8.8),
		SamplesElem(6, 6.666)
		});
	set7.emplace(1, 2);
	set7.earse(SamplesElem(1, 2));

	auto itera = ++set7.begin();
	set7.earse(itera);
	itera = ++set7.begin();

	cout << set7;
	itera->to_string();

	//set7.earse(itera, set7.end());
	itera = set7.find(SamplesElem(1, 1.1111));
	/*cout << set1;
	cout << set2;
	cout << set3;
	cout << set4;
	cout << set5;
	cout << set6;*/
	cout << set7;

	GMultiSet<SamplesElem> multiset;
	multiset.insert({
		SamplesElem(1,1.1111),
		SamplesElem(1,1.1111),
		SamplesElem(1,1.1111),
		SamplesElem(1,1.1111),
		});
	cout << multiset;

}

#endif // !USE_GSET_AND_GMULTISET_SAMPLE
