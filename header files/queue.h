#ifndef QUEUE_H
#define QUEUE_H
#include"list.h"
template<class T>
class Queue
{
	List<T>que;
public:
	Queue(){}
	~Queue(){}
	void Push(const T &item) { que.PushBack(item); } //���
	T Pop() { T item = que.Front(); que.PopFront(); return item; } //����
	const T &Front()const{ return que.Front(); } //ȡ��ͷԪ��
	void Clear() { que.Clear(); } //�ÿն�
	int Size()const{ return que.Size(); } //ȡ����
	int Empty()const{ return que.Empty(); } //�п�
};
#endif