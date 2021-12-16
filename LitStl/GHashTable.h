#ifndef GHASH_TABLE_H
#define GHASH_TABLE_H
#include "GVector.h"
#include "GHashFunction.h"

namespace GEngine {
	namespace GStl {
		template<class NodeType, class HashFunc, class ExtractKey, class EqualHashCode, GMemManagerFun MMFun> class __hash_table;

		template<class Key,class Value>
		class GSTL_API __map_hash_table_node
		{
		public:
			typedef Key    key_type;
			typedef Value  value_type;
			typedef __map_hash_table_node<Key, Value>* node_pointer;

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

		public:
			Key   key;
			node_pointer next;
		};


		template<class NodeType,class ConflictHandlingFun,class ExtractKey,class EqualHashCode, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GSTL_API __hash_table : public GContainer<NodeType>
		{
		public:
			typedef NodeType::key_type    key_type;
			typedef NodeType*             node_pointer;

		protected:
			__hash_table();
			
		protected:
			static const size_t __stl_num_primes = 28;
			static const unsigned long __stl_prime_list[__stl_num_primes];

			ConflictHandlingFun   hashCode;
			ExtractKey            extractKey;
			EqualHashCode         hashEquals;

			GVector<NodeType*>    m_bucket;
		};

		template<class Key, class ConflictHandlingFun, class ExtractKey, class EqualHashCode, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GSTL_API __set_hash_table : public __hash_table<__set_hash_table_node<Key>, ConflictHandlingFun, ExtractKey, EqualHashCode, MMFun>
		{

		};

#include "GHashTable.inl"
	}
}

#endif // !GHASH_TABLE_H

