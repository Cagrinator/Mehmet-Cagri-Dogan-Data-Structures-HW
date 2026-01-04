#include <stdio.h>

#define MAXN 1000

typedef struct {
    int a[MAXN];
    int size;
} Heap;

/* -------- Utility -------- */
static void swap(int *x, int *y) {
    int t = *x;
    *x = *y;
    *y = t;
}

static void print_heap(const Heap *h) {
    if (h->size == 0) {
        printf("(empty)\n");
        return;
    }
    for (int i = 0; i < h->size; i++) {
        printf("%d ", h->a[i]);
    }
    printf("\n");
}

/* -------- MAX HEAP -------- */
static void max_heapify_up(Heap *h, int i) {
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->a[p] >= h->a[i]) break;
        swap(&h->a[p], &h->a[i]);
        i = p;
    }
}

static void max_heapify_down(Heap *h, int i) {
    while (1) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int best = i;

        if (l < h->size && h->a[l] > h->a[best]) best = l;
        if (r < h->size && h->a[r] > h->a[best]) best = r;

        if (best == i) break;
        swap(&h->a[i], &h->a[best]);
        i = best;
    }
}

static int max_insert(Heap *h, int x) {
    if (h->size >= MAXN) return 0;
    h->a[h->size] = x;
    max_heapify_up(h, h->size);
    h->size++;
    return 1;
}

static int max_peek(const Heap *h, int *out) {
    if (h->size == 0) return 0;
    *out = h->a[0];
    return 1;
}

static int max_extract(Heap *h, int *out) {
    if (h->size == 0) return 0;
    *out = h->a[0];
    h->size--;
    h->a[0] = h->a[h->size];
    max_heapify_down(h, 0);
    return 1;
}

/* -------- MIN HEAP -------- */
static void min_heapify_up(Heap *h, int i) {
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->a[p] <= h->a[i]) break;
        swap(&h->a[p], &h->a[i]);
        i = p;
    }
}

static void min_heapify_down(Heap *h, int i) {
    while (1) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int best = i;

        if (l < h->size && h->a[l] < h->a[best]) best = l;
        if (r < h->size && h->a[r] < h->a[best]) best = r;

        if (best == i) break;
        swap(&h->a[i], &h->a[best]);
        i = best;
    }
}

static int min_insert(Heap *h, int x) {
    if (h->size >= MAXN) return 0;
    h->a[h->size] = x;
    min_heapify_up(h, h->size);
    h->size++;
    return 1;
}

static int min_peek(const Heap *h, int *out) {
    if (h->size == 0) return 0;
    *out = h->a[0];
    return 1;
}

static int min_extract(Heap *h, int *out) {
    if (h->size == 0) return 0;
    *out = h->a[0];
    h->size--;
    h->a[0] = h->a[h->size];
    min_heapify_down(h, 0);
    return 1;
}

/* -------- Demo Menu -------- */
static void print_menu(void) {
    printf("\nChoose:\n");
    printf(" 1) Insert into Max-Heap\n");
    printf(" 2) Extract max from Max-Heap\n");
    printf(" 3) Peek max\n");
    printf(" 4) Print Max-Heap\n");
    printf(" 5) Insert into Min-Heap\n");
    printf(" 6) Extract min from Min-Heap\n");
    printf(" 7) Peek min\n");
    printf(" 8) Print Min-Heap\n");
    printf(" 0) Exit\n");
    printf("Enter choice: ");
}

int main(void) {
    Heap maxH = { .size = 0 };
    Heap minH = { .size = 0 };

    int choice;
    while (1) {
        print_menu();
        if (scanf("%d", &choice) != 1) {
            printf("Input error.\n");
            return 1;
        }

        if (choice == 0) break;

        int x, val;
        switch (choice) {
            case 1:
                printf("Value to insert (Max-Heap): ");
                if (scanf("%d", &x) != 1) { printf("Input error.\n"); return 1; }
                if (!max_insert(&maxH, x)) printf("Max-Heap is full!\n");
                else printf("Inserted.\n");
                break;

            case 2:
                if (!max_extract(&maxH, &val)) printf("Max-Heap is empty!\n");
                else printf("Extracted max: %d\n", val);
                break;

            case 3:
                if (!max_peek(&maxH, &val)) printf("Max-Heap is empty!\n");
                else printf("Max is: %d\n", val);
                break;

            case 4:
                printf("Max-Heap array:\n");
                print_heap(&maxH);
                break;

            case 5:
                printf("Value to insert (Min-Heap): ");
                if (scanf("%d", &x) != 1) { printf("Input error.\n"); return 1; }
                if (!min_insert(&minH, x)) printf("Min-Heap is full!\n");
                else printf("Inserted.\n");
                break;

            case 6:
                if (!min_extract(&minH, &val)) printf("Min-Heap is empty!\n");
                else printf("Extracted min: %d\n", val);
                break;

            case 7:
                if (!min_peek(&minH, &val)) printf("Min-Heap is empty!\n");
                else printf("Min is: %d\n", val);
                break;

            case 8:
                printf("Min-Heap array:\n");
                print_heap(&minH);
                break;

            default:
                printf("Invalid choice.\n");
                break;
        }
    }

    printf("Bye.\n");
    return 0;
}