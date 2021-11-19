#include "CPlusPlus_11_NewFeature.h"
#include "CommonTool.h"

#include <string>

#include "GUtility.h"
#include "GMemory.h"
#include "GStackWalker.h"
#include "GMemManager.h"
#include "GTimer.h"

using namespace GEngine::GStl;
using namespace GEngine::GSystem;

DWORD64 frames[32];

void USE_CUSTOM_PAIR()
{
	GPair<int, std::string> p1(1, "1hello world...");
	std::cout << "first value:" << p1.first << "  second value:" << p1.second << std::endl;

	GPair<int, std::string> p2(g_move(p1));
	GPair<int, std::string> p3 = g_make_pair<int, std::string>(2, "2hello world...");
	std::cout << "p1  first value:" << p1.first << "  second value:" << p1.second << std::endl;
	std::cout << "p2  first value:" << p2.first << "  second value:" << p2.second << std::endl;
	std::cout << "p3  first value:" << p3.first << "  second value:" << p3.second << std::endl;

	std::cout << "\n" << "After Swap..." << "\n";
	g_swap(p2, p3);
	std::cout << "p1  first value:" << p1.first << "  second value:" << p1.second << std::endl;
	std::cout << "p2  first value:" << p2.first << "  second value:" << p2.second << std::endl;
	std::cout << "p3  first value:" << p3.first << "  second value:" << p3.second << std::endl;
}
void USE_CUSTOM_TUPLE()
{
	GTuple<double, int, float> t1(1.0, 10, 1.0f);
	std::cout << "t1 第一个元素：" << g_get<0>(t1) << std::endl;
	std::cout << "t1 第二个元素：" << g_get<1>(t1) << std::endl;
	std::cout << "t1 第三个元素：" << g_get<2>(t1) << std::endl;

	std::cout << std::endl;

	GTuple<double, int, float, int> t2 = g_make_tuple(1.0, 10, 11.0f, 20);
	std::cout << "t1 第一个元素：" << g_get<0>(t2) << std::endl;
	std::cout << "t1 第二个元素：" << g_get<1>(t2) << std::endl;
	std::cout << "t1 第三个元素：" << g_get<2>(t2) << std::endl;
	std::cout << "t2 第四个元素：" << g_get<3>(t2) << std::endl;

	std::cout << std::endl;

	GTuple<int,double> t3 = g_make_tuple(200,11.236);
	std::cout << "t3 第一个元素：" << g_get<0>(t3) << std::endl;
	std::cout << "t3 第二个元素：" << g_get<1>(t3) << std::endl;
}
void USE_CUSTOM_SMART_POINT()
{
	GSharedPtr<std::string> pNico(GNEW std::string("nico"));
	GSharedPtr<std::string> pJutta(GNEW std::string("jutta"));

	(*pNico)[0] = 'N';
	pJutta->replace(0, 1, "J");

	std::vector<GSharedPtr<std::string>> whoMakeCoffee;
	whoMakeCoffee.push_back(pJutta);
	whoMakeCoffee.push_back(pJutta);
	whoMakeCoffee.push_back(pNico);
	whoMakeCoffee.push_back(pJutta);
	whoMakeCoffee.push_back(pNico);

	for (auto ptr : whoMakeCoffee) {
		std::cout << *ptr << " ";
	}
	std::cout << std::endl;

	*pNico = "Nicolai";

	for (auto ptr : whoMakeCoffee) {
		std::cout << *ptr << " ";
	}
	std::cout << std::endl;
	std::cout << "pJutta's Use Count:" << pJutta.use_count() << std::endl;

	GSharedPtr<GPair<int, int>> shared_p1 = g_make_shared<GPair<int, int>>(1, 1);
	std::cout << "shared_p1's Use Count:" << shared_p1.use_count() << std::endl;
}

void GetStackCallRecord()
{
	GStackWalker sw;
	if (sw.IsInitialized())
	{
		sw.GetStackFrameEntryAddressArray(frames);
		//sw.ShowCallStack(GetCurrentProcess(), GetCurrentThreadId());
		sw.PrintCallStackFramesLog(frames);
	}
}

void Function3()
{
	GetStackCallRecord();
}

void Function2()
{
	Function3();
}

void Function1()
{
	Function2();
}

int main()
{
	//CPLUSPLUS_11_NEW_FEATURE_MAIN();
	//COMMON_TOOL_MAIN();

	//USE_CUSTOM_PAIR();
	//USE_CUSTOM_TUPLE();
	//USE_CUSTOM_SMART_POINT();

	
	//Function1();

	/*GDebugMem Alloc;
	Alloc.PrintMemCallAndReleaseLog();*/
	/*printf("\n");
	for (size_t i = 0; i < 32; i++)
		printf("%p\n", frames[i]);*/

	/*int* p = GNEW int;
	int* p2 = GNEW int;*/

	//GDELETE p;
	//GDELETE p2;
	/*
	*p = 10;
	
	*p2 = 100;

	printf("%d ; %d", *p, *p2);*/

	while (true)
	{
		GTimer::GetTimer().UpdateFps();
		printf("[DelatTime:%f]  [FPS:%f]  [RuningTime:%f]  [TotalTime:%f]",
			GTimer::GetTimer().GetDeltaTime(),
			GTimer::GetTimer().GetFPS(),
			GTimer::GetTimer().GetRuningTime(),
			GTimer::GetTimer().GetTotalTime());
		system("cls");
	}

	//getchar();
	return 0;
}