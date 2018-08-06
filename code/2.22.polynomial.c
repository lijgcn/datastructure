#include <stdio.h>
#include <stdlib.h>

typedef struct term{
    float coef;
    int expn;
    struct term* next;
}term,*LinkList;

typedef LinkList polynomial;

int cmp(LinkList pa,LinkList pb)
{
    if(pa->expn > pb->expn)
        return 1;
    else if(pa->expn == pb->expn)
        return 0;
    else
        return -1;
}

int LocateElem(LinkList L,LinkList t,LinkList *q)
{
    LinkList p1=L->next;
    LinkList p2=L;
    while(p1)
    {
        if(t->expn > p1->expn)
        {
            p1=p1->next;
            p2=p2->next;
        }
        else if(t->expn == p1->expn)
        {
            *q=p1;
            return 1;
        }
        else
        {
            *q=p2;
            return 0;
        }
    }
    if(!p1)
    {
        *q=p2;
        return 0;
    }
}

int printPolyn(polynomial P)
{
    LinkList q;
    q=P->next;
    while(q)
    {
        printf("%.2f*x^%d",q->coef,q->expn);
        q=q->next;
        if(q)
            printf("+");
        else
            printf("\n");
    }
}

int CreatePolyn(polynomial P,int m)
{
    int i;
    LinkList t;
    LinkList q;
    P->next=NULL;
    printf("input coefficient,exponent:\n");
    for(i=0;i<m;i++)
    {
        t=(LinkList)malloc(sizeof(term));
        t->next=NULL;
        scanf("%f,%d",&t->coef,&t->expn);
        if(!LocateElem(P,t,&q))
        {
            t->next=q->next;
            q->next=t;
        }
        else
        {
            i--;
        }
    }
}

int AddPolyn(polynomial Pa,polynomial Pb)
{
    LinkList qa=Pa->next;
    LinkList qb=Pb->next;
    LinkList qc=Pa;
    LinkList s,s1,s2;
    float sum;

    while(qa && qb)
    {
        switch(cmp(qa,qb))
        {
            case -1:
                qc->next=qa;
                qc=qa;
                qa=qa->next;
                break;
            case 0:
                sum=qa->coef+qb->coef;
                if(sum != 0.0)
                {
                    s=qb;
                    qa->coef=sum;
                    qc->next=qa;
                    qc=qa;
                    qa=qa->next;
                    qb=qb->next;
                    free(s);
                }
                else
                {
                    s1=qa;
                    s2=qb;
                    qc->next=qa->next;
                    qa=qa->next;
                    qb=qb->next;
                    free(s1);
                    free(s2);
                }
                break;
            case 1:
                qc->next=qb;
                qc=qb;
                qb=qb->next;
                break;
        }
    }
    qc->next=qa?qa:qb;
    free(Pb);
}

int main()
{
    polynomial Pa;
    polynomial Pb;
    Pa=(LinkList)malloc(sizeof(term));
    Pb=(LinkList)malloc(sizeof(term));

    CreatePolyn(Pa,2);
    printPolyn(Pa);
    CreatePolyn(Pb,3);
    printPolyn(Pb);

    printf("Pb+Pb=");
    AddPolyn(Pa,Pb);
    printPolyn(Pa);

    return 0;
}
