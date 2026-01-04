#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

static Node* create_node(int x) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) return NULL;
    n->data = x;
    n->prev = NULL;
    n->next = NULL;
    return n;
}

static void insert_end(Node **head, int x) {
    Node *n = create_node(x);
    if (!n) {
        printf("Memory allocation failed.\n");
        return;
    }

    if (*head == NULL) {
        *head = n;
        return;
    }

    Node *cur = *head;
    while (cur->next != NULL) cur = cur->next;

    cur->next = n;
    n->prev = cur;
}

static void traverse_forward(const Node *head) {
    if (!head) {
        printf("(empty)\n");
        return;
    }
    const Node *cur = head;
    while (cur) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

static void traverse_backward(const Node *head) {
    if (!head) {
        printf("(empty)\n");
        return;
    }

    const Node *cur = head;
    while (cur->next) cur = cur->next;

    while (cur) {
        printf("%d ", cur->data);
        cur = cur->prev;
    }
    printf("\n");
}

static Node* search(Node *head, int x) {
    Node *cur = head;
    while (cur) {
        if (cur->data == x) return cur;
        cur = cur->next;
    }
    return NULL;
}

static int delete_by_value(Node **head, int x) {
    if (!head || !*head) return 0;

    Node *cur = *head;
    while (cur && cur->data != x) cur = cur->next;
    if (!cur) return 0; 

    if (cur->prev == NULL) {
        *head = cur->next;
        if (*head) (*head)->prev = NULL;
    } else {
        cur->prev->next = cur->next;
        if (cur->next) cur->next->prev = cur->prev;
    }

    free(cur);
    return 1;
}


static int delete_at_position(Node **head, int pos) {
    if (!head || !*head || pos < 0) return 0;

    Node *cur = *head;
    int i = 0;
    while (cur && i < pos) {
        cur = cur->next;
        i++;
    }
    if (!cur) return 0;

    if (cur->prev == NULL) {
        *head = cur->next;
        if (*head) (*head)->prev = NULL;
    } else {
        cur->prev->next = cur->next;
        if (cur->next) cur->next->prev = cur->prev;
    }

    free(cur);
    return 1;
}

static void free_list(Node **head) {
    Node *cur = head ? *head : NULL;
    while (cur) {
        Node *nxt = cur->next;
        free(cur);
        cur = nxt;
    }
    if (head) *head = NULL;
}

static void menu(void) {
    printf("\n--- Doubly Linked List Menu ---\n");
    printf("1) Insert at end\n");
    printf("2) Traverse forward\n");
    printf("3) Traverse backward\n");
    printf("4) Search value\n");
    printf("5) Delete by value\n");
    printf("6) Delete at position (0-based)\n");
    printf("0) Exit\n");
    printf("Choice: ");
}

int main(void) {
    Node *head = NULL;
    int choice;

    while (1) {
        menu();
        if (scanf("%d", &choice) != 1) {
            printf("Input error.\n");
            free_list(&head);
            return 1;
        }

        if (choice == 0) break;

        int x, pos;
        Node *found;

        switch (choice) {
            case 1:
                printf("Enter value: ");
                if (scanf("%d", &x) != 1) { printf("Input error.\n"); break; }
                insert_end(&head, x);
                printf("Inserted.\n");
                break;

            case 2:
                printf("Forward: ");
                traverse_forward(head);
                break;

            case 3:
                printf("Backward: ");
                traverse_backward(head);
                break;

            case 4:
                printf("Search value: ");
                if (scanf("%d", &x) != 1) { printf("Input error.\n"); break; }
                found = search(head, x);
                if (found) printf("Found: %d\n", found->data);
                else printf("Not found.\n");
                break;

            case 5:
                printf("Delete value: ");
                if (scanf("%d", &x) != 1) { printf("Input error.\n"); break; }
                if (delete_by_value(&head, x)) printf("Deleted.\n");
                else printf("Value not found.\n");
                break;

            case 6:
                printf("Delete position (0-based): ");
                if (scanf("%d", &pos) != 1) { printf("Input error.\n"); break; }
                if (delete_at_position(&head, pos)) printf("Deleted.\n");
                else printf("Invalid position.\n");
                break;

            default:
                printf("Invalid choice.\n");
                break;
        }
    }

    free_list(&head);
    printf("Bye.\n");
    return 0;
}