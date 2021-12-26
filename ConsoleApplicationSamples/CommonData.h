#include <GSystem.h>
#include <iostream>
#include <GHashFunction.h>
#include <GReference.h>
#ifndef COMMON_DATA_H
#define COMMON_DATA_H
using namespace GEngine::GStl;
using namespace GEngine::GGraphic;
class SamplesElem : public GReference
{
public:
	int* i;
	float f;

public:
	SamplesElem()
	{
		i = GNEW int;
		f = 0.0f;
		//std::cout << "调用了一次无参构造函数->SamplesElem" << std::endl;
	}

	SamplesElem(int _i, float _f)
	{
		i = GNEW int;
		*i = _i;
		f = _f;
		//std::cout << "调用了一次赋初值构造函数->SamplesElem(_i,_f)" << std::endl;
	}

	SamplesElem(const SamplesElem& elem)
	{
		i = GNEW int;
		*i = *(elem.i);
		f = elem.f;
		std::cout << "调用了一次复制构造函数->SamplesElem(const SamplesElem&)" << std::endl;
	}

	void operator=(const SamplesElem& cv)
	{
		if (i != nullptr && cv.i != nullptr) {
			*i = *(cv.i);
			f = cv.f;
		}
	}

	bool operator==(const SamplesElem& cv)
	{
		return (*i) == *(cv.i) && f == cv.f;
	}

	bool operator!=(const SamplesElem& cv)
	{
		return !(*this == cv);
	}

	bool operator<(const SamplesElem& cv)
	{
		if ((*i) != *(cv.i))
			return (*i) < *(cv.i);
		return f < cv.f;
	}

	bool operator>(const SamplesElem& cv)
	{
		if ((*i) != *(cv.i))
			return (*i) > *(cv.i);
		return f > cv.f;
	}

	bool operator<=(const SamplesElem& cv)
	{
		if ((*i) != *(cv.i))
			return (*i) < *(cv.i);

		if (f != cv.f)
			return f < cv.f;

		return (*i) == *(cv.i) && f == cv.f;
	}

	bool operator>=(const SamplesElem& cv)
	{
		if ((*i) != *(cv.i))
			return (*i) > *(cv.i);

		if (f != cv.f)
			return f > cv.f;

		return (*i) == *(cv.i) && f == cv.f;
	}

	void operator=(SamplesElem&& rv) noexcept
	{
		GSAFE_DELETE(i)
			i = rv.i;
		f = rv.f;
		rv.i = nullptr;
	}

	~SamplesElem() {
		GSAFE_DELETE(i)
	}

	void to_string()
	{
		if (i != nullptr)
			std::cout << "int:" << *i << " float:" << f << std::endl;
		else
			std::cout << "float:" << f << std::endl;
	}
};
IMPLEMENT_EXTRACT_HASH_KEY_FUNCTOR1(SamplesElem, float, f)
#endif // !COMMON_DATA_H
