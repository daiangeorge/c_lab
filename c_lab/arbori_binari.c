#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct node_type
{
    int id; /* numele nodului */
    /* alte informatii  utile */
    struct node_type *left, *right;
} NodeT;

void fatalError( const char *msg )
{
    printf( msg );
    printf( "\n" );
    exit ( 1 );
}

void postorder( NodeT *p )
{

    if ( p != NULL )
    {
        postorder( p->left);
        postorder( p->right);
        printf("%d \n", p->id);
    }
}

void inorder( NodeT *p )
{
    if ( p != NULL )
    {
        inorder(p->left);
        printf("%d \n", p->id);
        inorder(p->right);

    }
}

int leaf_node(NodeT *node)
{
    //scrieti codul pentru calcularea numarului de frunze ale unui arbore
    if (node == NULL)
        return 0;
    if (node->left == NULL && node->right == NULL) {
        printf("%d este frunza\n", node->id);
        return 1;
    }
    return leaf_node(node->left) + leaf_node(node->right);
}

int noduri_interne(NodeT *node)
{
    //scrieti codul pentru calcularea numarului de noduri interne ale unui
    if (node == NULL)
        return 0;
    if (node->left == NULL && node->right == NULL)
        return 0;
    printf("%d ", node->id);
    return 1 + noduri_interne(node->left) + noduri_interne(node->right);
}

int max(int left, int right)
{
    return left > right ? left : right;
}

int inaltime(NodeT *node)
{
    //scrieti codul pentru calcularea inaltimii unui arbore
    if (node == NULL)
        return -1;
    return 1 + max(inaltime(node->left), inaltime(node->right));
}


void preorder( NodeT *p )
/*
 * p = nodul curent;
*/
{
    if ( p != NULL )
    {
        printf( "%d \n", p->id );
        preorder( p->left);
        preorder( p->right);
    }
}
//creaza un arbore binar prin citirea de la tastatura
NodeT *createBinTree(int branch, NodeT *parent)
{
    NodeT *p;
    int id;

    /* read node id */
    if ( branch == 0 )
        printf( "Valoarea pentru radacina [0 pt null] =" );
    else if ( branch == 1 )
        printf( "Fiul stang al nodului cu valoarea %d [0 pt null] =",
                parent->id );
    else
        printf( "Fiul drept al nodului cu valoarea %d [0 pt null] =",
                parent->id );
    scanf("%d", &id);
    if ( id == 0 )
        return NULL;
    else
    {
        /* construim nodul la care pointeaza p */
        p = ( NodeT *)malloc(sizeof( NodeT ));
        if ( p == NULL )
        {
            printf( "Nu mai avem memorie in createBinTree" );
            exit(1);
        }
        /* fill in node */
        p->id = id;
        p->left = createBinTree( 1, p );
        p->right = createBinTree( 2, p );
    }
    return p;
}
NodeT *createBinTreeFromFile(FILE* f)
{
    NodeT *p;
    int c;

    /* se citeste id-ul nodului */
    fscanf(f, "%d", &c);
    if ( c == 0 )
        return NULL; /* arbore vid, nu facem nimic */
    else /* else inclus pentru claritate */
    {
        /* construim nodul la care pointeaza p */
        p = ( NodeT *) malloc( sizeof( NodeT ));
        if ( p == NULL )
            fatalError( "Nu mai avem memorie in createBinTree" );
        /* se populeaza nodul */
        p->id = c;
        p->left = createBinTreeFromFile(f);
        p->right = createBinTreeFromFile(f);
    }
    return p;
}

NodeT *search(NodeT *root, int key)
{
    if (root == NULL)
        return NULL;
    if (root->id == key)
        return root;
    if (search(root->left, key) == NULL)
        return search(root->right, key);
    else return search(root->left, key);
}

int main()
{
    NodeT *root;
    FILE *f = fopen("ArboriBinari.txt", "r");
    if (!f)
    {
        printf("Nu se poate deschide fisierul ArboreBinar.txt\n");
        return -1;
    }
    root = createBinTreeFromFile(f);
    fclose(f);

    printf( "\nParcurgere in preordine\n" );
    preorder( root );

    printf("\nParcurgere in postordine\n");
    postorder(root);

    printf("\nParcurgere in inorder\n");
    inorder(root);

    int nr_frunze = leaf_node(root);
    printf("Numarul de frunze este %d\n", nr_frunze);//3

    printf("Noduri interne = %d \n", noduri_interne(root));//5

    printf("Inaltimea arborelui = %d \n", inaltime(root)); //3

    NodeT *found = search(root, 1);
    if (found == NULL)
        printf("Nu s-a gasit nodul!\n");
    else
    {
        printf("Found = %d\n", found->id);
        printf("Inaltimea nodului returnat: %d\n", inaltime(found));
    }
    return 0;
}
