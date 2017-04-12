/* Se da un vector de chei intregi, ordonat descrescator (keys[8] in main). Sa se scrie urmatoarele functii:
 * 1. Functia care insereaza intr-o lista simplu inlantuita (avand referinta doar la inceputul listei), astfel incat
 * inserand pe rand cheile din vectorul dat, lista sa fie sortata
 *      a. (2p) completati structura NodeL cu campurile necesare, si implementati functia
 *      void insertList(NodeL** first, int key) care insereaza cheia key in lista a carui
 *      prim nod este *first (conform declaratiei functiei), astfel incat sa respectati ordonarea ceruta
 * 2. Functia care afiseaza cheile din lista
 *      a. (1p) void printList(NodeL* first)
 * 3. Functia care sterge, din lista inlantuita, nodul avand o cheie data (lista ramane nemodificata daca nodul nu exista)
 *      a. (2p) implementati void delete(NodeL** first, int key)
 * 4. Functia care muta toate elementele avand chei mai mari decat key - data - din lista data de *first intr-o lista noua,
 *    si returneaza inceputul noii liste
 *      a. (2p) implementati NodeL* moveLarger(NodeL** first, int key)
 * 5. Functia care inverseaza o lista
 *      a. (2p) implementati void reverseList(NodeL **first)
 * */


#include <stdio.h>
#include <stdlib.h>

//P1
typedef struct nodelist{
    //TODO completati
}NodeL;

void insertList(NodeL** first, int key){
    //TODO completati
}

//P2
void printList(NodeL* first){
    printf("Lista: ");
    //TODO completati
    printf("\n");
}

//P3
void delete(NodeL** first, int key){
    //TODO completati
}

//P4
NodeL* moveLarger(NodeL** first, int key){
    //TODO completati
    return NULL;
}

//P5
void reverseList(NodeL **first){
    //TODO completati
}

int main() {
    int keys[8] = {31, 23, 20, 19, 16, 12, 9, 4};
    int n   = 8;
    int key = 0;

    //P1
    NodeL *first = NULL;
    for(int i=0; i<n; i++) {
        printf("Inserez nodul cu cheia %d\n", keys[i]);
        insertList(&first, keys[i]);
    }

    //P2
    printList(first);

    //P3
    key = 16;
    delete(&first, key);
    printf("Am sters cheia %d\n", key);
    printList(first);

    key = 17;
    delete(&first, key);
    printf("Am sters cheia %d\n", key);
    printList(first);

    //P4
    NodeL *largerList = moveLarger(&first, 18);
    printf("Mut elementele cu chei mai mari decat 18. Listele rezultate sunt: \n");
    printList(first);
    printList(largerList);

    reverseList(&first);
    printf("Prima lista inversata\n");
    printList(first);

    return 0;
}
