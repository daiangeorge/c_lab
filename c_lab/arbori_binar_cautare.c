#include <stdio.h>
#include <stdlib.h>


typedef struct NodeT
{
    int key;
    struct NodeT *left;
    struct NodeT *right;
} NodeT;


NodeT* insertNode(NodeT *root, int key)
{
    if (root == NULL)
    {
        NodeT *nod = (NodeT*)malloc(sizeof(NodeT));
        nod->key = key;
        nod->left = nod->right = NULL;
        return nod;
    }
    if (key < root->key)
        root->left = insertNode(root->left, key);
    else if (key > root->key)
        root->right = insertNode(root->right, key);
    return root;
}


NodeT* searchKey(NodeT *root, int key)
{
    if (root == NULL)
        return NULL;
    if (root->key == key)
        return root;
    if (key < root->key)
        return searchKey(root->left, key);
    if (key > root->key)
        return searchKey(root->right, key);
    return NULL;
}

NodeT *findMin(NodeT *root)
{
    if (root == NULL)
        return NULL;
    if (root->left != NULL)
        return findMin(root->left);
    return root;
}

NodeT *findMax(NodeT *root)
{
    if (root == NULL)
        return NULL;
    if (root->left != NULL)
        return findMax(root->right);
    return root;
}

NodeT* succesor(NodeT *root, NodeT *node)
{
    if(root == NULL) return NULL;
    if(node->right != NULL) return findMin(node->right);
    NodeT* suc = NULL;
    while(root != NULL)
    {
        if(node->key < root->key)
        {
            suc = root;
            root = root->left;
        }
        else root = root->right;
    }
    return suc;

}

NodeT* predecesor(NodeT *root, NodeT *node)
{
    if(root==NULL) return NULL;
    if (node->left!=NULL) return findMax(node->left);
    NodeT* pre=NULL;
    while(root != NULL)
    {
        if(node->key > root->key)
        {
            pre = root;
            root = root->right;
        }
        else root = root->left;
    }
    return pre;
}

NodeT *deleteKey(NodeT *root, int key)
{
    if(root == NULL) return NULL;
    if(key < root->key)
        root->left = deleteKey(root->left,key);
    else if(key>root->key)
        root->right = deleteKey(root->right,key);
    else
    {
        if((root->left == NULL) && (root->right == NULL))
        {
            free(root);
            root=NULL;
        }
        else if(root->left == NULL)
        {
            NodeT* temp=root;
            root=root->right;
            free(temp);
        }
    }
}

void inOrder(NodeT *root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

void preOrder(NodeT *root)
{
    if (root != NULL)
    {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(NodeT *root)
{
    if (root != NULL)
    {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->key);
    }
}

int main()
{

    NodeT *root = NULL;
    NodeT *p;

    int n = 11;
    int keys[] = {15, 6, 18, 17, 20, 3, 7, 2, 4, 13, 9};

    root = insertNode(root, keys[0]);

    for (int i = 1; i < n; i++)
    {
        insertNode(root, keys[i]);
    }

    printf( "\nPreorder listing\n" );
    preOrder( root);
    printf( "\nInorder listing\n" );
    inOrder( root );
    printf( "\nPostorder listing\n" );
    postOrder( root);

    int key = 2;
    p = searchKey( root, key );
    if ( p != NULL )
    {
        printf( "\nNod cu cheia = %d gasit\n", key);
        NodeT *m = findMin(p);
        printf("Minimul din subarborele care are ca radacina nodul %d este %d \n", p->key, m->key);
    }
    else
        printf( "Nodul NU a fost gasit \n" );

    NodeT *s = succesor(root, p);
    if ( s != NULL )
    {
        printf( "Nod cu cheia = %d are sucesor pe %d\n", p->key, s->key);
    }
    else
        printf( "Nodul NU are succesor !\n" );

    NodeT *q = predecesor(root, p);
    if ( q != NULL )
    {
        printf( "Nod cu cheia = %d are predecesor pe %d\n", p->key, q->key);
    }
    else
        printf( "Nodul NU are predecesor !\n" );


    key = 15;
    printf("Nodul de sters este: %d\n", key);
    root = deleteKey(root, key);
    inOrder(root);
    return 0;
}
