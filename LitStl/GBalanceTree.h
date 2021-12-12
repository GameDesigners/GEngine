#ifndef GBLANCE_TREE_H
#define GBLANCE_TREE_H
#include "GContainer.h"

namespace GEngine {
	namespace GStl {

		enum __tree_node_color : unsigned short 
		{
			red,
			black
		};

		template<class Key,class Value>
		class __balance_tree_node
		{                   
			typedef __balance_tree_node<Key,Value>* node_pointer;

		private:
			__balance_tree_node(Key k, Value v, __tree_node_color c, node_pointer p, node_pointer l, node_pointer r)
				: color(c), key(k), value(v), left(l), right(r), parent(p) {}
		
		private:
			__tree_node_color color;
			node_pointer      left;
			node_pointer      right;
			node_pointer      parent;
			Key               key;
			Value             value;
		};

		template<class Key,class Value,GMemManagerFun MMFun= GMemObject::GetMemManager>
		class GSTL_API __balance_tree : public GContainer<__balance_tree_node<Key,Value>>
		{
			friend class __balance_tree_node<Key, Value>;
		public:
			typedef Key                              key_type;
			typedef Value                            value_type;
			typedef __balance_tree_node<Key, Value>* node_pointer;

		public:
			__balance_tree();
			~__balance_tree();

		//遍历函数
		public:
			void PreOrder();
			void InOrder();
			void PostOrder();

		//增删查改、销毁
		public:
			node_pointer Search(const Key& Key);
			node_pointer IterativeSearch(const Key& key);
			value_type Minmum();
			value_type Maxmum();
			node_pointer Successor(node_pointer node);  //查找后继节点
			node_pointer PreDecessor(node_pointer node);//查找前驱节点
			void Insert(key_type key, value_type value);
			void Remove(key_type key);
			void Destroy();
			void Print();
			
		//辅助函数
		private:

			void __left_rotate(node_pointer& root, node_pointer x);
			void __right_rotate(node_pointer& root, node_pointer x);


		private:
			node_pointer m_root;

		};

#include "GBalanceTree.inl"
	}
}
#endif // !GBLANCE_TREE_H

