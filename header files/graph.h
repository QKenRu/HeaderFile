#ifndef GRAPH_H
#define GRAPH_H
#include"../../AAAPublicHeaderFile/list.h"
#include"../../AAAPublicHeaderFile/vector.h"
#include"../../AAAPublicHeaderFile/queue.h"
#include"../../AAAPublicHeaderFile/heap.h"
#include<float.h>
#include<fstream>
#include<optional>
#include<iostream>
using namespace std;
bool operator==(const optional<double> &a,const optional<double> &b)
{
	if(!a.has_value() && !b.has_value())
	{ //��ʽ���߶�û��ֵʱ��Ĭ���������
		return true;
	}
	else if(a.has_value() && b.has_value())
	{
		return a.value()==b.value();
	}
	else
	{
		return false;
	}
}
bool operator!=(const optional<double> &a,const optional<double> &b)
{
	if(!a.has_value() && !b.has_value())
	{ //��ʽ���߶�û��ֵʱ��Ĭ���������
		return false;
	}
	else if(a.has_value() && b.has_value())
	{
		return a.value()!=b.value();
	}
	else
	{ //һ����ֵһ����ֵĬ�ϲ����
		return true;
	}
}
bool operator>(const optional<double> &a,const optional<double> &b)
{
	if(!a.has_value() && !b.has_value())
	{ //��ʽ���߶�û��ֵʱ��Ĭ���������
		return false;
	}
	else if(a.has_value() && b.has_value())
	{ //��ʽ������ֵ
		return a.value() > b.value();
	}
	else if(a.has_value() && !b.has_value())
	{ //��ʽ��ֵ��ʽ��ֵ����ֵ��Ϊ����󣬼���ʽ��
		return false;
	}
	else if(!a.has_value() && b.has_value())
	{ //��ʽ��ֵ��ʽ��ֵ����ʽ��
		return true;
	}
	else
	{
		throw "Operator '>' occured an error.";
	}
}
bool operator>=(const optional<double> &a,const optional<double> &b)
{
	if(!a.has_value() && !b.has_value())
	{ //��ʽ���߶�û��ֵʱ��Ĭ���������
		return false;
	}
	else if(a.has_value() && b.has_value())
	{ //��ʽ������ֵ
		return a.value() >= b.value();
	}
	else if(a.has_value() && !b.has_value())
	{ //��ʽ��ֵ��ʽ��ֵ����ֵ��Ϊ����󣬼���ʽ��
		return false;
	}
	else if(!a.has_value() && b.has_value())
	{ //��ʽ��ֵ��ʽ��ֵ����ʽ��
		return true;
	}
	else
	{
		throw "Operator '>=' occured an error.";
	}
}
bool operator<(const optional<double> &a,const optional<double> &b)
{
	if(!a.has_value() && !b.has_value())
	{ //��ʽ���߶�û��ֵʱ��Ĭ���������
		return false;
	}
	else if(a.has_value() && b.has_value())
	{ //��ʽ������ֵ
		return a.value() < b.value();
	}
	else if(a.has_value() && !b.has_value())
	{ //��ʽ��ֵ��ʽ��ֵ����ֵ��Ϊ����󣬼���ʽС
		return true;
	}
	else if(!a.has_value() && b.has_value())
	{ //��ʽ��ֵ��ʽ��ֵ����ʽ��
		return false;
	}
	else
	{
		throw "Operator '<' occured an error.";
	}
}
bool operator<=(const optional<double> &a,const optional<double> &b)
{
	if(!a.has_value() && !b.has_value())
	{ //��ʽ���߶�û��ֵʱ��Ĭ���������
		return false;
	}
	else if(a.has_value() && b.has_value())
	{ //��ʽ������ֵ
		return a.value() <= b.value();
	}
	else if(a.has_value() && !b.has_value())
	{ //��ʽ��ֵ��ʽ��ֵ����ֵ��Ϊ����󣬼���ʽС
		return true;
	}
	else if(!a.has_value() && b.has_value())
	{ //��ʽ��ֵ��ʽ��ֵ����ʽ��
		return false;
	}
	else
	{
		throw "Operator '<=' occured an error.";
	}
}
optional<double> operator+(const optional<double> &a,const optional<double> &b)
{
	if(!a.has_value() || !b.has_value())
	{ //����һ����ֵ����������ֵ
		return nullopt;
	}
	else if(a.has_value() && b.has_value())
	{ //������ֵ����������
		return a.value()+b.value();
	}
	else
	{
		throw "Operator '+' occured an erro.";
	}
}
struct PathData
{ //������С�������㷨��һ�ֽ��ṹ
	int start,dest; //�ߵ������յ���±�
	optional<double> cost; //Ȩ
	operator optional<double>()const
	{ //��Աת�����������ڱȽ�����
		if(cost.has_value())
		{
			return cost.value();
		}
		else
		{
			return nullopt;
		}
	}
};

