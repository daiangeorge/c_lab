#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*****************************************************
  Citirea datelor despre un graf dintr-un fisier
  cu reprezentarea grafului prin liste de adiacenta dinamice.
  In fisier se da numarul n de varfuri ale grafului,
  apoi muchiile sub forma de perechi i j, cu 0<=i,j<n
  (i si j reprezinta indicii varfurilor conectate prin
   arc (sau muchie)).
  Graful se parcurge DFS (iterativ var. 1) si se scriu la consola
  nodurile în ordinea parcurgerii.
******************************************************/

int T[100];

typedef struct nod
{
    int val;
    struct nod *next;
} NodeT;

enum
{
    NEVIZITAT, VIZITAT
};

typedef struct
{
    int n;      // numar de varfuri
    NodeT **t;    // tabloul de liste (va fi alocat dinamic)
} Graf;     // structura pentru memorarea grafului prin liste de adiacenta dinamice

void push(NodeT **stiva, int val)
{
    NodeT *el = (NodeT *) malloc(sizeof(NodeT));
    el->val = val;
    el->next = (*stiva);
    *(stiva) = el;
}

/* returneaza elementul din varful stivei fara sa il stearga */
int top(NodeT *stiva)
{

    assert(stiva != NULL);

    return stiva->val;

}
/* sterge elementul din varful stivei */
void pop(NodeT **stiva)
{

    assert(stiva != NULL);

    NodeT *firstElement = (*stiva);
    *stiva = (*stiva)->next;
    free(firstElement);

}

/* returneaza 1 daca stiva este goala */
int empty(NodeT *stiva)
{
    return stiva == NULL;
}

void printErr()
{
    printf("Memorie insuficienta!\n");
    exit(1);
}

// TODO: varianta 1/2 DFS iterativ
void dfs_visit_iterativ(Graf *G, int v, int *vizitate)
{
    NodeT *stiva = NULL;
    push(&stiva, v);
    while (!empty(stiva))
    {
        v = top(stiva);
        pop(&stiva);
        if (vizitate[v] == NEVIZITAT)
        {
            vizitate[v] = VIZITAT;
            printf("%d ", v);
            int w;
            NodeT *p = G->t[v];
            while (p != NULL)
            {
                w = p->val;
                if (vizitate[w] == NEVIZITAT)
                {
                    T[w] = v;
                    push(&stiva, w);
                }
                p = p->next;
            }
        }
    }
}

void dfs(Graf *G)
{

    int *vizitate, i;
    vizitate = (int *) calloc(G->n, sizeof(int));
    if (vizitate == NULL) printErr();

    for ( i = 0; i < G->n; i++)
    {
        vizitate[i] = NEVIZITAT;
    }

    for (i = 0; i < G->n; i++)
        if (vizitate[i] == NEVIZITAT)
            dfs_visit_iterativ(G, i, vizitate);
    free(vizitate);
}

void citesteGraf(FILE *f, Graf *pG)
{

    fscanf(f, "%d", &pG->n);  // citeste nr. de varfuri

    pG->t = (NodeT **) calloc(pG->n, sizeof(NodeT *));
    if (pG->t == NULL) printErr();  // alocare esuata

    int i;
    for (i = 0; i < pG->n; i++)
    {
        pG->t[i] = NULL;
    }

    int v, w;
    while (fscanf(f, "%d%d", &v, &w) == 2)
    {
        // reprezentare cu liste de adiacenta, graf neorientat:
        push(&pG->t[w], v);
        push(&pG->t[v], w);
    }
}

int main()
{
    FILE *f = fopen("graf.txt", "r");
    if (f == NULL)
    {
        perror("graf.txt");
        exit(1);
    }
    Graf G;
    citesteGraf(f, &G);
    fclose(f);

    printf("GRAF\n");
    for(int i = 0; i < G.n; i++)
    {
        NodeT *p = G.t[i];
        while (p != NULL)
        {
            printf("%d ", p->val);
            p = p->next;
        }
        printf("\n");
    }

    printf("\n DFS iterativ varianta 1/2: ");
    dfs(&G); // output: 0 3 1 2 5 6 4
    printf("\nVector de tati: ");
    for(int i = 0; i < G.n; i++)
        printf("%d ", T[i]);
    return 0;
}
