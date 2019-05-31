#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#if !defined(MIN)
    #define MIN(A,B) ({(A<B)?A:B;})
#endif

#if !defined(MAX)
    #define MAX(A,B) ({(A>B)?A:B;})
#endif

static unsigned long const kInvalidValue = 10000000000000001; // Greater than 10^9

struct HeapItem {
    unsigned long value;
    unsigned long aux;
};
typedef struct HeapItem HeapItem;

#define kInvalidHeapItem { .value = kInvalidValue, .aux = kInvalidValue };

struct MinHeap {
    size_t maxSize;
    unsigned long size;
    HeapItem * items;
};
typedef struct MinHeap MinHeap;

struct MinHeap heapInit(size_t maxSize) {
    MinHeap h;
    h.maxSize = maxSize;
    h.size = 0;
    h.items = calloc(maxSize, sizeof(HeapItem));
    return h;
}

unsigned long heap_parent(unsigned long i) {
    i++;
    unsigned long parent = (i % 2)?floor(i/2):(i/2);
    parent--;
    return parent;
}

unsigned long heap_childL(unsigned long i) {
    i++;
    return 2*i - 1;
}

unsigned long heap_childR(unsigned long i) {
    i++;
    return 2*i;
}

void heap_bubble_up(MinHeap * h, unsigned long i) {
    if (!h->size || !i) {
        return;
    }
    
    unsigned long parentIdx = heap_parent(i);
    HeapItem parentItem = h->items[parentIdx];
    
    if (h->items[i].value < parentItem.value) {
        h->items[parentIdx] = h->items[i];
        h->items[i] = parentItem;
        heap_bubble_up(h, parentIdx);
        return;
    }
}

void heap_bubble_down(MinHeap * h, unsigned long i) {
    if (!h->size || i == h->size) {
        return;
    }
    
    // check what child is the smallest. Start by defaulting the left and getting the right if it exists and is smaller
    unsigned long childIdx = heap_childL(i);
    if (childIdx >= h->size) {
        return;
    }
    HeapItem childItem = h->items[childIdx];
    unsigned long rightChildIdx = heap_childR(i);
    HeapItem rightChildItem = h->items[rightChildIdx];
    if (rightChildIdx < h->size && childItem.value > rightChildItem.value) {
        childIdx = rightChildIdx;
        childItem = rightChildItem;
    }
    
    if (h->items[i].value > childItem.value) {
        h->items[childIdx] = h->items[i];
        h->items[i] = childItem;
        heap_bubble_down(h, childIdx);
        return;
    }
}

void heap_insert(MinHeap * h, HeapItem item) {
    if (h->size == h->maxSize) {
        printf("*** ERROR: Heap is full ***\n");
        exit(1);
        return;
    }
    
    unsigned long idx = h->size;
    h->items[idx] = item;
    h->size++;
    heap_bubble_up(h, idx);
}

void heap_delete(MinHeap * h, unsigned long i) {
    if (!h->size) {
        return;
    }
    
    if (i < h->size) {
        HeapItem item = h->items[h->size - 1];
        h->items[i] = item;
        
        // Reduce size and invalidate that item
        h->size--;
        h->items[h->size] = (HeapItem)kInvalidHeapItem;
        
        heap_bubble_down(h, i); // Bubble down from that index
    }
}

HeapItem heap_extract_min(MinHeap * h) {
    if (!h->size) {
        return (HeapItem)kInvalidHeapItem;
    }
    
    HeapItem item = h->items[0];
    heap_delete(h, 0);
    return item;
}

HeapItem heap_current_min(MinHeap * h) {
    if (!h->size) {
        return (HeapItem)kInvalidHeapItem;
    }
    
    return h->items[0];
}

void heap_print(MinHeap * h) {
    for(int i = 0; i < h->size; i++) {
        HeapItem item = h->items[i];
        printf("[%i] = %lu %lu\n", i, item.value, item.aux);
    }
}

int main() {
    int c;
    scanf("%d", &c); // customers
    
    MinHeap h1 = heapInit(c);
    
    // Sorting the items in order of arrival, to then process them in order
    for(int i = 0; i < c; i++) {
        unsigned long at, ct; // arrival time & cooking time
        scanf("%lu %lu", &at, &ct);
        
        HeapItem item = { .value = at, .aux = ct };
        heap_insert(&h1, item);
    }
    
    // Get the time when the first order arrived
    HeapItem firstItem = heap_current_min(&h1);
    
    
    MinHeap h = heapInit(c);
    long long time = firstItem.value - 1;
    long long cookingWillFinishAt = 0;
    unsigned long combinedWaitingTime = 0;
    HeapItem currentCookingItem;

    while (h1.size) {
        time++;
        
        HeapItem item = heap_current_min(&h1);
        if (item.value <= time) {
            // remove the item
            heap_delete(&h1, 0);
            
            HeapItem order;
            order.value = item.aux;
            order.aux = item.value;
            heap_insert(&h, order);
        }
        
        if (cookingWillFinishAt <= time) {
            currentCookingItem = heap_extract_min(&h);
            if (kInvalidValue != currentCookingItem.value) {
                cookingWillFinishAt = time + currentCookingItem.value;
                combinedWaitingTime += cookingWillFinishAt - currentCookingItem.aux;
            }
        }
        
        time = MAX(time, MIN(item.value, cookingWillFinishAt) - 1);
    }
    
    while (h.size) {
        time++;
        
        if (cookingWillFinishAt <= time) {
            currentCookingItem = heap_extract_min(&h);
            if (kInvalidValue != currentCookingItem.value) {
                cookingWillFinishAt = time + currentCookingItem.value;
                combinedWaitingTime += cookingWillFinishAt - currentCookingItem.aux;
            }
        }
        time = MAX(time, cookingWillFinishAt - 1);
    }
    
    printf("%lu\n", combinedWaitingTime/c);
    
    return(0);
}