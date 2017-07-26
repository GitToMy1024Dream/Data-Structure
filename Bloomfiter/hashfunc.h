#pragma once
#include<iostream>
#include<cstdlib>
using namespace std;

template <typename K>
struct _Funcpos1
{
	size_t BKDRHash(const char *str)
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = hash * 131 + ch;     							       
		}
		return hash;
	}

	size_t operator()(const string& key)
	{
		return BKDRHash(key.c_str());
	}
};
template<typename K>
struct _Funcpos2
{
	size_t SDBMHash(const char *str)
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = 65599 * hash + ch;
		}
		return hash;
	}
	size_t operator()(const string& key)
	{
		return SDBMHash(key.c_str());
	}
};
template<typename K>
struct _Funcpos3
{
	size_t RSHash(const char *str)
	{
		register size_t hash = 0;
		size_t magic = 63689;
		while (size_t ch = (size_t)*str++)
		{
			hash = hash * magic + ch;
			magic *= 378551;
		}
		return hash;
	}
	size_t operator()(const string& key)
	{
		return RSHash(key.c_str());
	}
};
template<typename K>
struct _Funcpos4
{
	size_t RSHash(const char *str)
	{
		register size_t hash = 0;
		size_t ch;
		for (long i = 0; ch = (size_t)*str++; i++)
		{
			if ((i & 1) == 0)
			{
				hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
			}
			else
			{
				hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
			}
		}
		return hash;
	}
	size_t operator()(const string& key)
	{
		return RSHash(key.c_str());
	}
};

template<typename K>
struct _Funcpos5
{
	size_t RSHash(const char *str)
	{
		if (!*str)       
			return 0;
		register size_t hash = 1315423911;
		while (size_t ch = (size_t)*str++)
		{
			hash ^= ((hash << 5) + ch + (hash >> 2));
		}
		return hash;
	}
	size_t operator()(const string& key)
	{
		return RSHash(key.c_str());
	}
};