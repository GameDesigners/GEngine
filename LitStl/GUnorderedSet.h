#ifndef GUNORDERED_SET_H
#define GUNORDERED_SET_H
#include "GHashTable.h"
#include "GUtility.h"
#include "GIterator.h"

namespace GEngine {
	namespace GStl {
		template<class T, class ConflictHandlingFun, class ExtractT, class EqualHashCode, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GSTL_API __GUnorderedSet : public __set_hash_table<T,ConflictHandlingFun,ExtractT,EqualHashCode,MMFun>
		{
		public:
			typedef _SingleMemUnit_Iterator<T>  iterator_type;
			typedef _SingleMemUnit_Iterator<T>  c_iterator_type;
			typedef _SingleMemUnit_Iterator<T>  r_iterator_type;
			typedef _SingleMemUnit_Iterator<T>  cr_iterator_type;
		public:
			__GUnorderedSet();
			__GUnorderedSet(size_t bnum);
			__GUnorderedSet(const __GUnorderedSet& cv);
			__GUnorderedSet(__GUnorderedSet&& rv);
			__GUnorderedSet(iterator_type _begin, iterator_type _end);
			__GUnorderedSet(iterator_type _begin, iterator_type _end,size_t bnum);
			__GUnorderedSet(std::initializer_list<T> values);

		//赋值函数
		public:
			void operator=(const __GUnorderedSet& cv);
			void operator=(__GUnorderedSet&& rv);
			void operator=(std::initializer_list<T> values);
			void swap(__GUnorderedSet& v);

		//插入和删除
		public:
			GPair<iterator_type, bool> insert(const T& val);
			//void insert(const iterator_type& pos, const T& val);
			void insert(iterator_type _begin, iterator_type _end);
			void insert(std::initializer_list<T> values);
			template<typename... Args> GPair<iterator_type, bool> emplace(Args... args);
			//template<typename... Args> void emplace(iterator_type pos, Args... args);
			void earse(const T& val);
			void earse(iterator_type pos);
			void earse(iterator_type _begin, iterator_type _end);

		//布局操作
		public:
			ConflictHandlingFun coflict_handling_function();
			ExtractT hash_function();
			EqualHashCode hash_code_equals_function();
			size_t bucket_count();
			size_t max_bucket_count();
			float load_factor();
			float max_load_factor();
			void set_max_load_factor();
			void rehash(size_t bnum);
			void reverse(size_t num);
			iterator_type begin(size_t buckidx);
			iterator_type end(size_t buckidx);
			iterator_type cbegin(size_t buckidx);
			iterator_type cend(size_t buckidx);

		//访问
		public:

		//特殊查找操作
		size_t count(T val);
		T& find(const T& val);


		//虚函数重写
		public:
			virtual bool empty();
			virtual size_t size();
			virtual void clear();

		//运算符重写
		public:
			bool operator==(const __GUnorderedSet& rhs);
			bool operator!=(const __GUnorderedSet& rhs);

		//迭代器
		public:
			iterator_type    begin();
			iterator_type    end();
			c_iterator_type  cbegin();
			c_iterator_type  cend();
			r_iterator_type  rbegin();
			r_iterator_type  rend();
			cr_iterator_type crbegin();
			cr_iterator_type crend();

		private:
			virtual size_t capcity() { return 0; }

		};

#include "GUnorderedSet.inl"
	}
}

#endif // !GUNORDERED_SET_H
