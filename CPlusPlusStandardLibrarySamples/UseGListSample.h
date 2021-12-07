#ifndef USE_GLIST_SAMPLE_H
#define USE_GLIST_SAMPLE_H

#include <GList.h>
using namespace GEngine::GSystem;
using namespace GEngine::GStl;

ostream& operator<<(ostream& os, GList<SamplesElem>& list)
{
	os << "listÔªËØ¡¾cout:"<<list.size() << "¡¿\n";
	for (auto p = list.begin(); p != list.end(); p++)
		p->to_string();
	os << endl;
	return os;
}


void GListSample()
{
	GList<SamplesElem> list1;
	for (int index = 0; index < 10; index++)
		list1.push_back(SamplesElem(index, index));

	GList<SamplesElem> list2(list1);
	GList<SamplesElem> list3(g_move(list2));
	GList<SamplesElem> list4(5);
	GList<SamplesElem> list5(6, SamplesElem(101, 13.14));
	GList<SamplesElem> list6(list1.begin(), list1.end());
	GList<SamplesElem> list7({
		SamplesElem(101, 13.14),
		SamplesElem(38540, 86.354),
		SamplesElem(343, 126.856),
		SamplesElem(23453, 34.245)
		});

	list2 = list7;
	GList<SamplesElem> list8 = g_move(list2);
	list1 = {
		SamplesElem(5776, 13.14),
		SamplesElem(496, 86.354),
		SamplesElem(2718, 251.56),
		SamplesElem(374, 7684)
	};

	list6.assign(12, SamplesElem(2718, 251.56));
	list2.assign(list1.begin(), list1.end());

	list2.assign({
		SamplesElem(75858, 13.14),
		SamplesElem(373, 86.354),
		SamplesElem(284, 251.56),
		SamplesElem(12, 7684)
		});

	list1.swap(list2);

	list1.front() = SamplesElem(0, 0);
	list1.back() = SamplesElem(1, 1);
	list1.pop_back();
	list1.pop_front();
	list1.push_front(SamplesElem(11, 1));
	list1.push_front(SamplesElem(15, 1));
	list1.push_front(SamplesElem(10, 1));
	for (auto p = list1.begin(); p != list1.end(); p++)
	{

	}

	cout << list1;
	cout << list2;
	cout << list3;
	cout << list4;
	cout << list5;
	cout << list6;
	cout << list7;
	cout << list8;
	

}



#endif // !USE_GLIST_SAMPLE_H
