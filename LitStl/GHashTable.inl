template<class NodeType, class HashFunc, class ExtractKey, class EqualHashCode, GMemManagerFun MMFun>
const size_t __hash_table<NodeType, HashFunc, ExtractKey, EqualHashCode, MMFun>::__stl_num_primes;

template<class NodeType, class HashFunc, class ExtractKey, class EqualHashCode, GMemManagerFun MMFun>
const unsigned long __hash_table<NodeType, HashFunc, ExtractKey, EqualHashCode, MMFun>::__stl_prime_list[__hash_table<NodeType, HashFunc, ExtractKey, EqualHashCode, MMFun>::__stl_num_primes] =
{
    53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593,
    49157, 98317, 196613, 393241, 786433, 1572869, 3145739,
    6291469, 12582917, 25165843, 50331653, 100663319,
    201326611, 402653189, 805306457, 1610612741,
    3221225473ul, 4294967291ul 
};

// ¹¹Ôìº¯Êý
//*************************************************************************

template<class NodeType, class HashFunc, class ExtractKey, class EqualHashCode, GMemManagerFun MMFun>
__hash_table<NodeType, HashFunc, ExtractKey, EqualHashCode, MMFun>::__hash_table()
{
    m_count = 0;
    m_current_bucket_idx = 0;
    m_bucket.assign(__stl_prime_list[m_current_bucket_idx]);
}

template<class NodeType, class ConflictHandlingFun, class ExtractKey, class EqualHashCode, GMemManagerFun MMFun>
inline GEngine::GStl::__hash_table<NodeType, ConflictHandlingFun, ExtractKey, EqualHashCode, MMFun>::__hash_table(size_t bnum)
{
    m_count == 0;
    m_current_bucket_idx = 0;
    while (__stl_num_primes[m_current_bucket_idx] < bnum)
        m_current_bucket_idx++;
    m_bucket.assign(__stl_num_primes[m_current_bucket_idx];)
}

template<class NodeType, class ConflictHandlingFun, class ExtractKey, class EqualHashCode, GMemManagerFun MMFun>
inline void GEngine::GStl::__hash_table<NodeType, ConflictHandlingFun, ExtractKey, EqualHashCode, MMFun>::__resize_bucket_table(size_t bnum)
{
    
}