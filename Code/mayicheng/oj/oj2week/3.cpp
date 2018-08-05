#include "iostream"
#include "cmath"
#include "cstdio"
#include "cstdlib"
#include "cstring"
using namespace std;
char c[8][8] = { 0 };
char S[9] = { 0 };
int n,k;	//n���к��У�k�Ƕ�������
int sum;
int mm;//�ѷ����ӵ���Ŀ
void dfs(int a)	//a����,mm�Ƿ��˶��ٸ������� a�Ǵ�0��ʼ�� 
{
	if(mm == k)	//���ӹ���Ҳ����ͣ�� 
	{
		sum++;
		return;
	}
	if(a >= n)	//���˾�Խ���� 
	return;
	int i = 0;
	for(i = 0;i < n;i++)
	{
		if(S[i] || (c[a][i] == 1))
		continue;
		S[i] = 1;
		mm++;
		dfs(a + 1);
		mm--;
		S[i] = 0;
	}
	dfs(a + 1);
}
int main()
{
	while(1)
	{
		memset(c,0,sizeof(c));
		memset(S,0,sizeof(S));
		sum = 0;
		scanf("%d%d",&n,&k);
		if(n == -1 && k == -1)
		break;
		getchar();
		int i,j;
		for(i = 0;i < n;i++)		//��'#'��'.'�ĳ�0��1������ 
			for(j = 0;j < n;j++)
			{
				char a = getchar();
				while(a == ' ' || a == '\n')
					a = getchar();
				if(a == '#')
				c[i][j] = 0;
				if(a == '.')
				c[i][j] = 1;
			}
		dfs(0);
		printf("%d\n",sum);	
	}
}
