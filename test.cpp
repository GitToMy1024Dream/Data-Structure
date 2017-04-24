#include "maze.h"
void FunTest()
{
	//const DataType n = 10;
	DataType Maze[n][n];
	GetMaze((DataType*)Maze, n);
	PrintMap((DataType*)Maze, n);
	Pos _pos(1,0);
	stack<Pos> _s;
	GetMazePath((DataType*)Maze, n, _pos, _s);
	PrintMap((DataType*)Maze, n);
	if (_s.empty())
	{
		cout << "Error:迷宫没有出口!" << endl;
		cout << endl;
	}
	else
	{
		cout << "Success:迷宫有出口!" << endl;
		cout << endl;
	}
}
int main()
{
	FunTest();
	system("pause");
	return 0;
}
