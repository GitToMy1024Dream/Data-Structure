#include "hashfunc.h"
#include "bitset.h"
template<class K,class HashFun1 = _Funcpos1<K>,
				 class HashFun2 = _Funcpos2<K>,
                 class HashFun3 = _Funcpos3<K>,
				 class HashFun4 = _Funcpos4<K>,
				 class HashFun5 = _Funcpos5<K>>
class BloomFilter
{
public:
	BloomFilter(size_t size = 10)
		: _capacity(_GetNextPrime(size))
		,_table(_capacity)
	{}
	void Set(const K& key)
	{
		size_t hashAddr = HashFun1()(key) % _capacity;
		_table.Set(hashAddr);
		hashAddr = HashFun2()(key) % _capacity;
		_table.Set(hashAddr);
		hashAddr = HashFun3()(key) % _capacity;
		_table.Set(hashAddr);
		hashAddr = HashFun4()(key) % _capacity;
		_table.Set(hashAddr);
		hashAddr = HashFun5()(key) % _capacity;
		_table.Set(hashAddr);
	}
	bool IsIn(const K& key)
	{
		size_t hashAddr = HashFun1()(key) % _capacity;
		if (!_table.Test(hashAddr))
			return false;
		hashAddr = HashFun2()(key) % _capacity;
		if (!_table.Test(hashAddr))
			return false;
		hashAddr = HashFun3()(key) % _capacity;
		if (!_table.Test(hashAddr))
			return false;
		hashAddr = HashFun4()(key) % _capacity;
		if (!_table.Test(hashAddr))
			return false;
		hashAddr = HashFun5()(key) % _capacity;
		if (!_table.Test(hashAddr))
			return false;
		return true;
	}
	size_t _GetNextPrime(size_t size)
	{
		const int _PrimeSize = 28;
		static const unsigned long _PrimeList[_PrimeSize] =
		{
			53ul, 97ul, 193ul, 389ul, 769ul,
			1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
			49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
			1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
			50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
			1610612741ul, 3221225473ul, 4294967291ul
		};
		for (size_t i = 0; i < _PrimeSize; ++i)
		{
			if (_PrimeList[i] > size)
			{
				return _PrimeList[i];
			}
		}
		return _PrimeList[_PrimeSize - 1];
	}
private:
	BitSet _table;
	size_t _capacity;
};