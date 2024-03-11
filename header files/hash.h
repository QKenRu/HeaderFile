#ifndef HASH_H
#define HASH_H
#include"..\..\AAAPublicHeaderFile\vector.h"
#include"..\..\AAAPublicHeaderFile\list.h"
#include<iostream>
#include<iomanip>
using namespace std;
template<class T>
//�����Hash����÷�������(separate chaining)������ؼ���(key)��ͻ(collision)�����ص��ǰ�ɢ�е�ͬһ��Ͱ��Ĺؼ��뱣����һ�������У�ÿ������һ��List����ɢ�б���List��������
class Hash
{
	Vector<List<T>> ht; //һ��Ͱһ��List����htȫ��Ϊhash table����ɢ�б���ϣ��
	int (*hf)(const T &x); //ɢ�к���ָ��
	int sizeBucket; //Ͱ����
public:
	explicit Hash(int n,int (*hash)(const T &)):ht(n),hf(hash){ sizeBucket=n; } //����"int (*hash)(const T &)"�ǽ�һ��int�ͺ�����Ϊ��һ���ĺ������βΣ���ζ��ͷ�ļ����Դ�ɢ�к������������û��������
	bool Insert(const T &x); //����
	bool Erase(const T &x); //ɾ��
	bool Find(const T &x)const; //����
	int SizeKey()const; //�ؼ�������
	void Output()const; //��ʾ�����
};

template<class T>
int Hash<T>::SizeKey()const
{ //�ؼ�������
	int counter=0; //�ۼ���
	for(int i=0;i<sizeBucket;++i)
	{ //�ۼ�ÿ��Ͱ�ĳ���
		counter+=ht[i].Size();
	}
	return counter;
}

template<class T>
bool Hash<T>::Insert(const T &x)
{ //����
	if(!Find(x))
	{
		ht[hf(x)].PushBack(x);
		return 1;
	}
	return 0;
}
template<class T>
bool Hash<T>::Erase(const T &x)
{ //ɾ��
	List<T> &L=ht[hf(x)];
	typename List<T>::iterator first=L.Begin();
	typename List<T>::iterator last=L.End();
	for(;first!=last;++first)
	{
		if(*first==x)
		{
			L.Erase(first);
			return 1;
		}
	}
	return 0;
}
template<class T>
bool Hash<T>::Find(const T &x)const
{ //����
	const List<T> &L=ht[hf(x)];
	typename List<T>::const_iterator first=L.Begin();
	typename List<T>::const_iterator last=L.End();
	for(;first!=last;++first)
	{
		if(*first==x)
		{
			return 1;
		}
	}
	return 0;
}

template<class T>
void Hash<T>::Output()const
{ //��ʾ�����
	typename List<T>::const_iterator first;
	typename List<T>::const_iterator last;
	for(int i=0;i<sizeBucket;++i)
	{
		first=ht[i].Begin();
		last=ht[i].End();
		for(;first!=last;++first)
		{
			cout<<setw(6)<<*first<<' ';
		}
		cout<<endl;
	}
}

#endif