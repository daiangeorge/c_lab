#include <stdio.h>
#include <stdlib.h>
int *dist,*T;
/*****************************************************
  Citirea datelor despre un graf dintr-un fisier
  cu reprezentarea grafului prin liste de adiacenta dinamice.
  In fisier se da numarul n de varfuri ale grafului,
  apoi muchiile sub forma de perechi i j, cu 0<=i,j<n
  (i si j reprezinta indicii varfurilor conectate prin
   arc (sau muchie)).
  Graful se parcurge BFS si se scriu într-un fisier
  nodurile în ordinea parcurgerii.
******************************************************/

typedef struct nod
{
    int key;
    struct nod* next;
} NodeT;

typedef struct
{
    int n;      // numar de varfuri
    NodeT* *t;    // tabloul de liste (va fi alocat dinamic)
} Graf;     // structura pentru memorarea grafului prin liste de adiacenta dinamice

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
        NodeT *crt = G.t[v];
        while(crt!=NULL)
        {
            w=crt->key;
            if ( vizitate[ w ] == NEVIZITAT )
            {
                vizitate[ w ] = VIZITAT;
                dist[w]=dist[v]+1;
                T[w]=v;
                enqueue( Q,w );
                afisare(Q);
            }
            crt=crt->next;
        }
    }
}
void citesteGraf(FILE* f, Graf* pG)
{
    fscanf(f, "%d", &pG->n);    // citeste nr. de varfuri

    // Alocam dinamic tabloul de liste de adiacenta de dimensiune n:
    pG->t = calloc(pG->n, sizeof(NodeT*));
    if (pG->t == NULL) printErr();  // alocare esuata

    int i;
    for (i=0; i<pG->n; i++)
    {
        // initializam (liste vide)
        pG->t[i] = NULL;
    }

    int v, w;
    // citeste pe rand perechi (v, w) si memoreaza arcul/muchia in listele de adiacenta:
    while (fscanf(f, "%d%d", &v, &w) == 2)
    {
        /// TODO: memoreaza arcul/muchia in listele de adiacenta
        NodeT *p=(NodeT*)malloc(sizeof(NodeT));
        p->key=w;
        p->next=pG->t[v];
        pG->t[v]=p;
    }
}

int main()
{
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

    int v,i;
    printf("Numarul de noduri: %d. \nDati nodul sursa: ", G.n);
    scanf("%d", &v);

    bfs(G, v);
    printf("Distanta de la nodu sursa: ");
    for(i=0; i<G.n; i++)
        printf("%d ",dist[i]);
    printf("\nVector de tati: ");
    for(i=0; i<G.n; i++)
        printf("%d ",T[i]);
    return 0;
}
