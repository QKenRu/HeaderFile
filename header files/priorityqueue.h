#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include"list.h"
template<class T>
class PQueue
{
	List<T>que;
public:
	PQueue(){}
	~PQueue(){}
	void Push(const T &item) { que.PushBack(item); } //���
	T Pop(); //����
	void Clear() { que.Clear(); } //��ն���
	int Size()const{ return que.Size(); } //ȡ����Ԫ�ظ���
	bool Empty()const{ return que.Empty(); } //�п�
};
template<class T>
T PQueue<T>::Pop() //����СֵΪ���ȼ����
{
	typename List<T>::iterator min = que.Begin(); //������Ԫ������СԪ��
	typename List<T>::iterator first = que.Begin();
	typename List<T>::iterator last = que.End(); //������СԪ��
	for (; first != last; ++first) //������СԪ��
		if ((*first) < (*min))
			min = first; //ָ��ǰ��СԪ��
	T item = *min; //�洢��СԪ��ֵ
	que.Erase(min); //ɾ����СԪ�ؽ��
	return item; //������СԪ��ֵ
}
#endif