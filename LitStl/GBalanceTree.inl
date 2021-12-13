//构造函数
//*************************************************************************
template<class Key, class Value, GMemManagerFun MMFun>
__balance_tree<Key, Value, MMFun>::__balance_tree()
{
	m_root = nuulptr;
}

template<class Key, class Value, GMemManagerFun MMFun>
__balance_tree<Key, Value, MMFun>::~__balance_tree()
{
	__destroy();
}

//增删查改、销毁
//*************************************************************************

template<class Key, class Value, GMemManagerFun MMFun>
__balance_tree<Key, Value, MMFun>::node_pointer __balance_tree<Key, Value, MMFun>::Search(const Key& key)
{
	node_pointer root = m_root;
	return __search(root, key);
}

template<class Key, class Value, GMemManagerFun MMFun>
__balance_tree<Key, Value, MMFun>::node_pointer __balance_tree<Key, Value, MMFun>::IterativeSearch(const Key& key)
{
	node_pointer root = m_root;
	return __interative_search(root, key);
}

template<class Key, class Value, GMemManagerFun MMFun>
Value& __balance_tree<Key, Value, MMFun>::Minmum()
{
	node_pointer tree = m_root; 
	return __minimum(tree)->value;
}

template<class Key, class Value, GMemManagerFun MMFun>
Value& __balance_tree<Key, Value, MMFun>::Maxmum()
{
	node_pointer tree = m_root;
	return __maximum(tree)->value;
}

template<class Key, class Value, GMemManagerFun MMFun>
__balance_tree<Key, Value, MMFun>::node_pointer __balance_tree<Key, Value, MMFun>::Successor(node_pointer node)
{
	node_pointer p = node;
	if (p->right != nullptr) return __minimum(p->right);
	
	node_pointer parent = p->parent;
	while (parent != nullptr && p == parent->right)
	{
		p = parent;
		parent = parent->parent;
	}
	return parent;
}

template<class Key, class Value, GMemManagerFun MMFun>
__balance_tree<Key, Value, MMFun>::node_pointer __balance_tree<Key, Value, MMFun>::PreDecessor(node_pointer node)
{
	node_pointer p = node;
	if (p->left != nullptr) return __maximum(p->left);

	node_pointer parent = p->parent;
	while (parent != nullptr && p == parent->left)
	{
		p = parent;
		parent = parent->parent;
	}
	return parent;
}

template<class Key, class Value, GMemManagerFun MMFun>
void __balance_tree<Key, Value, MMFun>::Insert(key_type key, value_type value)
{
	node_pointer new_node = __create_node(key, value);
	__insert(m_root, new_node);
}

template<class Key, class Value, GMemManagerFun MMFun>
void __balance_tree<Key, Value, MMFun>::Remove(key_type key)
{
	__remove(m_root, key);
}

template<class Key, class Value, GMemManagerFun MMFun>
void __balance_tree<Key, Value, MMFun>::Destroy()
{
	__destroy(m_root);
}

//辅助函数
//*************************************************************************

template<class Key, class Value, GMemManagerFun MMFun>
void __balance_tree<Key, Value, MMFun>::__create_node(const Key& key, const Value& value)
{
	node_pointer node = this->New(1);
	GASSERT(node);
	GNEW(node)__balance_tree_node<Key, Value>(key, value, colors::red, nullptr, nullptr, nullptr);
}

template<class Key, class Value, GMemManagerFun MMFun>
__balance_tree<Key, Value, MMFun>::node_pointer __balance_tree<Key, Value, MMFun>::__search(node_pointer x, Key key) const
{
	if (x == nullptr || x->key == key)
		return x;

	if (key < x->key)
		return __search(x->left, key);
	else
		return __search(x->right, key);
}

