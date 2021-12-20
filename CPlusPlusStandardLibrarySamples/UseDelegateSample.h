#ifndef USE_DELEGATE_SAMPLE_H
#define USE_DELEGATE_SAMPLE_H
#include <GDelegate.h>
using namespace GEngine::GSystem;
using namespace GEngine::GStl;

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
	_add(1, 2);
}

#endif // !USE_DELEGATE_SAMPLE_H
