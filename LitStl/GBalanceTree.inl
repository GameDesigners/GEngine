//构造函数
//*************************************************************************
template<class NodeType, typename Compare, GMemManagerFun MMFun>
__balance_tree<NodeType, Compare, MMFun>::__balance_tree()
{
	m_root = nullptr;
	m_count = 0;
}

template<class NodeType, typename Compare, GMemManagerFun MMFun>
__balance_tree<NodeType, Compare, MMFun>::~__balance_tree()
{
	__destroy(m_root);
	m_count = 0;
}


//增删查改、销毁
//*************************************************************************

template<class NodeType, typename Compare, GMemManagerFun MMFun>
void __balance_tree<NodeType, Compare, MMFun>::PreOrder()
{
	node_pointer root = m_root;
	__pre_order(root);
}

template<class NodeType, typename Compare, GMemManagerFun MMFun>
void __balance_tree<NodeType, Compare, MMFun>::InOrder()
{
	node_pointer root = m_root;
	__in_order(root);
}

template<class NodeType, typename Compare, GMemManagerFun MMFun>
void __balance_tree<NodeType, Compare, MMFun>::PostOrder()
{
	node_pointer root = m_root;
	__post_order(root);
}


//增删查改、销毁
//*************************************************************************

template<class NodeType, typename Compare, GMemManagerFun MMFun>
typename __balance_tree<NodeType, Compare, MMFun>::node_pointer __balance_tree<NodeType, Compare, MMFun>::Search(const key_type& key)
{
	node_pointer root = m_root;
	return __search(root, key);
}

template<class NodeType, typename Compare, GMemManagerFun MMFun>
typename __balance_tree<NodeType, Compare, MMFun>::node_pointer __balance_tree<NodeType, Compare, MMFun>::IterativeSearch(const key_type& key)
{
	node_pointer root = m_root;
	return __interative_search(root, key);
}

template<class NodeType, typename Compare, GMemManagerFun MMFun>
typename __balance_tree<NodeType, Compare, MMFun>::node_pointer __balance_tree<NodeType, Compare, MMFun>::Minmum()
{
	node_pointer tree = m_root; 
	return __minimum(tree);
}

template<class NodeType, typename Compare, GMemManagerFun MMFun>
typename __balance_tree<NodeType, Compare, MMFun>::node_pointer __balance_tree<NodeType, Compare, MMFun>::Maxmum()
{
	node_pointer tree = m_root;
	return __maximum(tree);
}

template<class NodeType, typename Compare, GMemManagerFun MMFun>
typename __balance_tree<NodeType, Compare, MMFun>::node_pointer __balance_tree<NodeType, Compare, MMFun>::Successor(node_pointer node)
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

template<class NodeType, typename Compare, GMemManagerFun MMFun>
typename __balance_tree<NodeType, Compare, MMFun>::node_pointer __balance_tree<NodeType, Compare, MMFun>::PreDecessor(node_pointer node)
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

template<class NodeType, typename Compare, GMemManagerFun MMFun>
template<typename... Args>
typename __balance_tree<NodeType, Compare, MMFun>::node_pointer __balance_tree<NodeType, Compare, MMFun>::Insert(Args ...args)
{
	node_pointer node = this->New(1);
	GASSERT(node);
	GNEW(node)NodeType(args...);
	__insert(m_root, node);
	return node;
}

template<class NodeType, typename Compare, GMemManagerFun MMFun>
template<typename... Args>
typename __balance_tree<NodeType, Compare, MMFun>::node_pointer __balance_tree<NodeType, Compare, MMFun>::Insert(node_pointer pos,Args ...args)
{
	node_pointer node = this->New(1);
	GASSERT(node);
	GNEW(node)NodeType(args...);
	__insert(pos, node);
	return node;
}

template<class NodeType, typename Compare, GMemManagerFun MMFun>
void __balance_tree<NodeType, Compare, MMFun>::Remove(const key_type& key)
{
	node_pointer searchres = Search(key);
	if (searchres != nullptr)
		__remove(m_root, searchres);
}

template<class NodeType, typename Compare, GMemManagerFun MMFun>
void __balance_tree<NodeType, Compare, MMFun>::Destroy()
{
	__destroy(m_root);
}

//辅助函数
//*************************************************************************

template<class NodeType, typename Compare, GMemManagerFun MMFun>
typename __balance_tree<NodeType, Compare, MMFun>::node_pointer __balance_tree<NodeType, Compare, MMFun>::__search(node_pointer x, const key_type& key) const
{
	if (x == nullptr || x->key == key)
		return x;

	if (comparator(x->key, key))
		return __search(x->right, key);
	else
		return __search(x->left, key);
}

template<class NodeType, typename Compare, GMemManagerFun MMFun>
typename __balance_tree<NodeType, Compare, MMFun>::node_pointer __balance_tree<NodeType, Compare, MMFun>::__interative_search(node_pointer x, const key_type& key) const
{
	while (x != nullptr && x->key != key)
	{
		if (comparator(key, x->key))
			x = x->left;
		else
			x = x->right;
	}
	return x;
}

template<class NodeType, typename Compare, GMemManagerFun MMFun>
typename __balance_tree<NodeType, Compare, MMFun>::node_pointer __balance_tree<NodeType, Compare, MMFun>::__minimum(node_pointer tree) const
{
	if (tree == nullptr)
		return nullptr;

	while (tree->left != nullptr)
		tree = tree->left;
	return tree;
}

template<class NodeType, typename Compare, GMemManagerFun MMFun>
typename __balance_tree<NodeType, Compare, MMFun>::node_pointer __balance_tree<NodeType, Compare, MMFun>::__maximum(node_pointer tree) const
{
	if (tree == nullptr)
		return nullptr;

	while (tree->right != nullptr)
		tree = tree->right;
	return tree;
}



