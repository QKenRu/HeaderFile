#ifndef SIMULATION_H
#define SIMULATION_H
#include<iomanip>
#include<iostream>
#include"pqueue.h" //���ȼ���������ģ��
#include"queue.h" //��������ģ��
using namespace std;
class Event //�¼�����
{
	int time; //�¼�����ʱ��
	int etype; //�¼����͡�0��ʾ�����0������ʾ�ӸúŴ����뿪
public:
	Event():time(0),etype(0){} //Ĭ�Ϲ���
	Event(int t,int e):time(t),etype(e){} //һ�㹹��
	operator int()const{ return(time); } //��Աת��
	int GetTime()const{ return(time); } //��ȡ�¼�����ʱ��
	int GetEventType()const{ return(etype); } //��ȡ�¼�����
};
struct Service //�Ŷӿͻ���Ϣ�ṹ
{
	int arrivalTime; //�ͻ�����ʱ��
	int serviceTime; //����ʱ��
};
struct TellerStatus //������Ϣ�ṹ
{
	int totalCustomer; //�Ӵ��ͻ�����
	int totalService; //����ʱ������
	int totalWait; //�ͻ��ȴ�ʱ������
};
class Simulation
{
	int SimulationLength; //ģ��ʱ�䳤��
	int numTellers; //���񴰿ڸ���
	int arrivalLow,arrivalHigh; //�ͻ�������̺��ʱ����
	int serviceLow,serviceHigh; //�ͻ���̺������ʱ��
	TellerStatus t[11]; //���10�����ڣ�TellerStatus t[1]~t[10]
	Queue<Service>Q[11]; //���10�����ڶ��У�Q[1]~Q[10]
	PQueue<Event>PQ; //�¼������ȼ�������
	int GetIntertime() //��ȡ�ͻ������ʱ����
	{
		return (arrivalLow + rand() % (arrivalHigh - arrivalLow + 1));
	}
	int GetServiceTime() //��ȡ����ʱ��
	{
		return (serviceLow + rand() % (serviceHigh - serviceLow + 1));
	}
	int GetNextTeller(); //ȡ��һ�����ô���
	void Arrived(const Event &e); //����һλ�ͻ������¼�
	void Departure(const Event &s); //����һλ�ͻ��뿪�¼�
	void PrintPQueue(); //��ʾ�¼���
	void PrintQueue(); //��ʾ���ڶ���
public:
	Simulation(); //ģ����̳�ʼ��
	Simulation(int L,int nT,int aL,int aH,int sL,int sH);
	void RunSimulation(); //ִ��ģ��
	void PrintSimulationResults(); //��ʾģ�����
};
#endif