template<class T>
class Graph
{
	struct Edge
	{ //�߽�����ݽṹ
		int dest; //�ߵ��յ��±�
		double cost; //�ߵ�Ȩ
		operator int() {return dest;} //��Աת��
	};
	Vector<T> vt; //���������洢����
	List<Edge> *el; //ָ�������������ָ��
	optional<double> GetCost(int s,int e)const; //���ݶ����±��ȡ�ߵ�Ȩ
	void DFS(List<T> &L,int id,bool *visited)const; //ͼ��������ȱ�����˽�з�����
public:
	explicit Graph(int max=100):vt(max){el=new List<Edge>[max];} //Ĭ�Ϲ��캯��
	virtual ~Graph(){delete []el;} //��������
	
	int SizeV()const{return vt.Size();} //ȡ������
	int SizeE()const; //ȡ����
	int InDegree(int id)const; //��ĳ��������
	int OutDegree(int id)const {return el[id].Size();} //��ĳ����ĳ���

	int FindV(const T &item)const; //ȡ�����±�
	void GetVertexItem(T &x,int id)const; //ȡ�±�Ϊid�Ķ��㣬�洢��Ԫ��x��
	optional<double> GetCost(const T &v1,const T &v2)const; //���ݶ���Ԫ�ض�ȡ�ߵ�Ȩ
	
	void InsertV(const T &item){vt.PushBack(item);} //���붥��
	bool InsertE(const T &v1,const T &v2,double w); //�����

	void BFS(List<T> &L,const T &v)const; //ͼ�Ĺ�����ȱ���
	void DFS(List<T> &L,const T &v)const; //ͼ��������ȱ��������з�����
	
	bool Prim(const T &v,Vector<PathData> &vt)const; //��С����������Prim�㷨
	bool Kruskal(Vector<PathData> &vt)const; //��С����������Kruskal�㷨

	bool Dijkstra(const T &v,Vector<optional<double>> &dist,Vector<int> &prefix)const; //���·�����⡪��Dijkstra�㷨
	bool BellmanFord(const T &src,Vector<optional<double>> &dist,Vector<int> &prefix); //���·�����⡪��Bellman-Ford�㷨

	bool TopologicalSort(Vector<int> &tp)const; //���������㷨

	void CriticalPath(Vector<double> &ve,Vector<double> &vl)const; //�ؼ�·���㷨

	void ReadGraph(const char *filename); //�Ӵ����ļ���ȡͼ������
	void WriteGraph(const char *filename); //�Ӵ����ļ�д��ͼ������

	void Output()const; //�������ʾ��

};

template<class T>
int Graph<T>::SizeE()const
{ //ȡ����
	int n=vt.Size(); //ȡ�������
	int counter=0; //�ۼ���
	for(int i=0;i<n;++i)
	{
		counter+=el[i].Size(); //�ۼ�ÿ����������
	}
	return counter;
}

template<class T>
int Graph<T>::InDegree(int id)const
{ //��ĳ��������
	int counter=0; //������
	int n=SizeV(); //��������
	for(int i=0;i<n;++i)
	{
		typename List<Edge>::const_iterator first=el[i].Begin();
		typename List<Edge>::const_iterator last=el[i].End();
		for(;first!=last;++first)
		{
			if((*first).dest==id)
			{
				++counter;
				break;
			}
		}
	}
	return counter;
}

