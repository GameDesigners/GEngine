template<class NodeType, class HashFunc, class ExtractKey, class EqualKey, GMemManagerFun MMFun>
const size_t __hash_table<NodeType, HashFunc, ExtractKey, EqualKey, MMFun>::__stl_num_primes;

template<class NodeType, class HashFunc, class ExtractKey, class EqualKey, GMemManagerFun MMFun>
const unsigned long __hash_table<NodeType, HashFunc, ExtractKey, EqualKey, MMFun>::__stl_prime_list[__hash_table<NodeType, HashFunc, ExtractKey, EqualKey, MMFun>::__stl_num_primes] =
{
    53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593,
    49157, 98317, 196613, 393241, 786433, 1572869, 3145739,
    6291469, 12582917, 25165843, 50331653, 100663319,
    201326611, 402653189, 805306457, 1610612741,
    3221225473ul, 4294967291ul 
};

// 构造函数
//**********************************************************************************************************************************************

template<class NodeType, class HashFunc, class ExtractKey, class EqualKey, GMemManagerFun MMFun>
__hash_table<NodeType, HashFunc, ExtractKey, EqualKey, MMFun>::__hash_table()
{
    m_max_load_factor = 0.75;
    m_current_bucket_idx = 0;
    m_count = 0;
    m_bucket.assign(__stl_prime_list[m_current_bucket_idx]);
    
}

template<class NodeType, class ConflictHandlingFun, class ExtractKey, class EqualKey, GMemManagerFun MMFun>
inline GEngine::GStl::__hash_table<NodeType, ConflictHandlingFun, ExtractKey, EqualKey, MMFun>::__hash_table(size_t bnum)
{
    m_count == 0;
    m_current_bucket_idx = __location_capcity_idx();
    m_bucket.assign(__stl_num_primes[m_current_bucket_idx]);
}

template<class NodeType, class ExtractKey, class ConflictHandlingFun, class EqualKey, GMemManagerFun MMFun>
template<typename ...Args>
inline NodeType* GEngine::GStl::__hash_table<NodeType, ExtractKey, ConflictHandlingFun, EqualKey, MMFun>::__hash_insert(Args ...args)
{
    node_pointer node = this->New(1);
    GASSERT(node != nullptr);
    GNEW(node)NodeType(args...);

    size_t idx = __get_bucket_idx_by_key(node->key);
    node->next = rehash_vec[idx];
    rehash_vec[idx] = node;
    m_count++;
    return node;
}

template<class NodeType, class ExtractKey, class ConflictHandlingFun, class EqualKey, GMemManagerFun MMFun>
inline void GEngine::GStl::__hash_table<NodeType, ExtractKey, ConflictHandlingFun, EqualKey, MMFun>::__remove(const key_type& key)
{
    size_t idx = __get_bucket_idx_by_key(key);
    node_pointer p = m_bucket[idx];
    if (p->key == key)
    {
        //删除首节点
        m_bucket[idx] = p->next;
        this->Delete(p, 1, 1);
    }
    else
    {
        //查找删除节点
        node_pointer q = p->next;
        while (q != nullptr)
        {
            if (q->key == key)
            {
                p->next = q->next;
                this->Delete(q, 1, 1);
                q = p->next;
                continue;
            }
            p = q;
            q = q->next;
        }
        
    }
}

template<class NodeType, class ExtractKey, class ConflictHandlingFun, class EqualKey, GMemManagerFun MMFun>
inline NodeType* GEngine::GStl::__hash_table<NodeType, ExtractKey, ConflictHandlingFun, EqualKey, MMFun>::__search(const key_type& key)
{
    size_t idx = __get_bucket_idx_by_key(key);
    node_pointer p = m_bucket[idx];
    while (p!=nullptr)
    {
        if (keyEquals(p->key, key))
            return p;
    }
    return nullptr;
}

template<class NodeType, class ConflictHandlingFun, class ExtractKey, class EqualKey, GMemManagerFun MMFun>
inline void GEngine::GStl::__hash_table<NodeType, ConflictHandlingFun, ExtractKey, EqualKey, MMFun>::__rehash_table(size_t bnum)
{
    size_t idx = __location_capcity_idx(bnum);
    GVector<node_pointer> temp(__stl_prime_list[idx], nullptr);
    for (auto p = m_bucket.begin(); p != m_bucket.end(); p++)
    {
        node_pointer q = *p;
        while (q!=nullptr)
        {
            node_pointer node = q->next;
            node_pointer new_node = this->New(1);
            new_node->move_data(g_move(q));
            __insert(new_node);
            this->Delete(q, 1, 1);
            q = node;
        }
    }
}

template<class NodeType, class ExtractKey, class ConflictHandlingFun, class EqualKey, GMemManagerFun MMFun>
inline void GEngine::GStl::__hash_table<NodeType, ExtractKey, ConflictHandlingFun, EqualKey, MMFun>::__rehash_insert(node_pointer node, GVector<node_pointer>& rehash_vec, const size_t& capcity)
{
    size_t hashcode = extractKey(node->key);//获取哈希值
    size_t idx = conflictHandlingFun(hashcode, capcity);
    GASSERT(idx < capcity);
    node->next = rehash_vec[idx];
    rehash_vec[idx] = node;
}