#ifndef GMEMORY_H
#define GMEMORY_H

#include "GStlMicro.h"

namespace GEngine{
	namespace GStl {

		template<typename T>
		class GSTL_API GSharedPtr
		{
		public:
			using value_type = T;
			using value_pointer = T*;
			using value_reference = T&;
			
			GSharedPtr(value_pointer pVal);
			GSharedPtr(const GSharedPtr& ptr);
			//GSharedPtr(GSharedPtr&& ptr) noexcept;
			~GSharedPtr();

			size_t use_count();

			value_reference operator=(const GSharedPtr& rhs);
			value_reference operator*();
			value_pointer operator->();
		
		private:
			GSharedPtr(value_pointer pVal, size_t* _p_reference_count) : val(pVal), p_reference_count(_p_reference_count) {}
		private:
			size_t* p_reference_count;
			value_pointer val;
		};

		template<typename T>
		class GSTL_API GWeakPtr
		{

		};

		template<typename T>
		GSharedPtr<T> g_make_shared()
		{
			return GSharedPtr<T>(new T());
		}

		template<typename T,typename... Params>
		GSharedPtr<T> g_make_shared(Params... args)
		{
			return GSharedPtr<T>(new T(args...));
		}

#include "GMemory.inl"
	}
}


#endif // !GMEMORY_H
