#include<stdio.h>
int x[100];
int solutii_totale;

int phi(int k)
{
    for(int i=0; i < k; i++)
        if(x[k] <= x[i])
            return 0;
    return 1;
}

void list(int x[], int n)
{
    for(int i=0; i<n; i++)
        printf(" %d",x[i]);
    printf("   e solutie");
    printf("\n");
    solutii_totale++;
}
void back(int k,int n, int kapa)
{
    int i;
    for(i=1; i<=n; i++)
    {
        x[k]=i;
        if(phi(k)==1)
            if(k<kapa - 1)
                back(k+1,n, kapa);
            else
                list(x,kapa);

    }
}

int main()
{
    int n = 5, k = 4;
    back(0,n, k);
    printf(" %d total solutions.\n", solutii_totale);
    return 0;
}
