#include <stdio.h>
#include <stdlib.h>

int main()
{
    int La[]={3,5,8,11};
    int Lb[]={2,6,8,9,11,15,20};
    int La_len=sizeof(La)/sizeof(La[0]);
    int Lb_len=sizeof(Lb)/sizeof(Lb[0]);
    int Lc[La_len+Lb_len];
    int i=0,j=0,k=0;

    while((i<La_len)&&(j<Lb_len))
    {
        if(La[i]<=Lb[j])
            Lc[k++]=La[i++];
        else
            Lc[k++]=Lb[j++];
    }
    while(i<La_len)
    {
        Lc[k++]=La[i++];
    }
    while(j<Lb_len)
    {
        Lc[k++]=Lb[j++];
    }
    k=0;
    while(k<sizeof(Lc)/sizeof(Lc[0]))
    {
        printf("%d ",Lc[k]);
        k++;
    }
    return 0;
}
