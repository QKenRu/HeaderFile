#ifndef LIST_H
#define LIST_H
template<class T>
class List
{
	struct Node
	{
		T data;
		Node *prev,*next;
		Node(const T &d=T(),Node *p=0,Node *n=0):data(d),prev(p),next(n){}
	};
	int size;
	Node *head;
	Node *tail;
	void Init() { size=0; head=new Node; tail=new Node; head->next=tail; tail->prev=head; }
public:
	class const_iterator
	{
	protected:
		Node*current;
		T &Retrieve()const{ return current->data; }
		const_iterator(Node *p):current(p){} //ת������
		friend class List<T>;
	public:
		const_iterator():current(0){} //Ĭ�Ϲ���
		const T &operator*()const{ return Retrieve(); }
	//�����Լ�
		const_iterator &operator++() //ǰ++
		{
			current=current->next;
			return *this;
		}
		const_iterator operator++(int) //��++
		{
			const_iterator old=*this;
			++(*this);
			return old;
		}
		const_iterator &operator--() //ǰ--
		{
			current - current->prev;
			return *this;
		}
		const_iterator operator--(int) //��--
		{
			const_iterator old=*this;
			--(*this);
			return old;
		}
		//��ϵ����
		bool operator==(const const_iterator &itr)const{ return current==itr.current; }
		bool operator!=(const const_iterator &itr)const{ return current !=itr.current; }
	};
	class iterator:public const_iterator
	{
	protected:
		iterator(Node *p):const_iterator(p){} //ת������
		friend class List<T>;
	public:
		iterator(){} //Ĭ�Ϲ���
		T &operator*() { return const_iterator::Retrieve(); }
		const T &operator*() const{ return const_iterator::operator*(); }
	//�����Լ�
		iterator &operator++() //ǰ++
		{
			this->current=this->current->next;
			return *this;
		}
		iterator operator++(int) //��++
		{
			iterator old=*this;
			++(*this);
			return old;
		}
		iterator &operator--() //ǰ--
		{
			this->current=this->current->prev;
			return *this;
		}
		iterator operator--(int) //��--
		{
			iterator old=*this;
			--(*this);
			return old;
		}
	};
	List() { Init(); } //Ĭ�Ϲ���
	List(const List<T> &l) { Init(); *this=l; } //���ƹ���
	~List() { Clear(); delete head; delete tail; } //����
	const List<T> &operator=(const List<T> &l); //���ƹ���
	int Empty()const{ return size==0; }
	int Size()const{ return size; }
	const_iterator Begin()const{ return const_iterator(head->next); } //ָ��Ԫ���׽��
	iterator Begin() { return iterator(head->next); }
	const_iterator End()const{ return const_iterator(tail); } //ָ������β���
	iterator End() { return iterator(tail); }
	iterator Erase(iterator itr); //ɾ��������ָ��Ľ��
	void PopFront() { Erase(Begin()); } //ɾ��Ԫ���׽��
	void PopBack() { Erase(--End()); } //ɾ��Ԫ��β���
	void Clear() { while (!Empty()) PopFront(); } //���
	iterator Insert(iterator itr,const T &item); //�ڵ�����λ�ò���
	void PushBack(const T &item) { Insert(End(),item); } //������β�ڵ����
	void PushFront(const T &item) { Insert(Begin(),item); } //ǰ��
	T &Front() { return *Begin(); } //������Ԫ�ص�����
	const T &Front() const{ return *Begin(); } //������Ԫ�صĳ���������
	T &Back() { return *--End(); } //����βԪ�ص�����
	const T &Back() const{ return *--End(); } //����βԪ�صĳ���������
};
template<class T>
typename List<T>::iterator List<T>::Erase(iterator itr)
{
	Node*p=itr.current;
	iterator re(p->next);
	p->prev->next=p->next;
	p->next->prev=p->prev;
	delete p;
	--size;
	return re;
}
template<class T>
typename List<T>::iterator List<T>::Insert(iterator itr,const T &item)
{
	Node*p=itr.current;
	p->prev->next=new Node(item,p->prev,p);
	p->prev=p->prev->next;
	++size;
	return iterator(p->prev);
}
template<class T> //���Ƹ�ֵ
const List<T> &List<T>::operator=(const List<T> &l)
{
	Clear(); //���
	const_iterator first=l.Begin(),last=l.End();
	for (; first !=last; ++first)
		PushBack(*first);
	return *this;
}
template<class T> //��������
void InvertList(List<T> &L)
{
	typename List<T>::iterator first=L.Begin();
	typename List<T>::iterator last=L.End();
	typename List<T>::iterator next=first;
	++next;
	if(L.Size()>=1)
		while (next !=last)
		{
			L.PushFront(*next);
			L.Erase(next);
			next=first;
			++next;
		}
}
#endif