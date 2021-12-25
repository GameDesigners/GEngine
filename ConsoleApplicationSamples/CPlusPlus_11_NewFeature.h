#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<complex>
#include<utility>  //std::move

class Player
{
public:
	Player(int _ID, std::string _Name) : ID(_ID),Name(_Name) {}
public:
	int ID;
	std::string Name;

};

void UseUniformInitializationAndIntializerList();
void PrintIntSequece(std::initializer_list<int>);
void MoveOrCopy();
void NewStringLiteral();
constexpr int square(int);
void UseVariadicTemplate();
void UseLambdaExpresion();

//Main函数
void CPLUSPLUS_11_NEW_FEATURE_MAIN();

//一次性初始化和初值列的使用
void UseUniformInitializationAndIntializerList()
{
	
	int values[]{ 1,2,3,4,5,6 };
	std::vector<int> v{ 1,2,3,4,5,6 };
	std::vector<std::string> cities{ "BeiJing","New Tork" };
	std::complex<double> c{ 4.0,3.0 };

	PrintIntSequece({ 10, 5, 23, 8, 9 });
}

void PrintIntSequece(std::initializer_list<int> sequence)
{
	//使用了Range-Based For
	for(auto v : sequence)
		std::cout << v << "\t";
	std::cout<<std::endl;
}

void MoveOrCopy()
{
	std::vector<Player> playerList;
	Player p1{ 1,"Player1" };
	playerList.push_back(p1);

	//使用std::move
	Player p2{ 2,"Player2" };
	playerList.push_back(std::move(p2));

	Player p3{ 3,"Player3" };
	playerList.push_back(static_cast<Player&&>(p3));

	std::cout << "P1的Name:" << p1.Name << std::endl;  //"Player1"
	std::cout << "P2的Name:" << p2.Name << std::endl;  //""
	std::cout << "P3的Name:" << p3.Name << std::endl;  //""
}

//新的字面量
void NewStringLiteral()
{
	std::string RawStringLireral1 = R"(\n\n\n（支持中文）)";  //无转义符的字符串

	char16_t char16_tString[] = u"hello,world by char16_t Ecoding...";
	char32_t char32_tString[] = U"hello,world by char16_t Ecoding...";
	wchar_t  wchar_tString[] =L"hello,world by char16_t Ecoding...";



	std::cout << "RawStringLireral1:" << RawStringLireral1 << std::endl;
	std::cout << "char16_tString:" << char16_tString << std::endl;
	std::cout << "char32_tString:" << char32_tString << std::endl;
	std::cout << "wchar_tString:" << wchar_tString << std::endl;
}         

//constexpr关键字
constexpr int square(int x)
{
	return x * x;
}



//可变模板
void Print() {}

//递归实现可变模板形式
template<typename T,typename... Types>
void Print(const T& firstArgs, const Types&... args)
{
	std::cout << firstArgs << std::endl;
	Print(args...);
}

void UseVariadicTemplate()
{
	Print("hello", 7, 3.0);
}


void UseLambdaExpresion()
{
	//无参lambda表达式声明、定义和调用
	auto function = [] {
		std::cout << "hello world！ :)" << std::endl;
	};function();

	//有参数lambda表达式声明、定义和调用
	auto debug = [](const std::string& s) {
		std::cout << s << std::endl;
	};
	debug("hello world!  :)");

	//lambda可返回值
	auto square_lambda = [](const int& x) {
		return x * x;
	};
	std::cout << "5的平方=" << square_lambda(5) << std::endl;

	//指明返回类型的的版本
	auto square_lambda_define_return_type = [](const int& x)->int {
		return x * x;
	};
	std::cout << "5的平方=" << square_lambda_define_return_type(5) << std::endl;
}




void CPLUSPLUS_11_NEW_FEATURE_MAIN()
{
	//UseUniformInitializationAndIntializerList();

	MoveOrCopy();

	//NewStringLiteral();

	//int arrays[square(9)];  //合法

	//UseVariadicTemplate();

	//UseLambdaExpresion();
}