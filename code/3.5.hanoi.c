#include <stdio.h>
#include <stdlib.h>

void move(char x, int n, char z)
{
    printf("Move %d From %c To %c\n", n, x, z);
}

void hanoi(int n, char x, char y, char z)
{
    if(n==1)
        move(x, 1, z);
    else
    {
        hanoi(n-1, x, z, y);
        move(x, n, z);
        hanoi(n-1, y, x, z);
    }
}

int main()
{
    int n = 10;
    char x = 'X';
    char y = 'Y';
    char z = 'Z';
    hanoi(n, x, y, z);
}
