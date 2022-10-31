/*
 * Stack containing race conditions
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

pthread_mutex_t lock; // mutex lock for critical region
// critical region is top
// so to achieve maximum concurrency,
// mutex lock should be set over smallest possible region
// so it will be set in push and pop function
// instead of in testStack

// how it is correct
// push -1
// then run thread routing which pushs first and pops first
// in indeterminate manner but after it finishes,
// there should be same number -1

// Linked list node
typedef int value_t;
typedef struct Node
{
    value_t data;
    struct Node *next;
} StackNode;

// Stack function declarations
void push(value_t v, StackNode **top);
value_t pop(StackNode **top);
int is_empty(StackNode *top);
// it will push 500*3 and pop 500*3 by each thread
// therefore, total push: 500*3*200 and same pops
void* testStack(void *arg){
    // thread routing runs 500 times
    StackNode *top = (StackNode *) arg;
    
    for(int i=0; i< 500; i++){
        push(1, &top);
        pop(&top);
        push(2, &top);
        pop(&top);
        push(3, &top);
        pop(&top);
    }
}

int main(void)
{
    int nthreads = 200;
    pthread_t threads[nthreads]; // creating arrays for threads
    int thread_count =0;    
    StackNode *top = NULL;
    push(-1, &top); // it will checked after threads are done
    printf("pushing first: -1\n");
    // if last value is not -1, then it is not working properly
    for(; thread_count < nthreads; thread_count++){
        // let the threads run in weird manner concurrently
        pthread_create(&threads[thread_count], NULL, testStack, top);
    }

    // collect all threads here
    for(int i = 0; i < nthreads; i++){
        pthread_join(threads[i], NULL);
    }

    // all threads have been collected
    // now it is time to evaluate
    // make sure stack is empty
    
    assert(pop(&top) == -1 && "Stack should be empty\n");
    printf("After running 200 threads ...\n");
    printf("passed: last pop is: -1\n");

    return 0;
}

// Stack function definitions
void push(value_t v, StackNode **top)
{
    StackNode * new_node = malloc(sizeof(StackNode));
    new_node->data = v;
    
    pthread_mutex_lock(&lock);
    //printf("pushing: %d\n", v);
    new_node->next = *top;
    *top = new_node;
    pthread_mutex_unlock(&lock);
    
}

value_t pop(StackNode **top)
{
    if (is_empty(*top)) return (value_t)0;

    pthread_mutex_lock(&lock);    
    value_t data  = (*top)->data;
    //printf("poping: %d\n", data);
    StackNode * temp  = *top;
    *top = (*top)->next;    
    free(temp);
    pthread_mutex_unlock(&lock);

    return data;
}
int is_empty(StackNode *top) {
    if (top == NULL) return 1;
    else return 0;
}
