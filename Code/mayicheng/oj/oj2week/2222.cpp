#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "iostream"
#include <queue>
using namespace std; 
int f;
int l;
//����������
//
//push(x) ��xѹ����е�ĩ��
//
//pop() �������еĵ�һ��Ԫ��(�Ӷ�Ԫ��)��ע��˺������������κ�ֵ
//
//front() ���ص�һ��Ԫ��(�Ӷ�Ԫ��)
//
//back() �������ѹ���Ԫ��(��βԪ��)
//
//empty() ������Ϊ��ʱ������true
//
//size() ���ض��еĳ���
//
// 
//
//ʹ�÷�����
//
//ͷ�ļ���
//
//#include <queue>
// ����������
//
//1����ͨ����
//
//queue<int>q;
//2���ṹ��
//
//struct node
//{    
//   int x, y;
//};
//queue<node>q;
// 
int n[110000];		//��¼�߹�û�߹�˳���¼�����˶��� 
struct node
{
	int x;
};
queue <node> q;
int bfs()
{ 
	memset(n, 0, sizeof(n));
	while(!q.empty())	//ÿ����֮ǰ������� 
	{
		q.pop();
	}
	node m;
	m.x = l;
	n[l] = 1;
	q.push(m);
	while(!q.empty())
	{
		node a = q.front();
//		if(a.x == f)
//		return n[f];
		if(n[f])		//����У����˳� 
		return n[f];
		q.pop();
		if(a.x < 0 || a.x > 110000)
		continue; 
//	if((n[a.x + 1] == 0)&& ((a.x + 1) <= 110000))
	if(((a.x + 1) <= 110000) && (n[a.x + 1] == 0))
	{
		node next;
		n[a.x + 1] = n[a.x] + 1;
		next.x = a.x + 1;
		q.push(next);
	}
	if((n[a.x - 1] == 0)&& ((a.x - 1) >= 0))
	{
		node next;
		n[a.x - 1] = n[a.x] + 1;
		next.x = a.x - 1;
		q.push(next);
	}
	//if((n[a.x * 2] == 0 )&& ((a.x * 2) < 110000))
	if(((a.x * 2) < 110000) && (n[a.x * 2] == 0 ))
	{
		node next;
		n[a.x * 2] = n[a.x] + 1;
		next.x = a.x * 2;
		q.push(next);
	}
	}
}
int main()
{
	int a,b;
	while(scanf("%d%d",&a,&b) != EOF)
	{
		l = a;
		f = b;
		printf("%d\n",bfs() - 1);
	}
	return 0; 
}
