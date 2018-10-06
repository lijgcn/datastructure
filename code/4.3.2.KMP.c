#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define TRUE 2
#define FALSE -2

#define MAXSTRLEN 255

typedef unsigned char SString[MAXSTRLEN+1];
typedef int Status;

Status StrAssign(SString T, unsigned char *chars)
{
	int i=0;
	int n;
	
	while(*(chars+i))
	{
		if(i<MAXSTRLEN)
		{
			n = i+1;
			T[n] = *(chars+i);
			i++;
		}
		else
		{
			break;
		}
	}
	T[0] = i;
	return OK;
}

Status get_next(SString T, int next[])
{
	int i = 1;
	next[1] = 0;
	int j = 0;
	printf("next[1] = 0\n");
	while(i < T[0])
	{
		if(j == 0 || T[i] == T[j])
		{
			i++;
			j++;
			next[i] = j;
			printf("next[%d] = %d\n", i, j);
		}
		else
		{
			j = next[j];
		}
	}
}

Status get_nextval(SString T, int next[])
{
	int i = 1;
	next[1] = 0;
	int j = 0;
	printf("next[1] = 0\n");
	while(i < T[0])
	{
		if(j == 0 || T[i] == T[j])
		{
			i++;
			j++;
			if(T[i] != T[j])
			{
				next[i] = j;
			}
			else
			{
				next[i] = next[j];
			}
			printf("next[%d] = %d\n", i, next[i]);
		}
		else
		{
			j = next[j];
		}
	}
	return OK;
}

int Index(SString S, SString T, int pos)
{
	int i=pos;
	int j=1;

	while(i <= S[0] && j <= T[0])
	{
		if(S[i] == T[j]) 
		{
			i++;
			j++;
		}
		else
		{
			i = i-j+2;
			j=1;
		}
	}
	if(j > T[0])
	{
		return i-T[0];
	}
	else
	{
		return 0;
	}
}

int Index_KMP(SString S, SString T, int pos)
{
	int i=pos;
	int j=1;
	int next[20];

	//get_next(T, next);
	get_nextval(T, next);
	
	while(i <= S[0] && j <= T[0])
	{
		if(j == 0 || S[i] == T[j])
		{
			i++;
			j++;
		}
		else
		{
			j = next[j];
		}
	}
	if(j > T[0])
	{
		return i-T[0];
	}
	else
	{
		return 0;
	}
}

int main()
{
	SString S;
	SString P;

	unsigned char *str1 = "acabaabaabcacaabc";
	unsigned char *str2 = "abaabcac";

	int pos, pos_kmp;

	StrAssign(S, str1);
	StrAssign(P, str2);

	pos = Index(S, P, 1);
	printf("Index position %d\n", pos);

	pos_kmp = Index_KMP(S, P, 1);
	printf("Index KMP position %d\n", pos_kmp);

	return OK;
}
