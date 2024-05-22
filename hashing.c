#include <stdio.h>
#include <stdlib.h>

typedef enum { LINEAR, QUADRATIC } ProbingType;

typedef struct {
    int *table;
    int capacity;
    ProbingType probingType;
} HashTable;

int hashFunction(int key, int capacity) {
    return key % capacity;
}

int linearProbe(int key, int i, int capacity) {
    return (hashFunction(key, capacity) + i) % capacity;
}

int quadraticProbe(int key, int i, int capacity) {
    return (hashFunction(key, capacity) + i * i) % capacity;
}

void initHashTable(HashTable *hashTable, int size, ProbingType probingType) {
    hashTable->capacity = size;
    hashTable->probingType = probingType;
    hashTable->table = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        hashTable->table[i] = -1;
    }
}

void insert(HashTable *hashTable, int key) {
    int index = hashFunction(key, hashTable->capacity);
    int i = 0;
    while (hashTable->table[index] != -1) {
        if (hashTable->probingType == LINEAR) {
            index = linearProbe(key, ++i, hashTable->capacity);
        } else if (hashTable->probingType == QUADRATIC) {
            index = quadraticProbe(key, i++, hashTable->capacity);
        }
    }
    hashTable->table[index] = key;
}

int search(HashTable *hashTable, int key) {
    int index = hashFunction(key, hashTable->capacity);
    int i = 0;
    while (hashTable->table[index] != key) {
        if (hashTable->table[index] == -1) {
            return 0; // Key not found
        }
        if (hashTable->probingType == LINEAR) {
            index = linearProbe(key, ++i, hashTable->capacity);
        } else if (hashTable->probingType == QUADRATIC) {
            index = quadraticProbe(key, i++, hashTable->capacity);
        }
    }
    return 1; // Key found
}

void display(HashTable *hashTable) {
    printf("Hash Table:\n");
    for (int i = 0; i < hashTable->capacity; ++i) {
        if (hashTable->table[i] != -1)
            printf("%d: %d\n", i, hashTable->table[i]);
        else
            printf("%d: Empty\n", i);
    }
}

int main() {
    int size, numKeys, choice;
    printf("Enter the size of the hash table: ");
    scanf("%d", &size);

    printf("Choose probing method:\n1. Linear Probing\n2. Quadratic Probing\nEnter choice (1 or 2): ");
    scanf("%d", &choice);

    ProbingType probingType = (choice == 1) ? LINEAR : QUADRATIC;
    HashTable hashTable;
    initHashTable(&hashTable, size, probingType);

    printf("Enter the number of keys to insert: ");
    scanf("%d", &numKeys);

    printf("Enter the keys to insert:\n");
    for (int i = 0; i < numKeys; ++i) {
        int key;
        scanf("%d", &key);
        insert(&hashTable, key);
    }

    printf("Enter the key to search: ");
    int searchKey;
    scanf("%d", &searchKey);

    if (search(&hashTable, searchKey)) {
        printf("Key %d found in the hash table.\n", searchKey);
    } else {
        printf("Key %d not found in the hash table.\n", searchKey);
    }

    display(&hashTable);
    free(hashTable.table);
    return 0;
}
