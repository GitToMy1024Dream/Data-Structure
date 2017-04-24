#pragma once
#include <iostream>
#include <assert.h>
#define  DataType int 
#include <stack>
#pragma warning (disable:4996)
using namespace std;
//迷宫的入口点
struct Pos
{
	DataType _row;
	DataType _col;
	Pos(DataType row,DataType col)
		:_row(row)
		,_col(col)
	{}
};
//读取文件中的字符
void GetMaze(DataType* Maze, DataType n);
//打印迷宫地图
void PrintMap(DataType* Maze, size_t n);
//是否为通路
bool IsCheckPath(DataType* Maze, size_t n, Pos _p);
//遍历上下左右的字符
void GetMazePath(DataType* Maze, size_t n, Pos _p, stack<Pos>& _s);

