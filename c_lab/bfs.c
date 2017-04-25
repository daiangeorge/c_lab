#include <stdio.h>
#include <stdlib.h>
int *dist,*T;
/*****************************************************
  Citirea datelor despre un graf dintr-un fisier
  cu reprezentarea grafului prin matrice de adiacenta.
  In fisier se da numarul n de varfuri ale grafului,
  apoi muchiile sub forma de perechi i j, cu 0<=i,j<n
  (i si j reprezinta indicii varfurilor conectate prin
   arc (sau muchie)).
  Graful se parcurge BFS si se scriu într-un fisier
  nodurile în ordinea parcurgerii.
******************************************************/

typedef struct
{
    int n;      // numar de varfuri
    int **m;    // matricea de adiacenta
} Graf;     // structura pentru memorarea grafului prin matrice de adiacenta

enum { NEVIZITAT, VIZITAT };

/// TODO: de definit o structura Coada si
/// operatiile initializeaza, enqueue, dequeue, goala
typedef struct nodelist
{
    int key;
    struct nodelist *next;
} NodeL;

typedef struct queue
{
    NodeL *first;
    NodeL *last;
} Coada;

void afisare (Coada *coada)
{
    NodeL *p=coada->first;
    while(p!=NULL)
    {
        printf("%d ",p->key);
        p=p->next;
    }
    printf("\n");
}

int goala(Coada* coada)
{
    if(coada->first==NULL) return 1;
    else return 0;
}

Coada* createQueue()
{
    Coada *queueTest=(Coada*)malloc(sizeof(Coada));
    queueTest->first=NULL;
    queueTest->last=NULL;
    return queueTest;
}

void enqueue(Coada *coada, int key)
{
    NodeL *p=(NodeL*)malloc(sizeof(NodeL));
    p->key=key;
    p->next=NULL;
    if(coada->first==NULL)
    {
        coada->first=p;
        coada->last=p;
    }
    else
    {
        coada->last->next=p;
        coada->last=p;
    }
}

NodeL* dequeue(Coada *coada)
{
    if(coada->last==NULL)// nodSursa va fi primul nod scos din coada
    {
        printf("COADA ESTE GOALA!");
        return;
    }
    NodeL *q=coada->first;
    coada->first=coada->first->next;
    if(coada->first==NULL)
        coada->last=NULL;
    return q;
}

void printErr()
{
    printf("Memorie insuficienta!\n");
    exit(1);
}


void bfs( Graf G, int nodSursa )
{
    int* vizitate; /* pentru marcarea nodurilor vizitate */
    vizitate = calloc(G.n, sizeof(int));
    if (vizitate == NULL) printErr();

    Coada *Q=createQueue();

    int i, v, w; /* noduri */

    for ( i = 0; i < G.n; i++ ) /* marcam toate nodurile ca nevizitate */
        vizitate[ i ] = NEVIZITAT;
    vizitate[ nodSursa ] = VIZITAT; /* marcam nodul sursa ca vizitat */
    enqueue( Q,nodSursa);
    afisare(Q);

    while( ! goala( Q ))
    {
        v = dequeue( Q )->key; // nodSursa va fi primul nod scos din coada
        for (w=0; w<G.n; w++)
            if(G.m[v][w]==1)
                if ( vizitate[ w ] == NEVIZITAT )
                {
                    vizitate[ w ] = VIZITAT;
                    dist[w]=dist[v]+1;
                    T[w]=v;
                    enqueue( Q,w );
                    afisare(Q);
                }
    }
}

void citesteGraf(FILE* f, Graf* pG)
{
    fscanf(f, "%d", &pG->n);    // citeste nr. de varfuri

    // Alocam dinamic matricea de adiacenta:
    pG->m = calloc(pG->n, sizeof(int*));
    if (pG->m == NULL) printErr();  // alocare esuata
    int i;
    for (i=0; i<pG->n; i++)
    {
        // alocam dinamic linia i a matricii, cu n elemente intregi
        pG->m[i] = calloc(pG->n, sizeof(int));
        if (pG->m[i] == NULL) printErr();
    }

    int v, w;
    // citeste pe rand perechi (v, w) si memoreaza arcul/muchia in matricea de adiacenta:
    while (fscanf(f, "%d%d", &v, &w) == 2)
    {
        pG->m[v][w]=1;
    }
}

int main()
{
    int i;
    FILE* f = fopen("graf.txt", "r");
    if (f == NULL)
    {
        perror("graf.txt");
        exit(1);
    }
    Graf G;
    citesteGraf(f, &G);
    fclose(f);

    dist=calloc(G.n, sizeof(int));
    T=calloc(G.n, sizeof(int));

    int v;
    printf("Numarul de noduri: %d. \nDati nodul sursa: ", G.n);
    scanf("%d", &v);

    bfs(G, v);
    printf("Distante de la nodul de pornire: ");
    for(i=0; i<G.n; i++)
        printf("%d ",dist[i]);
    printf("\nVector de tati: ");
    for(i=0; i<G.n; i++)
        printf("%d ",T[i]);
    return 0;
}
