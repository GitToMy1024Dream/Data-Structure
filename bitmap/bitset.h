#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <assert.h>
using namespace std;
class BitSet
{
public:
	BitSet(size_t bitNum)
	{
		_bitset.resize((bitNum >> 5) + 1);
	}
	BitSet(string bit)
	{
		for (size_t idx = 0; idx < bit.size(); ++idx)
		{
			if (bit[idx] != '0' || bit[idx] != '1')
				return;
		}
		_bitset.resize((bit.size() >> 5) + 1);
		for (size_t idx = 0; idx < bit.size(); ++idx)
		{
			if (bit[idx] == '1')
				Set(idx);
		}
	}
	//����λ״̬Ϊ1
	void Set(size_t whichBit)
	{
		size_t pos = whichBit >> 5;
		assert(pos < _bitset.size());
		size_t index = whichBit % 32;
		_bitset[pos] |= (1 << index);
	}
	//����λ״̬Ϊ0
	void ReSet(size_t whichBit)
	{
		size_t pos = whichBit >> 5;
		size_t index = whichBit % 32;
		_bitset[pos] &= (~(1 << index));
	}
	//����λ״̬
	bool Test(size_t whichBit)
	{
		size_t pos = whichBit >> 5;
		size_t index = whichBit % 32;
		return _bitset[pos] & (1 << index);
	}
	//��Чλ�õĸ���
	size_t Count()const
	{
		char OneOfByte[] = "\0\1\1\2\1\2\2\3\1\2\2\3\2\3\3\4";
		size_t count = 0;
		for (size_t idx = 0; idx < _bitset.size(); ++idx)
		{
			int i = 0;
			size_t value = _bitset[idx];
			while (i < sizeof(_bitset[0]))
			{
				char c = value;
				count += OneOfByte[c & 0x0f];
				c >>= 4;
				count += OneOfByte[c & 0x0f];
				value >>= 8;
				i++;
			}
		}
		return count;
	}
private:
	vector<size_t> _bitset;
};