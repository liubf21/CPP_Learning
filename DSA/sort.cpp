#include<bits/stdc++.h>

using namespace std;

void quicksort();


// heap sort
#define root 0
#define lson(idx) (idx << 1|1)
#define rson(idx) ((idx << 1) + 2)
#define parent(idx) ((idx - 1) >> 1)

typedef struct 
{
    int key;
    void *any;
}DataType;

typedef struct 
{
    DataType *data; // data array
    int size;
    int capacity;
}Heap;

int compareData(const DataType *a, const DataType *b)
{
    return a->key - b->key;
}

void swapData(DataType *a, DataType *b)
{
    DataType tmp = *a;
    *a = *b;
    *b = tmp;
}

bool heapIsEmpty(Heap *heap)
{
    return heap->size == 0;
}

bool heapIsFull(Heap *heap)
{
    return heap->size == heap->capacity;
}

DataType* heapTop(Heap *heap)
{
    if(heapIsEmpty(heap))
    {
        return NULL;
    }
    return &heap->data[0];
}

void heapShiftUp(Heap *heap, int curr)
{
    int p = parent(curr);
    while(curr != root)
    {
        if(compareData(&heap->data[curr], &heap->data[p]) < 0)
        {
            swapData(&heap->data[curr], &heap->data[p]);
            curr = p; // update curr
            p = parent(curr); // update p
        }
        else
        {
            break;
        }
    }
}

void heapShiftDown(Heap *heap, int curr)
{
    int son = lson(curr);
    while (son < heap->size)
    {
        if(rson(curr) < heap->size && compareData(&heap->data[rson(curr)], &heap->data[son]) < 0)
        {
            son = rson(curr); // update son
        }
        if(compareData(&heap->data[son], &heap->data[curr]) < 0)
        {
            swapData(&heap->data[son], &heap->data[curr]);
            curr = son; // update curr
            son = lson(curr); // update son
        }
        else
        {
            break;
        }
    }
}

bool heapPush(Heap *heap, DataType *data)
{
    if(heapIsFull(heap))
    {
        return false;
    }
    heap->data[heap->size++] = *data;
    heapShiftUp(heap, heap->size-1);
    return true;
}

Heap* heapPop(Heap *heap)
{
    if(heapIsEmpty(heap))
    {
        return NULL;
    }
    swapData(&heap->data[0], &heap->data[--heap->size]);
    heapShiftDown(heap, 0);
    return heap;
}

Heap* heapCreate(DataType *data, int dataSize, int maxSize)
{
    int i;
    Heap *h = (Heap*)malloc(sizeof(Heap));
    h->data = (DataType*)malloc(sizeof(DataType) * maxSize);
    h->size = 0;
    h->capacity = maxSize;
    for(i = 0; i < dataSize; i++)
    {
        heapPush(h, &data[i]);
    }
    return h;
}

void heapDestroy(Heap *heap)
{
    free(heap->data);
    free(heap);
}


// test
int main()
{
    int i;
    int a[] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 0 };
    int size = sizeof(a) / sizeof(int);
    qsort(a, 0, size - 1);
    for (i = 0; i < size; i++)
    {
        printf("%d ", a[i]);
    }
    return 0;
}