template<class T>
int Graph<T>::FindV(const T &item)const
{ //ȡ������±�
	int n=SizeV();
	for(int i=0;i<n;++i)
	{
		if(vt[i]==item)
		{
			return i;
		}
	}
	cout<<"The vertex for element "<<item<<" does not exist."<<endl;
	return -1;
}

template<class T>
void Graph<T>::GetVertexItem(T &x,int id)const
{ //ȡ�±�Ϊid�Ķ��㣬�洢��x��
	if(id<0||id>=SizeV())
	{
		cout<<"The vertex of id "<<id<<" does not exist."<<endl;
		return;
	}
	x=vt[id];
}

template<class T>
optional<double> Graph<T>::GetCost(const T &v1,const T &v2)const
{ //���ݶ���Ԫ�ض�ȡ�ߵ�Ȩ�����з�����
	int s=FindV(v1);
	int e=FindV(v2);
	return GetCost(s,e); //���ݶ����±��ȡ�ߵ�Ȩ��˽�з�����
}
template<class T>
optional<double> Graph<T>::GetCost(int s,int e)const
{ //���ݶ����±��ȡ�ߵ�Ȩ��˽�з�����
		typename List<Edge>::const_iterator first=el[s].Begin();
		typename List<Edge>::const_iterator last=el[s].End();
		for(;first!=last;++first)
		{
			if((*first).dest==e)
			{
				return (*first).cost;
			}
		}
		return nullopt;
}

template<class T>
bool Graph<T>::InsertE(const T &v1,const T &v2,double w)
{ //�����
	int s=FindV(v1);
	int e=FindV(v2); //ȷ���ߵ�ʼ����յ���±�
	if(s==-1 || e==-1 || s==e)
	{
		cout<<"Vertex "<<v1<<" or "<<v2<<" doesn't exist, or they are the same vertex."<<endl;
		return 0;
	}
	Edge ed; //�ߵĽṹ����
	ed.dest=e;
	ed.cost=w; //���ߵĽṹ������
	el[s].PushBack(ed); //β�嵽������
	return 1;
}

template<class T>
void Graph<T>::ReadGraph(const char *filename)
{ //�Ӵ����ļ���ȡͼ������
	fstream infile;
	infile.open(filename,ios::in);
	if(!infile)
	{
		cout<<"Can't open "<<filename<<endl;
		return;
	}
	char str[40];
	int n;
	T s,e;
	double w;
	infile>>str>>n;
	for(int i=0;i<n;++i)
	{
		infile>>s;
		InsertV(s);
	}
	infile>>str>>n;
	for(int i=0;i<n;++i)
	{
		infile>>s>>e>>w;
		InsertE(s,e,w);
	}
	infile.close();
}
template<class T>
void Graph<T>::WriteGraph(const char *filename)
{ //��ͼ����������������ļ�
	fstream outfile;
	outfile.open(filename,ios::out); //�򿪴����ļ�
	if(!outfile)
	{
		cout<<"Can't open "<<filename<<endl;
		return;
	}
	int n=SizeV();
	typename List<Edge>::const_iterator first,last;
	for(int i=0;i<n;++i)
	{
		outfile<<i<<'-'<<vt[i]<<':'; //��������±��Ԫ��
		first=el[i].Begin(), last=el[i].End();
		for(;first!=last;++first)
		{ //���������
			outfile<<'('<<(*first).dest<<' '<<(*first).cost<<')'<<' ';
		}
		outfile<<endl;
	}
	outfile.close();
}

template<class T>
void Graph<T>::Output()const
{ //��ͼ�������������ʾ��
	int n=SizeV();
	typename List<Edge>::const_iterator first,last;
	for(int i=0;i<n;++i)
	{
		cout<<i<<'-'<<vt[i]<<':'; //��������±��Ԫ��
		first=el[i].Begin(),last=el[i].End();
		for(;first!=last;++first)
		{
			cout<<'('<<(*first).dest<<' '<<(*first).cost<<')'<<' ';
		}
		cout<<endl;
	}
}

