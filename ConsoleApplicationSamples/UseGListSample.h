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
	GList<SamplesElem> list4(10);
	GList<SamplesElem> list5(5, SamplesElem(1, 1));
	GList<SamplesElem>::iterator_type iter1 = list5.begin();
	for (int index = 0; index < 2; index++) iter1++;
	GList<SamplesElem> list6(iter1, list5.end());
	GList<SamplesElem> list7 = {
		SamplesElem(5776, 13.14),
		SamplesElem(496, 86.354),
		SamplesElem(2718, 251.56),
		SamplesElem(374, 7684),
		SamplesElem(374, 7684)
	};

	list1 = list7;
	list7 = g_move(list1);
	list7 = {
		SamplesElem(374, 7684),
		SamplesElem(1, 1),
		SamplesElem(5776, 13.14),
		SamplesElem(496, 86.354),
		SamplesElem(374, 7684),
		SamplesElem(2718, 251.56),
		SamplesElem(374, 7684),
		SamplesElem(374, 7684),
		SamplesElem(374, 7684),
	};
	/*list7.swap(list6);
	list7.swap(list6);

	list7.front() = SamplesElem(1, 1);
	list7.back() = SamplesElem(99999, 999.999);
	list7.pop_back();
	list7.push_back(SamplesElem(888888, 888.888));
	list7.pop_front();
	list7.push_front(SamplesElem(111111, 111.111));*/
	
	/*
	list7.insert(iter1, {
	SamplesElem(111111, 111.111),
	SamplesElem(111111, 111.111),
	SamplesElem(111111, 111.111)
		});
	*/
	//list7.insert(iter1, SamplesElem(222222, 222.222));
	//list7.insert(iter1, 5,SamplesElem(222222, 222.222));
	//list7.insert(iter1, iter2, iter3);
	//list7.emplace(iter1, 123, 666.666);
	//list7.emplace_front(14568, 25655);
	//list7.emplace_back(1454, 12364);
	//list7.erase(iter1);
	//list4.erase(iter2, iter3);
	//list4.remove(SamplesElem());
	//list7.remove(SamplesElem(374, 7684));
	//list7.resize(10,SamplesElem(555555,555.555));
	cout << list4;
	cout << list7;

	iter1 = list7.begin();
	for (int index = 0; index < 2; index++) iter1++;
	GList<SamplesElem>::iterator_type iter2 = list4.begin();
	for (int index = 0; index < 1; index++) iter2++;
	GList<SamplesElem>::iterator_type iter3 = list4.begin();
	for (int index = 0; index < 4; index++) iter3++;

	iter1->to_string();
	iter2->to_string();
	iter3->to_string();


	cout << "list4 == list7--> " <<  (list4 == list7) << endl;
	cout << "list4 != list7--> " <<  (list4 != list7) << endl;
	cout << "list4 >  list7--> " <<  (list4 >  list7) << endl;
	cout << "list4 >= list7--> " <<  (list4 >= list7) << endl;
	cout << "list4 <  list7--> " <<  (list4 <  list7) << endl;
	cout << "list4 <= list7--> " <<  (list4 <= list7) << endl;
	cout << list4;
	cout << list7;

	cout << "**************************************" << endl;
	for (auto p = list7.cbegin(); p != list7.cend(); p++)
		p->to_string();
	cout << endl;
	for (auto p = list7.rbegin(); p != list7.rend(); p++)
		p->to_string();
	cout << endl;
	for (auto p = list7.crbegin(); p != list7.crend(); p++)
		p->to_string();
	/*cout << list1;
	cout << list2;
	cout << list3;
	cout << list4;
	cout << list5;
	*/


}



#endif // !USE_GLIST_SAMPLE_H
