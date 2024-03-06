#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include"vector.h"
#include"binarytree.h"
#include"heap.h"
#include"stack.h"
#include"seqlist.h"
template<class T>
struct Hufm
{
	BTNode<T> *t;
	int operator<(const Hufm &h) { return t->data < h.t->data; }
	int operator<=(const Hufm &h) { return t->data <= h.t->data; }
	int operator>(const Hufm &h) { return t->data > h.t->data; }
	int operator>=(const Hufm &h) { return t->data >= h.t->data; }
	int operator==(const Hufm &h) { return t->data == h.t->data; }
	int operator!=(const Hufm &h) { return t->data != h.t->data; }
};
template<class T>
BTNode<T> *HufmTree(const SeqList<T> &value,int n) //��n��Ȩ�洢�������У��ø����齨����������
{
	Hufm<T>hf; //�������ṹ����
	BTNode<T> *l; //����������ָ��
	BTNode<T> *r; //����������ָ��
	Heap<Hufm<T>>H(n); //�����Թ������ṹ����ΪԪ�ص�С����
	for (int i = 0; i < n; ++i) //ÿһ��Ȩ����һ���������ṹ������Ϊ����������������ѡ�����Ȩ���ǽ�����ݳ�Աdata��ֵ
	{
		hf.t = new BTNode<T>(value.GetData(i));
		H.Insert(hf);
	}
	while (H.Size() > 1) //����ѭ����ÿһ�ε������Ӷ�����ȡ����Ԫ����Ϊ���Һ��ӣ��γɶ�����������Ȩ�����Һ��ӵ�Ȩ֮�ͣ�Ȼ�����ѣ�ֱ������ֻ��һ��Ԫ��
	{
		H.Remove(hf);
		l = hf.t;
		H.Remove(hf);
		r = hf.t;
		hf.t = new BTNode<T>(l->data + r->data,l,r);
		H.Insert(hf);
	}
	H.Remove(hf); //��ȡ���е�Ԫ�أ��������е����ݳ�Ա�����ǹ��������ĸ�
	return hf.t;
}
/*
template<class T>
void OutputCode(Vector<const BTNode<T>*>vt) //�����������
{
	Tname Vector<const BTNode<T>*>::iterator first = vt.Begin();
	Tname Vector<const BTNode<T>*>::iterator last = vt.End();
	cout << (  *(last - 1))->data << ':'; //��������Ȩ
	const BTNode<T> *t = *first;
	++first;
	while (first != last)
	{
		if (t->left == *first)
			cout << '0';
		else
			cout << '1';
		t = *first;
		++first;
	}
	cout << endl;
}
template<class T>
void HafmCoder(const BTNode<T> *t) //�����������
{
	if (t == 0)
		return;
	const BTNode<T> *p;
	Vector<const BTNode<T>*>S; //�ѽ��ָ��ջ��Ϊ���ָ���������Ա�ͨ������·�����õ�����������
	int tag;
	Stack<int>tagS; //��¼���ָ����ջ�����������ڶ��γ�ջʱ�����ʸý��
	while(t||!S.Empty())
		if (t)
		{
			S.PushBack(t);
			tagS.Push(1);
			t = t->left;
		}
		else
		{
			p = S.Back();
			S.PopBack();
			tag = tagS.Pop();
			if (tag == 1)
			{
				S.PushBack(p);
				tagS.Push(2);
				t = p->right;
			}
			else if (p->left == 0 & &p->right == 0) //���������������Ϊ���Ҷ�ӵ�������Ҷ�ӵ���������Ϊ�ա����Ҷ�ӵĲ���������
			{
				S.PushBack(p); //��Ҷ��β�嵽��������������������洢�ĸ�����Ҷ�ӵ�·��
				OutputCode(S); //ͨ���������������Ҷ�ӵı���
				S.PopBack(); //βɾ��Ҷ�ӣ�����������������㷨
			}
		}
}
*/
template<class T>
void OutputCode(Vector<const BTNode<T>*>vt,const SeqList<int> &value,const SeqList<char> &word,const int n) //�����������
{
	fstream file;
	file.open("D:\\HuffmanCode.txt",ios::out|ios::app);
	typename Vector<const BTNode<T>*>::iterator first = vt.Begin();
	typename Vector<const BTNode<T>*>::iterator last = vt.End();
	for (int i = 0; i < n; ++i)
	{
		if (value.GetData(i) == (*(last - 1))->data)
		{
			cout << word.GetData(i) << ':';
			file << word.GetData(i) << ':'; //��������Ȩ
		}
	}
	const BTNode<T> *t = *first;
	++first;
	while (first != last)
	{
		if (t->left == *first)
		{
			cout << '0';
			file << '0';
		}
		else
		{
			cout << '1';
			file << '1';
		}
		t = *first;
		++first;
	}
	cout << endl;
	file << endl;
	file.close();
}
template<class T>
void HafmCoder(const BTNode<T> *t,const SeqList<int> &value,const SeqList<char> &word,const int n) //�����������
{
	if (t == 0)
		return;
	const BTNode<T> *p;
	Vector<const BTNode<T>*>S; //�ѽ��ָ��ջ��Ϊ���ָ���������Ա�ͨ������·�����õ�����������
	int tag;
	Stack<int>tagS; //��¼���ָ����ջ�����������ڶ��γ�ջʱ�����ʸý��
	while (t || !S.Empty())
		if (t)
		{
			S.PushBack(t);
			tagS.Push(1);
			t = t->left;
		}
		else
		{
			p = S.Back();
			S.PopBack();
			tag = tagS.Pop();
			if (tag == 1)
			{
				S.PushBack(p);
				tagS.Push(2);
				t = p->right;
			}
			else if (p->left == 0 & &p->right == 0) //���������������Ϊ���Ҷ�ӵ�������Ҷ�ӵ���������Ϊ�ա����Ҷ�ӵĲ���������
			{
				S.PushBack(p); //��Ҷ��β�嵽��������������������洢�ĸ�����Ҷ�ӵ�·��
				OutputCode(S,value,word,n); //ͨ���������������Ҷ�ӵı���
				S.PopBack(); //βɾ��Ҷ�ӣ�����������������㷨
			}
		}
}
template<class T>
void Output(const Vector<T>vt) //����������ڣ��������
{
	fstream file;
	file.open("D:\\HuffmanText.txt",ios::out|ios::app);
	Vector<T>::const_iterator first = vt.Begin();
	Vector<T>::const_iterator last = vt.End();
	while (first != last)
	{
		file << *first<<" ";
		++first;
	}
	file << endl;
	file.close();
}
template<class T>
void HufmDecoder(const BTNode<T> *t,char *c) //�����������
{
	const BTNode<T> *r = t; //��ȡ��������
	int i = 0;
	Vector<int>v; //���ڴ������
	while (c[i] != '\0' & &r != 0)
	{
		if (c[i] == '0')
			r = r->left;
		else
			r = r->right;
		if (r->left == 0 & &r->right == 0) //����Ҷ��
		{
			v.PushBack(r->data); //���������һ���ַ�
			r = t;
		}
		++i;
	}
	if (c[i] == '\0' & &r != t) //����û�н�������ǰ����
		cout << "Error." << endl;
	else
		Output(v);
}
#endif