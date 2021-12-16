template<class T, class ConflictHandlingFun, class ExtractT, class EqualHashCode, GMemManagerFun MMFun>
inline GEngine::GStl::__GUnorderedSet<T, ConflictHandlingFun, ExtractT, EqualHashCode, MMFun>::__GUnorderedSet() {}

template<class T, class ConflictHandlingFun, class ExtractT, class EqualHashCode, GMemManagerFun MMFun>
inline GEngine::GStl::__GUnorderedSet<T, ConflictHandlingFun, ExtractT, EqualHashCode, MMFun>::__GUnorderedSet(size_t bnum) : __hash_table(bnum) {}

template<class T, class ConflictHandlingFun, class ExtractT, class EqualHashCode, GMemManagerFun MMFun>
inline GEngine::GStl::__GUnorderedSet<T, ConflictHandlingFun, ExtractT, EqualHashCode, MMFun>::__GUnorderedSet(const __GUnorderedSet& cv)
{
	this->m_current_bucket_idx = cv.m_current_bucket_idx;
	this->m_count = cv.m_count;

}

template<class T, class ConflictHandlingFun, class ExtractT, class EqualHashCode, GMemManagerFun MMFun>
inline GEngine::GStl::__GUnorderedSet<T, ConflictHandlingFun, ExtractT, EqualHashCode, MMFun>::__GUnorderedSet(__GUnorderedSet&& rv)
{
	this->m_current_bucket_idx = rv.m_current_bucket_idx;
	this->m_count = rv.m_count;
	this->m_bucket=g_move(rv.m_bucket);

	rv.m_current_bucket_idx = 0;
	rv.m_count = 0;
}