#ifndef GUNORDERED_SET_H
#define GUNORDERED_SET_H
#include "GHashTable.h"
#include "GUtility.h"
#include "GIterator.h"

namespace GEngine {
	namespace GStl {
		template<class T, class ExtractKey, class ConflictHandlingFun, class EqualKey, GMemManagerFun MMFun, bool IsMulti> class __GUnorderedSet;

		template<class T, class ExtractKey, class ConflictHandlingFun, class EqualKey, GMemManagerFun MMFun> 
		class GSTL_API _GUnorderedSet_Iterator : public iterator<forward_iterator_tag, T>
		{
			friend class __GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualKey, MMFun, true>;
			friend class __GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualKey, MMFun, false>;

		public:
			typedef forward_iterator_tag              iterator_category;
			typedef ptrdiff_t                         distance;
			typedef T                                 value_type;
			typedef T* value_pointer;
			typedef T& value_reference;

			typedef __set_hash_table_node<T>* node_pointer;
			typedef _GUnorderedSet_Iterator<T, ExtractKey, ConflictHandlingFun, EqualKey,MMFun>  self_type;

		public:
			_GUnorderedSet_Iterator() : current(nullptr),m_pBucket(nullptr) {}
			_GUnorderedSet_Iterator(node_pointer val,GVector<node_pointer>* bucket) : current(val),m_pBucket(bucket) {}
			_GUnorderedSet_Iterator(const _GUnorderedSet_Iterator& _itera) { current = _itera.current; m_pBucket = _itera.m_pBucket; }
			~_GUnorderedSet_Iterator() {}
			void operator=(const _GUnorderedSet_Iterator& _itera) { current = _itera.current; m_pBucket = _itera.m_pBucket; }

			self_type& operator++() { current = next(); return *this; }
			self_type operator++(int) { node_pointer temp = current; current = next(); return _GUnorderedSet_Iterator<T, ExtractKey, ConflictHandlingFun, EqualKey, MMFun>(temp, m_pBucket); }

			T& operator*() { return current->key; }
			T* operator->() { return &current->key; }

			bool operator!=(const _GUnorderedSet_Iterator& rhs) { return current != rhs.current; }
			bool operator==(const _GUnorderedSet_Iterator& rhs) { return current == rhs.current; }

		private:
			node_pointer next()
			{
				if (current->next != nullptr)
					return current->next;
				else
				{
					size_t capcity = m_pBucket->size();
					size_t hashcode = extractKey(current->key);//获取哈希值
					size_t idx = ConflictHandlingFun()(hashcode, capcity);
					GASSERT(idx < capcity);
					idx++;
					while (idx < capcity && m_pBucket->at(idx) == nullptr)
						idx++;

					if (idx == capcity) return nullptr;
					else return m_pBucket->at(idx);
				}
			}

			node_pointer current;
			GVector<node_pointer>* m_pBucket;
			ExtractKey extractKey;
		};

		template<class T, class ExtractKey, class ConflictHandlingFun, class EqualKey, GMemManagerFun MMFun>
		class GSTL_API _GUnorderedSet_CIterator : public iterator<forward_iterator_tag, T>
		{
			friend class __GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualKey, MMFun, true>;
			friend class __GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualKey, MMFun, false>;

		public:
			typedef forward_iterator_tag              iterator_category;
			typedef ptrdiff_t                         distance;
			typedef T                                 value_type;
			typedef T* value_pointer;
			typedef T& value_reference;

			typedef __set_hash_table_node<T>* node_pointer;
			typedef _GUnorderedSet_CIterator<T, ExtractKey, ConflictHandlingFun, EqualKey, MMFun>  self_type;

		public:
			_GUnorderedSet_CIterator() : current(nullptr), m_pBucket(nullptr) {}
			_GUnorderedSet_CIterator(node_pointer val, GVector<node_pointer>* bucket) : current(val), m_pBucket(bucket) {}
			_GUnorderedSet_CIterator(const _GUnorderedSet_CIterator& _itera) { current = _itera.current; m_pBucket = _itera.m_pBucket; }
			~_GUnorderedSet_CIterator() {}
			void operator=(const _GUnorderedSet_CIterator& _itera) { current = _itera.current; m_pBucket = _itera.m_pBucket; }

			self_type& operator++() { current = next(); return *this; }
			self_type operator++(int) { node_pointer temp = current; current = next(); return _GUnorderedSet_CIterator<T, ExtractKey, ConflictHandlingFun, EqualKey, MMFun>(temp, m_pBucket); }

