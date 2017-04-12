/** Se cere sa implementati urmatoarele operatii pe structurile date:
 * 1. Operatiile de inserare/stergere intr-o stiva ce contine elemente intregi, implementata ca vector:
 *  a. (1p) definiti corect structura Stack, si completati implementarea functiei Stack* createStack() - initializarea
 *      corecta a campurilor structurii
 *  b. (1p) implementati void push(Stack *stiva, int key)
 *  c. (1p) implementati int pop(Stack* stiva)
 *  d. (1p) implementati functia void printStack(Stack *stiva) care afiseaza continutul stivei, incepand de la
 *      elementul din varful stivei
 * 2. Operatiile de inserare/cautare intr-o tabela de dispersie care utilizeaza inlantuirea (chaining) ca si
 * strategie de tratare a coliziunilor - dimensiunea tabelei este 7, functia de dispersie data in cod (cheile - intregi):
 *  a. (1p) definiti structura de nod de lista (NodeL) necesara
 *  b. (2p) implementati void insertHash(NodeL **HT, int key)
 *  c. (1p) implementati functia void printHash(NodeL **HT) care afiseaza continutul tabelei
 *          (cate o lista pe linie diferita)
 *  d. (1p) implementati NodeL* search(NodeL **HT, int key) - returneaza adresa nodului gasit, sau NULL daca cheia
 *         nu exista in tabela
 * **/

#include <stdio.h>
#include <stdlib.h>

#define STACK_CAPACITY 5
#define HASH_SIZE 7

typedef struct stack{
   //TODO completati aici
   int keys[STACK_CAPACITY];
   int size;
}Stack;

//P2
typedef struct nodelist{
    //TODO completati aici
    int val;
    struct nodelist *next;
}NodeL;
////


Stack* createStack(){
    Stack *stivaTest=(Stack*)malloc(sizeof(Stack));
    stivaTest->size = 0;
    //TODO completati aici
    for (int i = 0; i < STACK_CAPACITY; i++)
        stivaTest->keys[i] = 0;
    return stivaTest;
}

//P1
void push(Stack *stiva, int key){
    //TODO completati aici
    int i;
    if (stiva->size + 1 > STACK_CAPACITY) {
        printf("NU SE MAI POATE ADAUGA IN STIVA!\n");
        return;
    }
    for (i = stiva->size; i > 0; i--)
        stiva->keys[i] = stiva->keys[i - 1];
    stiva->keys[0] = key;
    stiva->size++;
}

int pop(Stack* stiva){
    //TODO completati aici
    if (stiva->size == 0)
        return -1;
    int x = stiva->keys[0];
    for (int i = 0; i < stiva->size; i++)
        stiva->keys[i] = stiva->keys[i + 1];
    stiva->size--;
    return x;
}

void push2(Stack *stiva, int key)
{
    if (stiva->size + 1 > STACK_CAPACITY){
        printf("NU SE MAI POATE ADAUGA IN STIVA!\n");
        return;
    }
    stiva->keys[stiva->size++] = key;
}

int pop2(Stack* stiva)
{
    if (stiva->size > 0) {
        stiva->size--;
        return stiva->keys[stiva->size];
    }
    return -1;
}

void printStack(Stack *stiva){
    //TODO completati aici
    for (int i = 0; i < stiva->size; i++)
        printf("%d ", stiva->keys[i]);
    printf("\n");
}

void printStack2(Stack *stiva)
{
    for (int i = stiva->size - 1; i >=0 ; i--)
        printf("%d ", stiva->keys[i]);
    printf("\n");
}

//P2
int hkey(int key){
    return key % HASH_SIZE;
}

void initHash(NodeL **HT){
    for(int i=0; i<HASH_SIZE; i++)
        HT[i] = NULL;
}

void insertHash(NodeL **HT, int key){
    //TODO completati aici
    int x = hkey(key);
    NodeL *p=(NodeL*)malloc(sizeof(NodeL));
    p->val=key;
    p->next=HT[x];
    HT[x]=p;
}

void printHash(NodeL **HT){
    //TODO completati aici
    for (int i = 0; i < HASH_SIZE; i++)
    {
        printf("[%d] = ", i);
        NodeL *p = HT[i];
        while (p != NULL)
        {
            printf("%d ", p->val);
            p = p->next;
        }
        printf("\n");
    }
}

NodeL* searchHash(NodeL **HT, int key){
    //TODO completati aici
    NodeL *p = HT[hkey(key)];
    while (p != NULL)
        if (p->val == key)
            return p;
        else p = p->next;
    return NULL;
}

int main() {

    Stack *stivaTest = createStack();
    NodeL* hashtableTest[HASH_SIZE];
    initHash(hashtableTest);

    push2(stivaTest, 3);
    push2(stivaTest, 6);
    push2(stivaTest, 9);
    push2(stivaTest, 12);
    push2(stivaTest, 15);
    push2(stivaTest, 21);

    printStack2(stivaTest);

    printf("\nAm extras %d\n", pop2(stivaTest));
    printf("Am extras %d\n", pop2(stivaTest));
    printf("Am extras %d\n", pop2(stivaTest));

    printStack2(stivaTest);

    insertHash(hashtableTest, 2);
    insertHash(hashtableTest, 9);
    insertHash(hashtableTest, 16);
    insertHash(hashtableTest, 23);
    insertHash(hashtableTest, 3);
    insertHash(hashtableTest, 4);
    insertHash(hashtableTest, 5);
    insertHash(hashtableTest, 6);

    printHash(hashtableTest);

    printf("Cautarea dupa cheia 23 returneaza %d \n", (int)searchHash(hashtableTest, 23));
    printf("Cautarea dupa cheia 30 returneaza %d \n", (int)searchHash(hashtableTest, 30));
    printf("Cautarea dupa cheia 1 returneaza %d \n", (int)searchHash(hashtableTest, 1));

    return 0;
}
