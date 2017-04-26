#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*****************************************************
 *   Citirea datelor despre un graf dintr-un fisier
 *     cu reprezentarea grafului prin liste de adiacenta dinamice.
 *       In fisier se da numarul n de varfuri ale grafului,
 *         apoi muchiile sub forma de perechi i j, cu 0<=i,j<n
 *           (i si j reprezinta indicii varfurilor conectate prin
 *              arc (sau muchie)).
 *                Graful se parcurge DFS si se scriu la consola
 *                  nodurile în ordinea parcurgerii.
 *                  ******************************************************/

int T[100];

typedef struct nod
{
	int val;
	struct nod *next;
} NodeT;

typedef struct
{
	int n;      // numar de varfuri
	NodeT **t;    // tabloul de liste (va fi alocat dinamic)
	int *d;
	int *f;
	int *color;
} Graf;     // structura pentru memorarea grafului prin liste de adiacenta dinamice

enum
{
	ALB, GRI, NEGRU
};

void push(NodeT **first, int val)
{

	NodeT *el = (NodeT *) malloc(sizeof(NodeT));
	el->val = val;
	el->next = (*first);
	*(first) = el;
}

void printErr()
{
	printf("Memorie insuficienta!\n");
	exit(1);
}

void dfs_visit_color(int v, Graf *G, int *time)
{
	time++;
	G->d[v] = time;
	G->color[v] = GRI;
	NodeT *p = G->t[v];
	int w;
	printf("%d ", v);
	while (p != NULL)
	{
		w = p->val;
		if (G->color[w] == ALB)
		{
			T[w] = v;
			dfs_visit_color(w, G, time);
		}
		p = p->next;
	}
	G->color[v] = NEGRU;
	time++;
	G->f[v] = time;
}

void dfs_color(Graf *G)
{

	int time = 0, i;

	for (i = 0; i < G->n; i++)
	{
		if (G->color[i] == ALB)
		{
			dfs_visit_color(i, G, &time);
		}
	}
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

	pG->d = (int *) calloc(pG->n, sizeof(int));
	pG->f = (int *) calloc(pG->n, sizeof(int));
	pG->color = (int *) calloc(pG->n, sizeof(int));

	int v, w;
	while (fscanf(f, "%d%d", &v, &w) == 2)
	{

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

	printf("\n DFS color: ");
	dfs_color(&G);

	free(G.color);
	free(G.d);
	free(G.f);

	int i;
	for (i = 0; i < G.n; i++)
	{
		free(G.t[i]);
	}

	free(G.t);

	return 0;
}

