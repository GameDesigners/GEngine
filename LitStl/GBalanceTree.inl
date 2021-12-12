template<class Key, class Value, GMemManagerFun MMFun>
__balance_tree<Key, Value, MMFun>::__balance_tree()
{
	m_root = nuulptr;
}



//¸¨Öúº¯Êý
//*************************************************************************
template<class Key, class Value, GMemManagerFun MMFun>
void __balance_tree<Key, Value, MMFun>::__left_rotate(node_pointer& root, node_pointer x)
{
	node_pointer _right = x->right;
	x->right = _right->left;
	_right->left = x;
	
	if (root->left == x)
		root->left = _right;
	else
		root->right = _right;
}