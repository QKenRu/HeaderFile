#ifndef STRING_H
#define STRING_H
#include<iostream>
using namespace std;
class String
{
private:
	char *str;
	int size;
public:
	//���������
	String(const char *c = ""):size(0),str(0) { *this = c; } //ת����Ĭ�Ϲ���
	String(const String &s):size(0),str(0) { *this = s; } //���ƹ���
	~String() { delete[]str; } //����
	//��ֵ
	String &operator=(const char *c); //ת����ֵ���മ=C��
	String &operator=(const String &s) { return *this = s.str; } //���Ƹ�ֵ���മ=�മ
	//�������
	friend istream &operator>>(istream &istr,String &s); //��ȡ��
	friend ostream &operator<<(ostream &ostr,const String &s); //�����
	//����
	String operator+(const String &s) const; //�മ+�മ
	String operator+(const char *c) const; //�മ+C��
	friend String operator+(const char *c,const String &s); //C��+�മ
	//�����ɾ��
	String &Insert(int id,const String &s); //�����മ
	String &Insert(int id,const char *c); //����C��
	String &Erase(int id,int num); //ɾ���Ӵ�
	//ȡ�Ӵ�
	String SubStr(int id,int num) const; //ȡ�Ӵ�
	//����
	int FindFirstOf(char ch,int id) const; //��id��ʼ����ch�״γ��ֵ�λ��
	int FindFirstOf(const String &s,int id) const;
	int FindFirstOf(const char *c,int id) const{ return FindFirstOf(String(c),id); }
	int Size() { return size; }
	//����
	char &operator[](int id) { return str[id]; }
	const char &operator[](int id) const{ return str[id]; }
	//�ַ�����
	int Strlen(const char *s)const;
	//�ַ�������
	char *Strcpy(char *s1,const char *s2)const;
	char *Strncpy(char *s1, char *s2, int n)const;
	//�ַ�������
	char *Strcat(char *s1,char *s2)const;
	char *Strncat(char *s1,char *s2,int n)const;
	//�ַ�����Сд�滻
	String &Strupr(String &s);
	String &Strlwr(String &s);
	//�ַ����Ƚ�
	static int Strcmp(const char *s1,const char *s2); //�����ַ����Ƚ�
	static int Strncmp(const char *s1,const char *s2,int n); //ָ��ǰn���ַ����ַ����Ƚ�

	//��ϵ����
	bool operator==(const String &s) const
	{
		return Strcmp(str, s.str) == 0; //�മ==�മ
	}
	bool operator==(const char *c) const
	{
		return Strcmp(str, c) == 0; //�മ==C��
	}
	friend bool operator==(const char *c, const String &s)
	{
		return Strcmp(c, s.str) == 0; //C��==�മ
	}
	bool operator>(const String &s) const
	{
		return Strcmp(str, s.str) > 0; //�മ>�മ
	}
	bool operator>(const char *c) const
	{
		return Strcmp(str, c) > 0; //�മ>C��
	}
	friend bool operator>(const char *c, const String &s)
	{
		return Strcmp(c, s.str) > 0; //C��>�മ
	}
};

int String::Strlen(const char *s)const
{
	int i=0;
	while(s[i]!='\0')
	{
		++i;
	}
	return i;
}

int String::Strcmp(const char *s1,const char *s2)
{ //���ַ���s1��s2���ַ���ǰ��������Ƚϣ������ʱ����0������ʱ�Ƚ�ֹͣ��ǰ�ߴ�ʱ����1�����ߴ�ʱ����-1
	int i=0; //����Ԫ������
	int token=0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			break;
		}
		++i;
	}
	if(s1[i]>s2[i]) //'\0'��ASCII��Ϊ0�����κ��ַ���ҪС��
	{
		token=1;
	}
	else if(s1[i]<s2[i])
	{
		token=-1;
	}
	return token;
}
int String::Strncmp(const char *s1,const char *s2,int n)
{ //���ַ���s1��s2��ǰn���ַ���ǰ����Ƚ�
	int i=0,token=0;
	while(i<n && s1[i]!='\0' && s2[i]!='\0')
	{
		if(s1[i]!=s2[i])
		{
			break;
		}
		++i;
	}
	if(s1[i]>s2[i])
	{
		token=1;
	}
	else if(s1[i]<s2[i])
	{
		token=-1;
	}
	return token;
}

char *String::Strcpy(char *s1,const char *s2)const
{ //��Դ�ַ���s2���Ƶ�Ŀ���ַ�����Ŀ���ַ�����s1������ָ��s1
	int i=0;
	while(s2[i]!='\0')
	{
		s1[i]=s2[i++];
	}
	s1[i]='\0';
	return s1;
}
char *String::Strncpy(char *s1,char *s2,int n)const
{ //��Դ�ַ���s2��ǰn���ַ��滻Ŀ���ַ���s1��ǰn���ַ�������ָ��s1
	int i;
	int token=1;
	if(Strlen(s1)<n)
	{
		token=0;
	}
	for(i=0;i<n;++i)
	{
		s1[i]=s2[i];
	}
	if(token==0)
	{
		s1[i]='\0';
	}
	return s1;
}

