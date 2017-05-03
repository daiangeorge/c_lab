#include<stdio.h>
int x[100];

int phi(int k)
{
    for(int i=0; i<k; i++)
        if(x[k]==x[i])
            return 0;
    return 1;
}

void list(int x[], int n)
{
    for(int i=0; i<n; i++)
        printf(" %d",x[i]);
    printf("   e solutie");
    printf("\n");
}
void back(int k,int n)
{
    int i;
    for(i=1; i<=n; i++)
    {
        x[k]=i;
        for(int j=0; j<=k; j++)
            printf(" %d",x[j]);
        printf("\n");
        if(phi(k)==1)
            if(k<n-1)
                back(k+1,n);
            else
                list(x,n);

    }
}

int main()
{
    int n;
    printf("n=");
    scanf("%d", &n);
    back(0,n);
    return 0;
}
