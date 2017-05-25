#pragma once
#include <iostream>
#include <vector>
#include <assert.h>
#define DataType int
using namespace std;
template<class T>
class Greate//���
{
public:
	bool operator()(const T& left, const T& right)//�º���������()����
	{
		return left > right;
	}
};
template<class T>
class Less//С��
{
public:
	bool operator()(const T& left, const T& right)//�º���������()С��
	{
		return left < right;
	}
};
template<class T,class Compare = Greater<T>>//�ڶ���ģ�����Ĭ��Ϊ���
class Myheap
{
public:
	//�ն�
	Myheap()
	{}
	Myheap(const T* arr, DataType size)
	{
		assert(arr);
		_heap.resize(size);//���ٿռ�(��vector��pushback��)
		for (size_t idx = 0; idx < size; ++idx)
		{
			_heap[idx] = arr[idx];
		}
		//size-1Ϊ���һ���ڵ���±꣬(size-1-1)/2 = ���ڵ�
		size_t Root = (size - 2) >> 1;
		for (DataType idx = Root; idx >= 0; idx--)
		{
			AdjustDown(idx);
		}
	}
	//�п�
	bool Empty()const
	{
		return _heap.empty();
	}
	//�ѵĴ�С
	size_t Size()const
	{
		return _heap.size();
	}
	//�Ѷ�Ԫ��
	T& Top()
	{
		assert(Size() > 0);
		return _heap[0];
	}
	const T& Top()const
	{
		assert(Size() > 0);
		return _heap[0];
	}
	void PushHeap(const T& elem)//����в���Ԫ��
	{
		//�Ƚ��½ڵ����ĩβ
		_heap.push_back(elem);
		//�ڽ����һ��Ԫ�����ϵ���
		AdjustUp(_heap.size() - 1);
	}
	void PopHeap()//�Ӷ���ȡ���Ѷ���Ԫ��
	{
		assert(!Empty());//�Ѳ�Ϊ��
		//�Ƚ����Ѷ��ڵ����β�ڵ�
		std::swap(_heap[0], _heap[_heap.size() - 1]);
		//ɾ�����һ���ڵ�
		_heap.pop_back();
		//�ӶѶ����µ���,���ڶ���ڵ�ʱ�ŵ���
		if (_heap.size() > 1)
		{
			AdjustDown(0);
		}
	}
     //���������һ����Ҷ�ӽ��
     //�������ǰ���ĺ��ӽ�����Ӵ����Һ��ӣ�����childָ������ӽ�㣨�Һ��Ӵ��ڣ�
     //�������ǰ�����С�ں��ӽ�㣬���������ڵ�ָ���ӣ�����ָ������
	void AdjustDown(DataType _root)//����
	{
		DataType Parent = _root;//��ʱ�����_rootΪ������һ����Ҷ�ӽ��
		DataType Child = Parent * 2 + 1;//���ӵ��±���ڸ��ڵ�*2+1
		Compare _Compare;//�º������ڱȽ����ȼ�
		//���Ӵ���
		while (Child < _heap.size())
		{
			//�Һ��Ӵ������Һ��ӵ�ֵ��������
			if (Child + 1 < _heap.size() && _Compare(_heap[Child+1],_heap[Child]))
			{
				Child = Child + 1;//��Child��㱣���ֵ
			}
			//���ӽ������ȼ����ڸ��ڵ�(Child��ֵ����Parent��ֵ)
			if (_Compare(_heap[Child], _heap[Parent]))
			{
				std::swap(_heap[Child], _heap[Parent]);//�������ڵ��ֵ
				//����
				Parent = Child;//�ø��ڵ�ָ���ӽڵ�
				Child = Parent * 2 + 1;//���ӽڵ�ָ�����ӽڵ�
			}
			//���ӽ������ȼ�С�ڸ��ڵ�(Child��ֵС��Parent��ֵ)������Ҫ����
			else
				break;
		}
	}
        //�ٴ���β�ڵ�
        //��ֻҪ��ǰ�ڵ�δ�����ڵ㣬��һֱ����
        //�ۺ��ӽڵ�����ȼ����ڸ��ڵ�����ȼ�������������ָ���ף�����ָ��үү
//ע�⣺�ڴ˲��ÿ�����������˭��˭С���ϵ���������ӽ��ȸ����������϶����ֵܽ���
	void AdjustUp(DataType Child)//����
	{
		//��ʱ�����ChildΪ���һ���ڵ������
		DataType Parent = (Child - 1) >> 1;
		Compare _Compare;//�º������ڱȽ����ȼ�
		//���˵Ĺ��̣�ֻҪû�����ڵ��һֱ����
		while (Child > 0 )
		{
			//���ӽڵ�����ȼ����ڸ��ڵ�����ȼ�
			if (_Compare(_heap[Child], _heap[Parent]))
			{
				std::swap(_heap[Child], _heap[Parent]);//�����ڵ��ֵ
				//����
				Child = Parent;//���ӽڵ�ָ�򸸽ڵ�
				Parent = (Child - 1) >> 1;//���ڵ�ָ��үү�ڵ�
			}
			//���ӽڵ�����ȼ�С�ڸ��ڵ�����ȼ�������Ҫ����
			else
				break;
		}
	}
private:
	std::vector<T> _heap;
};