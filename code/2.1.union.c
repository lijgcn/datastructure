#include <stdio.h>
#include <stdlib.h>

int cmp(int,int*,int);

int main()
{
    int La[10]={20,21,22,23,24};
    int Lb[5]={30,21,32,33,24};
    int La_len,Lb_len;
    int i,j;

    La_len=10;
    Lb_len=5;

    for(i=0,j=0;i<Lb_len;i++)
    {
        if(cmp(Lb[i],La,La_len))
        {
            La[Lb_len+j++]=Lb[i];
        }
    }
    i=0;
    while(La[i])
    {
        printf("%d ",La[i]);
        i++;
    }
    return 0;
}

int cmp(int a,int* arr,int len)
{
    int i;
    for(i=0;i<len;i++)
    {
        if(a==*(arr+i))
            return 0;
    }
    return 1;
}