template<class Key, class Value, GMemManagerFun MMFun>
__balance_tree<Key, Value, MMFun>::node_pointer __balance_tree<Key, Value, MMFun>::__interative_search(node_pointer x, Key key) const
{
	while (x != nullptr && x->key != key)
	{
		if (key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	return x;
}

template<class Key, class Value, GMemManagerFun MMFun>
__balance_tree<Key, Value, MMFun>::node_pointer __balance_tree<Key, Value, MMFun>::__minimum(node_pointer tree) const
{
	if (tree == nullptr)
		return nullptr;

	while (tree->left != nullptr)
		tree = tree->left;
	return tree;
}

template<class Key, class Value, GMemManagerFun MMFun>
__balance_tree<Key, Value, MMFun>::node_pointer __balance_tree<Key, Value, MMFun>::__maximum(node_pointer tree) const
{
	if (tree == nullptr)
		return nullptr;

	while (tree->right != nullptr)
		tree = tree->right;
	return tree;
}



template<class Key, class Value, GMemManagerFun MMFun>
void __balance_tree<Key, Value, MMFun>::__left_rotate(node_pointer& root, node_pointer x)
{
	node_pointer xp = x->parent;

	//将ly 转移到 x的右子节点
	node_pointer y = x->right;
	x->right = y->left;
	if (y->left != nullptr)
		y->left->parent = x;

	y->left = x;
	x->parent = y;

	if (parent != nullptr) {
		root = y;
		y->parent = nullptr;
	}
	else
	{
		if (xp->left == x)
			xp->left = y;
		else
			xp->right = y;


		y->parent = xp;
	}
}

template<class Key, class Value, GMemManagerFun MMFun>
void __balance_tree<Key, Value, MMFun>::__right_rotate(node_pointer& root, node_pointer y)
{
	node_pointer yp = y->parent;
	node_pointer x = y->left;
	y->left = x->right;
	if (x->right != nullptr)
		x->right->parent = y;

	x->right = y;
	y->parent = x;

	if (yp == nullptr)
	{
		root = x;
		x->parent = nullptr;
	}
	else
	{
		if (yp->left == y)
			yp->left = x;
		else
			yp->right = x;

		x->parent = yp;
	}
}

template<class Key, class Value, GMemManagerFun MMFun>
void __balance_tree<Key, Value, MMFun>::__insert_fix_up(node_pointer& root, node_pointer node)
{
	/*node_pointer parent, gparent;
	while ((paren = node->parent) && parent->color == colors::red)
	{
		gparent = parent->parent;

		if (parent == gparent->left)
		{
			node_pointer uncle = gparent->right;
			if (uncle && uncle->color == colors::red)
			{
				uncle->color = colors::black;
				parent->color = colors::black;
				gparent->color = colors::red;

				node = gparent;
				continue;
			}

			if (parent->right == node)
			{
				node_pointer temp;
				__left_rotate(root, parent);
				temp = parent;
				parent = node;
				node = temp;
			}

			parent->color = colors::black;
			gparent->color = colors::red;
			__right_rotate(root, gparent);
		}
		else
		{
			node_pointer uncle = gparent->left;
			if (uncle && uncle->color == colors::red)
			{
				uncle->color = colors::black;
				parent->color = colors::black;
				gparent->color = colors::red;

				node = gparent;
				continue;
			}

			if (parent->left == node)
			{
				node_pointer temp;
				__right_rotate(root, parent);
				temp = parent;
				parent = node;
				node = temp;
			}

			parent->color = colors::black;
			gparent->color = colors::red;
			__left_rotate(root, gparent);
		}
	}

	root->color = colors::black;*/

	node_pointer parent = node->parent;
	node_pointer grand_parent = nullptr;
	node_pointer uncle = nullptr;
	while (parent != nullptr && parent->color == colors::red)
	{
		parent = node->parent;
		grand_parent = parent->parent;  //根节点是黑色节点可知，parent不可能是根节点，因此不需要判断grand_parent是否为空

		if (grand_parent->left == parent)
		{
			uncle = grand_parent->right;
			if (uncle != nullptr && uncle->color == colors::red)
			{
				parent->color = colors::black;
				grand_parent->right->color = colors::black;
				grand_parent->color = colors::red;
				node = grand_parent;
				continue;
			}
			
			if (parent->right == node)
			{
				__left_rotate(root, parent);
				__node_point_swap(node, parent);
			}
			else
			{
				parent->color = colors::black;
				grand_parent->color = colors::red;
				__right_rotate(root, grand_parent);
			}
		}
		else
		{
			uncle = grand_parent->left;
			if (uncle && uncle->color == colors::red)
			{
				uncle->color = colors::black;
				parent->color = colors::black;
				grand_parent->color = colors::red;
				node = grand_parent;
				continue;
			}

			if (parent->left == node)
			{
				__right_rotate(root, parent);
				__node_point_swap(node, parent);
			}
			else
			{
				parent->color = colors::black;
				grand_parent->color = colors::red;
				__left_rotate(root, grand_parent);
			}
		}
	}
	root->color = colors::black;
}

template<class Key, class Value, GMemManagerFun MMFun>
void __balance_tree<Key, Value, MMFun>::__remove_fix_up(node_pointer& root, node_pointer node, node_pointer parent)
{
	node_pointer other;
	while ((!node || node->color == colors::black) && node != root)
	{
		if (parent->left == node)
		{
			other = parent->right;
			if (other->color == colors::red)
			{
				other->color = colors::black;
				parent->color = colors::red;
				__left_rotate(root, parent);
				other = parent->right;
			}

			if ((!other->left || other->left->color==colors::black) && (!other->right || other->left->color == colors::black))
			{
				other->color = colors::red;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!other->right || other->right->color == colors::black)
				{
					other->left->color = colors::black;
					other->color = colors::red;
					__right_rotate(root, other);
					other = parent->right;
				}

				other->color = parent->color;
				parent->color = colors::black;
				other->right->color = colors::black;
				__left_rotate(root, parent);
				node = root;
				break;
			}
		}
		else
		{
			other = parent->left;
			if (other->color == colors::red)
			{
				other->color = colors::black;
				parent->color = colors::red;
				__right_rotate(root, parent);
				other = parent->left;
			}

			if ((!other->left || other->left->color == colors::black) && (!other->right || other->left->color == colors::black))
			{
				other->color = colors::red;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!other->right || other->right->color == colors::black)
				{
					other->right->color = colors::black;
					other->color = colors::red;
					__left_rotate(root, other);
					other = parent->left;
				}

				other->color = parent->color;
				parent->color = colors::black;
				other->left->color = colors::black;
				__right_rotate(root, parent);
				node = root;
				break;
			}
		}
	}

	if (node)
		node->color = colors::black;
}