			const T& operator*() { return current->key; }
			T* operator->() { return &current->key; }

			bool operator!=(const _GUnorderedSet_CIterator& rhs) { return current != rhs.current; }
			bool operator==(const _GUnorderedSet_CIterator& rhs) { return current == rhs.current; }

		private:
			node_pointer next()
			{
				if (current->next != nullptr)
					return current->next;
				else
				{
					size_t capcity = m_pBucket->size();
					size_t hashcode = extractKey(current->key);//获取哈希值
					size_t idx = ConflictHandlingFun()(hashcode, capcity);
					GASSERT(idx < capcity);
					idx++;
					while (idx < capcity && m_pBucket->at(idx) == nullptr)
						idx++;

					if (idx == capcity) return nullptr;
					else return m_pBucket->at(idx);
				}
			}

			node_pointer current;
			GVector<node_pointer>* m_pBucket;
			ExtractKey extractKey;
		};

		template<class T, class ExtractKey, class ConflictHandlingFun, class EqualKey, GMemManagerFun MMFun>
		class GSTL_API _GUnorderedSet_RIterator : public iterator<forward_iterator_tag, T>
		{
			friend class __GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualKey, MMFun, true>;
			friend class __GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualKey, MMFun, false>;

		public:
			typedef forward_iterator_tag              iterator_category;
			typedef ptrdiff_t                         distance;
			typedef T                                 value_type;
			typedef T* value_pointer;
			typedef T& value_reference;

			typedef __set_hash_table_node<T>* node_pointer;
			typedef _GUnorderedSet_RIterator<T, ExtractKey, ConflictHandlingFun, EqualKey, MMFun>  self_type;

		public:
			_GUnorderedSet_RIterator() : current(nullptr), m_pBucket(nullptr) {}
			_GUnorderedSet_RIterator(node_pointer val, GVector<node_pointer>* bucket) : current(val), m_pBucket(bucket) {}
			_GUnorderedSet_RIterator(const _GUnorderedSet_RIterator& _itera) { current = _itera.current; m_pBucket = _itera.m_pBucket; }
			~_GUnorderedSet_RIterator() {}
			void operator=(const _GUnorderedSet_RIterator& _itera) { current = _itera.current; m_pBucket = _itera.m_pBucket; }

			self_type& operator++() { current = prev(); return *this; }
			self_type operator++(int) { node_pointer temp = current; current = prev(); return _GUnorderedSet_RIterator<T, ExtractKey, ConflictHandlingFun, EqualKey, MMFun>(temp, m_pBucket); }

			T& operator*() { return current->key; }
			T* operator->() { return &current->key; }

			bool operator!=(const _GUnorderedSet_RIterator& rhs) { return current != rhs.current; }
			bool operator==(const _GUnorderedSet_RIterator& rhs) { return current == rhs.current; }

		private:
			node_pointer prev()
			{
				if (current->next != nullptr)
					return current->next;
				else
				{
					size_t capcity = m_pBucket->size();
					size_t hashcode = extractKey(current->key);//获取哈希值
					size_t idx = ConflictHandlingFun()(hashcode, capcity);
					GASSERT(idx < capcity);
					idx--;
					while (idx > 0 && m_pBucket->at(idx) == nullptr)
						idx--;

					if (idx == 0) return nullptr;
					else return m_pBucket->at(idx);
				}
			}

			node_pointer current;
			GVector<node_pointer>* m_pBucket;
			ExtractKey extractKey;
		};

		template<class T, class ExtractKey, class ConflictHandlingFun, class EqualKey, GMemManagerFun MMFun>
		class GSTL_API _GUnorderedSet_CRIterator : public iterator<forward_iterator_tag, T>
		{
			friend class __GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualKey, MMFun, true>;
			friend class __GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualKey, MMFun, false>;

		public:
			typedef forward_iterator_tag              iterator_category;
			typedef ptrdiff_t                         distance;
			typedef T                                 value_type;
			typedef T* value_pointer;
			typedef T& value_reference;

			typedef __set_hash_table_node<T>* node_pointer;
			typedef _GUnorderedSet_CRIterator<T, ExtractKey, ConflictHandlingFun, EqualKey, MMFun>  self_type;

		public:
			_GUnorderedSet_CRIterator() : current(nullptr), m_pBucket(nullptr) {}
			_GUnorderedSet_CRIterator(node_pointer val, GVector<node_pointer>* bucket) : current(val), m_pBucket(bucket) {}
			_GUnorderedSet_CRIterator(const _GUnorderedSet_CRIterator& _itera) { current = _itera.current; m_pBucket = _itera.m_pBucket; }
			~_GUnorderedSet_CRIterator() {}
			void operator=(const _GUnorderedSet_CRIterator& _itera) { current = _itera.current; m_pBucket = _itera.m_pBucket; }

