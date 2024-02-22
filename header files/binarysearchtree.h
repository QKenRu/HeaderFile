#ifndef BINARYSEARCHTREE_H //��������������
#define BINARYSEARCHTREE_H
#include"queue.h"
#include"stack.h"
#include<iostream>
using namespace std;
template<class T>
class BSTree
{
	struct BTNode
	{
		T data;
		BTNode *left, *right;
		BTNode(const T &item=T(),BTNode *l=0,BTNode *r=0):data(item),left(l),right(r){}
	};
	BTNode *root; //��ָ��
	int size; //������
	void Insert(const T &x,BTNode **t); //����
	void Erase(const T &x,BTNode **t); //ɾ��
	void Update(const T &x,BTNode **t); //����
	void Clear(BTNode *t); //���
	BTNode *FindMin(BTNode *t)const; //������СԪ��
	BTNode *FindMax(BTNode *t)const; //�������Ԫ��
	BTNode *Find(const T &x,BTNode *t)const; //����
	void PrintBSTree(const BTNode *t,int w); //��ֱ���
public:
	class const_iterator  //���������
	{
	protected:
		BTNode *current;
		T &retrieve()const{ return current->data; }
		const_iterator(BTNode *t) { current = GoFarLeft(t); } //���캯��
		Stack<BTNode*>St; //ջ
		BTNode *GoFarLeft(BTNode *t) //�������������׽��ָ��
		{
			if (t == 0)
				return 0;
			while (t->left)
			{
				St.Push(t);
				t = t->left;
			}
			return t;
		}
		friend class BSTree<T>;
	public:
		const_iterator():current(0) {}
		const T &operator *()const{ return retrieve(); }
		const_iterator &operator++() //ǰ++
		{
			if (current->right)
				current = GoFarLeft(current->right);
			else if (!St.Empty())
				current = St.Pop();
			else
				current = 0;
			return *this;
		}
		bool operator==(const const_iterator &rhs)const{ return current == rhs.current; }
		bool operator!=(const const_iterator &rhs)const{ return current != rhs.current; }
	};
	class iterator: public const_iterator
	{
	protected:
		iterator(BTNode *t):const_iterator(t) {}
		friend class BSTree<T>;
	public:
		iterator() {}
		T &operator*() { return this->retrieve(); }
		const T &operator*()const{ return(const_iterator::operator*()); }
		iterator &operator++()
		{
			if (this->current->right)
				this->current = this->GoFarLeft(this->current->right);
			else if (!this->St.Empty())
				this->current = this->St.Pop();
			else
				this->current = 0;
			return  *this;
		}
	};
public:
	BSTree():root(0),size(0) {}; //Ĭ�Ϲ���
	virtual ~BSTree() { Clear(); } //����
	const_iterator Begin()const{ return const_iterator(root); }
	iterator Begin() { return iterator(root); }
	const_iterator End()const{ return const_iterator(0); }
	iterator End() { return iterator(0); }
	void Insert(const T &x) { Insert(x,&root); } //����
	void Erase(const T &x) { Erase(x,&root); } //ɾ��
	void Update(const T &x) { Update(x,&root); } //����
	void Clear() { Clear(root); }  //���
	T &FindMin()const{ return FindMin(root)->data; } //������СԪ��
	T &FindMax()const{ return FindMax(root)->data; } //�������Ԫ��
	int Find(const T &x)const{ return Find(x,root) != 0; } //����
	int Size() { return size; } //��ȡ������
	void PrintBSTree(int w) { PrintBSTree(root,w); /*����˽�з���*/ } //��ֱ���
};
template<class T>
void BSTree<T>::Clear(BTNode *t) //���
{
	if (t == 0)
		return;
	Clear(t->left);
	Clear(t->right);
	delete t;
}
template<class T>
void BSTree<T>::Insert(const T &x,BTNode **t) //����
{
	while ((*t) != 0)
	{
		if (x < (*t)->data) //����ȵ�ǰ����ֵС
			t = &((*t)->left); //�����������Ҳ���λ��
		else //����ȵ�ǰ����ֵ��
			t = &((*t)->right); //�����������Ҳ���λ��
	}
	(*t) = new BTNode(x); //����
	++size;
}
struct Location //��ֱ�����λ��
{
	int x,y;
};
void Gotoxy(int x,int y) //��ֱ������ƶ���굽����(x,y)
{
	static int indent = 0; //ƫ����
	static int level = 0; //����
	if (y == 0)
	{
		level = 0;
		indent = 0;
	}
	if (y != level) //�������ʱ����ͷ��ʼ
	{
		int n = y - level;
		for (int i = 0; i < n; ++i)
		{
			cout << endl;
			++level;
		}
		indent = 0;
	}
	cout.width(x - indent); //ͬ�����ʱ����
	indent = x; //��¼�����������
}
template<class T>
void BSTree<T>::PrintBSTree(const BTNode *t,int w) //��ֱ���
{ //�������ͬbtnode.h�Ĵ�ֱ���������PrintBTree����
	if (t == 0)
		return;
	int level = 0,off = w / 2; //��0�㿪ʼ��ƫ�����ǿ�ȵ�1/2
	Location f,c;
	Queue<const BTNode*>Q; //�洢���ָ�룬�˴���btnode.h�еĺ�����ͬ
	Queue<Location>LQ; //�洢������λ��
	f.x = off;
	f.y = level;
	Q.Push(t);
	LQ.Push(f);
	while (!Q.Empty())
	{
		t = Q.Pop();
		f = LQ.Pop();
		Gotoxy(f.x,f.y); //�ƶ���굽���λ��
		cout << t->data;
		if (f.y != level) //�����⣬ÿ���׽������󣬶��޸Ĳ�����ƫ����
		{
			++level;
			off /= 2;
		}
		if (t->left)
		{
			Q.Push(t->left);
			c.x = f.x - off / 2;
			c.y = f.y + 1;
			LQ.Push(c);
		}
		if (t->right)
		{
			Q.Push(t->right);
			c.x = f.x + off / 2;
			c.y = f.y + 1;
			LQ.Push(c);
		}
	}
	cout << endl;
}
template<class T>
void BSTree<T>::Erase(const T &y,BTNode **t) //ɾ������Ϊɾ������Ҫ�޸Ľ����ָ�����ֵ��������Ҫ����ָ��ĵ�ַ����Ӧ���β�Ϊָ��ָ���ָ��
{
	T z = y;
	while (*t) //����Ҫɾ���Ľ�㡣���Ҫɾ����Ԫ�رȵ�ǰ����ֵС���͵����������ң����Ҫɾ����Ԫ�رȵ�ǰ����ֵ�󣬾͵�����������
		if (z < (*t)->data)
			t = &((*t)->left);
		else if (z > (*t)->data)
			t = &((*t)->right);
		else if ((*t)->left != 0 & &(*t)->right != 0) //Ҫɾ����Ԫ�ؽ�����������������Ҹýڵ�����������С��㣬����С����ֵ����Ҫɾ���Ľ���ֵ��Ȼ�����ֵ��ΪҪɾ����Ԫ�أ������������Ҹ�Ԫ�ؽ�㣬������һ��û��������
		{
			(*t)->data = FindMin((*t)->right)->data;
			z = (*t)->data;
			t = &((*t)->right);
		}
		else //Ҫɾ����Ԫ�ؽ��û����������������������û�С�������ֱ����Ҫɾ���Ľ���˫������
		{
			BTNode *old = *t; //ָ��Ҫɾ���Ľ��
			(*t) = ((*t)->left != 0) ? (*t)->left: (*t)->right; //��ʵ�˴�(*t)���һ��û����������ָ���ʱҪôΪNULL��ҪôΪ(*t)->right
			delete old;
			--size;
		}
}
template<class T>
void BSTree<T>::Update(const T  &x,BTNode **t) //����
{
	BTNode *p = Find(x,*t); //���ݹؼ��ʲ��ҽ��
	if (p) //���ҵ�
		p->data = x;
	else //û���ҵ�
		Insert(x);
}
template<class T>
typename BSTree<T>::BTNode *BSTree<T>::Find(const T &x,BTNode *t)const //����
{
	while (t != 0 & &x != t->data)
		if (x < t->data)
			t = t->left;
		else
			t = t->right;
	return t;
}
template<class T>
typename BSTree<T>::BTNode *BSTree<T>::FindMin(BTNode *t)const //������СԪ��
{
	if (t != 0)
		while (t->left != 0)
			t = t->left;
	return t;
}
template<class T>
typename BSTree<T>::BTNode *BSTree<T>::FindMax(BTNode *t)const //�������Ԫ��
{
	if (t != 0)
		while (t->right != 0)
			t = t->right;
	return t;
}
#endif