#include <stdio.h>
#include <stdlib.h>
#define M 8 //dimensiunea tabelei de dispersie


typedef struct cell
{
    int val;
    struct cell *next;
} NodeT;

int hFunction(int value)
{
    return value % M;
}

NodeT* FindElement(NodeT* hTable[M], int Key)
{
    NodeT *p = hTable[hFunction(Key)];
    while (p)
    {
        if (p->val == Key)
            return p;
        p = p->next;
    }
    return NULL;
}

void insertElement(NodeT* hTable[M], int key)
{
    int x = hFunction(key);
    NodeT *p=(NodeT*)malloc(sizeof(NodeT));
    p->val=key;
    p->next=hTable[x];
    hTable[x]=p;
}

void deleteKey(NodeT* hTable[M], int key)
{
    int x = hFunction(key);
    NodeT *p = hTable[x];
    NodeT *element = FindElement(hTable, key);
    if (element == NULL)
        return;
    if (element->val == p->val)
    {
        if (p->next == NULL)
            hTable[x] = NULL;
        else
        {
            p->val = p->next->val;
            element = p->next;
            p->next = p->next->next;
            free(element);
        }
    }
    else
    {
        while (p->next != NULL && p->next->val != key)
            p = p->next;
        if (p->next == NULL)
            return;
        p->next = p->next->next;
        free(element);
    }
}

//afisarea tuturor elmentelor din tebela de dispersie
void showAll(NodeT* hTable[M])
{
    int i;
    for(i = 0; i < M; i++)
    {
        printf(" %d :",i);
        //verificam daca la slotul i am adaugat ceva
        if(hTable[i] != NULL)
        {

            NodeT *p;
            p = hTable[i];
            while (p != NULL)
            {
                printf(" %d ",p->val);
                p = p->next;
            }
        }
        printf("\n");
    }
    printf("\n");
}


int main()
{

    // tabela de dispersie
    NodeT* hTable[M];
    int i, n,x;
    //initializam tabelul nostru de dispersie
    for(i = 0; i < M; i++)
    {
        hTable[i] = NULL;
    }

    //inseram un nou element in tabel
    insertElement(hTable, 36);
    insertElement(hTable, 18);
    insertElement(hTable, 6);
    insertElement(hTable, 43);
    insertElement(hTable, 72);

    insertElement(hTable, 10);
    insertElement(hTable, 5);
    insertElement(hTable, 15);

    //afisam toate elementele
    showAll(hTable);
    //stergere
    deleteKey(hTable, 10);
    deleteKey(hTable, 10);
    deleteKey(hTable, 15);
    //afisam toate elementele din tabel din nou
    showAll(hTable);
    return 0;
}

