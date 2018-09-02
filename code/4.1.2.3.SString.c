#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define TRUE 2
#define FALSE 0

#define MAXSTRLEN 255

typedef unsigned char SString[MAXSTRLEN+1];
typedef int Status;


void PrintSS(SString S)
{
	int i=1;
	int total = S[0];
	printf("total=%d\n", total);
	while(i<=total)
	{
		printf("%c", S[i]);
		i++;
	}
	printf("\n");
}

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

int StrCompare(SString S, SString T)
{
	int i=1;
	if(S[0]>0 && T[0]>0)
	{
		while(i<=S[0] && i<=T[0])
		{
			if(S[i] > T[i])
			{
				return 11;
			}
			else if(S[i] < T[i])
			{
				return -11;
			}
			else
			{
				i++;
			}
		}
		if(S[0]>T[0])
		{
			return 11;
		}
		else if(S[0]<T[0])
		{
			return -11;
		}
		else
		{
			return 10; 
		}
	}
	else
	{
		return ERROR;
	}
}

int StrLength(SString S)
{
	int len=0;
	len = S[0];
	return len;
}

Status StrConcat(SString T, SString S1, SString S2)
{
	int i, j;
	int uncut;
	if(S1[0]+S2[0] <= MAXSTRLEN)
	{
		for(i=1; i<=S1[0]; i++)
		{
			T[i] = S1[i];
		}
		for(j=1; j<=S2[0]; j++)
		{
			T[S1[0]+j] = S2[j];
		}
		T[0] = S1[0] + S2[0];
		uncut = TRUE;
	}
	else if(S1[0] < MAXSTRLEN)
	{
		for(i=1; i<=S1[0]; i++)
		{
			T[i] = S1[i];
		}
		for(j=1; j<=MAXSTRLEN-S1[0]; j++)
		{
			T[S1[0]+j] = S2[j];
		}
		T[0] = MAXSTRLEN;
		uncut = FALSE;
	}
	else
	{
		for(i=1; i<=MAXSTRLEN; i++)
		{
			T[i] = S1[i];
		}
		T[0] = MAXSTRLEN;
		uncut = FALSE;
	}
	return uncut;
}

Status SubString(SString Sub, SString S, int pos, int len)
{
	int i;
	if(pos<1 || pos>S[0] || len<0 || len>S[0]-pos+1)
	{
		return ERROR;
	}
	for(i=1; i<=len; i++)
	{
		Sub[i] = S[i+pos-1];
	}
	Sub[0] = len;
	return OK;
}

int Index(SString S, SString T, int pos)
{
	int i, n, m;
	SString sub;
	int crs;

	if(pos>0)
	{
		n = S[0];
		m = T[0];
		i = pos;
		while(i <= n-m+1)
		{
			SubString(sub, S, i, m);
			crs = StrCompare(sub, T);
			if(crs == 10)
			{
				return i;	
			}
			else
			{
				i++;
			}
		}
	}
	return ERROR;
}

int main()
{
	SString SS1;
	SString SS2;
	SString SSc;
	SString sSS;
	SString SSi;

	unsigned char *str1 = "abcdefgh";	
	unsigned char *str2 = "efg";

	int sl1, sl2;
	int max;
	int index;

	StrAssign(SS1, str1);	
	StrAssign(SS2, str2);
	
	PrintSS(SS1);	
	PrintSS(SS2);

	sl1 = StrLength(SS1);
	sl2 = StrLength(SS2);
	printf("sl1=%d\nsl2=%d\n", sl1, sl2);

	max = StrCompare(SS1, SS2);
	printf("max=%d\n", max);

	StrConcat(SSc, SS1, SS2);
	PrintSS(SSc);

	SubString(sSS, SS1, 2, 5);
	PrintSS(sSS);

	StrAssign(SSi, "fg");
	index = Index(SS1, SSi, 1);
	printf("index=%d\n", index);

	return OK;
}
