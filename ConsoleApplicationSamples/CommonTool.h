#pragma once
#include <utility>  //


void COMMON_TOOL_MAIN();

void UsePairAndTuple();



void COMMON_TOOL_MAIN()
{
	UsePairAndTuple();
}

void UsePairAndTuple()
{
	std::pair<int, double> elem{ 1,10.0f };
	std::cout << "first value:" << elem.first << "  second value:" << elem.second << std::endl;

	//std::get<0>(elem);
}