template<class NodeType, typename Compare, GMemManagerFun MMFun>
void __balance_tree<NodeType, Compare, MMFun>::__left_rotate(node_pointer& root, node_pointer x)
{
	node_pointer xp = x->parent;

	//将ly 转移到 x的右子节点
	node_pointer y = x->right;
	x->right = y->left;
	if (y->left != nullptr)
		y->left->parent = x;

	y->left = x;
	x->parent = y;

	if (xp==nullptr) {
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

template<class NodeType, typename Compare, GMemManagerFun MMFun>
void __balance_tree<NodeType, Compare, MMFun>::__right_rotate(node_pointer& root, node_pointer y)
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

template<class NodeType, typename Compare, GMemManagerFun MMFun>
void __balance_tree<NodeType, Compare, MMFun>::__insert_fix_up(node_pointer& root, node_pointer node)
{
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
			parent->color = colors::black;
			grand_parent->color = colors::red;
			__right_rotate(root, grand_parent);
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
			parent->color = colors::black;
			grand_parent->color = colors::red;
			__left_rotate(root, grand_parent);
		}
	}
	root->color = colors::black;
}

template<class NodeType, typename Compare, GMemManagerFun MMFun>
void __balance_tree<NodeType, Compare, MMFun>::__remove_fix_up(node_pointer& root, node_pointer node, node_pointer parent)
{
	//parent : deleted node's parent
	//node   : deleted node's child

	node_pointer s;
	while ((!node || node->color == colors::black) && node != root)  //前面一段略过了node不为nullptr且为红色的情况，因为不需要做调整，仅需要将节点设置为黑色即可保持平衡
	{
		if (parent->left == node)
		{
			s = parent->right;
			if (s->color == colors::red)
			{
				parent->color = colors::red;
				s->color = colors::black;
				__left_rotate(root, parent);
				s = parent->right;
			}

			//下面都表示s节点的颜色是黑色的情况
			if ((s->left == nullptr || s->left->color == colors::black) && (s->right == nullptr || s->right->color == colors::black))
			{
				s->color == colors::red;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (s->right == nullptr || s->right->color == colors::black)
				{
					s->left->color = colors::black;
					s->color = colors::red;
					__right_rotate(root, s);
					s = parent->right;
				}

				s->color = parent->color;
				parent->color = colors::black;
				s->right->color = colors::black;
				__left_rotate(root, parent);
				node = root;
				break;
			}
		}
		else
		{
			s = parent->left;
			if (s->color == colors::red)
			{
				parent->color = colors::red;
				s->color = colors::black;
				__right_rotate(root, parent);
				s = parent->left;
			}

			//下面都表示s节点的颜色是黑色的情况
			if ((s->left == nullptr || s->left->color == colors::black) && (s->right == nullptr || s->right->color == colors::black))
			{
				s->color == colors::red;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (s->left == nullptr || s->left->color == colors::black)
				{
					s->right->color = colors::black;
					s->color = colors::red;
					__left_rotate(root, s);
					s = parent->left;
				}

				s->color = parent->color;
				parent->color = colors::black;
				s->left->color = colors::black;
				__right_rotate(root, parent);
				node = root;
				break;
			}
		}
	}

	if (node != nullptr)
		node->color == colors::black;
}

template<class NodeType, typename Compare, GMemManagerFun MMFun>
void __balance_tree<NodeType, Compare, MMFun>::__insert(node_pointer& root, node_pointer node)
{
	node_pointer x = root;
	node_pointer y = nullptr;

	//找到符合二叉搜索树的适合叶节点位置
	while (x != nullptr)
	{
		y = x;
		if (comparator(node->key, x->key))
			x = x->left;
		else if (comparator(x->key, node->key))
			x = x->right;
	}

	node->parent = y;
	if (y != nullptr)
	{
		if (comparator(node->key, y->key))
			y->left = node;
		else
			y->right = node;
	}
	else {
		root = node;
		node->color = colors::black;  //根节点是黑色
		m_count++;
		return;
	}

	//设置颜色
	node->color = colors::red;
	
	//修正成红黑树
	__insert_fix_up(root, node);
	m_count++;
}

template<class NodeType, typename Compare, GMemManagerFun MMFun>
void __balance_tree<NodeType, Compare, MMFun>::__remove(node_pointer& root, node_pointer node)
{
	node_pointer child, parent;
	colors color;

	if (node->left != nullptr && node->right != nullptr)
	{
		node_pointer replace = node->right;
		while (replace->left != nullptr)
			replace = replace->left;

		child = replace->right;
		parent = replace->parent;
		color = replace->color;

		//交换值，将删除的节点转移到replace
		//node->key = replace->key;


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
		node->right->parent = replace;



		if (color == colors::black)  //修正：[从一个节点到该节点的子孙节点的所有路径上包含相同数目的黑节点]，因为删除了黑节点意味着在该路上将会 -1
			__remove_fix_up(root, child, parent);
		this->Delete(node, 1, 1);
		node = nullptr;
		m_count--;
		return;
	}

	if (node->left != nullptr)
		child = node->left;
	else
		child = node->right;

	parent = node->parent;
	color = node->color;
	if (child != nullptr)
		child->parent = parent;
	if (parent != nullptr)//不是根节点
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
	this->Delete(node, 1, 1);
	m_count--;
}

template<class NodeType, typename Compare, GMemManagerFun MMFun>
void __balance_tree<NodeType, Compare, MMFun>::__destroy(node_pointer& tree)
{
	if (tree == nullptr)
		return;

	if (tree->left != nullptr)
		__destroy(tree->left);
	if (tree->right)
		__destroy(tree->right);
	this->Delete(tree, 1, 1);
	tree = nullptr;
	m_count = 0;
}