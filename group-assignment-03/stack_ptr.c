/*
 * Stack containing race conditions
 */

#include <stdio.h>   // printf
#include <stdlib.h>  // malloc free exit
#include <pthread.h> // pthread_create pthread_join

// Linked list node
typedef int value_t; // value type of the node (int)
typedef struct Node  // node type
{
    value_t data;      // data of the node (int)
    struct Node *next; // pointer to the next node in the list (Node*)
} StackNode;           // node type (Node)

// Stack function declarations
void push(value_t v, StackNode **top); // push a value to the stack (void)
value_t pop(StackNode **top);          // pop a value from the stack (int)
int is_empty(StackNode *top);          // check if the stack is empty (int)

int main(void)
{
    StackNode *top = NULL; // top of the stack (Node*) (NULL)

    push(5, &top);  // push 5 to the stack (void)
    push(10, &top); // push 10 to the stack (void)
    pop(&top);      // pop a value from the stack (int)
    push(15, &top); // push 15 to the stack (void)
    pop(&top);      // pop a value from the stack (int)
    pop(&top);      // pop a value from the stack (int)
    push(20, &top); // push 20 to the stack (void)

    push(-5, &top);  // push -5 to the stack (void)
    pop(&top);       // pop a value from the stack (int)
    push(-10, &top); // push -10 to the stack (void)
    pop(&top);       // pop a value from the stack (int)
    pop(&top);       // pop a value from the stack (int)
    push(-15, &top); // push -15 to the stack (void)
    pop(&top);       // pop a value from the stack (int)
    push(-20, &top); // push -20 to the stack (void)

    return EXIT_SUCCESS; // return success
}

// Stack function definitions
void push(value_t v, StackNode **top) // push a value to the stack (void)
{
    // allocate memory for a new node (Node*)
    StackNode *new_node = malloc(sizeof(StackNode));

    new_node->data = v;    // set the data of the new node (int)
    new_node->next = *top; // set the next node of the new node (Node*)
    *top = new_node;       // set the top of the stack (Node*)
}

value_t pop(StackNode **top) // pop a value from the stack (int)
{
    if (is_empty(*top))    // check if the stack is empty (int)
        return (value_t)0; // return 0

    value_t data = (*top)->data; // get the data of the top node (int)
    StackNode *temp = *top;      // get the top node (Node*)
    *top = (*top)->next;         // set the top of the stack (Node*)

    free(temp); // free the top node (void)

    return data; // return the data of the top node (int)
}
int is_empty(StackNode *top) // check if the stack is empty (int)
{
    if (top == NULL) // check if the top is NULL (int)
        return 1;    // return 1 (true) when the top is NULL
    else
        return 0; // return 0 (false) when the top is not NULL
}