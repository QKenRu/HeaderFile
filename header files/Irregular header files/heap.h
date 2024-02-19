#ifndef HEAP_H
#define HEAP_H
#include"binarytree.h"
#include<iostream>
using namespace std;
template<class T>
class Heap
{
	Vector<T>vt; //��������Ϊ�ײ�ṹ
	void PercolateDown(); //���µ���ΪС���ѣ�����ɾȡ����
	void PercolateUp(); //���ϵ���ΪС���ѣ����ڲ������
public:
	explicit Heap(int max=100):vt(max){} //���ն�
	virtual ~Heap(){} //����
	int Empty()const { return vt.Empty(); } //�ж϶��Ƿ�Ϊ��
	int Size()const { return vt.Size(); } //�ж�Ԫ�ظ���
	const T& Top()const { return vt.Front(); } //ȡ����Ԫ��
	void Insert(const T& item); //����
	void Remove(T& item); //ɾȡ����ɾ��Ԫ��ȡ��
	void Clear() { vt.Clear(); } //�����
	const T& operator[](int id) const { return vt[id]; } //�������������������
};
template<class T>
BTNode<T>* MakeBTree(const Heap<T>& H) //�ɶ����ɶ�������
{
	Queue<BTNode<T>*>Q;
	BTNode<T>* t = new BTNode<T>(H[0]); //���ɸ�ָ��
	BTNode<T>* f, * c; //˫�׺ͺ���ָ��
	Q.Push(t); //��ָ�����
	int i = 0, n = H.Size();
	while (!Q.Empty())
	{
		f = Q.Pop(); //һ�����ָ�����
		if (2 * i + 1 < n && H[2 * i + 1] != T()) //���������
		{
			c = new BTNode<T>(H[2 * i + 1]); //�������ӽ��
			f->left = c; //��˫������
			Q.Push(c); //����ָ�����
		}
		if (2 * i + 2 < n && H[2 * i + 2] != T()) //������Һ���
		{
			c = new BTNode<T>(H[2 * i + 2]); //�����Һ��ӽ��
			f->right = c; //��˫������
			Q.Push(c); //�Һ���ָ�����
		}
		++i;
	}
	return t;
}
template<class T>
void Heap<T>::Insert(const T& item) //�Ѳ���
{
	vt.PushBack(item); //��ȡβԪ��
	PercolateUp(); //�Ƚ�ѭ������βԪ��Ϊ���ӣ���˫�����ȡԪ�رȽϣ��������ڶ�ȡԪ�أ������ѭ���������˫�׶�ȡ��д�뺢�ӣ�Ȼ����ԭ��˫��Ϊ���Ӽ�������
}
template<class T>
void Heap<T>::PercolateUp() //���ϵ���ΪС���� 
{
	int size = Size(); //Ԫ�ظ���
	int c = size - 1; //β��Ԫ�ص�����
	int f = (c - 1) / 2; //˫������
	T x = vt[c]; //��ȡβԪ��
	while (c > 0) //�Ƚ�ѭ������βԪ��Ϊ���ӣ���˫�����ȡԪ�رȽϣ��������ڶ�ȡԪ�أ������ѭ���������˫�׶�ȡ��д�뺢�ӣ�Ȼ����ԭ��˫��Ϊ���Ӽ�������
		if (vt[f] <= x) //˫�ײ����ڶ�ȡ��Ԫ��
			break;
		else //˫�״��ڶ�ȡ��Ԫ��
		{
			vt[c] = vt[f]; //��˫�׶�ȡ��д�뺢��
			c = f; //��ԭ��˫��Ϊ����
			f = (c - 1) / 2;
		}
	vt[c] = x; //�Ѷ�ȡԪ��д������ȡ��λ��
}
template<class T>
void Heap<T>::Remove(T& item) //��ɾȡ��ɾ����Ԫ��ͨ����������
{
	item = vt[0]; //��ȡ��Ԫ��
	vt[0] = vt[Size() - 1]; //��βԪ�ظ�����Ԫ��
	vt.PopBack(); //βɾ
	PercolateDown(); //���µ���ΪС����
}
template<class T>
void Heap<T>::PercolateDown() //���µ���ΪС����
{
	int size = Size(); //Ԫ�ظ���
	int f = 0; //˫������
	int c = 2 * f + 1; //��������
	T x = vt[f]; //��ȡ��Ԫ��
	while (c < size) //�Ƚ�ѭ��������Ԫ��Ϊ˫�ף������Һ��ӵ�С�����ȡԪ�رȽϣ�����С�ڶ�ȡԪ�أ������ѭ���������С�߶�ȡ��д��˫�ף�Ȼ����ԭ��С��Ϊ˫�׼�������
	{
		if (c + 1 < size && vt[c + 1] < vt[c]) //ȡ���Һ��ӵ�С��
			++c;
		if (vt[c] >= x) //С�߲�С�ڶ�ȡԪ��
			break;
		else //С��С�ڶ�ȡԪ��
		{
			vt[f] = vt[c]; //��С�߶�ȡ��д��˫��
			f = c; //��ԭ��С��Ϊ˫��
			c = 2 * f + 1; 
		}
	}
	vt[f] = x; //�Ѷ�ȡԪ��д������ȡ��λ��
}

