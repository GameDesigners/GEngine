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

void GVectorSample()
{
	SamplesElem temp(520, 13.14);
	GVector<SamplesElem> vector1;
	for (int idx = 0; idx < 5; idx++)
		vector1.push_back(SamplesElem(idx, 20.2));
	
	GVector<SamplesElem> vector2(vector1);
	GVector<SamplesElem> vector3(g_move(vector2));
	GVector<SamplesElem> vector4(10);
	GVector<SamplesElem> vector5(10, temp);
	GVector<SamplesElem> vector6(vector1.begin()+1, vector1.begin() + 3);
	GVector<SamplesElem> vector7({
			SamplesElem(22, 20.2),
			SamplesElem(52, 20.88),
			SamplesElem(46, 82.3),
		});

	
	GVector<SamplesElem> vector8 = vector7;
	GVector<SamplesElem> vector9 = g_move(vector8);

	vector9 = {
		SamplesElem(62, 60.2),
		SamplesElem(122, 890.88),
		SamplesElem(1846, 8222.3),
		SamplesElem(62, 60.2),
		SamplesElem(122, 890.88),
		SamplesElem(1846, 8222.3),
	};

	vector9.assign(25, SamplesElem(62, 60.2));
	vector9.assign(vector7.begin() + 1, vector7.begin() + 2);
	vector9.assign({
		SamplesElem(62, 60.2),
		SamplesElem(122, 890.88),
		SamplesElem(1846, 8222.3),
		SamplesElem(62, 60.2),
		SamplesElem(122, 890.88),
		SamplesElem(1846, 8222.3),
	});
	vector9.swap(vector1);

	std::cout << std::endl;
	std::cout << "Ê×ÔªËØ£º"; vector1.front().to_string();
	std::cout << "Î²ÔªËØ£º"; vector1.back().to_string();
	vector9.pop_back();
	vector9.insert(vector9.begin() + 3, temp);
	vector9.insert(vector9.end(), 2, SamplesElem(101, 13.14));
	vector9.insert(vector9.begin() + 3, vector9.begin(), vector9.begin() + 1);
	vector9.insert(vector9.begin() + 3, {
		SamplesElem(62, 60.2)
		});
	vector9.emplace(vector9.begin(), 0, 0);
	vector9.emplace_back(2, 2);
	vector9.erase(vector9.begin());
	vector9.erase(vector9.begin() + 1, vector9.begin() + 3);
	vector9.resize(3);
	vector9.resize(12, SamplesElem(1011314, 13.14));
	vector9.reserve(50);
	vector9.shrink_to_fit();
	vector9.swap(vector7);
	std::cout << "***************************************" << std::endl;
	std::cout 
		<< "vector9 size:" << vector9.size() << " capcity:" << vector9.capcity() 
		<<" is empty:"<<vector9.empty() << std::endl;

	const SamplesElem c;
	std::cout << "vector9 size:" << vector9.size() << " capcity:" << vector9.capcity() << std::endl;
	for (auto p = vector9.begin(); p != vector9.end(); p++)
		p->to_string();
	std::cout << "***************************************" << std::endl;
	for (auto p = vector9.cbegin(); p != vector9.cend(); p++)
		p->to_string();
	std::cout << "***************************************" << std::endl;
	for (auto p = vector9.rbegin(); p != vector9.rend(); p++)
		p->to_string();
	std::cout << "***************************************" << std::endl;
	for (auto p = vector9.crbegin(); p != vector9.crend(); p++)
		p->to_string();
	vector9.clear();

	//for (int index = 0; index < vector1.size(); index++)
	//	vector1[index].to_string();

	std::cout << std::endl;
}

#endif // !USE_GVECTOR_SAMPLE_H
