#include <stdio.h>

#define CAPACITY 1000

typedef struct {
    int a[CAPACITY];
    int size;
} Array;

static void print_array(const Array *arr) {
    if (arr->size == 0) {
        printf("(empty)\n");
        return;
    }
    for (int i = 0; i < arr->size; i++) {
        printf("%d ", arr->a[i]);
    }
    printf("\n");
}

static int push_back(Array *arr, int x) {
    if (arr->size >= CAPACITY) return 0;
    arr->a[arr->size++] = x;
    return 1;
}

static int insert_at(Array *arr, int index, int x) {
    if (arr->size >= CAPACITY) return 0;
    if (index < 0 || index > arr->size) return 0;

    for (int i = arr->size; i > index; i--) {
        arr->a[i] = arr->a[i - 1];
    }
    arr->a[index] = x;
    arr->size++;
    return 1;
}

static int delete_at(Array *arr, int index, int *deleted_value) {
    if (arr->size == 0) return 0;
    if (index < 0 || index >= arr->size) return 0;

    if (deleted_value) *deleted_value = arr->a[index];

    for (int i = index; i < arr->size - 1; i++) {
        arr->a[i] = arr->a[i + 1];
    }
    arr->size--;
    return 1;
}

static int search_value(const Array *arr, int x) {
    for (int i = 0; i < arr->size; i++) {
        if (arr->a[i] == x) return i;
    }
    return -1;
}

static int delete_by_value(Array *arr, int x) {
    int idx = search_value(arr, x);
    if (idx == -1) return 0;
    return delete_at(arr, idx, NULL);
}

static void menu(void) {
    printf("\n--- Array Operations Menu ---\n");
    printf("1) Insert at end\n");
    printf("2) Insert at index\n");
    printf("3) Delete at index\n");
    printf("4) Delete by value (first occurrence)\n");
    printf("5) Search value\n");
    printf("6) Print array\n");
    printf("0) Exit\n");
    printf("Choice: ");
}

int main(void) {
    Array arr;
    arr.size = 0;

    int choice;
    while (1) {
        menu();
        if (scanf("%d", &choice) != 1) {
            printf("Input error.\n");
            return 1;
        }

        if (choice == 0) break;

        int x, index, deleted;

        switch (choice) {
            case 1:
                printf("Value: ");
                if (scanf("%d", &x) != 1) { printf("Input error.\n"); return 1; }
                if (push_back(&arr, x)) printf("Inserted.\n");
                else printf("Array is full.\n");
                break;

            case 2:
                printf("Index (0..%d): ", arr.size);
                if (scanf("%d", &index) != 1) { printf("Input error.\n"); return 1; }
                printf("Value: ");
                if (scanf("%d", &x) != 1) { printf("Input error.\n"); return 1; }
                if (insert_at(&arr, index, x)) printf("Inserted.\n");
                else printf("Invalid index or array full.\n");
                break;

            case 3:
                printf("Index (0..%d): ", arr.size - 1);
                if (scanf("%d", &index) != 1) { printf("Input error.\n"); return 1; }
                if (delete_at(&arr, index, &deleted)) printf("Deleted: %d\n", deleted);
                else printf("Invalid index or array empty.\n");
                break;

            case 4:
                printf("Value to delete: ");
                if (scanf("%d", &x) != 1) { printf("Input error.\n"); return 1; }
                if (delete_by_value(&arr, x)) printf("Deleted.\n");
                else printf("Value not found.\n");
                break;

            case 5:
                printf("Value to search: ");
                if (scanf("%d", &x) != 1) { printf("Input error.\n"); return 1; }
                index = search_value(&arr, x);
                if (index != -1) printf("Found at index: %d\n", index);
                else printf("Not found.\n");
                break;

            case 6:
                printf("Array: ");
                print_array(&arr);
                break;

            default:
                printf("Invalid choice.\n");
                break;
        }
    }

    printf("Bye.\n");
    return 0;
}