#ifndef STACK_H
#define STACK_H
#include"list.h"
template<class T>
class Stack
{
	List<T>st;
public:
	Stack(){}
	~Stack(){}
	void Push(const T &item) { st.PushBack(item); } //��ջ
	T Pop() { T item = st.Back(); st.PopBack(); return item; } //��ջ
	const T &Top()const{ return st.Back(); } //ȡջ��Ԫ��
	void Clear() { st.Clear(); } //��ջ
	int Size()const{ return st.Size(); } //ȡ����
	int Empty()const{ return st.Empty(); } //�п�
};
#endif