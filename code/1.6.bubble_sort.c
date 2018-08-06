#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int* arr,int n);

int main()
{
    int arr[10]; //={9,8,7,6,5,4,3,2,1};
    int n,i;

    printf("Please input 10 number:\n");
    for(i=0;i<10;i++)
    {
        scanf("%d",&arr[i]);
    }
    n=sizeof(arr)/sizeof(arr[0]);
    bubble_sort(arr,n);
    for(i=0;i<10;i++)
    {
        printf("%d ",arr[i]);
    }

    return 0;
}

void bubble_sort(int *arr,int n)
{
    int i,j;
    int tmp;

    for(i=n-1;i>=1;i--)
    {
        for(j=0;j<i;j++)
        {
            if(arr[j]>arr[j+1])
            {
                tmp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=tmp;
            }
        }
    }
}
