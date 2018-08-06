#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OK 2
#define TRUE 1
#define FALSE 0
#define ERROR -1
#define OVERFLOW -2

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef int status;
typedef char mazeType;

typedef struct{
    int x;
    int y;
    int flag;
}posType;

typedef struct{
    int ord;
    posType seat;
    int di;
}sElemType,elemType;

typedef struct{
    sElemType* base;
    sElemType* top;
    int stacksize;
}SqStack;

status initStack(SqStack* S)
{
    S->base=(elemType*)malloc(STACK_INIT_SIZE*sizeof(elemType));
    if(!S->base)
        exit(OVERFLOW);
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
    return OK;
}

status push(SqStack* S,elemType e)
{
    if(S->top-S->base >= S->stacksize)
    {
        S->base=(elemType*)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(elemType));
        if(!S->base)
            exit(OVERFLOW);
        S->top=S->base+S->stacksize;
        S->stacksize+=STACKINCREMENT;
    }
    *S->top++=e;
    return OK;
}

status pop(SqStack* S,elemType* e)
{
    if(S->base==S->top)
        return ERROR;
    *e=*--S->top;
    return OK;
}

status stackEmpty(SqStack S)
{
    if(S.base==S.top)
        return TRUE;
    else
        return FALSE;
}

status initMaze(char maze[5][5])
{
    int i,j;
    time_t t;

    srand((unsigned) time(&t));
    for(j=0;j<5;j++)
    {
        for(i=0;i<5;i++)
        {
            if(i==0 || j==0 || i==4 || j==4)
                maze[i][j]='#';
            else
            {
                if((rand()%500)%5==0)
                    maze[i][j]='#';
                else
                    maze[i][j]='O';
            }
            maze[1][1]=maze[3][3]='O';
            printf("%c",maze[i][j]);
            if((i+1)%5==0)
                printf("\n");
        }
    }
    return OK;
}

status pass(mazeType maze[][5],posType curpos)
{
    int m=curpos.x;
    int n=curpos.y;


    if(maze[m][n]=='O' && curpos.flag==0)
        return TRUE;
    else
        return FALSE;
}

status footPrint(posType* curpos)
{
    curpos->flag=1;
    return OK;
}

posType nextPos(posType seat,int di,SqStack S)
{
    sElemType chkelem=*(S.top-2);
    posType chkpos=chkelem.seat;
    int nextflag;

    switch(di)
    {
        case 1:
            seat.x++;
            break;
        case 2:
            seat.y++;
            break;
        case 3:
            seat.x--;
            break;
        case 4:
            seat.y--;
            break;
    }
    if(seat.x==chkpos.x && seat.y==chkpos.y)
        nextflag=1;
    else
        nextflag=0;
    posType nextpos={seat.x,seat.y,nextflag};

    return nextpos;
}

status markPrint(mazeType maze[][5],posType seat)
{
    maze[seat.x][seat.y]='#';
    return OK;
}

status mazePath(mazeType maze[][5],posType start,posType end)
{
    SqStack S;
    posType curpos=start;
    sElemType e;
    int curstep=1;
    initStack(&S);

    printf("\nSTART->");
    do
    {
        if(pass(maze,curpos))
        {
            footPrint(&curpos);
            printf("[%d,%d]->",curpos.x,curpos.y);
            sElemType e={curstep,curpos,1};
            push(&S,e);
            if(curpos.x==end.x && curpos.y==end.y)
            {
                printf("END\n");
                return TRUE;
            }
            curpos=nextPos(curpos,1,S);
            curstep++;
        }
        else
        {
            if(!stackEmpty(S))
            {
                pop(&S,&e);
                while(e.di==4 && !stackEmpty(S))
                {
                    markPrint(maze,e.seat);
                    pop(&S,&e);
                }
                if(e.di<4)
                {
                    e.di++;
                    push(&S,e);
                    curpos=nextPos(e.seat,e.di++,S);
                }
            }
        }
    }while(!stackEmpty(S));
    printf("DEAD END!\n");

    return FALSE;
}

int main()
{
    char maze[5][5];
    posType start={1,1,0};
    posType end={3,3,1};

    initMaze(maze);
    mazePath(maze,start,end);
    return 0;
}
