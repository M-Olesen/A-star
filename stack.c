#include "stack.h"

// ------------------------------------------------------------ STACK ----------------------------------------------------------------------------------------
// function to create a stack of given capacity. It initializes size of
// stack as 0
struct Stack* createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (Pair*)malloc(stack->capacity * sizeof(Pair));
    return stack;
}

// Stack is full when top is equal to the last index
int isFull(struct Stack* stack)
{
    return stack->top == stack->capacity - 1;
}

// Stack is empty when top is equal to -1
int isEmpty(struct Stack* stack)
{
    return stack->top == -1;
}

// Function to add an item to stack. It increases top by 1
void push(struct Stack* stack, Pair item)
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

// Function to remove an item from stack. It decreases top by 1
Pair pop(struct Stack* stack)
{
    return stack->array[stack->top--];
}

// Function to return the top from stack without removing it
Pair peek(struct Stack* stack)
{
    return stack->array[stack->top];
}

// Funtion to empth a whole stack
void emptyStack(struct Stack* stack) {
    while(!isEmpty(stack)) {
        pop(stack);
    }
}

// ------------------------------------------------------------ SET ----------------------------------------------------------------------------------------
// Function to initialize an empty set
void initializeSet(Set* set) {
    set->size = 0;
}

// Function to check if a pPair is in the set
bool isInSet(Set* set, pPair element) {
    for (int i = 0; i < set->size; i++) {
        if (set->elements[i].first == element.first &&
            set->elements[i].second.first == element.second.first &&
            set->elements[i].second.second == element.second.second) {
            return true;
        }
    }
    return false;
}

// Function to get the first element of the set
pPair Begin(Set *set) {
    if (set->size > 0) {
        return set->elements[0];
    } else {
        // You might want to handle this case differently based on your requirements
        // For now, returning an element with first as -1 as an indicator that the set is empty
        pPair emptyElement = {-1.0, { -1, -1 }};
        return emptyElement;
    }
}


// Function to add a pPair to the set
void addToSet(Set* set, pPair element) {
    if (!isInSet(set, element) && set->size < MAX_SIZE) {
        set->elements[set->size++] = element;
    }
}

// Function to remove a pPair from the set
void removeFromSet(Set* set, pPair element) {
    for (int i = 0; i < set->size; i++) {
        if (set->elements[i].first == element.first &&
            set->elements[i].second.first == element.second.first &&
            set->elements[i].second.second == element.second.second) {
            // Shift elements to fill the gap
            for (int j = i; j < set->size - 1; j++) {
                set->elements[j] = set->elements[j + 1];
            }
            set->size--;
            break;
        }
    }
}

// Function to check if the set is empty
bool isSetEmpty(Set *set) {
    return set->size == 0;
}