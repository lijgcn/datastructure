#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef int Status;

#define MAXSIZE 500

typedef struct Component{
    ElemType data;
    int cur;
}component,SLinkList[MAXSIZE];

void InitSpace_SL(SLinkList space)
{
    int i;
    for(i=0;i<MAXSIZE-1;i++)
    {
        space[i].cur=i+1;
    }
    space[MAXSIZE-1].cur=0;
}

int Malloc_SL(SLinkList space)
{
    int i;
    i=space[0].cur;
    if(space[0].cur)
        space[0].cur=space[i].cur;
    return i;
}

void Free_SL(SLinkList space,int k)
{
    space[k].cur=space[0].cur;
    space[0].cur=k;
}

void LocateElem_SL(SLinkList space,int S,ElemType e)
{
    int i;
    i=space[S].cur;
    while(i && space[i].data!=e)
        i=space[i].cur;
    if(space[i].data==e)
        printf("found in %d.",i);
    else
        printf("not found.");
}

void difference(SLinkList space,int S)
{
    int r,p,k,q;
    int m,n;
    int i,j;
    int b;

    InitSpace_SL(space);
    S=Malloc_SL(space);
    r=S;
    printf("Input m & n:\n");
    scanf("%d %d",&m,&n);
    for(j=1;j<=m;j++)
    {
        i=Malloc_SL(space);
        printf("Input A[%d]:",j);
        scanf("%d",&space[i].data);
        space[r].cur=i;
        r=i;
    }
    space[r].cur=0;
    for(j=1;j<=n;j++)
    {
        printf("Input B[%d]:",j);
        scanf("%d",&b);
        p=S;
        k=space[S].cur;
        while(k!=space[r].cur && space[k].data!=b)
        {
            p=k;
            k=space[k].cur;
        }
        if(k==space[r].cur)
        {
            i=Malloc_SL(space);
            space[i].data=b;
            space[i].cur=space[r].cur;
            space[r].cur=i;
            r=i;
        }
        else
        {
            space[p].cur=space[k].cur;
            Free_SL(space,k);
            if(r==k)
                r=p;
        }
    }
    q=space[S].cur;
    while(space[q].data && space[q].cur!=0)
    {
        printf("%d\n",space[q].data);
        q=space[q].cur;

    }
    printf("%d\n",space[r].data);
    //locate
    LocateElem_SL(space,S,1);
}

int main()
{
    SLinkList space[MAXSIZE];
    int S;
    //difference
    difference(space,S);
    return 0;
}
