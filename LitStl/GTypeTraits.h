#ifndef GTYPE_TRAITS_H
#define GTYPE_TRAITS_H
#include "GStlMicro.h"
namespace GEngine {
	namespace GStl {
		template<class T>
		struct GSTL_API GTypeTraits
		{
			typedef T         value_type;
			typedef T*        value_pointer;
			typedef T&        value_reference;
			typedef const T*  const_pointer;
		};

		//���ԭ��ָ��ĵ���������������ȡ��
		template<class T>
		struct GTypeTraits<T*>
		{
			typedef T         value_type;
			typedef T*        value_pointer;
			typedef T&        value_reference;
			typedef const T* const_pointer;
		};

		//���const ԭ��ָ��ĵ���������������ȡ��
		template<class T>
		struct GTypeTraits<const T*>
		{
			typedef T         value_type;
			typedef T*        value_pointer;
			typedef T&        value_reference;
			typedef const T*  const_pointer;
		};

		template<class T> struct TIsPointerType { enum { Value = false }; };
		template<class T> struct TIsPointerType<T*> { enum { Value = true }; };
		template<class T> struct TIsPointerType<const T*> { enum { Value = true }; };
	}
}
#endif // !GTYPE_TRAITS_H