template<class T>
void Graph<T>::BFS(List<T> &L,const T &v)const
{ //ͼ�Ĺ�����ȱ���
	int id=FindV(v); //ȡ�����±�
	if(id==-1)
	{
		return; //FindV()���б�����ʾ���˴�����Ҫ����
	}
	int n=SizeV();
	bool *visited=new bool[n](); //��־���飬��ʼ��Ԫ��ֵΪ0����¼����Ƿ񱻷��ʹ�
	
	Queue<int>Q;
	Q.Push(id); //��ʼ��������
	visited[id]=1; //�������ʹ��ı�־
	typename List<Edge>::const_iterator first, last; //�����������	
	while(!Q.Empty()) //�����в�Ϊ�գ��Ӷ���ȡ��һ��������ʣ�Ȼ������ö���ı����������ڽӵ�δ�����ʣ��Ͳ�����У�ͬʱ�������ʹ��ı�־
	{
		id=Q.Pop(); //�Ӷ���ȡ�������±�
		L.PushBack(vt[id]); //�ѹ�����ȶ��д���������Ϊ��������
		first=el[id].Begin(),last=el[id].End(); //ָ���������ס�β���
		for(;first!=last;++first)
		{ //��������������δ�����ʵ��ڽӵ�
			if(visited[(*first).dest]==0) //���ڽӵ�δ������
			{
				Q.Push((*first).dest); //�ڽӵ��±������
				visited[(*first).dest]=1; //�������ʹ��ı�־
			}
		}
	}
	delete []visited;
}

template<class T>
void Graph<T>::DFS(List<T> &L,const T &v)const
{ //ͼ��������ȱ��������з�����
	int id=FindV(v);
	if(id==-1)
	{
		cout<<"Vertex "<<v<<" doesn't exist.";
		return;
	}
	int n=SizeV();
	bool *visited=new bool[n](); //��־����
	DFS(L,id,visited);
}
template<class T>
void Graph<T>::DFS(List<T> &L,int id,bool *visited)const
{ //ͼ��������ȱ�����˽�з�����
	L.PushBack(vt[id]); //����ʼ��
	visited[id]=1; //�����ʱ��
	typename List<Edge>::const_iterator first,last; //�����������
	first=el[id].Begin(),last=el[id].End(); //ָ���������ס�β���
	for(;first!=last;++first)
	{ //������δ���ʹ����ڽӵ�Ϊʼ�㣬����������ȱ���
		if(visited[(*first).dest]==0)
		{
			DFS(L,(*first).dest,visited);
		}
	}
}

template<class T>
void OutputList(const List<T> &L)
{ //������ֱ�����ʽ�洢������L�Ľ��
	typename List<T>::const_iterator first=L.Begin(),last=L.End();
	for(;first!=last;++first)
	{
		cout<<*first<<'\t';
	}
	cout<<endl;
}

