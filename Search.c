#include <stdio.h>
#include <stdbool.h>

// Definition of Pair
typedef struct {
    int first;
    int second;
} Pair;

// Definition of pPair
typedef struct {
    double first;
    Pair second;
} pPair;

#define MAX_SIZE 100

// Definition of Set
typedef struct {
    pPair elements[MAX_SIZE];
    int size;
} Set;

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

// Function to print the elements of the set
void printSet(Set* set) {
    printf("{ ");
    for (int i = 0; i < set->size; i++) {
        printf("(%lf, (%d, %d)) ", set->elements[i].first, set->elements[i].second.first, set->elements[i].second.second);
    }
    printf("}\n");
}

int main() {
    // Example usage
    Set mySet;
    initializeSet(&mySet);

    Pair pair1 = {1, 2};
    Pair pair2 = {3, 4};

    pPair pPair1 = {1.0, pair1};
    pPair pPair2 = {2.5, pair2};

    addToSet(&mySet, pPair1);
    addToSet(&mySet, pPair2);

    printf("Set: ");
    printSet(&mySet);

    pPair pairToRemove = {1.0, pair1};
    removeFromSet(&mySet, pairToRemove);

    printf("After removing (%lf, (%d, %d)): ", pairToRemove.first, pairToRemove.second.first, pairToRemove.second.second);
    printSet(&mySet);

    return 0;
}
