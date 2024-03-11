#ifndef DATECLASS_H
#define DATECLASS_H
#include<iostream>
using namespace std;
class Date
{
	int year,month,day;
	static const int NoLeapyear[]; //��̬���ݳ�Ա
	bool Leapyear(int y)const{ return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0); }
public:
	Date():year(1),month(1),day(1) {} //Ĭ�Ϲ���
	Date(int y,int m,int d):year(y),month(m),day(d) {}
	explicit Date(int ndays) { *this = ndays; } //ת������
	Date &operator=(int ndays); //ת����ֵ
	operator int() const; //��Աת��
	bool Leapyear()const{ return Leapyear(year); }
	friend istream &operator>>(istream &istr,Date &dt);
	friend ostream &operator<<(ostream &ostr,const Date &dt);
	Date &operator++(); //ǰ++
	Date operator++(int); //��++
	Date &operator--(); //ǰ--
	Date operator--(int); //��--
	void SetYear(int y) { year = y; } //��Ա��ֵ
	void SetMonth(int m) { month = m; }
	void SetDay(int d) { day = d; }
	int GetYear()const{ return year; } //��Աȡֵ
	int GetMonth()const{ return month; }
	int GetDay()const{ return day; }
};
const int Date::NoLeapyear[] = { 31,28,31,30,31,30,31,31,30,31.30,31 }; //ƽ����

Date &Date::operator=(int ndays) //ת����ֵ
{
	int n;
	year = month = day = 0;
	year = 1;
	n = Leapyear(year) ? 366: 365; //�Թ�Ԫ1�꿪ʼ�����������п۳������������ÿ�۳�1�꣬��ݼ�1.
	while (ndays > n)
	{
		ndays -= n;
		++year;
		n = Leapyear(year) ? 366: 365;
	}
	month = 1; //��1�¿�ʼ�����������п۳����µ�������ÿ�۳�1�£��·ݼ�1.
	n = NoLeapyear[month - 1];
	while (ndays > n)
	{
		ndays -= n;
		++month;
		n = NoLeapyear[month - 1];
		if (month == 2 && Leapyear(year))
			++n;
	}
	day = ndays; //ʣ�������������
	return *this;
}

Date::operator int() const //��Աת��
{
	int i;
	int ndays = 0;
	for (i = 1; i < year; ++i) //�ӹ�Ԫ1�����ۼ�ÿһ�����������
		ndays += Leapyear(i) ? 366: 365;
	for (i = 1; i < month; ++i) //��������������ݣ���1�����ۼ�ÿ�����µ��������������2�£���Ҫ�ж��Ƿ����꣬�Ծ����Ƿ��ټ�һ��
		ndays += NoLeapyear[i - 1];
	if (month > 2 && Leapyear(year))
		++ndays;
	ndays += day; //���������·�����
	return ndays; //���ؽ��
}

ostream &operator<<(ostream &ostr,const Date &dt) //���������
{
	ostr << dt.year << '-' << dt.month << '-' << dt.day;
	return ostr;
}
istream &operator>>(istream &istr,Date &dt) //��ȡ������
{
	istr >> dt.year >> dt.month >> dt.day;
	return istr;
}

Date &Date::operator++() //ǰ++
{
	int ndays = *this; //���ó�Աת���������ö���ת��Ϊ����
	++ndays; //������1
	*this = ndays; //����ת����ֵ��������ת����ֵ�����ö���
	return *this; //���ص��ö��������
}
Date Date::operator++(int) //��++
{
	Date t(*this); //�������ö����ԭֵ
	int ndays = *this; //���ó�Աת���������ö���ת��Ϊ����
	++ndays; //������1
	*this = ndays; //����ת����ֵ��������ת����ֵ�����ö���
	return t; //���ص��ö���ı���ֵ
}
Date &Date::operator--() //ǰ--
{
	int ndays = *this;
	--ndays;
	*this = ndays;
	return *this;
}
Date Date::operator--(int) //��--
{
	Date t(*this);
	int ndays = *this;
	--ndays;
	*this = ndays;
	return t;
}
#endif