template<class T>
bool Graph<T>::Prim(const T &v,Vector<PathData> &vt)const
{ //��С�������㷨����Prim�㷨
    //��ʼ������������ѡ���������ඥ����ɺ�ѡ�㼯���Ѻ�ѡ�߼�����PathData�ṹ����
	int nv=SizeV(); //������
	PathData *E=new PathData[nv-1]; //���ݱ����������飬��С�������ı������ڶ�������1
	int s=FindV(v); //ȡʼ������
	if(s==-1)
	{
		cout<<"Vertex "<<v<<" doesn't exist."<<endl;
		return 0;
	}
	PathData item;
	optional<double> cost;
	int id=0,n=0; //����
	for(int e=0;e<nv;++e)
	{ //s��e�ֱ��Ǳߵ�ʼ����յ�����
		if(e!=s)
		{
			item.start=s;
			item.dest=e;
			item.cost=GetCost(s,e);
			E[id++]=item;
			++n;
		}
	} //�ں�ѡ�߼���ѡ��һ��Ȩ��С�ļ��뵽��ѡ������ʵ����һ�����ķ����ǽ���ѡ�߼�����ΪС���ѣ�С������Ԫ�ؾ���Ȩֵ��С�ĺ�ѡ��
	BuildHeap(E,n); //�Ժ�ѡ�߼���С����
	//���º�ѡ�߼�������ѡ�������¶�����Ϊʼ�㡢��ѡ�㼯�Ķ���Ϊ�յ������ɵı���ͬһ�յ��ԭ��ѡ�߱Ƚϣ��ñ�ȨС���滻��Ȩ���
	int i,j,counter=0; //����������¼��С�������ı���
	for(i=0;i<n;++i)
	{ //���º�ѡ�߼�
		if(E[0].cost.has_value())
		{ //����ѡ�߼�����С�ߴ��ڣ���������1
			++counter;
		}
		s=E[0].dest; //ȡ�µ���ѡ������
		for(j=1;j<n-i;++j)
		{ //���º�ѡ�߼�
			cost=GetCost(s,E[j].dest);
			if(E[j].cost>cost)
			{
				E[j].cost=cost;
				E[j].start=s;
			}
		}
		item=E[0]; //��ѡ�߼�����βԪ�ؽ�����item��������������ʱ����
		E[0]=E[n-1-i]; //id-1-i��ɾ�����βԪ���±�
		E[n-1-i]=item;
		BuildHeap(E,n-1-i); //�ؽ�С����
	}
	//�����ʱ����ֵ����ͼ�Ķ��������1��˵����������С����������������ֵΪ1������Ϊ0
	vt.Clear(); //��������������ڴ洢��С�������Ľ��
	if(counter==nv-1)
	{
		for(i=0;i<counter;++i)
		{
			vt.PushBack(E[i]);
		}
		delete []E;
		return 1;
	}
	delete []E;
	cout<<"Prim algorithm failed in generating minimal spanning tree."<<endl;
	return 0;
}
template<class T>
bool Graph<T>::Kruskal(Vector<PathData> &vt)const
{ //��С����������Kruskal�㷨
	//��n������ֱ����n��ֻ�е����������ͨ��������ʱ���鼯(����DS)��ÿ��Ԫ��ֵ��-1
	int nv=SizeV(); //��С�������Ķ������
	int *DS=new int[nv]; //���鼯
	int i,j;
	for(i=0;i<nv;++i)
	{ //��ʼ�����鼯
		DS[i]=-1;
	}
	//��ÿһ���ߵ���Ϣ����С����
	optional<double> cost;
	PathData item;
	Heap<PathData> H; //С����
	for(i=0;i<nv;++i)
	{
		for(j=i+1;j<nv;++j)
		{
			cost=GetCost(i,j);
			if(cost.has_value())
			{
				item.start=i; //����С�Ķ����ʾʼ��
				item.dest=j; //������Ķ����ʾ�յ�
				item.cost=cost.value();
				H.Insert(item); //����С����
			}
		}
	}
	//�Ӷ�����ȡ��ɾ����һ���ߣ������ߵ�Ȩ��С����һ������С�ģ�����ʼ����յ����ڲ�ͬ����ͨ��������������������ͨ�����ĸ���ͬ����
	//�ͽ��������ӳ�һ����ͨ��������������������С�ģ���Ȼ��������ߵ���Ϣ������������Ϊ��С�������ı�
	int id=0,counter=0;
	PathData *E=new PathData[nv-1]; //��С�������ı���Ϊ��������1
	while(!H.Empty())
	{
		H.Remove(item); //ɾȡ����ȡ��ɾ�����ѵ���Ԫ��
		i=item.start;
		while(DS[i]>=0) //���ұߵ�ʼ������ͨ�����еĸ�
		{ //DS[i]��С��0����ʾ���Ϊi�Ķ�����һ����ͨ�����ĸ�������ֵ�������ͨ�����Ķ��������������0��DS[i]=j��ʾ���Ϊi,j(j<i)�Ķ�����һ����ͨ������
			i=DS[i];
		}
		j=item.dest;
		while(DS[j]>=0) //���ұߵ��յ�����ͨ�����еĸ�
		{
			j=DS[j];
		}
		if(i!=j)
		{ //���ߵ�ʼ�����յ����ڲ�ͬ����ͨ��������ϲ�
			if(i<j)
			{
				DS[i]+=DS[j]; //��������ͨ�����Ķ�������ӵ����Ϻ����ͨ�����Ķ������DS[i]��
				DS[j]=i; //�޸ı��̲�����ͨ�����ĸ�
			}
			else
			{
				DS[j]+=DS[i];
				DS[i]=j;
			}
			E[id++]=item; //������С�������ı�
			++counter;
		}
	}
	delete []DS;
	vt.Clear(); //��������������ڴ洢��С�������Ľ��
	if(counter==nv-1)
	{
		for(i=0;i<counter;++i)
		{
			vt.PushBack(E[i]);
		}
		delete []E;
		return 1;
	}
	delete []E;
	cout<<"Kruskal algorithm failed in generating minimal spanning tree."<<endl;
	return 0;
}
void MSTOutput(const Vector<PathData> &vt)
{ //��С�������������
	int n=vt.Size();
	for(int i=n-1;i>=0;--i)
	{
		std::cout<<'('<<vt[i].start<<"-"<<vt[i].dest<<','<<vt[i].cost.value()<<')'<<std::endl;
	}
	return;
}

