#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} MaxHeap;

// Function to create a max-heap
MaxHeap* createMaxHeap(int capacity) {
    MaxHeap *heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    heap->data = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify function to maintain the max-heap property
void maxHeapify(MaxHeap *heap, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->data[left] > heap->data[largest]) {
        largest = left;
    }
    if (right < heap->size && heap->data[right] > heap->data[largest]) {
        largest = right;
    }
    if (largest != i) {
        swap(&heap->data[i], &heap->data[largest]);
        maxHeapify(heap, largest);
    }
}

// Function to insert a new element into the max-heap
void insertMaxHeap(MaxHeap *heap, int value) {
    if (heap->size == heap->capacity) {
        printf("Heap overflow! Cannot insert more elements.\n");
        return;
    }

    // Insert the new element at the end
    heap->size++;
    int i = heap->size - 1;
    heap->data[i] = value;

    // Fix the max-heap property if it is violated
    while (i != 0 && heap->data[(i - 1) / 2] < heap->data[i]) {
        swap(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Function to display the max-heap
void displayMaxHeap(MaxHeap *heap) {
    printf("Max-Heap elements: ");
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

// Main function to test the max-heap implementation
int main() {
    int capacity, numElements;
    printf("Enter the capacity of the max-heap: ");
    scanf("%d", &capacity);

    MaxHeap *heap = createMaxHeap(capacity);

    printf("Enter the number of elements to insert: ");
    scanf("%d", &numElements);

    printf("Enter the elements:\n");
    for (int i = 0; i < numElements; i++) {
        int value;
        scanf("%d", &value);
        insertMaxHeap(heap, value);
    }

    displayMaxHeap(heap);

    // Free the allocated memory
    free(heap->data);
    free(heap);

    return 0;
}
