#include"maze.h"
//读取文件中的字符
void GetMaze(DataType* Maze, DataType n)
{
	FILE* fp = fopen("map.txt", "r");//以只读方式打开文件
	assert(fp);//断言fp，若fp为NULL直接返回
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n;)
		{
			char _cnt = fgetc(fp);//获取文件中的单个字符
			if (_cnt == '0' || _cnt == '1')
			{
				Maze[i * n + j] = _cnt - '0';//读取每一个坐标对应的字符'1'或'0'
				j++;
			}
		}
	}
	fclose(fp);//记得关闭文件，防止内存泄漏
}
//打印迷宫地图
void PrintMap(DataType* Maze, size_t n)
{
	//遍历数组即可
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			cout << Maze[i*n + j] << "  ";
		}
		cout << endl;
	}
	cout << endl;
}
//是否为通路
bool IsCheckPath(DataType* Maze, size_t n, Pos _p)
{
	//条件
	//1.数组未出界
	//2.坐标点为1，即为通路
	if ((_p._row >= 0 && _p._row < n) &&
		(_p._col >= 0 && _p._col < n) &&
		(Maze[_p._row*n + _p._col] == 1))
	{
		return true;
	}
	else
		return false;
}
//遍历上下左右的字符(核心算法)
void GetMazePath(DataType* Maze, size_t n, Pos _p, stack<Pos>& _s)
{
	//边界检查
	assert(_p._col >= 0 && _p._col < n
		&& _p._row >= 0 && _p._row < n);
	Pos _cur = _p;//保存当前入口点
	Pos _next = _cur;
	Maze[_cur._row * n + _cur._col] = 2;//将入口点置为2，
	//表示走过此坐标点
	_s.push(_p);//将当前入口点压栈
	while (!_s.empty())//栈不为空时
	{
		//如果栈顶元素的横/纵坐标到达边界，证明有通路
		if (_s.top()._row == (n - 1) || _s.top()._col == (n - 1))
		{
			return;//直接跳出循环，表示成功
		}
		//上
		_next = _s.top();//获取当前栈顶元素
		_next._row -= 1;//返回上一行
		//符合通路条件
		if (IsCheckPath((DataType*)Maze, n, _next))
		{
			_s.push(_next);//将当前栈顶元素压栈
			Maze[_next._row * n + _next._col] = 2;//并置为2
			//system("cls");//清屏函数
			//PrintMap((DataType*)Maze, n);//打印，可以在调试阶
			//段实时看数组元素的变化
			continue;//返回到while，继续遍历
		}
		//下面三种与上的方法类似，可参考上的注释
		//右
		_next = _s.top();
		_next._col += 1;
		if (IsCheckPath((DataType*)Maze, n, _next))
		{
			_s.push(_next);
			Maze[_next._row*n + _next._col] = 2;
			//system("cls");
			//PrintMap((DataType*)Maze, n);
			continue;
		}
		//下
		_next = _s.top();
		_next._row += 1;
		if (IsCheckPath((DataType*)Maze, n, _next))
		{
			_s.push(_next);
			Maze[_next._row*n + _next._col] = 2;
			//system("cls");
			//PrintMap((DataType*)Maze, n);
			continue;
		}
		//左
		_next = _s.top();
		_next._col -= 1;
		if (IsCheckPath((DataType*)Maze, n, _next))
		{
			_s.push(_next);
			Maze[_next._row * n + _next._col] = 2;
			//system("cls");
			//PrintMap((DataType*)Maze, n);
			continue;
		}
		//没有通路，返回上一层
		Pos _etn = _s.top();//获取栈顶元素
		Maze[_etn._row*n + _etn._col] = 3;//置为3，表示走过，但未走通
		//system("cls");
		//PrintMap((DataType*)Maze, n);
		_s.pop();//出栈，即返回上一层的调用坐标
	}
}