template<class T>
bool Graph<T>::Dijkstra(const T &v,Vector<optional<double>> &dist,Vector<int> &prefix)const
{
	int nv=SizeV(); //������
	PathData *E=new PathData[nv-1]; //��ѡ·�����ı���Ϊnv-1
	int i,j;
	dist.Clear(); //�����������
	prefix.Clear();
	for(i=0;i<nv-1;++i)
	{ //���������ʼ��Ϊ0��Ԫ�ظ���size����Ϊnv
		dist.PushBack(0);
		prefix.PushBack(0);
	}
	int s=FindV(v); //Ѱ��ʼ����±�
	if(s==-1)
	{
		return 0;
	}
	dist[s]=0; //��Դ�㵽����·������Ϊ0
	prefix[s]=-1; //Դ����ǰ��
	PathData item;
	optional<double> cost;
	int id=0,n=0; //n���ڼ�¼��ѡ·����
	for(int e=0;e<nv;++e)
	{ //s��e�ֱ��Ǻ�ѡ·����ʼ����յ�����
		if(e!=s)
		{
			item.start=s;
			item.dest=e;
			item.cost=GetCost(s,e);
			cost=GetCost(s,e);
			E[id++]=item;
			++n;
			dist[e]=item.cost;
			prefix[e]=(cost.has_value() ? s : -1);
		}
	}
	BuildHeap(E,n); //�Ժ�ѡ·������С����
	int counter=0;
	optional<double> distBLMAX=nullopt;
	for(int i=0;i<n;++i)
	{
		if(E[0].cost<distBLMAX)
		{ //nullopt�ڱȽ�����������б�����Ϊ���distBL_MAXҲС��nullopt
			++counter;
		}
		s=E[0].dest;
		for(j=1;j<n-i;++j)
		{
			cost=GetCost(s,E[j].dest);
			if(E[j].cost>E[0].cost+cost)
			{
				E[j].cost=E[0].cost+cost;
				E[j].start=s;
				dist[E[j].dest]=E[j].cost;
				prefix[E[j].dest]=s;
			}
		}
		item=E[0];
		E[0]=E[n-1-i];
		E[n-1-i]=item;
		BuildHeap(E,n-1-i); //�ؽ�С����
	}
	delete []E;
	return counter==nv-1 ? 1 : 0;
}
template<class T>
bool Graph<T>::BellmanFord(const T &source,Vector<optional<double>> &dist,Vector<int> &prefix)
{
	int nv=SizeV();
	int ne=SizeE();
	int s,e,src;
	src=FindV(source); //Ѱ��ʼ���±�
	if(src==-1)
	{
		return 0;
	}
	PathData *item=new PathData[ne];
	Vector<optional<double>>backupDist;
	optional<double> cost;
	for(int i=0;i<nv-1;++i)
	{ //���������ʼ��Ϊ0��Ԫ�ظ���size����Ϊnv
		dist.PushBack(0);
		backupDist.PushBack(0);
		prefix.PushBack(0);
	}
	//��ʼ��������Դ��������ж������̾������ֵ dist[v] �� +��, dist[s] ��0;
	for(int i=0;i<nv;++i)
	{
		dist[i]=nullopt; //nullopt�ڱȽ������������Ϊ��󣬴���DBL_MAX
		backupDist[i]=nullopt;
	}
	dist[src]=0; //ʼ�㵽�Լ��ľ���Ϊ0
	backupDist[src]=0;
	prefix[src]=-1; //ʼ���ǰ׺Ϊ-1
	//������⣺�����Ա߼�E�е�ÿ���߽����ɳڲ�����ʹ�ö��㼯V�е�ÿ������v����̾������ֵ�𲽱ƽ�����̾��룻������nv-1�Σ�
	int k=0;
	for(int i=0;i<nv;++i)
	{ //��ʼ���߼�item
		for(int j=0;j<nv;++j)
		{
			if(GetCost(i,j)!=nullopt)
			{
				item[k].start=i;
				item[k].dest=j;
				item[k].cost=GetCost(i,j);
				if(i==src)
				{
					dist[j]=item[k].cost;
					prefix[j]=i;
				}
				++k;
			}
		}
	}
	for(int i=0;i<nv;++i)
	{ //���ݱ߼��������������������һ�ε�item����Ļ�����̾�������2���ڲ�ѭ��ֻ������һ�Σ������ڸ��µĹ����лᷢ����������������˵�ȸ�����2�ŵ㣬Ȼ��������2�ŵ������3�ŵ�������ľ��룬
	  //�����ͷ����ˡ���������3�ŵ㲻�ܱ�2�ŵ���£������Ͳ�������಻����x���ߵ�Ҫ����
		for(int j=0;j<nv;++j)
		{
			backupDist[j]=dist[j];
		}
		for(int j=0;j<ne;++j)
		{ //�߼�item�ͱ��ݱ߼�backItem�ı߶�����ֵ��
			s=item[j].start;
			e=item[j].dest;
			if(dist[e] > backupDist[s]+item[j].cost)
			{ //�ɳڲ���
				dist[e]=backupDist[s]+item[j].cost;
				prefix[e]=s;
			}
		}
	}
	//���鸺Ȩ��·���жϱ߼�E�е�ÿһ���ߵ������˵��Ƿ��������������δ�����Ķ��㣬���㷨����false�����������޽⣻�����㷨����true�����Ҵ�Դ��ɴ�Ķ���v����̾��뱣����dist[v]�С�
	bool hasNegativeLoop=false;
	for(int i=0;i<ne;++i)
	{
		s=item[i].start;
		e=item[i].dest;
		cost=item[i].cost;
		if(dist[s].has_value() && dist[s]+cost < dist[e])
		{
			hasNegativeLoop=true;
			break;
		}
	}
	if(hasNegativeLoop)
	{
		cout<<"Graph has negative edge loops."<<endl;
		return 0;
	}
	return 1;
}
template<class T>
void SPPOutput(const Graph<T> &G,const Vector<optional<double>> &dist,const Vector<int> &prefix)
{
	int n=G.SizeV();
	T v;
	int f;
	int *stack=new int[n];
	int size; //��¼ջԪ�ظ���
	for(int i=0;i<n;++i)
	{
		if(dist[i].has_value())
		{
			cout<<dist[i].value()<<':';
			size=0; //���ջ
			stack[size++]=i; //���յ�ѹջ
			f=prefix[i]; //ȡ����vi��·���ϵ�ǰһ������
			while(f!=-1)
			{
				stack[size++]=f;
				f=prefix[f]; //ȡǰ������
			}
			for(int j=size-1;j>=0;--j)
			{ //��ջ����ʼ�㿪ʼ���
				G.GetVertexItem(v,stack[j]);
				cout<<v;
				if(j>0)
				{ //�������·���յ�
					cout<<"->";
				}
			}
			cout<<endl;
		}
	}
	delete []stack;
}

