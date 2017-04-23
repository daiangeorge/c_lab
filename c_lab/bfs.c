#include <stdio.h>
#include <stdlib.h>

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

#define QUEUE_MAX_SIZE 100

typedef struct
{
    int n;      // numar de varfuri
    int **m;    // matricea de adiacenta
} Graf;     // structura pentru memorarea grafului prin matrice de adiacenta

enum { NEVIZITAT, VIZITAT };

/// TODO: de definit o structura Coada si
typedef struct
{
    int array[QUEUE_MAX_SIZE];
    int capacity;
    int head;
    int size;
    int tail;
} Coada;

int goala(Coada c)
{
    return c.size == 0;
}

void enqueue(int key, Coada *my_queue)
{
    if (my_queue->tail >= my_queue->capacity)
        my_queue->tail = 0;
    if (my_queue->tail == my_queue->head && my_queue->size != 0)
    {
        printf("OVERFLOW!\n");
        return;
    }
    my_queue->array[my_queue->tail++] = key;
    my_queue->size++;

}


int dequeue(Coada *my_queue)
{
    if (my_queue->head >= my_queue->capacity)
        my_queue->head = 0;
    if (my_queue->head != my_queue->tail)
    {
        int x = my_queue->array[my_queue->head++];
        my_queue->size--;
        return x;
    }
    return -1;
}

void initializeaza(Coada *c)
{
    int i;
    c->size = 0;
    c->head = 0;
    c->tail = 0;
    c->capacity = QUEUE_MAX_SIZE;
    for (i = 0; i < c->capacity; i++)
        c->array[i] = 0;
}


void printErr()
{
    printf("Memorie insuficienta!\n");
    exit(1);
}

void afiseaza_coada(Coada my_queue)
{
    if (my_queue.head < my_queue.tail)
    {
        int i;
        for (i= my_queue.head; i < my_queue.tail; i++)
        {
            printf("%d ", my_queue.array[i]);
        }
    }
    else
    {
        int i = my_queue.head;
        while(i<=my_queue.capacity-1)
        {
            printf("%d ", my_queue.array[i]);
            i++;
        }
        i = 0;
        while (i<my_queue.tail)
        {
            printf("%d ", my_queue.array[i]);
            i++;
        }

    }
    printf("\n\n");


}

void bfs( Graf G, int nodSursa )
{
    int* vizitate; /* pentru marcarea nodurilor vizitate */
    vizitate = calloc(G.n, sizeof(int));
    if (vizitate == NULL) printErr();

    Coada Q; /* coada nodurilor - intregi */

    int i, v, w; /* noduri */

    initializeaza( &Q );
    for ( i = 0; i < G.n; i++ ) /* marcam toate nodurile ca nevizitate */
        vizitate[ i ] = NEVIZITAT;
    vizitate[ nodSursa ] = VIZITAT; /* marcam nodul sursa ca vizitat */
//	procesam informatia pt nodSursa;
    enqueue(nodSursa, &Q);
    // nodSursa va fi primul nod scos din coada
    while(!goala(Q))
    {
        v = dequeue(&Q);
        for (w = 0; w < G.n; w++)
        {
            if (G.m[w][v] == 1)
            {
                if (vizitate[w] == NEVIZITAT)
                {
                    vizitate[w] = VIZITAT;
                    enqueue(w, &Q);
                    afiseaza_coada(Q);
                }
            }
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
        pG->m[v][w] = pG->m[w][v] = 1;
    }
}

void afiseaza_graf(Graf g)
{
    int i, j;
    for (i = 0; i < g.n; i++)
    {
        for (j = 0; j < g.n; j++)
            printf("%d ", g.m[i][j]);
        printf("\n");
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
    afiseaza_graf(G);
    fclose(f);

    int v;
    printf("Numarul de noduri: %d. \nDati nodul sursa: ", G.n);
    scanf("%d", &v);

    bfs(G, v);
    return 0;
}