char *String::Strcat(char *s1,char *s2)const
{
	int i=Strlen(s1); //�ַ���s1�Ľ���������
	int j=0; //�ַ���s2������
	while(s2[j]!='\0')
	{
		s1[i++]=s2[j++];
	}
	s1[i]='\0';
	return s1;
}
char *String::Strncat(char *s1,char *s2,int n)const
{
	int i=Strlen(s1);
	int j=0;
	while(j<n && s2[j]!='\0')
	{
		s1[i++]=s2[j++];
	}
	s1[i]='\0';
	return s1;
}

String &String::Strupr(String &s)
{
	for(int i=0;i<s.Size();++i)
	{
		if(s.str[i]>96 && s.str[i]<123) //Сд��ĸ��ASCII��
		{
			s.str[i]-=32; //��32���Ǵ�д��ĸ��ASCII��
		}
	}
	return s;
}

String &String::Strlwr(String& s)
{
	for(int i=0;i<s.Size();++i)
	{
		if(s.str[i]>64 && s.str[i]<91)
		{
			s.str[i]+=32;
		}
	}
	return s;
}

String &String::operator=(const char *c) //ת����ֵ���മ=C��
{
	delete []str;
	int len = Strlen(c);
	str = new char[len + 1];
	if (str==0)
	{
		cout << "operator=:overflow!";
		exit(1);
	}
	Strcpy(str,c);
	size = len;
	return *this;
}
ostream &operator<<(ostream &ostr,const String &s)
{
	ostr << s.str;
	return ostr;
}
istream &operator>>(istream &istr,String &s)
{
	char buf[80]; //��������һ���������80���ַ�
	cin.get(buf,80); //�Ӽ�������1���ַ������뻺����
	cin.get(); //������뻺����
	s = buf;
	return istr;
}
String String::operator+(const String &s) const //�മ+�മ
{
	String w; //�´�
	delete[]w.str;
	w.size = size + s.size;
	w.str = new char[w.size + 1];
	Strcpy(w.str,str); //����Ԫ�е�C�����Ƶ��´�
	Strcat(w.str,s.str); //����Ԫ�е�C�����ӵ��´��е�C��
	return w;
}
String String::operator+(const char *c) const //�മ+C��
{
	String w(c); //ת�����죬�����മw
	w = *this + w; //�മ+�മ�͸��Ƹ�ֵ
	return w;  //���ظ�ֵ����മ
}
String operator+(const char *c,const String &s) //������id������һ���മ
{
	String w(c); //����ת�����죬�����മw
	w = w + s; //���á��മ+�മ���͸��Ƹ�ֵ
	return w;
}
String &String::Insert(int id,const String &s) //�Ӵ�����
{
	String old(*this); //�������ö���
	str = new char[size + s.size + 1]; //���·�����ö���Ŀռ�
	if (str == 0)
	{
		cout << "overflow!";
		exit(1);
	}
	Strcpy(str,old.str); //ȡ��ԭ���ö����ֵ
	Strcpy(old.str,str + id); //�������ö�����Ҫ�ƶ����Ӵ�
	Strcpy(str + id,s.str); //�ڲ���λ�ø���Ҫ������Ӵ�
	Strcat(str,old.str); //���������ƶ��Ӵ����ӵ����ö���
	size = size + s.size;
	return *this;
}
String &String::Insert(int id,const char *c) //������id������C��
{
	String w(c); //ת�����������മ
	Insert(id,w); //�����മ���뺯��
	return *this;
}
String &String::Erase(int id,int num) //ɾ���Ӵ�
{
	if (size - id < num)
		num = size - id;
	String old(str + id + num);
	Strcpy(str + id,old.str);
	old = str;
	*this = old;
	return *this;
}
String String::SubStr(int id,int num) const //ȡ�Ӵ�
{
	if (size - id < num)
		num = size - id;
	String w(str + id);
	w.Erase(num,w.size - num);
	return w;
}
int String::FindFirstOf(char ch,int id)const //��id��ʼ����ch�״γ��ֵ�λ��
{
	for (int i = id; str[i] != '\0'; ++i)
		if (str[i] == ch)
			return i;
	return -1;
}
int String::FindFirstOf(const String &x,int id) const
{
	char firstch = x.str[0],lastch = x.str[x.size - 1];
	int firstid = FindFirstOf(firstch,id);
	int lastid = firstid + x.size - 1;
	while (firstid != -1 && lastid < size)
	{
		if (str[lastid] == lastch)
		{
			if (SubStr(firstid,x.size) == x)
				return firstid;
		}
		id = firstid + 1;
		firstid = FindFirstOf(firstch,id);
		lastid = firstid + x.size - 1;
	}
	return -1;
}
#endif