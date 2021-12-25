#ifndef USE_DELEGATE_SAMPLE_H
#define USE_DELEGATE_SAMPLE_H
#include <GDelegate.h>
using namespace GEngine::GSystem;
using namespace GEngine::GStl;


typedef GEvents<int(int, int)> EventsSample;

int add(int a, int b)
{
	int sum = a + b;
	cout << a << "+" << b << "=" << sum << endl;
	return sum;
}

class Sum
{
public:
	int add(int a, int b)
	{
		int sum = a + b;
		cout << a << "+" << b << "=" << sum << endl;
		return sum;
	}
};

void DelegateSample()
{
	
	GDelegate<int(int, int)> _add = GDelegate<int(int, int)>::FromFun<&add>();
	Sum sum;
	GDelegate<int(int, int)>  _add_method = GDelegate<int(int, int)>::FromMethod<Sum, &Sum::add>(&sum);
	EventsSample events;
	events += _add;
	events += _add_method;
	events.invoke(1, 2);
	events.invoke_without(1, 2, _add_method);
}

#endif // !USE_DELEGATE_SAMPLE_H
