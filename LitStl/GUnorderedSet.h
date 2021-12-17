#ifndef GUNORDERED_SET_H
#define GUNORDERED_SET_H
#include "GHashTable.h"
#include "GUtility.h"
#include "GIterator.h"

namespace GEngine {
	namespace GStl {
		template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun, bool IsMulti> class __GUnorderedSet;

		template<class T, class ExtractKey, class ConflictHandlingFun, class EqualHashCode, GMemManagerFun MMFun> 
		class _GUnorderedSet_Iterator : public iterator<forward_iterator_tag, T>
		{
			friend class __GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, true>;
			friend class __GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun, false>;

		public:
			typedef forward_iterator_tag              iterator_category;
			typedef ptrdiff_t                         distance;
			typedef T                                 value_type;
			typedef T* value_pointer;
			typedef T& value_reference;

			typedef __set_hash_table_node<T>* node_pointer;
			typedef _GUnorderedSet_Iterator<T, ExtractKey, ConflictHandlingFun, EqualHashCode,MMFun>  self_type;

		public:
			_GUnorderedSet_Iterator() : current(nullptr) {}
			_GUnorderedSet_Iterator(node_pointer val) : current(val) {}
			_GUnorderedSet_Iterator(const _GUnorderedSet_Iterator& _itera) { current = _itera.current; }
			~_GUnorderedSet_Iterator() {}
			void operator=(const _GUnorderedSet_Iterator& _itera) { current = _itera.current; }

			self_type& operator++() { current = next(); return *this; }
			self_type& operator++(int) { node_pointer temp = current; current = next(current); return _GUnorderedSet_Iterator<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun>(temp); }

			T& operator*() { return current->key; }
			T* operator->() { return &current->key; }

			bool operator!=(const _GUnorderedSet_Iterator& rhs) { return current != rhs.current; }
			bool operator==(const _GUnorderedSet_Iterator& rhs) { return current == rhs.current; }

		private:
			node_pointer void next()
			{
				if (current->next != nullptr)
					return current->next;
				else
				{
					size_t capcity = m_bucket->capcity();
					size_t hashcode = extractKey(current->key);//获取哈希值
					size_t idx = conflictHandlingFun(hashcode, capcity);
					GASSERT(idx < capcity);
					idx++;
					while (m_bucket->at(idx)==nullptr||idx<capcity)
						idx++;

					if (idx == capcity) return nullptr;
					else return m_bucket->at(idx);
				}
			}

			node_pointer current;
			GVector<node_pointer>* m_bucket;
		};




		template<class T,class ExtractKey= __extract_key_fun<T>, class ConflictHandlingFun = __conflict_handling_fun<T>, class EqualHashCode= __hash_equal<T>, GMemManagerFun MMFun = GMemObject::GetMemManager,bool IsMulti=true>
		class GSTL_API __GUnorderedSet : public __set_hash_table<T, ExtractKey, ConflictHandlingFun,EqualHashCode,MMFun>
		{
		public:
			typedef _GUnorderedSet_Iterator<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun>  iterator_type;
			typedef _GUnorderedSet_Iterator<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun>  c_iterator_type;
			typedef _GUnorderedSet_Iterator<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun>  r_iterator_type;
			typedef _GUnorderedSet_Iterator<T, ExtractKey, ConflictHandlingFun, EqualHashCode, MMFun>  cr_iterator_type;

			typedef __set_hash_table_node<T>    node_pointer;
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
			ExtractKey hash_function();
			EqualHashCode hash_code_equals_function();
			size_t bucket_count();
			size_t max_bucket_count();
			float load_factor();
			float max_load_factor();
			void set_max_load_factor(size_t max_factor);
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
