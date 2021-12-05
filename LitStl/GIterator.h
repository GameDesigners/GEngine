#ifndef GITERATOR_H
#define GITERATOR_H
#include "GStlMicro.h"
namespace GEngine {
	namespace GStl {
		//�ο�StlԴ������

		struct input_iterator_tag {};
		struct output_iterator_tag {};
		struct forward_iterator_tag : public input_iterator_tag {};
		struct bidirectional_iterator_tag : public forward_iterator_tag {};
		struct random_access_iterator_tag : public bidirectional_iterator_tag {};

		template<
			class Category,
			class T,
			class Distance=ptrdiff_t,
			class Pointer=T*,
			class Reference=T&
		>
		struct iterator
		{
			typedef Category    iterator_category;
			typedef T           value_type;
			typedef Distance    difference_type;
			typedef Pointer     value_pointer;
			typedef Reference   value_reference;
		};


		//�����ĵ���������������ȡ��
		template<class Iterator>
		struct iterator_traits
		{
			typedef typename Iterator::iterator_category iterator_category;
			typedef typename Iterator::value_type        value_type;
			typedef typename Iterator::difference_type   difference_type;
			typedef typename Iterator::value_pointer     value_pointer;
			typedef typename Iterator::value_reference   value_reference;
		};

		//���ԭ��ָ��ĵ���������������ȡ��
		template<class T>
		struct iterator_traits<T*>
		{
			typedef random_access_iterator_tag  iterator_category;
			typedef T                           value_type;
			typedef ptrdiff_t                   difference_type;
			typedef T*                          value_pointer;
			typedef T&                          value_reference;
		};

		//���const ԭ��ָ��ĵ���������������ȡ��
		template<class T>
		struct iterator_traits<const T*>
		{
			typedef random_access_iterator_tag  iterator_category;
			typedef T                           value_type;
			typedef ptrdiff_t                   difference_type;
			typedef const T*                    value_pointer;
			typedef const T&                    value_reference;
		};

		//��ȡ����������
		template<class Iterator>
		inline typename iterator_traits<Iterator>::iterator_category iterator_category(const Iterator&)
		{
			return iterator_traits<Iterator>::iterator_category();
		}

		template<class Iterator>
		inline typename iterator_traits<Iterator>::value_type* value_type(const Iterator&)
		{
			return static_cast<iterator_traits<Iterator>::value_type*>(0);
		}

		template<class Iterator>
		inline typename iterator_traits<Iterator>::difference_type* difference_type(Iterator&)
		{
			return static_cast<iterator_traits<Iterator>::difference_type*>(0);
		}


		//����������
		template<class InputIterator>
		inline typename iterator_traits<InputIterator>::difference_type __distance(InputIterator first, InputIterator last, input_iterator_tag)
		{
			typename iterator_traits<InputIterator>::difference_type _distance = 0;
			while (first != last)
			{
				_distance++;
				first++;
			}
			return _distance;
		}

		template<class RandomAccessIterator>
		inline typename iterator_traits<RandomAccessIterator>::difference_type __distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag)
		{
			return last - first;
		}

		template<class Iterator>
		inline typename iterator_traits<Iterator>::difference_type distance(const Iterator& first, const Iterator& last)
		{
			typedef iterator_traits<Iterator>::iterator_category category;
			return __distance(first, last, category());
		}


		template<class InputIterator,class Distance>
		inline void __advance(InputIterator& iter, Distance n, input_iterator_tag)
		{
			while (n--)
				iter++;
		}

		template<class BidirectionalIterator,class Distance>
		inline void __advance(BidirectionalIterator& iter, Distance n, bidirectional_iterator_tag)
		{
			if (n > 0)
			{
				while (n--)
					iter++;
			}
			else
			{
				while (n++)
					iter--;
			}
		}

		template<class RandomAccessIterator,class Distance>
		inline void __advance(RandomAccessIterator& iter, Distance n, random_access_iterator_tag)
		{
			iter += n;
		}

		template<class Iterator, class Distance>
		inline void advance(Iterator& iter, Distance n)
		{
			typedef iterator_traits<Iterator>::iterator_category category;
			__advance(iter, n, category());
		}




