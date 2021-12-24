/*
 *   �����飺
 *   ***********************************************************************************************************************************************************
 *   *����        |   *ʱ�临�Ӷ�(ƽ��) |   *ʱ�临�Ӷ�(�)   |    *ʱ�临�Ӷ�(���)         |    *�ռ临�Ӷ�          |    *�ȶ���           |                       |
 *   ***********************************************************************************************************************************************************
 *   ð������      |   O(n^2)          |   O(n^2)            |    O(n)                   |     O(1)               |     �ȶ�             |                       |
 *   ѡ������      |   O(n^2)          |   O(n^2)            |    O(n^2)                 |     O(1)               |     ���ȶ�           |						   |
 *   ��������      |   O(n^2)          |   O(n^2)            |    O(n)                   |     O(1)               |     �ȶ�             |					   |
 *   ϣ������      |   O(n^1.3)        |   O(n^2)            |    O(n)                   |     O(1)               |     ���ȶ�           |						   |
 *   ��������      |   O(nlog2^n)      |   O(n^2)            |    O(nlog2^n)             |     O(nlog2^n)         |     ���ȶ�           |						   |
 *   �鲢����      |   O(nlog2^n)      |   O(nlog2^n)        |    O(nlog2^n)             |     O(n)               |     �ȶ�             | wrote date:2021.12.24 |
 *   ������        |   O(nlog2^n)      |   O(nlog2^n)        |    O(nlog2^n)             |     O(1)               |     ���ȶ�           |					   |
 *   ��������		  |   O(n*k)          |   O(n*k)            |    O(n*k)                 |     O(n+k)             |     �ȶ�             |					   |
 *   ***********************************************************************************************************************************************************
 */

template<typename Iterator, typename Compare>
void __merge(Iterator& begin, typename iterator_traits<Iterator>::value_pointer tempSpace, size_t _start, size_t _mid, size_t _end, const Compare& comparetor)
{
	GASSERT(_start <= _mid && _mid <= _end);
	int i = _start;
	int j = _mid + 1;
	int index = 0;

	while (i <= _mid && j <= _end)
	{
		if (comparetor(*(begin + i), *(begin + j)))
		{
			tempSpace[index++] = *(begin + i);
			i++;
		}
		else
		{
			tempSpace[index++] = *(begin + j);
			j++;
		}
	}

	while (i <= _mid)
	{
		tempSpace[index++] = *(begin + i);
		i++;
	}
	while (j <= _end)
	{
		tempSpace[index++] = *(begin + j);
		j++;
	}

	unsigned int sortNum = _end - _start + 1;
	for (int k = _start, index = 0; index < sortNum; k++, index++)
		*(begin + k) = tempSpace[index];
}

//������[0, length - 1]��һ�˹鲢����Ϊn�Ĺ鲢����
template<typename Iterator, typename Compare>
void __merge_pass(Iterator& begin, typename iterator_traits<Iterator>::value_pointer tmpSortSpace, size_t sortNum, size_t stepNum, const Compare& comparetor)
{
	GASSERT(sortNum > 0 && stepNum > 0);
	int i, sortLength = 2 * stepNum;
	for (i = 0; i + sortLength - 1 < sortNum; i += sortLength)
		__merge(begin, tmpSortSpace, i, i + stepNum - 1, i + sortLength - 1, comparetor);

	if (sortNum - 1 > i + stepNum - 1)
		__merge(begin, tmpSortSpace, i, i + stepNum - 1, sortNum - 1, comparetor);
}

//�����㷨
//**********************************************************************************************************************************************
template<typename Iterator>
inline void sort(Iterator begin, Iterator end)
{
	typename iterator_traits<Iterator>::iterator_category category = iterator_category(begin);
	__sort(begin, end, less<typename Iterator::value_type>(), category);
}

template<typename Iterator, typename Compare>
inline void sort(Iterator begin, Iterator end, const Compare& comparetor)
{
	typename iterator_traits<Iterator>::iterator_category category = iterator_category(begin);
	__sort(begin, end, comparetor, category);
}

template<typename Iterator,typename Compare>
inline void __sort(Iterator& begin, Iterator& end,const Compare& comparetor, random_access_iterator_tag)
{
	//ʹ�ù鲢�����򷽷�
	size_t sortNum = end - begin;
	typename iterator_traits<Iterator>::value_pointer tmpSortSpace = GNEW typename iterator_traits<Iterator>::value_type[sortNum];
	for (int n = 1; n < sortNum; n = (n << 1))
		__merge_pass(begin, tmpSortSpace, sortNum, n, comparetor);
	GSAFE_DELETE_ARRAY(tmpSortSpace);
}

template<typename Iterator, typename Compare>
inline void __sort(Iterator& begin, Iterator& end, const Compare& comparetor, bidirectional_iterator_tag)
{

}

template<typename Iterator, typename Compare>
inline void __sort(Iterator& begin, Iterator& end, const Compare& comparetor, forward_iterator_tag)
{

}

