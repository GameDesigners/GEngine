#ifndef USE_GSTRING_SAMPLE_H
#define USE_GSTRING_SAMPLE_H
#include <GStrings.h>
using namespace GEngine::GSystem;
using namespace GEngine::GStl;

ostream& operator<<(ostream& os, GString& str)
{
	os << str.c_str();
	return os;
}

void GStringsSample()
{
	GString string1;
	cout << "string1  isempty:" << string1.empty() << "  size:" << string1.size() << endl;
	GString string2("hello world!");
	GString string3(string2);
	GString string4(g_move(string2));
	GString string5(string4,2);
	GString string6(string4, 2,11);

	char str_arr[] = "Hello! GEngine!";
	char* p = str_arr;
	GString string7(p);
	GString string8(p,15);
	GString string9("GEngine", 3);
	GString string10(10, 'c');
	GString string11(string7.begin(), string7.end());
	GString string12({ 'h','i','!' });


	cout << string1 << endl;
	cout << string2 << endl;
	cout << string3 << endl;
	cout << string4 << endl;
	cout << string5 << endl;
	cout << string6 << endl;
	cout << string7 << endl;
	cout << string8 << endl;
	cout << string9 << endl;
	cout << string10 << endl;
	cout << string11 << endl;
	cout << string12 << endl;

	
	cout << "string12  isempty:" << string12.empty() << "  size:" << string12.size() << endl;

}
#endif // !USE_GSTRING_SAMPLE_H