		//������GArray��GVector���ݴ洢��һ�������ڴ�������������
		template<class T> class GSTL_API _SingleMemUnit_Iterator : public iterator<random_access_iterator_tag, T>
		{
		public:
			_SingleMemUnit_Iterator(T* val) : current(val) {}
			~_SingleMemUnit_Iterator() {}
			void operator=(const _SingleMemUnit_Iterator& _itera) { current = _itera.current; } //�������캯��
			_SingleMemUnit_Iterator& operator++() { ++current; return *this; }                  //ǰ��++
			_SingleMemUnit_Iterator& operator--() { --current; return *this; }                  //ǰ��--
			_SingleMemUnit_Iterator& operator+=(int idx) { current += idx; return *this; }
			_SingleMemUnit_Iterator& operator-=(int idx) { current -= idx; return *this; }
			T& operator*() { return *current; }                                                 //������
			T* operator->() { return current; }                                                 //ָ�����

			_SingleMemUnit_Iterator operator++(int) { T* temp = current; current++; return _SingleMemUnit_Iterator(temp); }  //����++(�����ذ汾)
			_SingleMemUnit_Iterator operator--(int) { T* temp = current; current--; return _SingleMemUnit_Iterator(temp); }  //����--(�����ذ汾)
			_SingleMemUnit_Iterator operator+(int idx) { return _SingleMemUnit_Iterator(current + idx); }
			_SingleMemUnit_Iterator operator-(int idx) { return _SingleMemUnit_Iterator(current - idx); }

			bool operator!=(const _SingleMemUnit_Iterator& rhs) { return current != rhs.current; }
			bool operator==(const _SingleMemUnit_Iterator& rhs) { return current == rhs.current; }
			int  operator-(const _SingleMemUnit_Iterator& rhs) { return this->current - rhs.current; }

		protected:
			T* current;
		};
		template<class T> class GSTL_API _SingleMemUnit_CIterator : public iterator<random_access_iterator_tag, T>
		{
		public:
			_SingleMemUnit_CIterator(T* val) : current(val) {}
			~_SingleMemUnit_CIterator() {}
			void operator=(const _SingleMemUnit_CIterator& _citera) { current = _citera.current; } //�������캯��

			_SingleMemUnit_CIterator& operator++() { ++current; return *this; }               //ǰ��++
			_SingleMemUnit_CIterator& operator--() { --current; return *this; }               //ǰ��--
			_SingleMemUnit_CIterator& operator+=(int idx) { current += idx; return *this; }
			_SingleMemUnit_CIterator& operator-=(int idx) { current -= idx; return *this; }
			const T& operator*() { return *current; }                                     //������
			T* operator->() { return current; }                                     //ָ�����

			_SingleMemUnit_CIterator operator++(int) { T* temp = current; current++; return _SingleMemUnit_CIterator(temp); }  //����++(�����ذ汾)
			_SingleMemUnit_CIterator operator--(int) { T* temp = current; current--; return _SingleMemUnit_CIterator(temp); }  //����--(�����ذ汾)
			_SingleMemUnit_CIterator operator+(int idx) { return _SingleMemUnit_CIterator(current + idx); }
			_SingleMemUnit_CIterator operator-(int idx) { return _SingleMemUnit_CIterator(current - idx); }

			bool operator!=(const _SingleMemUnit_CIterator& rhs) { return current != rhs.current; }
			bool operator==(const _SingleMemUnit_CIterator& rhs) { return current == rhs.current; }
			int  operator-(const _SingleMemUnit_CIterator& rhs) { return this->current - rhs.current; }
		private:
			T* current;
		};
		template<class T> class GSTL_API _SingleMemUnit_RIterator : public iterator<random_access_iterator_tag, T>
		{
		public:
			_SingleMemUnit_RIterator(T* val) : current(val) {}
			~_SingleMemUnit_RIterator() {}
			void operator=(const _SingleMemUnit_RIterator& _ritera) { current = _ritera.current; } //�������캯��

			_SingleMemUnit_RIterator& operator++() { --current; return *this; }               //ǰ��++
			_SingleMemUnit_RIterator& operator--() { ++current; return *this; }               //ǰ��--
			_SingleMemUnit_RIterator& operator+=(int idx) { current -= idx; return *this; }
			_SingleMemUnit_RIterator& operator-=(int idx) { current += idx; return *this; }
			T& operator*() { return *current; }                                   //������
			T* operator->() { return current; }                                   //ָ�����

			_SingleMemUnit_RIterator operator++(int) { T* temp = current; current--; return _SingleMemUnit_RIterator(temp); }  //����++(�����ذ汾)
			_SingleMemUnit_RIterator operator--(int) { T* temp = current; current++; return _SingleMemUnit_RIterator(temp); }  //����--(�����ذ汾)
			_SingleMemUnit_RIterator operator+(int idx) { return _SingleMemUnit_RIterator(current - idx); }
			_SingleMemUnit_RIterator operator-(int idx) { return _SingleMemUnit_RIterator(current + idx); }

			bool operator!=(const _SingleMemUnit_RIterator& rhs) { return current != rhs.current; }
			bool operator==(const _SingleMemUnit_RIterator& rhs) { return current == rhs.current; }
			int  operator-(const _SingleMemUnit_RIterator& rhs) { return this->current - rhs.current; }
		protected:
			T* current;
		};
		template<class T> class GSTL_API _SingleMemUnit_CRIterator : public iterator<random_access_iterator_tag, T>
		{
		public:
			_SingleMemUnit_CRIterator(T* val) : current(val) {}
			~_SingleMemUnit_CRIterator() {}
			void operator=(const _SingleMemUnit_CRIterator& _ritera) { current = _ritera.current; } //�������캯��

			_SingleMemUnit_CRIterator& operator++() { --current; return *this; }               //ǰ��++
			_SingleMemUnit_CRIterator& operator--() { ++current; return *this; }               //ǰ��--
			_SingleMemUnit_CRIterator& operator+=(int idx) { current -= idx; return *this; }
			_SingleMemUnit_CRIterator& operator-=(int idx) { current += idx; return *this; }
			const T& operator*() { return *current; }                                   //������
			T* operator->() { return current; }                                   //ָ�����
			_SingleMemUnit_CRIterator operator++(int) { T* temp = current; current--; return _SingleMemUnit_CRIterator(temp); }  //����++(�����ذ汾)
			_SingleMemUnit_CRIterator operator--(int) { T* temp = current; current++; return _SingleMemUnit_CRIterator(temp); }  //����--(�����ذ汾)
			_SingleMemUnit_CRIterator operator+(int idx) { return _SingleMemUnit_CRIterator(current - idx); }
			_SingleMemUnit_CRIterator operator-(int idx) { return _SingleMemUnit_CRIterator(current + idx); }

			bool operator!=(const _SingleMemUnit_CRIterator& rhs) { return current != rhs.current; }
			bool operator==(const _SingleMemUnit_CRIterator& rhs) { return current == rhs.current; }
			int  operator-(const _SingleMemUnit_CRIterator& rhs) { return this->current - rhs.current; }
		protected:
			T* current;
		};
	}
}
#endif // !GITERATOR_H