			self_type& operator++() { current = prev(); return *this; }
			self_type operator++(int) { node_pointer temp = current; current = prev(); return _GUnorderedSet_CRIterator<T, ExtractKey, ConflictHandlingFun, EqualKey, MMFun>(temp, m_pBucket); }

			const T& operator*() { return current->key; }
			T* operator->() { return &current->key; }

			bool operator!=(const _GUnorderedSet_CRIterator& rhs) { return current != rhs.current; }
			bool operator==(const _GUnorderedSet_CRIterator& rhs) { return current == rhs.current; }

		private:
			node_pointer prev()
			{
				if (current->next != nullptr)
					return current->next;
				else
				{
					size_t capcity = m_pBucket->size();
					size_t hashcode = extractKey(current->key);//获取哈希值
					size_t idx = ConflictHandlingFun()(hashcode, capcity);
					GASSERT(idx < capcity);
					idx--;
					while (idx > 0 || m_pBucket->at(idx) == nullptr)
						idx--;

					if (idx == 0) return nullptr;
					else return m_pBucket->at(idx);
				}
			}

			node_pointer current;
			GVector<node_pointer>* m_pBucket;
			ExtractKey extractKey;
		};

		template<class T,class ExtractKey= __extract_key_fun<T>, class ConflictHandlingFun = __conflict_handling_fun<size_t>, class EqualKey= __hash_equal<T>, GMemManagerFun MMFun = GMemObject::GetMemManager,bool IsMulti=true>
		class GSTL_API __GUnorderedSet : public __set_hash_table<T, ExtractKey, ConflictHandlingFun,EqualKey,MMFun>
		{
		public:
			typedef _GUnorderedSet_Iterator<T, ExtractKey, ConflictHandlingFun, EqualKey, MMFun>    iterator_type;
			typedef _GUnorderedSet_CIterator<T, ExtractKey, ConflictHandlingFun, EqualKey, MMFun>   c_iterator_type;
			typedef _GUnorderedSet_RIterator<T, ExtractKey, ConflictHandlingFun, EqualKey, MMFun>   r_iterator_type;
			typedef _GUnorderedSet_CRIterator<T, ExtractKey, ConflictHandlingFun, EqualKey, MMFun>  cr_iterator_type;

			typedef __set_hash_table_node<T>*    node_pointer;
		public:
			__GUnorderedSet();
			__GUnorderedSet(size_t bnum);
			__GUnorderedSet(const __GUnorderedSet& cv);
			__GUnorderedSet(__GUnorderedSet&& rv);
			__GUnorderedSet(iterator_type _begin, iterator_type _end);
			__GUnorderedSet(iterator_type _begin, iterator_type _end,size_t bnum);
			__GUnorderedSet(std::initializer_list<T> values);
			~__GUnorderedSet();

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
			EqualKey hash_code_equals_function();
			size_t bucket_count();
			size_t max_bucket_count();
			float load_factor();
			float max_load_factor();
			void set_max_load_factor(size_t max_factor);
			void rehash(size_t bnum);
			void reverse(size_t num);
			iterator_type begin(size_t buckidx);
			iterator_type end(size_t buckidx);
			c_iterator_type cbegin(size_t buckidx);
			c_iterator_type cend(size_t buckidx);

		//特殊查找操作
		size_t count(const T& val);
		T& find(const T& val);


		//虚函数重写
		public:
			virtual bool empty() const;
			virtual size_t size() const;
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
			virtual size_t capcity() const { return 0; }

		};

		template<class T, class ExtractKey = __extract_key_fun<T>, class ConflictHandlingFun = __conflict_handling_fun<size_t>, class EqualKey = __hash_equal<T>, GMemManagerFun MMFun = GMemObject::GetMemManager>
		using GUnorderedSet = __GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualKey, MMFun,false>;

		template<class T, class ExtractKey = __extract_key_fun<T>, class ConflictHandlingFun = __conflict_handling_fun<size_t>, class EqualKey = __hash_equal<T>, GMemManagerFun MMFun = GMemObject::GetMemManager>
		using GUnorderedMultiSet = __GUnorderedSet<T, ExtractKey, ConflictHandlingFun, EqualKey, MMFun, true>;


#include "GUnorderedSet.inl"
	}
}

#endif // !GUNORDERED_SET_H
