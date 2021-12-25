#ifndef USE_GMAP_AND_GMULTIMAP_SAMPLE_H
#define USE_GMAP_AND_GMULTIMAP_SAMPLE_H
#include <GMap.h>
#include "CommonData.h"
using namespace GEngine::GSystem;
using namespace GEngine::GStl;

ostream& operator<<(ostream& os, GMap<int,SamplesElem>& map)
{
	os << "set 's count:" << map.size() << endl;
	for (GMap<int, SamplesElem>::iterator_type p = map.begin(); p != map.end(); p++)
	{
		os << "key:" << (*p).first<<"    ";
		p->to_string();
	}
	os << endl;
	return os;
}

void GMapSample()
{
	GMap<int, SamplesElem> map1;
	for (int index = 0; index < 10; index++)
		map1.insert(index, SamplesElem(index, index));

	GMap<int, SamplesElem> map2(map1);
	GMap<int, SamplesElem> map3(g_move(map2));
	GMap<int, SamplesElem>::iterator_type iter = ++map3.begin();
	GMap<int, SamplesElem> map4(iter, map3.end());

	GMap<int, SamplesElem> map5 = {
		{2,SamplesElem(2.111,2.222)},
		{1,SamplesElem(1.111,1.222)},
		{4,SamplesElem(4.111,4.222)},
		{5,SamplesElem(5.111,5.222)},
		{3,SamplesElem(3.111,3.222)},
	};
	


	map3 = map5;
	map1.swap(map5);

	/*map5[0].to_string();
	map5[555] = SamplesElem(5, 5555555);
	map5.at(555).to_string();*/

	iter = ++map5.begin();
	++iter; ++iter;
	(*iter).second.to_string();
	map1.insert(iter, map5.end());

	cout << map1;
	cout << map2;
	cout << map3;
	cout << map4;
	cout << map5;
}

#endif // !USE_GMAP_AND_GMULTIMAP_SAMPLE_H
