#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
/*
typedef struct tag_unimportant {
    char *name;
    int num;
} A;
void func(A **a)
{
    *a = (A *)malloc(sizeof(A));
    //*name������
	(*a)->name = (char *)calloc(sizeof(100),1); 
    strcpy((*a)->name, "Xiyou Linux Group");
    (*a)->num = 20180728;
}
int main(int argc, char *argv[])
{
    A *a;
    func(&a);	//���������⣬һ����һ�����Ĳ�����ߵ� 
    printf("%s %d\n", a->name, a->num);
    return 0;
}
*/
struct strange {			//����һ���ṹ�� 
    char a, b, c, d, e, zero;		//�ṹ����߶������ 
};

int main(int argc, char *argv[])
{
    struct strange xp[3];	//�ṹ������ 
    int characters[6] = "abcde";		//��Ȼ������󣬵�����3�ֲ²�
										//1."abcde"��һ����ַ����ַ��[0]��
										//2.����С�˴洢����[0]��[1]��
										//3.ÿ��һ��
										//ͨ��˼��char *s[6]����Ϊ���ҷ���Ӧ����2 
										//���ʱ��С�˾���s[0] ='d''c''b''a',s[1]='e''0''0''0',���涼��0 
										//������һ�£���ʵ�и�С���⣬����ǰ��գ�int *��ת�����Ҿ�ȫ���ˣ� 
    for (int i = 0; i < 6; i++) {
        *((char *)(xp + 0) + i) = characters[i];	//ƫ����ÿ�μ�һ�����ðѽṹ��xp[0]�ĸ�ֵ�� 
    }					//d c b a e 0 

    strcpy((char *)&xp[1], (char *)characters);//�ǵ���ǰд��strcpy�Ĵ��룬�����൱��ǿת��int *��Ϊ��char *��
												//d c b a e 0
    memcpy(&xp[2], characters, sizeof(struct strange));//������ڴ濽�����ܿ����ٿ����� 
    printf("%zu\n", strlen((char *)characters));

    for (int i = 0; i < 3; i++) {
        printf("%c\n", xp[i].e);		//����e 
    }
}
