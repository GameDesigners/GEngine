#ifndef INITIALIZE_AND_TERMINAL_SYSTEM_SAMPLE_H
#define INITIALIZE_AND_TERMINAL_SYSTEM_SAMPLE_H


class Priority1
{
public:
	static bool RegistMainFactory();
	static bool ms_RegistedFactory;

	static int a;
};
int Priority1::a = 10;

class Priority2
{
public:
	static int a;
};

int Priority2::a = 10;

#endif // !INITIALIZE_AND_TERMINAL_SYSTEM_SAMPLE_H
