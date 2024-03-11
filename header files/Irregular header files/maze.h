#ifndef MAZE_H
#define MAZE_H
#include<stdlib.h>
#include<iostream>
using namespace std;
class Maze
{
	char **maze;
	int row,col; //��������������x��y���������������꣬��ô�ڶ�ά������Ӧ��д��a[y][x]���������൱���У��������൱����
	int inx,iny,outx,outy; //��ںͳ���
	void AllPath(int x,int y); //����ڵ���������·����˽�з���
public:
	explicit Maze(char **m,int row,int col,int inx,int iny,int outx,int outy);
	~Maze();
	void AllPath(){AllPath(inx,iny);} //����ڵ���������·���Ĺ��з���
	void PrintMaze(); //���һ��·��
};
Maze::Maze(char **m,int row,int col,int inx,int iny,int outx,int outy)
{
	this->row=row,this->col=col;
	this->inx=inx,this->iny=iny;
	this->outx=outx,this->outy=outy;
	maze=new char*[row];
	for(int i=0;i<row;++i)
	{
		maze[i]=new char[col];
	}
	for(int i=0;i<row;++i)
	{
		for(int j=0;j<col;++j)
		{
			maze[i][j]=m[i][j];
		}
	}
}
Maze::~Maze()
{
	for(int i=0;i<row;++i)
	{
		delete []maze[i];
	}
	delete []maze;
}
void Maze::PrintMaze()
{ //���һ��·��
	static int counter=0;
	++counter;
	cout<<"Path "<<counter<<endl;
	for(int i=0;i<row;++i)
	{
		for(int j=0;j<col;++j)
		{
			cout<<maze[i][j]<<' ';
		}
		cout<<endl;
	}
}
void Maze::AllPath(int x,int y)
{ //����ڵ���������·����˽�з���
	static int d[4][2]={{1,0},{0,1},{-1,0},{0,-1}}; //��ʾ�����ƶ���������ݣ���ʾ���ҡ����¡���������
	maze[y][x]='*';
	if(y==outy&&x==outx)
	{
		PrintMaze();
		return;
	}
	for(int i=0;i<4;++i)
	{
		if(maze[y+d[i][1]][x+d[i][0]]=='0')
		{ //ע�⣬x��y���������������꣬��ô�ڶ�ά������Ӧ��д��a[y][x]���������൱���У��������൱����
			AllPath(x+d[i][0],y+d[i][1]);
			maze[y+d[i][1]][x+d[i][0]]='0';
		}
	}
}
#endif