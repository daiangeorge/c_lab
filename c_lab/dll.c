#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
    int key;
    struct node *next;
    struct node *prev;
} NodeDL;

struct list_header
{
    NodeDL *first;
    NodeDL *last;
};

NodeDL *create(int key)
{
    NodeDL *p=(NodeDL*)malloc(sizeof(NodeDL));
    p->key=key;
    p->next=NULL;
    p->prev=NULL;
}
void print_forward(struct list_header L)
{
    NodeDL *p;
    p=L.first;
    while(p!=NULL)
    {
        printf("%d ",p->key);
        p=p->next;
    }
    printf("\n");
}

void print_backward(struct list_header L)
{
    NodeDL *p;
    p=L.last;
    while(p!=NULL)
    {
        printf("%d ",p->key);
        p=p->prev;
    }
    printf("\n");
}

NodeDL *search(struct list_header L, int givenKey)
{
    NodeDL*p;
    p=L.first;
    while((p!=NULL)&&(p->key!=givenKey))
    {
        p=p->next;
    }
    if(p==NULL)
        return NULL;
    else
        return p;
}


void insert_first(struct list_header *L, int givenKey)
{
    NodeDL *p=create(givenKey);
    if((*L).first==NULL)
        (*L).first=(*L).last=p;
    else
    {
        p->next=(*L).first;
        (*L).first->prev=p;
        p->prev=NULL;
        (*L).first=p;
    }

}

void insert_last(struct list_header *L, int givenKey)
{
    NodeDL *p=create(givenKey);
    if((*L).first==NULL)
        (*L).first=(*L).last=p;
    else
    {
        (*L).last->next=p;
        p->prev=(*L).last;
        p->next=NULL;
        (*L).last=p;

    }
}

void insert_after_key(struct list_header *L, int afterKey, int givenKey)
{
    NodeDL *p=(*L).first,*q=create(givenKey);
    while((p!=NULL)&&(p->key!=givenKey))
    {
        p=p->next;
    }
    if(p!=NULL)
    {
        if(p!=(*L).last)
        {
            q->next=p->next;
            p->next->prev=q;
            p->next=q;
            q->prev=p;
        }
        else
        {

            p->next=q;
            q->prev=p;
            (*L).last=q;
        }
    }
}

void delete_first(struct list_header *L)
{
    NodeDL *p;
    if((*L).first!=NULL)
    {
        p=(*L).first;
        (*L).first=(*L).first->next;
        (*L).first->prev=NULL;
        p->next=NULL;
        free(p);
    }
}

void delete_last(struct list_header *L)
{
    NodeDL *p;
    if((*L).last!=NULL)
    {
        p=(*L).last;
        p->prev->next=NULL;
        (*L).last=p->prev;
        p->prev=NULL;
        free(p);
    }
}

void delete_key(struct list_header *L, int givenKey)
{
    NodeDL *p=(*L).first;
    if((*L).first->key==givenKey)
        delete_first(L);
    else if((*L).last->key==givenKey)
        delete_last(L);
    else
    {
        while((p!=NULL)&&(p->key!=givenKey))
        {
            p=p->next;
        }
        if(p!=NULL)
        {
            p->prev->next=p->next;
            p->next->prev=p->prev;
            p->next=NULL;
            p->prev=NULL;
            free(p);
        }
    }


}


int main()
{
    /* initialize list to empty list */
    struct list_header L = {NULL, NULL};

    /* test insertion operations */
    /* insert some elements at the beginning */
    insert_first(&L, 3);
    insert_first(&L, 4);
    insert_first(&L, 2);
    insert_first(&L, 1);

    /* ... and some at the end */
    insert_last(&L, 6);
    insert_last(&L, 8);

    /* print list contents */
    print_forward(L); // 1 2 4 3 6 8
    print_backward(L); // 8 6 3 4 2 1

    /* test search operation */
    //search for two distinct keys...
    int toSearch = 2;
    NodeDL *foundNode = search(L, toSearch);
    if (foundNode == NULL)
    {
        printf("Node %d NOT found!\n", toSearch);
    }
    else
    {
        printf("Node %d found!\n", foundNode->key);
    }

    toSearch = 9;
    foundNode = search(L, toSearch);
    if (foundNode == NULL)
    {
        printf("Node %d NOT found!\n", toSearch);
    }
    else
    {
        printf("Node %d found!\n", foundNode->key);
    }


    /* test deletions */
    delete_first(&L);
    delete_last(&L);
    delete_key(&L, 4);
    delete_key(&L, 15);

    /* print list contents */
    print_forward(L); // 2 3 6
    print_backward(L); // 6 3 2

    delete_key(&L, 2);
    delete_key(&L, 6);

    /* print list contents */
    print_forward(L); // 3
    print_backward(L); // 3

    return 0;
}
