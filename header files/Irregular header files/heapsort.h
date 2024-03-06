#ifndef HEAPSORT_H
#define HEAPSORT_H
template<class T>
void PercolateUp(T *p,int id,int n) //��p[id:n)���ϵ���ΪС����
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
void BuildHeap(T *p,int n) //��p[0:n)����С����
{
	for (int num = 1; num < n; ++num) //�Ѳ��롣ע��������ȫ������������numӦ�ô�1��ʼ
		PercolateUp(p,0,num + 1); //��p[0,num+1)���ϵ���ΪС����
}
/*
�����齨��С���ѻ�����ʹ����һ��˼·��
�����鿴������ȫ�������Ĳ�����У�ÿ��Ҷ�Ӷ���С���ѡ����������ķ�Ҷ�ӿ�ʼ������ÿ����һ��Ԫ�أ������ܲ�����С���ѣ���Ҫ���µ���ΪС���ѡ�
template<class T>
void BuildHeap(T *p,int n) //��p[0:n)����С����
{
	for (int id = n / 2 - 1; id > -1; --id) //n/2-1�Ƿ�Ҷ�ӵ��������
		PercolaterDown(p,id,n); //��p[id:n)���µ���ΪС����
}
*/
template<class T>
void PercolateDown(T *p,int id,int n) //��p[id:n)���µ���ΪС����
{
	int f = id; //˫������
	int c = 2  *f + 1; //��������
	T x = p[f]; //��ȡ��Ԫ��
	while (c < n) //�Ƚ�ѭ��������Ԫ��Ϊ˫�ף������Һ��ӵ�С�����ȡԪ�رȽϣ�����С�ڶ�ȡԪ�أ������ѭ���������С�߶�ȡ��д��˫�ף�Ȼ����ԭ��С��Ϊ˫�׼�������
	{
		if (c + 1 < n & &p[c + 1] < p[c]) //ȡ���Һ��ӵ�С��
			++c;
		if (p[c] >= x) //С�߲�С�ڶ�ȡԪ��
			break;
		else //С��С�ڶ�ȡԪ��
		{
			p[f] = p[c]; //��С�߶�ȡ��д��˫��
			f = c; //��ԭ��С��Ϊ˫��
			c = 2  *f + 1;
		}
	}
	p[f] = x; //�Ѷ�ȡԪ��д������ȡ��λ��
}
template<class T>
void HeapSort(T *p,int n) //��p[0:n)�Ӵ�С������
{
	T item; //��Ϊ����ֵ�������м����
	BuildHeap(p,n); //��p[0:n)����С����
	for (int num = n; num > 0; --num) //��ɾȡ
	{
		item = p[0];
		p[0] = p[num - 1];
		p[num - 1] = item;
		PercolateDown(p,0,num - 1); //��p[0,num-1)���µ���ΪС����
	}
}
#endif