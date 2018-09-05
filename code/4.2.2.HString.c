#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR -1
#define OVERFLOW -2
#define TRUE 2
#define FALSE -3

typedef int Status;
typedef struct{
	char *ch;
	int length;
}HString;

Status InitHS(HString *T)
{
	T->ch = NULL;
	T->length = 0;
}

Status StrAssign(HString *T, char *chars)
{
	int i=0, j;
	char *c;

	if(T->ch)
	{
		free(T->ch);
	}

	c = chars;
	while(*c)
	{
		i++;
		c++;
	}

	if(!i)
	{
		T->ch = NULL;
		T->length = 0;
	}
	else
	{
		if(!(T->ch = (char *)malloc(i*sizeof(char))))
		{
			exit(OVERFLOW);
		}
		for(j=0; j<i; j++)
		{
			T->ch[j] = chars[j];
		}
		T->length = i;
	}

	return OK;
}

int StrLength(HString S)
{
	return S.length;
}

int StrCompare(HString S, HString T)
{
	int i;
	for(i=0; i<S.length && i<T.length; i++)
	{
		if(S.ch[i] != T.ch[i])
		{
			return S.ch[i]-T.ch[i];
		}
	}
	return S.length-T.length;
}

Status ClearString(HString *S)
{
	if(S->ch)
	{
		free(S->ch);
		S->ch = NULL;
	}
	S->length = 0;
	return OK;
}

Status Concat(HString *T, HString S1, HString S2)
{
	int i, j;
	if(T->ch)
	{
		free(T->ch);
	}

	if(!(T->ch = (char *)malloc((S1.length + S2.length)*sizeof(char))))
	{
		exit(OVERFLOW);
	}

	for(i=0; i<S1.length; i++)
	{
		T->ch[i] = S1.ch[i];
	}
	T->length = S1.length + S2.length;
	for(j=0; i<T->length; i++, j++)
	{
		T->ch[i] = S2.ch[j];
	}
	
	return OK;
}

Status SubString(HString *Sub, HString S, int pos, int len)
{
	int i;
	if(pos<1 || pos>S.length || len<0 || len>S.length-pos+1)
	{
		return ERROR;
	}

	if(Sub->ch)
	{
		free(Sub->ch);
	}

	if(!len)
	{
		Sub->ch = NULL;
		Sub->length = 0;
	}
	else
	{
		Sub->ch = (char *)malloc(len*sizeof(char));
		for(i=0; i<len; i++, pos++)
		{
			Sub->ch[i] = S.ch[pos-1];
		}
		Sub->length = len;
	}

	return OK;
}

Status StrInsert(HString *S, int pos, HString T)
{
	int i, j;
	if(pos < 1 || pos > S->length+1)
	{
		return ERROR;
	}
	if(T.length)
	{
		if(!(S->ch = (char *)realloc(S->ch, (S->length+T.length)*sizeof(char))))
		{
			exit(OVERFLOW);
		}
		for(i=S->length-1; i>=pos-1; i--)
		{
			S->ch[i+T.length] = S->ch[i];
		}
		for(i=pos-1, j=0; j<T.length; j++, i++)
		{
			S->ch[i] = T.ch[j];
		}
		S->length += T.length;
	}

	return OK;
}

Status PrintHS(HString S)
{
	int i;
	if(S.length)
	{
		for(i=0; i<S.length; i++)
		{
			printf("%c", S.ch[i]);
		}
		printf("\nlength=%d\n", S.length);
	}
	else
	{
		printf("null\n");
	}
	return OK;
}

int main()
{
	HString hs1, hs2, hs3;
	char *chars1 = "abcdefgh";
	char *chars2 = "wxyz";
	int rs;

	InitHS(&hs1);
	StrAssign(&hs1, chars1);
	PrintHS(hs1);

	InitHS(&hs2);
	StrAssign(&hs2, chars2);
	PrintHS(hs2);

	rs = StrCompare(hs1, hs2);
	printf("rs=%d\n", rs);
	
	InitHS(&hs3);
	Concat(&hs3, hs1, hs2);
	PrintHS(hs3);
	
	ClearString(&hs3);
	SubString(&hs3, hs1, 4, 3);
	PrintHS(hs3);

	StrInsert(&hs1, 5, hs2);
	PrintHS(hs1);
	
	return OK;
}