template<class Key, class Value, GMemManagerFun MMFun>
void __balance_tree<Key, Value, MMFun>::__insert(node_pointer& root, node_pointer node)
{
	node_pointer x = root;
	node_pointer y = nullptr;

	//找到符合二叉搜索树的适合叶节点位置
	while (x != nullptr)
	{
		y = x;
		if (node->key < x->key)
			x = x->left;
		else if (node->key > x->key)
			x = x->right;
	}

	node->parent = y;
	if (y != nullptr)
	{
		if (node->key < y->key)
			y->left = node;
		else
			y->right = node;
	}
	else {
		root = node;
		node->color = colors::black;  //根节点是黑色
		return;
	}

	//设置颜色
	node->color = colors::red;
	
	//修正成红黑树
	__insert_fix_up(root, node);
}

template<class Key, class Value, GMemManagerFun MMFun>
void __balance_tree<Key, Value, MMFun>::__remove(node_pointer& root, node_pointer node)
{
	/*node_pointer child, parent;
	colors color;

	if ((node->left != nullptr) && (node->right != nullptr))
	{
		node_pointer replace = node->right;
		while (replace->left != nullptr)
			replace = replace->left;

		if (node->parent != nullptr)
		{
			if (node->parent->left == node)
				node->parent->left = replace;
			else
				node->parent->right = replace;
		}
		else
			root = replace;

		child = replace->right;
		parent = replace->parent;
		color = replace->color;

		if (parent == node)
			parent = replace;
		else
		{
			if (child)
				child->parent = parent;
			parent->left = child;

			replace->right = node->right;
			node->right->parent = replace;
		}

		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;

		if (color == colors::black)
			__remove_fix_up(root, child, parent);

		this->Delete(node, 1, 1);
		return;
	}

	if (node->left != nullptr)
		child = node->left;
	else
		child = node->right;

	parent = node->parent;
	color = node->color;

	if (child)
		child->parent = parent;

	if (parent)
	{
		if (parent->left == node)
			parent->left = child;
		else
			parent->right = child;
	}
	else
		root = child;

	if (color == colors::black)
		__remove_fix_up(root, child, parent);
	this->Delete(node, 1, 1);*/

	node_pointer child, parent;
	colors color;

	if (node->left != nullptr && node->right != nullptr)
	{
		node_pointer replace = node->right;
		while (replace->left != nullptr)
			replace = replace->left;

		if (node->parent != nullptr)
		{
			if (node->parent->left == node)
				node->parent->left = replace;
			else
				node->parent->right = replace;
		}
		else
			root = replace;

		child = replace->right;
		parent = replace->parent;
		color = replace->color;

		if (parent == node)
			parent = replace;
		else
		{
			if (child != nullptr)
				child->parent = parent;
			parent->left = child;
			replace->right = node->right;
			node->right->parent = replace;
		}

		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;

		if (color == colors::black)  //修正：[从一个节点到该节点的子孙节点的所有路径上包含相同数目的黑节点]，因为删除了黑节点意味着在该路上将会 -1
			__remove_fix_up(root, child, parent);
		this->Delete(node, 1, 1);
		return;
	}
}

template<class Key, class Value, GMemManagerFun MMFun>
void __balance_tree<Key, Value, MMFun>::__destroy(node_pointer& tree)
{
	if (tree == nullptr)
		return;

	if (tree->left != nullptr)
		return __destroy(tree->left);
	if (tree->right)
		return __destroy(tree->right);
	this->Delete(tree, 1, 1);
	tree = nullptr;
}