#ifndef GRTTI_SAMPLE_H
#define GRTTI_SAMPLE_H
#include <GRtti.h>

class GRttiSample_A
{
    DECLARE_RTTI(GRttiSample_A)
};
IMPLEMENT_RTTI_NO_PARENT_NO_GENERATE_FUNC(GRttiSample_A)


class GRttiSample_B : public GRttiSample_A
{
	DECLARE_RTTI(GRttiSample_B)
};
IMPLEMENT_RTTI_NO_GENERATE_FUNC(GRttiSample_B, GRttiSample_A)





void GRttiSample()
{
	cout << endl;
	GRttiSample_A a;
	GRttiSample_B b;
	wcout <<"a����������Ϊ��"<< a.GetType().Name().c_str() << endl;
	wcout <<"a����������Ϊ��"<< b.GetType().Name().c_str() << endl;
	cout << "b�Ƿ���a�����ࣺ" << b.IsDerived(a.GetType()) << endl;
	cout << "b�Ƿ���b�����ࣺ" << a.IsDerived(b.GetType()) << endl;
	cout << endl;

}
#endif // !GRTTI_SAMPLE_H
