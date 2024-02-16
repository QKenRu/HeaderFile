#ifndef VECTOR_H
#define VECTOR_H
#include<stdlib.h>
using namespace std;
template<class T>
class Vector
{
private:
	T*data; //ָ��̬�����ָ��
	int size; //���������Ԫ�ظ���
	int max; //��������
public:
//����������
	typedef T*iterator; //������
	typedef const T*const_iterator; //const�͵�����
//��ȡ����������߽�
	iterator Begin() { return data; } //��ȡ�������
	const_iterator Begin()const{ return data; }
	iterator End() { return data + size; } //��ȡ�ҿ�����
	const_iterator End()const{ return data + size; }
//����������
	explicit Vector(int n=10):size(0),max(n) { data=new T[max]; } //ת����Ĭ�Ϲ���
	Vector(const Vector &v):data(0),max(0) { *this=v; } //���Ƹ�ֵ
	~Vector() { delete[]data; }
//���Ƹ�ֵ
	Vector &operator=(const Vector<T> &v); //���Ƹ�ֵ
//����
	void Reserve(int newMax); //������������������ԭ����
	void PushBack(const T &item); //β��
//ɾ��
	void PopBack() { --size; } //βɾ
	void Clear() { size=0; } //���
//�������������
	T &operator[](int id) { return data[id]; } //�±����������
	const T &operator[](int id)const{ return data[id]; } //�������±����������
//��ȡ
	bool Empty()const{ return size==0; } //�п�
	int Size()const{ return size; } //������Ԫ�ظ���
	int Max()const{ return max; } //����������
	const T &Back()const{ return data[size - 1]; } //����βԪ�ص�����
	const T &Front()const{ return data[0]; } //������Ԫ�ص�����
};

template<class T>
Vector<T> &Vector<T>::operator=(const Vector<T> &v) //���Ƹ�ֵ
{
	delete[]data;
	data=new T[v.max];
	size=v.size;
	max=v.max;
	for (int i=0; i < size; ++i)
		data[i]=v.data[i];
	return *this;
}
template<class T>
void Vector<T>::PushBack(const T &item) //β��
{
	if (size==max) //����ռ�������������Ҫ����������
		Reserve(2 *max + 1);
	data[size++]=item; //����Ԫ�ص�β��������Ԫ�ظ�����1
}

template<class T>
void Vector<T>::Reserve(int newmax)
{
	if(newmax <=max) //����������������㣬�򷵻�
		return;
	T*old=data; //����ԭ����
	data=new T[newmax]; //���·���������
	for (int i=0; i < size; ++i) //��ԭ�����е����ݸ��Ƶ�������
		data[i]=old[i];
	max=newmax; //�޸���������
	delete[]old; //�ͷ�ԭ����ռ�
}
#endif