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

	cout << string1 << endl;
	cout << string2 << endl;
	cout << string3 << endl;
	cout << string4 << endl;
	cout << string5 << endl;
	cout << string5.data() << endl;
	cout << "string5  isempty:" << string5.empty() << "  size:" << string5.size() << endl;

}
#endif // !USE_GSTRING_SAMPLE_H
