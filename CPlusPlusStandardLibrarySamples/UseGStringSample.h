#ifndef USE_GSTRING_SAMPLE_H
#define USE_GSTRING_SAMPLE_H
#include <GStrings.h>
using namespace GEngine::GSystem;
using namespace GEngine::GStl;

ostream& operator<<(ostream& os, GString& str)
{
	os << "isempty:" << str.empty() << "  size:" << str.size() << endl;
	os << str.c_str();
	os << endl;
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

	string12 = string11;
	string12 = g_move(string11);
	string12 += "GEngine is a custom game engine by myself...";
	string12 += '\n';
	string12 += 'G';
	string12 += {'a', 'm', 'e'};
	GString child = " dev is more fun than playing game.";
	string12.append(child);
	string12.insert(15, 1, '\n');
	string12.insert(15, 1, '\n');
	string12.insert(16, 44, '*');
	string12.insert(16, "It's not classical sentance <hello world!>...\n");
	string12.insert(16, "x x x x x x x x x x x x\n", 28);

	string2= string12.substr();
	string3 = string12.substr(16);
	string4 = string12.substr(16,5);


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

	cout << string12.find("llo") << endl;


	/*cout << "string1 > string12:" << (string1 > string12) << endl;
	cout << "string1 >= string12:" << (string1 >= string12) << endl;
	cout << "string1 < string12:" << (string1 < string12) << endl;
	cout << "string1 <= string12:" << (string1 <= string12) << endl;
	cout << "string1 == string12:" << (string1 == string12) << endl;


	cout << "string1 > hill:" << (string1 > "hill") << endl;
	cout << "string1 >= hill:" << (string1 >= "hill") << endl;
	cout << "string1 < hill:" << (string1 < "hill") << endl;
	cout << "string1 <= hill:" << (string1 <= "hill") << endl;
	cout << "string1 == hill:" << (string1 == "hill") << endl;*/

	//const GString cstring1("hello world!");
	//cout << (cstring1 == "hello") << endl;

}
#endif // !USE_GSTRING_SAMPLE_H
