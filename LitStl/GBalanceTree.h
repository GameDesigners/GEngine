#ifndef GBLANCE_TREE_H
#define GBLANCE_TREE_H
#include "GContainer.h"
#include "GAlgorithm.h"

namespace GEngine {
	namespace GStl {
		/*
		 * Reference Blogs : 
		 * https://www.cnblogs.com/skywang12345/p/3624291.html  rb-tree c++ code
		 * https://www.cnblogs.com/tongy0/p/5460623.html        node-remove graphic description
		 */
		template<class NodeType, typename Compare, GMemManagerFun MMFun> class __balance_tree;
		template<class T, bool IsMulti, typename Compare, GMemManagerFun MMFun> class GSTL_API __GSet;
		enum __tree_node_color : unsigned short 
		{
			red,
			black
		};

		template<class Key,class Value,typename Compare=less<Key>,GMemManagerFun MMFun= GMemObject::GetMemManager>
		class __map_balance_tree_node
		{
			friend class __balance_tree<__map_balance_tree_node<Key, Value, Compare, MMFun>, Compare, MMFun>;
			friend class GContainer<__map_balance_tree_node<Key, Value, Compare, MMFun>>;


		public:
			typedef Key    key_type;
			typedef Value  value_type;
			typedef __map_balance_tree_node<Key, Value,Compare,MMFun>* node_pointer;

		private:
			__map_balance_tree_node(const Key& k, const Value& v, __tree_node_color c, node_pointer p, node_pointer l, node_pointer r)
				: color(c), key(k), value(v), left(l), right(r), parent(p) {}

			~__map_balance_tree_node()
			{
				if (ValueBase<Key>::NeedsDestructor)
					key.~Key();

				if (ValueBase<Value>::NeedsDestructor)
					value.~Value();
			}

		public:
			__tree_node_color color;
			node_pointer      left;
			node_pointer      right;
			node_pointer      parent;
			Key               key;
			Value             value;
		};

		template<class Key, typename Compare=less<Key>, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class __set_balance_tree_node
		{
			friend class GContainer<__set_balance_tree_node<Key, Compare, MMFun>>;
			friend class __balance_tree<__set_balance_tree_node<Key, Compare, MMFun>, Compare, MMFun>;
			friend class __GSet<Key, true, Compare, MMFun>;
			friend class __GSet<Key, false, Compare, MMFun>;

		public:
			typedef Key                                  key_type;
			typedef __set_balance_tree_node<Key, Compare, MMFun>* node_pointer;

		public:
			__set_balance_tree_node(const Key& k, __tree_node_color c, node_pointer p, node_pointer l, node_pointer r)
				: color(c), key(k), left(l), right(r), parent(p) {}

			~__set_balance_tree_node() {
				if (ValueBase<Key>::NeedsDestructor)
					key.~Key();
			}
		public:
			Key               key;
			__tree_node_color color;
			node_pointer      left;
			node_pointer      right;
			node_pointer      parent;

		};


		template<class NodeType,typename Compare, GMemManagerFun MMFun= GMemObject::GetMemManager>
		class GSTL_API __balance_tree : public GContainer<NodeType>
		{
		public:
			typedef typename NodeType::key_type      key_type;
			typedef NodeType*                        node_pointer;
			typedef __tree_node_color                colors;

		protected:
			__balance_tree();    
			~__balance_tree();

		//遍历函数
		protected:
			void PreOrder();
			void InOrder();
			void PostOrder();

		//增删查改、销毁
		protected:
			node_pointer Search(const key_type& key);
			node_pointer IterativeSearch(const key_type& key);
			node_pointer Minmum();
			node_pointer Maxmum();
			node_pointer Successor(node_pointer node);  //查找后继节点
			node_pointer PreDecessor(node_pointer node);//查找前驱节点
			template<typename... Args> node_pointer Insert(Args ...args);
			template<typename... Args> node_pointer Insert(node_pointer pos, Args... args);
			void Remove(const key_type& key);
			void Destroy();
			
		protected:
			virtual bool empty() { return false; }
			virtual size_t size() { return 0; }
			virtual size_t capcity() { return 0; }
			virtual void clear() {}

		//辅助函数
		protected:
			inline void __node_point_swap(node_pointer p1, node_pointer p2) {
				node_pointer temp = p1;
				p1 = p2;
				p2 = temp;
			}

			node_pointer __search(node_pointer x, const key_type& key) const;
			node_pointer __interative_search(node_pointer x, const key_type& key) const;
			node_pointer __minimum(node_pointer tree) const;
			node_pointer __maximum(node_pointer tree) const;

			void __left_rotate(node_pointer& root, node_pointer x);
			void __right_rotate(node_pointer& root, node_pointer y);
			void __insert_fix_up(node_pointer& root, node_pointer node);
			void __remove_fix_up(node_pointer& root, node_pointer node, node_pointer parent);
			void __insert(node_pointer& root, node_pointer node);
			void __remove(node_pointer& root, node_pointer node);
			void __destroy(node_pointer& tree);


		protected:
			node_pointer m_root;
			Compare      comparator;
			size_t       m_count;
		};


		template<class Key, typename Compare=less<Key>, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GSTL_API __set_balance_tree : public __balance_tree<__set_balance_tree_node<Key, Compare, MMFun>, Compare, MMFun>
		{
		public:
			typedef __set_balance_tree_node<Key, Compare, MMFun>* node_pointer;
			typedef Key                                  key_type;
			typedef __tree_node_color                    colors;

		protected:
			virtual bool empty() { return false; }
			virtual size_t size() { return 0; }
			virtual size_t capcity() { return 0; }
			virtual void clear() {}

		protected:
			node_pointer __insert(const Key& key)
			{
				return this->Insert(key, colors::red, nullptr, nullptr, nullptr);
			}

			node_pointer __insert(node_pointer pos, const Key& key)
			{
				return this->Insert(pos, key, colors::red, nullptr, nullptr, nullptr);
			}
		};

		
		template<class Key, class Value,typename Compare = less<Key>, GMemManagerFun MMFun = GMemObject::GetMemManager>
		class GSTL_API __map_balance_tree : public __balance_tree<__map_balance_tree_node<Key,Value,Compare, MMFun>, Compare, MMFun>
		{
		public:
			typedef __map_balance_tree_node<Key,Value, Compare, MMFun>* node_pointer;
			typedef Key                                           key_type;
			typedef Value                                         value_type;
			typedef __tree_node_color                             colors;

		protected:
			virtual bool empty() { return false; }
			virtual size_t size() { return 0; }
			virtual size_t capcity() { return 0; }
			virtual void clear() {}

		protected:
			node_pointer __insert(const Key& key,const Value& value)
			{
				return this->Insert(key, value, colors::red, nullptr, nullptr, nullptr);
			}

			node_pointer __insert(node_pointer pos, const Key& key, const Value& value)
			{
				return this->Insert(pos, key, value, colors::red, nullptr, nullptr, nullptr);
			}
		};


#include "GBalanceTree.inl"
	}
}
#endif // !GBLANCE_TREE_H


