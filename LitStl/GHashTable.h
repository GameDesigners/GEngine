#ifndef GHASH_TABLE_H
#define GHASH_TABLE_H
#include "GVector.h"
#include "GHashFunction.h"

namespace GEngine {
	namespace GStl {
		template<class NodeType, class ConflictHandlingFun, class ExtractKey, class EqualKey, GMemManagerFun MMFun> class __hash_table;

		template<class Key,class Value>
		class GSTL_API __map_hash_table_node
		{
		public:
			typedef Key    key_type;
			typedef Value  value_type;
			typedef __map_hash_table_node<Key, Value>* node_pointer;

			__map_hash_table_node(const Key& _key, const Value& _value, node_pointer _next) : key(_key), value(_value), next(_next) {}
			void move_data(__map_hash_table_node&& rv)
			{
				key = g_move(rv.key);
				value = g_move(rv.value);
			}

		public:
			Key   key;
			Value value;
			node_pointer next;
		};

		template<class Key>
		class GSTL_API __set_hash_table_node
		{
		public:
			typedef Key    key_type;
			typedef __set_hash_table_node<Key>* node_pointer;
			
			__set_hash_table_node(const Key& _key,node_pointer _next) : key(_key),next(_next) {}
			void move_data(__set_hash_table_node&& rv)
			{
				if (ValueBase<Key>::NeedsDestructor)
					key.~Key();
				key = g_move(rv.key);
			}

		public:
			Key   key;
			node_pointer next;
		};


		template<class NodeType,class ExtractKey, class ConflictHandlingFun, class EqualKey, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GSTL_API __hash_table : public GContainer<NodeType>
		{
		public:
			typedef typename NodeType::key_type    key_type;
			typedef NodeType*                      node_pointer;

		protected:
			__hash_table();
			__hash_table(size_t bnum);

		protected:
			template<typename... Args> node_pointer __hash_insert(Args... args);
			void __remove(const key_type& key);
			node_pointer __search(const key_type& key);
			void __clear();
			void __rehash_table(size_t bnum, bool need_caculate_bucket_idx = true);
			void __rehash_insert(node_pointer node, GVector<node_pointer>& rehash_vec,const size_t& capcity);
			node_pointer __first_node();
			node_pointer __last_node();
			size_t __countof(const key_type& key);

			inline ConflictHandlingFun __get_conflict_handling_fun() { return conflictHandlingFun; }
			inline ExtractKey __get_extract_key_fun() { return extractKey; }
			inline EqualKey __get_hash_equals_fun() { return keyEquals; }
			inline size_t __get_current_bucket_count() { return __stl_prime_list[m_current_bucket_idx]; }
			inline size_t __get_max_bucket_count() const { return __stl_prime_list[__stl_num_primes - 1]; }
			inline float __get_load_factor() const { return static_cast<float>(m_count) / __stl_prime_list[m_current_bucket_idx];}
			inline float& __max_load_factor() { return m_max_load_factor;}
			inline size_t __location_capcity_idx(size_t bnum) {
				size_t  idx = 0;
				while (__stl_num_primes[m_current_bucket_idx] < bnum)
					idx++;
				return idx;
			}
			inline size_t __get_bucket_idx_by_key(const key_type& key){
				size_t capcity = m_bucket.capcity();
				size_t hashcode = extractKey(key);//获取哈希值
				size_t idx = conflictHandlingFun(hashcode, capcity);
				GASSERT(idx < capcity);
				return idx;
			}
			inline void __is_rehash_table(){
				float factor = __get_load_factor();
				GASSERT(++m_current_bucket_idx < __stl_num_primes);
				if (factor > m_max_load_factor)//需要重新调整哈希表桶的容量
					__rehash_table(__stl_prime_list[m_current_bucket_idx], false);
			}

		protected:
			static const size_t __stl_num_primes = 28;
			static const unsigned long __stl_prime_list[__stl_num_primes];

			ConflictHandlingFun   conflictHandlingFun;
			ExtractKey            extractKey;
			EqualKey              keyEquals;

			float                 m_max_load_factor;
			size_t                m_current_bucket_idx;
			size_t                m_count;
			GVector<NodeType*>    m_bucket;
		};

		template<class Key,  class ExtractKey, class ConflictHandlingFun, class EqualKey, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GSTL_API __set_hash_table : public __hash_table<__set_hash_table_node<Key>, ExtractKey, ConflictHandlingFun, EqualKey, MMFun>
		{
		public:
			typedef __set_hash_table_node<Key>* node_pointer;

		protected:
			virtual bool empty() { return false; }
			virtual size_t size() { return 0; }
			virtual size_t capcity() { return 0; }
			virtual void clear() {}

		protected:
			node_pointer __insert(const Key& key)
			{
				return this->__hash_insert(key, nullptr);
			}
		};

#include "GHashTable.inl"
	}
}

#endif // !GHASH_TABLE_H

