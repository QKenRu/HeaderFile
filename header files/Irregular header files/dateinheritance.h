#ifndef DATEINHERITANCE_H
#define DATEINHERITANCE_H
#include<iostream>
using namespace std;
class Date //����
{
protected:
	int year,month,day; //�����Գ�Ա
public:
	Date():year(2002),month(12),day(13){} //Ĭ�Ϲ���
	Date(int y,int m,int d):year(y),month(m),day(d){} //һ�㹹��
	virtual void Display()const{ cout << year << '/' << month << '/' << day << endl; }
};
class NewDate:public Date //�����ࡣ������ʽ�ǹ���
{
public:
	NewDate(){}
	NewDate(int y,int m,int d):Date(y,m,d){}
	void Display()const{ cout << year << '-' << month << '-' << day << endl; }
};
#endif