#ifndef GBLANCE_TREE_H
#define GBLANCE_TREE_H
#include "GContainer.h"

namespace GEngine {
	namespace GStl {
		//Framework Reference Blogs:https://www.cnblogs.com/skywang12345/p/3624291.html

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
			typedef __tree_node_color                colors;

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
			node_pointer Search(const Key& key);
			node_pointer IterativeSearch(const Key& key);
			value_type& Minmum();
			value_type& Maxmum();
			node_pointer Successor(node_pointer node);  //查找后继节点
			node_pointer PreDecessor(node_pointer node);//查找前驱节点
			void Insert(key_type key, value_type value);
			void Remove(key_type key);
			void Destroy();
			void Print();
			
		private:
			virtual bool empty() { return false; }
			virtual size_t size() { return 0; }
			virtual size_t capcity() {return 0；}
			virtual void clear() {}

		//辅助函数
		private:
			inline void __node_point_swap(node_pointer p1, node_pointer p2) {
				node_pointer temp = p1;
				p1 = p2;
				p2 = temp;
			}
			void __create_node(const Key& key, const Value& value);

			void __pre_order(node_pointer tree) const;
			void __in_order(node_pointer tree) const;
			void __post_order(node_pointer tree) const;
			node_pointer __search(node_pointer x, Key key) const;
			node_pointer __interative_search(node_pointer x, Key key) const;
			node_pointer __minimum(node_pointer tree) const;
			node_pointer __maximum(node_pointer tree) const;

			void __left_rotate(node_pointer& root, node_pointer x);
			void __right_rotate(node_pointer& root, node_pointer y);
			void __insert_fix_up(node_pointer& root, node_pointer node);
			void __remove_fix_up(node_pointer& root, node_pointer node, node_pointer parent);
			void __insert(node_pointer& root, node_pointer node);
			void __remove(node_pointer& root, node_pointer node);

			void __destroy(node_pointer& tree);
			void __print(node_pointer tree, T key, int direction);


		private:
			node_pointer m_root;

		};

#include "GBalanceTree.inl"
	}
}
#endif // !GBLANCE_TREE_H

