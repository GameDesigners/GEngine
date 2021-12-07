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


	cout << list1;
	cout << list2;
	cout << list3;
	cout << list4;

}



#endif // !USE_GLIST_SAMPLE_H