template<class T>
bool Graph<T>::TopologicalSort(Vector<int> &tp)const
{ //���������㷨
//����һ�����������һ�����У���¼ÿһ���������ȣ������Ϊ0�Ķ���������
	int nv=SizeV(); //��������
	int *ID=new int[nv];
	int id;
	Queue<int> Q;
	for(id=0;id<nv;++id)
	{
		ID[id]=InDegree(id);
		if(ID[id]==0)
		{ //�����������Ϊ0
			Q.Push(id);
		}
	}
//�����в��գ���ȡ��һ��������Ϊ�������еĶ��㣬ͬʱ������counter��1��Ȼ���Ըö���Ϊʼ��ıߵ��յ����Ӽ�1������1�����Ϊ0���򽫸��յ������С��ظ��������ֱ������Ϊ��
	int i,j;
	tp.Clear(); //�����������
	typename List<Edge>::const_iterator first,last;
	while(!Q.Empty())
	{
		i=Q.Pop();
		tp.PushBack(i); //��¼�������ж�������
		first=el[i].Begin();
		last=el[i].End();
		for(;first!=last;++first)
		{ //ɨ�������˶���Ϊʼ��ı�����
			j=(*first).dest;
			--ID[j];
			if(ID[j]==0)
			{
				Q.Push(j);
			}
		}
	}
	delete []ID;
//���������counter��ֵ����ͼ�Ķ������������㷨�ɹ�������ʧ��
	int counter=tp.Size();
	return counter==nv?1:0;
}
template<class T>
void TopoOutput(const Graph<T> &g,const Vector<int> &tp)
{ //���������������
	int nv=tp.Size();
	T v;
	for(int i=0;i<nv;++i)
	{
		g.GetVertexItem(v,tp[i]);
		cout<<v<<' ';
	}
	cout<<endl;
}

