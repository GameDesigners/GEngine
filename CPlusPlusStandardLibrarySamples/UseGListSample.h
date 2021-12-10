#ifndef USE_GLIST_SAMPLE_H
#define USE_GLIST_SAMPLE_H

#include <GList.h>
#include "CommonData.h"

using namespace GEngine::GSystem;
using namespace GEngine::GStl;

ostream& operator<<(ostream& os, GList<SamplesElem>& list)
{
	os << endl;
	os << "listÔªËØ¡¾cout:"<<list.size() << "¡¿\n";
	for (auto p = list.begin(); p != list.end(); p++)
		p->to_string();
	os << endl;
	return os;
}


void GListSample()
{
	GList<SamplesElem> list1;
	for (int index = 0; index < 5; index++)
		list1.push_back(SamplesElem(index, index));
	GList<SamplesElem> list2(list1);
	GList<SamplesElem> list3(g_move(list2));
	GList<SamplesElem> list4(5);
	GList<SamplesElem> list5(5, SamplesElem(1, 1));
	GList<SamplesElem>::iterator_type iter1 = list5.begin();
	for (int index = 0; index < 2; index++) iter1++;
	GList<SamplesElem> list6(iter1, list5.end());
	GList<SamplesElem> list7 = {
		SamplesElem(5776, 13.14),
		SamplesElem(496, 86.354),
		SamplesElem(2718, 251.56),
		SamplesElem(374, 7684)
	};

	list1 = list7;




	cout << list1;
	cout << list2;
	cout << list3;
	cout << list4;
	cout << list5;
	cout << list6;
	cout << list7;


}



#endif // !USE_GLIST_SAMPLE_H
