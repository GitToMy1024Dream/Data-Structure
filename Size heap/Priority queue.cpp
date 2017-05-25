//优先级队列(调用堆的方法即可)
template<class T,class Compare = Greate<T>>
class PriorityQueue
{
public:
	PriorityQueue()
	{}
	void Push(const T& data)
	{
		_hp.PushHeap(data);
	}
	void Pop()
	{
		_hp.PopHeap();
	}
	bool Empty()const
	{
		return _hp.Empty();
	}
	const T& Top()const
	{
		return _hp.Top();
	}
	size_t Size()
	{
		return _hp.Size();
	}
protected:
	Myheap<T, Greate<T>> _hp;
};