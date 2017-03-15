#include <stdlib.h>
#include <stdio.h>

#define CAPACITY 7

struct queue
{
    int array[CAPACITY];
    int capacity;
    int head;
    int size;
    int tail;
};

void enqueue(struct queue *my_queue, int key)
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


int dequeue(struct queue *my_queue)
{
    if (my_queue->head >= my_queue->capacity)
        my_queue->head = 0;
    if (my_queue->head != my_queue->tail)
    {
        int x = my_queue->array[my_queue->head++];
        return x;
    }
    return -1;
}

void print_queue_contents(struct queue my_queue)
{
    if (my_queue.head < my_queue.tail)
    {
        for (int i = my_queue.head; i < my_queue.tail; i++)
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

int main()
{

    struct queue a_queue = {{0},CAPACITY,0,0,0};

    enqueue(&a_queue, 1);
    enqueue(&a_queue, 3);
    enqueue(&a_queue, 5);
    enqueue(&a_queue, 2);

    print_queue_contents(a_queue); // 1 3 5 2

    dequeue(&a_queue);
    dequeue(&a_queue);

    print_queue_contents(a_queue); // 5 2

    enqueue(&a_queue, 4);
    enqueue(&a_queue, 9);
    enqueue(&a_queue, 2);
    enqueue(&a_queue, 6);

    print_queue_contents(a_queue); // 5 2 4 9 2 6

    dequeue(&a_queue);

    print_queue_contents(a_queue); // 2 4 9 2 6

    enqueue(&a_queue, 3);
    enqueue(&a_queue, 7);
    enqueue(&a_queue, 10); //error!! Overflow !!

    print_queue_contents(a_queue); // 2 4 9 2 6 3 7

    return 0;
}
