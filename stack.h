#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_SIZE 100

typedef struct {
    int first;
    int second;
} Pair;


typedef struct{
    double first;
    Pair second;
} pPair;

// Definition of Set
typedef struct {
    pPair elements[MAX_SIZE];
    int size;
} Set;

struct Stack* createStack(unsigned capacity);
int isFull(struct Stack* stack);
int isEmpty(struct Stack* stack);
void push(struct Stack* stack, Pair item);
Pair pop(struct Stack* stack);
Pair peek(struct Stack* stack);

// A structure to represent a stack
typedef struct Stack {
    int top;
    unsigned capacity;
    Pair* array;
} Stack;

void initializeSet(Set* set);
bool isInSet(Set* set, pPair element);
pPair Begin(Set *set);
void addToSet(Set* set, pPair element);
void removeFromSet(Set* set, pPair element);
bool isSetEmpty(Set *set);