template<class T>
void Graph<T>::CriticalPath(Vector<double> &ve,Vector<double> &vl)const
{
	int i,j,k;
	int nv=SizeV();
	Vector<int> tp;
	ve.Clear(); //�����������
	vl.Clear();
	for(int i=0;i<nv;++i)
	{ //��������ֵ0��Ԫ�ظ���size����Ϊnv
		ve.PushBack(0);
		vl.PushBack(0);
	}
	optional<double> temp;
	double min,max;
	if(TopologicalSort(tp))
	{ //ѡ��һ����������
//����������˳�򣬴�ǰ�������ÿ����������緢��ʱ�䡣������㷽������ve(0)=0��ʼ��ÿ���������緢��ʱ��������������Ϊ�յ������У�ʼ������緢��ʱ�����Ȩ��Ȩ������ֵ��
//��Ϊÿ������ߵ�ʼ����յ������������ж���ǰ�����еģ����Լ��㷽���ǵ��Ƶġ�
		ve[tp[0]]=0;
		for(k=1;k<nv;++k)
		{
			j=tp[k];
			max=DBL_MIN;
			for(i=0;i<nv;++i)
			{
				temp=GetCost(i,j);
				if(temp.has_value() && (ve[i]+temp.value())>max)
				{
					max=ve[i]+temp.value();
				}
			}
			ve[j]=max;
		}
//����������˳�򣬴Ӻ���ǰ����ÿ���������ٷ���ʱ�䡣������㷽������vl(nv-1)=ve(nv-1)��ʼ��ÿ��������ٷ���ʱ��������������Ϊʼ��ĳ����У�
//�յ����ٷ���ʱ���ȥȨ�����Сֵ����Ϊÿ������ߵ�ʼ����յ������������ж���ǰ�����еģ����Լ��㷽���ǵ��Ƶġ�
		vl[tp[nv-1]]=ve[tp[nv-1]];
		for(k=nv-2;k>=0;--k)
		{
			i=tp[k];
			min=DBL_MAX;
			for(j=0;j<nv;++j)
			{
				temp=GetCost(i,j);
				if(temp.has_value() && (vl[j]-temp.value())<min)
				{
					min=vl[j]-temp.value();
				}
			}
			vl[i]=min;
		}
	}
	return;
}
template<class T>
void CPOutput(const Graph<T> &g,const Vector<double> &ve,const Vector<double> &vl)
{ //�ؼ�·���������
	int nv=g.SizeV();
	T vj,vi;
	for(int j=0;j<nv;++j)
	{
		for(int i=0;i<nv;++i)
		{
			g.GetVertexItem(vi,i);
			g.GetVertexItem(vj,j);
			if(g.GetCost(vi,vj)!=nullopt)
			{ //���������Ǳߣ��������ʱ����ɳ���ʱ�䣩
				cout<<'<'<<vi<<','<<vj<<'>'<<"---"<<vl[j]-ve[i]-(g.GetCost(vi,vj)).value()<<endl;
			}
		}
	}
	return;
}

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
	static int d[4][2]={{1,0},{0,1},{-1,0},{0,-1}}; //��ʾ�����ƶ���������ݣ��ֱ��ʾ���ҡ����¡���������
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