//���º������ڶ����򣬲�����Heap��
template<class T>
void HeapSortPercolateUp(T* p, int id, int n) //��p[id:n)���ϵ���ΪС����
{
	int c = n - 1; //β��Ԫ�ص�����
	int f = (c - 1) / 2; //˫������
	T x = p[c]; //��ȡβԪ��
	while (c > id) //�Ƚ�ѭ������βԪ��Ϊ���ӣ���˫�����ȡԪ�رȽϣ��������ڶ�ȡԪ�أ������ѭ���������˫�׶�ȡ��д�뺢�ӣ�Ȼ����ԭ��˫��Ϊ���Ӽ�������
		if (p[f] <= x) //˫�ײ����ڶ�ȡ��Ԫ��
			break;
		else //˫�״��ڶ�ȡ��Ԫ��
		{
			p[c] = p[f]; //��˫�׶�ȡ��д�뺢��
			c = f; //��ԭ��˫��Ϊ����
			f = (c - 1) / 2;
		}
	p[c] = x; //�Ѷ�ȡԪ��д������ȡ��λ��
}
template<class T>
void BuildHeap(T* p, int n) //��p[0:n)����С����
{
	for (int num = 1; num < n; ++num) //�Ѳ��롣ע��������ȫ������������numӦ�ô�1��ʼ
		HeapSortPercolateUp(p, 0, num + 1); //��p[0,num+1)���ϵ���ΪС����
}
/*
�����齨��С���ѻ�����ʹ����һ��˼·��
�����鿴������ȫ�������Ĳ�����У�ÿ��Ҷ�Ӷ���С���ѡ����������ķ�Ҷ�ӿ�ʼ������ÿ����һ��Ԫ�أ������ܲ�����С���ѣ���Ҫ���µ���ΪС���ѡ�
template<class T>
void BuildHeap(T* p, int n) //��p[0:n)����С����
{
for (int id = n / 2 - 1; id > -1; --id) //n/2-1�Ƿ�Ҷ�ӵ��������
PercolaterDown(p, id, n); //��p[id:n)���µ���ΪС����
}
*/
template<class T>
void HeapSortPercolateDown(T* p, int id, int n) //��p[id:n)���µ���ΪС����
{
	int f = id; //˫������
	int c = 2 * f + 1; //��������
	T x = p[f]; //��ȡ��Ԫ��
	while (c < n) //�Ƚ�ѭ��������Ԫ��Ϊ˫�ף������Һ��ӵ�С�����ȡԪ�رȽϣ�����С�ڶ�ȡԪ�أ������ѭ���������С�߶�ȡ��д��˫�ף�Ȼ����ԭ��С��Ϊ˫�׼�������
	{
		if (c + 1 < n && p[c + 1] < p[c]) //ȡ���Һ��ӵ�С��
			++c;
		if (p[c] >= x) //С�߲�С�ڶ�ȡԪ��
			break;
		else //С��С�ڶ�ȡԪ��
		{
			p[f] = p[c]; //��С�߶�ȡ��д��˫��
			f = c; //��ԭ��С��Ϊ˫��
			c = 2 * f + 1;
		}
	}
	p[f] = x; //�Ѷ�ȡԪ��д������ȡ��λ��
}
template<class T>
void HeapSort(T* p, int n) //��p[0:n)�Ӵ�С������
{
	T item; //��Ϊ����ֵ�������м����
	BuildHeap(p, n); //��p[0:n)����С����
	for (int num = n; num > 0; --num) //��ɾȡ
	{
		item = p[0];
		p[0] = p[num - 1];
		p[num - 1] = item;
		HeapSortPercolateDown(p, 0, num - 1); //��p[0,num-1)���µ���ΪС����
	}
}
#endif