#ifndef SEQLIST_H
#define SEQLIST_H
#include<iostream>
using namespace std;
template<class T>
class SeqList
{
private:
	T *data;
	int max;
	int size;
public:
	explicit SeqList(int n = 10):max(10),size(0) { data = new T[n]; } //ת����Ĭ�Ϲ���
	SeqList(const SeqList &l):data(0) { *this = l;} //���ƹ���
	~SeqList() { delete[]data; } //����
	SeqList &operator=(const SeqList &l); //���Ƹ�ֵ
	void Reserve(int newmax); //����
	void Insert(int id,T item); //�������
	void Insertup(int id); //�����Լ�
	void Insertfix(int id,T item); //�����޸�
	void PushBack(const T &item) { Insert(size,item); } //β��
	void PushFront(const T &item) { Insert(0,item); } //�ײ�
	void Erase(int id); //����ɾ��
	void PopFront() { Erase(0); } //��ɾ
	void PopBack() { Erase(size); } //βɾ
	void Clear() { size = 0; } //���
	T &operator[](int id) { return data[id]; } //�ǳ�������
	const T &operator[](int id)const{ return data[id]; } //��������
	bool Empty()const{ return size == 0; }
	int GetSize()const{ return size; }
	const T &GetData(int id)const{ return data[id]; }
};
template<class T>
void SeqList<T>::Reserve(int newmax) //����
{
	if (newmax <= max)
		return;
	T *old = data; //ָ�����飬�Ա���ԭʼ����
	max = newmax; //�������鳤��
	data = new T[newmax]; //��������
	for (int i = 0; i < size; ++i) //��ԭʼ����Ԫ��д��������ռ�
		data[i] = old[i];
	delete []old; //�ͷ�ԭ����ռ�
}
template<class T>
void SeqList<T>::Insert(int id,T item) //�������
{
	if (id < 0 || id>size + 1)
		cout<<("Insert:Id is illegal");
	if (size == max)
		Reserve(2*max);
	for (int i = size - 1; i >= id; --i)
		data[i + 1] = data[i];
	data[id] = item;
	++size;
}
template<class T>
void SeqList<T>::Insertup(int id) //�����Լ�
{
	if (id < 0 || id>size + 1)
		cout << ("Insertup:Id is illegal");
	++data[id];
}
template<class T>
void SeqList<T>::Insertfix(int id,T item) //�����޸�
{
	if (id < 0 || id>size + 1)
		cout << ("Insertfix:Id is illegal");
	data[id]=item;
}
template<class T>
void SeqList<T>::Erase(int id) //����ɾ��
{
	if (id<0 || id>size)
		cout<<("Erase:id is illegal");
	for (int i = id + 1; i < size; ++i)
		data[i - 1] = data[i];
	--size;
}
template<class T>
SeqList<T> &SeqList<T>::operator=(const SeqList &l) //���Ƹ�ֵ
{
	delete[]data;
	data = new T[l.max];
	size = l.size;
	max = l.max;
	for (int i = 0; i < size; ++i)
		data[i] = l.data[i];
	return *this;
}
#endif