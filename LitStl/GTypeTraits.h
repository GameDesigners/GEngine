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

		//针对原生指针的迭代器数据类型萃取机
		template<class T>
		struct GTypeTraits<T*>
		{
			typedef T         value_type;
			typedef T*        value_pointer;
			typedef T&        value_reference;
			typedef const T* const_pointer;
		};

		//针对const 原生指针的迭代器数据类型萃取机
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
