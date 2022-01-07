#ifndef GMEMORY_H
#define GMEMORY_H

#include "GStlMicro.h"

namespace GEngine{
	namespace GStl {

		//Shared Smart Pointer (不适用于GObjectSystem中的对象，那里会通过继承的方式实现一个嵌入类中的智能指针)
        //**********************************************************************************************************************************************
		template<typename T>
		class GSTL_API GSharedPtr
		{
		public:
			using value_type = T;
			using value_pointer = T*;
			using value_reference = T&;
			
			GSharedPtr(value_pointer pVal = nullptr);
			GSharedPtr(const GSharedPtr& ptr);
			//GSharedPtr(GSharedPtr&& ptr) noexcept;
			~GSharedPtr();

			size_t use_count();

			GSharedPtr<T> operator=(const GSharedPtr& rhs);
			value_reference operator*();
			value_pointer operator->();
		
		private:
			GSharedPtr(value_pointer pVal, size_t* _p_reference_count) : val(pVal), p_reference_count(_p_reference_count) {}
		private:
			size_t* p_reference_count;
			value_pointer val;
		};


		//Generate Shared Smart Pointer with no params
		//**********************************************************************************************************************************************
		template<typename T> GSharedPtr<T> g_make_shared() { return GSharedPtr<T>(new T()); }

		//Generate Shared Smart Pointer with params
		//**********************************************************************************************************************************************
		template<typename T,typename... Params> GSharedPtr<T> g_make_shared(Params... args) { return GSharedPtr<T>(new T(args...)); }

#include "GMemory.inl"
	}
}


#endif // !GMEMORY_H
