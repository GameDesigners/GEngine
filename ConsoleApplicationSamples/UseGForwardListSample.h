#ifndef USE_GORWARDLIST_LIST_SAMPLE
#define USE_GORWARDLIST_LIST_SAMPLE

#include <GForwardList.h>
#include "CommonData.h"

ostream& operator<<(ostream& os, GForwardList<SamplesElem>& list)
{
	os << "list"<<std::endl;
	for (auto p = list.begin(); p != list.end(); p++)
		p->to_string();
	os << endl;
	return os;
}


void GForwardListSample()
{
	GForwardList<SamplesElem> forward_list1;
	for (int index = 0; index < 10; index++)
		forward_list1.push_front(SamplesElem(index, index));

	GForwardList<SamplesElem> forward_list2(forward_list1);
	GForwardList<SamplesElem> forward_list3(g_move(forward_list2));
	GForwardList<SamplesElem> forward_list4(5);
	GForwardList<SamplesElem> forward_list5(6, SamplesElem(2013, 14.0));
	GForwardList<SamplesElem> forward_list6(forward_list5.begin(), forward_list5.end());
	GForwardList<SamplesElem> forward_list7({
		SamplesElem(5776, 13.14),
		SamplesElem(496, 86.354),
		SamplesElem(2718, 251.56),
		SamplesElem(374, 7684)
	});

	//forward_list6 = g_move(forward_list7);
	forward_list7 = {
		SamplesElem(5464, 13.14),
		SamplesElem(1234, 23.4),
		SamplesElem(8974, 213.369),
		SamplesElem(25, 14570.1),
		SamplesElem(25, 14570.1)
	};

	forward_list7.assign(10,SamplesElem(10,10));
	forward_list7.assign(forward_list6.begin(), forward_list6.end());
	forward_list7.assign(
		{
			SamplesElem(454, 13.14),
		    SamplesElem(3212, 23.4),
		    SamplesElem(55112, 213.369),
		    SamplesElem(55454, 14570.1),
		    SamplesElem(4874, 14570.1)
		}
	);

	forward_list7.swap(forward_list6);
	forward_list7.front() = SamplesElem(20, 13.14);
	forward_list7.push_front(SamplesElem(19, 13.14));
	forward_list7.push_front(SamplesElem(18, 13.14));
	forward_list7.pop_front();
	GForwardList<SamplesElem>::iterator_type iter = forward_list7.begin();
	for (int index = 0; index < 2; index++)
		iter++;
	GForwardList<SamplesElem>::iterator_type insert1=forward_list7.insert_after(iter, SamplesElem(20000, 20000));
	GForwardList<SamplesElem>::iterator_type insert2 = forward_list7.insert_after(insert1, 10, SamplesElem(20001, 20001));
	GForwardList<SamplesElem>::iterator_type insert3 = forward_list7.insert_after(insert2, forward_list6.begin(),forward_list6.end());
	GForwardList<SamplesElem>::iterator_type insert4 = forward_list7.insert_after(insert3,
		{ 
			SamplesElem(17, 13.14),
			SamplesElem(17, 13.14),
			SamplesElem(20, 13.14),
			SamplesElem(20, 13.14),
			SamplesElem(17, 13.14),
			SamplesElem(17, 13.14),
		}
	);
	forward_list7.emplace_after(insert4, 12, 12);
	forward_list7.emplace_front(0, 0);
	forward_list7.remove(SamplesElem(2013, 14));

	iter = forward_list7.begin();
	for (int index = 0; index < 2; index++)
		iter++;

	GForwardList<SamplesElem>::iterator_type iter2 = forward_list1.begin();
	for (int index = 0; index < 5; index++)
		iter2++;

	GForwardList<SamplesElem>::iterator_type iter3 = forward_list1.begin();
	for (int index = 0; index < 8; index++)
		iter3++;

	iter->to_string();
	iter2->to_string();
	iter3->to_string();
	//forward_list7.erase_after(iter);
	//forward_list7.erase_after(iter, iter2);
	//forward_list7.resize(3);
	//forward_list7.resize(5, SamplesElem(1, 1));
	//forward_list7.unique();
	//forward_list7.splice_after(iter, forward_list1);
	//forward_list7.splice_after(forward_list7.begin(), forward_list1, forward_list1.begin());
	//forward_list1.merge(forward_list7);
	//forward_list7.splice_after(iter, forward_list1, iter2, iter3);
	//forward_list1.sort();
	//forward_list7.sort();
	//forward_list1.reverse();
	cout << endl;
	cout << forward_list1;
	cout << forward_list7;
	cout << endl;

	cout << "forward_list1 = forward_list7" << (forward_list1 == forward_list7) << endl;
	cout << "forward_list1 != forward_list7" << (forward_list1 != forward_list7) << endl;
	cout << "forward_list1 > forward_list7" << (forward_list1 > forward_list7) << endl;
	cout << "forward_list1 >= forward_list7" << (forward_list1 >= forward_list7) << endl;
	cout << "forward_list1 < forward_list7" << (forward_list1 < forward_list7) << endl;
	cout << "forward_list1 <= forward_list7" << (forward_list1 <= forward_list7) << endl;
	/*
	cout << forward_list2;
	cout << forward_list3;
	cout << forward_list4;
	cout << forward_list5;
	cout << forward_list6;*/
	//cout << forward_list1;
	
	cout << forward_list1;
	cout << forward_list7;


	//iter->to_string();
	/*insert1->to_string();
	insert2->to_string();
	insert3->to_string();
	insert4->to_string();*/
}
#endif // !USE_GORWARDLIST_LIST_SAMPLE
