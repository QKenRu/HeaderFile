#ifndef SHAPE_H
#define SHAPE_H
#include<iostream>
using namespace std;
const double PI = 3.1415926; //�ⲿ���󣬶�������ɼ�
class Shape //�������
{
public:
	virtual double Area()const = 0; //�������ӿ�
	virtual void Output()const = 0; //�������ӿ�
};

class Triangle:public Shape //������
{
	double bottom;
	double height;
	double Area()const{ return bottom  *height / 2; }
public:
	Triangle(double b = 0,double h = 0):bottom(b),height(h){}
	~Triangle(){}
	void Output()const{ cout << Area() << endl; }
};

class Rectangle:public Shape //����
{
	double length;
	double width;
	double Area()const{ return length  *width; }
public:
	Rectangle(double l = 0,double w = 0):length(l),width(w) {}
	~Rectangle(){}
	void Output()const{ cout << Area() << endl; }
};

class Trapezoide:public Shape //����
{
	double top;
	double bottom;
	double height;
	double Area()const{ return(top + bottom)  *height / 2; }
public:
	Trapezoide(double t = 0,double b=0,double h=0):top(t),bottom(b),height(h){}
	~Trapezoide(){}
	void Output()const{ cout << Area() << endl; }
};

class Circle: public Shape //Բ��
{
	double radius;
	double Area()const{ return PI  *radius  *radius; }
public:
	Circle(double r = 0):radius(r) {}
	~Circle() {}
	void Output()const{ cout << Area() << endl; }
};
#endif