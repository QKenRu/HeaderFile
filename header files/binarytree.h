#ifndef BINARYTREE_H
#define BTNARYTREE_H
#include"vector.h"
#include"queue.h"
#include"stack.h"
#include"seqlist.h"
#include<iostream>
template<class T>
struct BTNode //���������
{
	T data; //�洢����Ԫ��
	BTNode *left, *right; //ָ�����Һ��ӽ���ָ��
	BTNode(const T &item=T(),BTNode *l=0,BTNode *r=0):data(item),left(l),right(r){} //Ĭ�Ϲ���
};
template<class T> //����������
void Level(BTNode<T> *t)
{
	if (t == 0)
		return;
	Queue<BTNode<T>*>Q;
	Q.Push(t);
	while (!Q.Empty())
	{
		t = Q.Pop();
		cout << t->data;
		if (t->left)
			Q.Push(t->left);
		if (t->right)
			Q.Push(t->right);
	}
	cout << endl;
}
struct Location //������λ��
{
	int x,y;
};
void Gotoxy(int x,int y) //��λ����
{
	static int indent = 0; //ƫ��������ʵ��indent��̬�����ڱ����������õģ���Ϊ����ͣ�ر���ֵΪ0
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
void PrintBTree(const BTNode<T> *t,SeqList<int> &value,SeqList<char> &word,int w) //��ֱ���������
{
	if (t == 0)
		return;
	int level = 0,off = w / 2; //��0�㿪ʼ��ƫ�����ǿ�ȵ�1/2
	Location f,c;
	Queue<const BTNode<T>*>Q; //�洢���ָ��
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
		if (!t->left & &!t->right)
		{
			for (int i = 0; i < value.GetSize(); ++i)
				if ((t->data) == value.GetData(i))
					cout << word.GetData(i);
		}
		else
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
template<class T> //��˳��洢���ɶ�����ʽ�洢
BTNode<T> *MakeBTree(const T *p,int n)
{
	if (n <= 0)
		return 0;
	Queue<BTNode<T>*>Q;
	BTNode<T> *t = new BTNode<T>(p[0]); //���ɸ�ָ��
	BTNode<T> *f, *c; //˫�׺ͺ���ָ��
	Q.Push(t); //��ָ�����
	int i = 0;
	while (!Q.Empty())
	{
		f = Q.Pop(); //һ�����ָ�����
		if (2  *i + 1 < n & &p[2  *i + 1] != T()) //���������
		{
			c = new BTNode<T>(p[2  *i + 1]); //�������ӽ��
			f->left = c; //��˫������
			Q.Push(c); //����ָ�����
		}
		if (2  *i + 2 < n & &p[2  *i + 2] != T()) //������Һ���
		{
			c = new BTNode<T>(p[2  *i + 2]); //�����Һ��ӽ��
			f->right = c; //��˫������
			Q.Push(c); //�Һ���ָ�����
		}
		++i;
		while (i < n & &p[i] == T()) //������һ����0Ԫ��
			++i;
	}
	return t;
}
template<class T>
void Preorder(const BTNode<T> *t) //ǰ������ݹ麯��
{
	if (t == 0)
		return;
	cout << t->data << '\t'; //���ʸ�
	Preorder(t->left); //ǰ�����������
	Preorder(t->right); //�ϵ�(1)��ǰ�����������
} //�ϵ�(2)
/*ǰ������ݹ麯����һ���汾������if�Ӿ䣬������������������Ϊ��
template<class T>
void Preorder(const BTNode<T> *t)
{
	if(t==0)
		return;
	cout<<t->data<<'\t';
	if(t->left)
		Preorder(t->left);
	if(t->right)  //�ϵ�(1)
		Preorder(t->right);
} //�ϵ�(2)
*/
template<class T>
void SimPreoder(const BTNode<T> *t) //ǰ�������������
{
	if (t == 0)
		return;
	Stack<const BTNode<T>*>S; //�û�ջ
	while (t || !S.Empty())
		if (t)
		{
			cout << t->data << '\t'; //���ʽ��
			if (t->right)
				S.Push(t->right); //�Һ���ָ����ջ����
			t = t->left; //��ȡ����ָ��
		}
		else
			t = S.Pop(); //�Һ���ָ���ջ
}
template<class T> //�������򻮷�
int Partition(T *p,int left,int right) //��p[left:right]���֣����ظ�������
{
	T root = p[left]; //��ȡ������Ԫ����Ϊ����������λ
	while (left != right)
	{
		while (p[right] >= root & &right > left) //��ʣ�������Ԫ���У���������������ҵ���һ��С�ڸ���Ԫ��ֹͣ������Ԫ���Ƶ���һλ�Ŀ�λ�������µĿ�λ
			--right;
		if (right > left)
			p[left++] = p[right];
		while (p[left] <= root & &left < right) //��û�з��ʵ�����Ԫ���У��������ұ������ҵ���һ�����ڸ���Ԫ��ֹͣ������Ԫ���Ƶ���һλ�Ŀ�λ�������µĿ�λ
			++left;
		if (left < right)
			p[right--] = p[left];
	}
	p[left] = root; //�ظ����ϲ��裬ֱ������Ԫ�ض����ʹ���ֻʣһ����λ�������Ƶ���λ�����ظ�������
	return left;
}
template<class T>
void QuickSort(T *p,int left,int right) //��������
{
	if (left >= right)
		return;
	int m = Partition(p,left,right); //�����黮��
	QuickSort(p,left,m - 1); //����������������
	QuickSort(p,m + 1,right); //����������������
}
template<class T>
void QuickSort(T *p,int n) //������������
{
	QuickSort(p,0,n - 1); //���ÿ�������ݹ��㷨
}
template<class T>
void Inorder(const BTNode<T> *t) //��������ݹ��㷨 
{
	if (t == 0)
		return;
	Inorder(t->left); //�������������
	cout << t->data << '\t'; //�ϵ�(!)
	Inorder(t->right); //�������������
} //�ϵ�(2)
/*��������ݹ麯��������һ���汾������if�Ӿ䣬������������������Ϊ�գ����ݹ����ֱ��ָ����ָ��Ľ��û����������0Ϊֹ����ʼ����
template<class T>
void Inorder(const BTNode<T> *t)
{
	if(t==0)
		return;
	if(t->left)
		Inorder(t->left); //�������������
	cout<<t->data<<'\t'; //�ϵ�(!)
	if(t->right)
		Inorder(t->right); //�������������
} //�ϵ�(2)
*/
template<class T>
void SimInorder(const BTNode<T> *t) //������������㷨
{
	if (t == 0)
		return;
	Stack<const BTNode *> S; //�û�ջ
	while(t||!S.Empty())
		if (t)
		{
			S.Push(t); //���ָ����ջ����
			t = t->left; //��ȡ����ָ��
		}
		else
		{
			t = S.Pop(); //���ָ���ջ
			cout << t->data << '\t'; //���ʽ��
			t = t->right; //��ȡ�Һ���ָ��
		}
}
void Hanoi(int n,char S,char M,char E) //��ŵ���������
{ //����Ԫ��(n,��ʼλ��,�м�λ��,����λ��)��ʾn�׺�ŵ�����⡣�����������1�����������Һ��ӣ��������ӵĹ�ϵ�ǽ�����1���м�λ�úͽ���λ�ý�����
  //�����Һ��ӵĹ�ϵ�ǽ�����1����ʼλ�ú��м�λ�ý������������Ϊ��ŵ��״̬����n�׺�ŵ������ݹ����ģ���Ƕ�������������ݹ��㷨��
	if (n <= 0)
		return;
	if (n > 1)
		Hanoi(n - 1,S,E,M); //�м�λ�úͽ���λ�ý���
	cout << n << ':' << S << "->" << E << endl; //�ѵ�n�����Ӵ���ʼλ��ֱ���Ƶ�����λ��
	if (n > 1)
		Hanoi(n - 1,M,S,E); //��ʼλ�ú��м�λ�ý���
}
template<class T>
void Postorder(const BTNode<T> *t) //��������ݹ��㷨
{
	if (t == 0)
		return;
	Postorder(t->left); //�������������
	Postorder(t->right); //�ϵ�(1)���������������
	cout << t->data << '\t'; //�ϵ�(2)������������Ԫ��
}
/*��������ݹ麯��������һ���汾������if�Ӿ�
template<class T>
void Postorder(const BTNode<T> *t)
{
	if (t == 0)
		return;
	if (t->left)
		Postorder(t->left); //�������������
	if (t->right) //�ϵ�(1)
		Postorder(t->right); //�������������
	cout << t->data << '\t'; //�ϵ�(2)
}
*/
template<class T>
void SimPostorder(const BTNode<T> *t) //������������㷨
{
	if (t == 0)
		return;
	int tag;
	Stack<int>tagS; //��¼���ָ����ջ�����������ڶ��γ�ջʱ�����ʸý��
	Stack<const BTNode<T>*> S;
	const BTNode<T> *p;
	while(t||!S.Empty())
		if (t)
		{
			S.Push(t);
			tagS.Push(1);
			t=t->left;
		}
		else
		{
			p = S.Pop();
			tag = tagS.Pop();
			if (tag == 1) //��һ�γ�ջ
			{
				S.Push(p);
				tagS.Push(2);
				t = p->right;
			}
			else //�ڶ��γ�ջ
				cout << p->data << '\t';
		}
}
template<class T>
BTNode<T> *CopyTree(const BTNode<T> *t) //���ƶ�������ĵݹ��㷨
{
	if (t == 0)
		return 0;
	BTNode<T> *l = CopyTree(t->left);
	BTNode<T> *r = CopyTree(t->right);
	return new BTNode<T>(t->data,l,r);
}
template<class T>
int Depth(const BTNode<T> *t) //����������߶�
{
	if (t == 0)
		return -1;
	int l = Depth(t->left);
	int r = Depth(t->right);
	return(1 + (l > r ? l: r));
}
template<class T>
void DeleteBTree(BTNode<T> *t) //ɾ����������ĵݹ��㷨
{
	if (t == 0)
		return;
	DeleteBTree(t->left);
	DeleteBTree(t->right);
	delete t;
}
template<class T>
BTNode<T> *MakeBTree(const T *p,int size,int i) //���ɶ�������ĵݹ��㷨
{
	if (size == 0 || i >= size || p[i] == T())
		return 0;
	BTNode<T> *l = MakeBTree(p,size,2  *i + 1);
	BTNode<T> *r = MakeBTree(p,size,2  *i + 2);
	return new BTNode<T>(p[i],l,r);
}
#endif