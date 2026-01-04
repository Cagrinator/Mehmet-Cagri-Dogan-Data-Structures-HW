#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

static Node* create_node(int x) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) return NULL;
    n->data = x;
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
        n->next = n;
        return;
    }

    Node *cur = *head;
    while (cur->next != *head) cur = cur->next;

    cur->next = n;
    n->next = *head;
}
static void traverse(const Node *head) {
    if (!head) {
        printf("(empty)\n");
        return;
    }

    const Node *cur = head;
    do {
        printf("%d ", cur->data);
        cur = cur->next;
    } while (cur != head);
    printf("\n");
}

static Node* search(Node *head, int x) {
    if (!head) return NULL;

    Node *cur = head;
    do {
        if (cur->data == x) return cur;
        cur = cur->next;
    } while (cur != head);

    return NULL;
}
static int delete_by_value(Node **head, int x) {
    if (!head || !*head) return 0;

    Node *cur = *head;
    Node *prev = NULL;

    if (cur->next == cur) {
        if (cur->data == x) {
            free(cur);
            *head = NULL;
            return 1;
        }
        return 0;
    }
do {
        if (cur->data == x) break;
        prev = cur;
        cur = cur->next;
    } while (cur != *head);

    if (cur->data != x) return 0;

    if (cur == *head) {
        Node *tail = *head;
        while (tail->next != *head) tail = tail->next;

        *head = (*head)->next;
        tail->next = *head;

        free(cur);
        return 1;
    }

    prev->next = cur->next;
    free(cur);
    return 1;
}

static int delete_at_position(Node **head, int pos) {
    if (!head || !*head || pos < 0) return 0;

    Node *cur = *head;

    if (cur->next == cur) {
        if (pos == 0) {
            free(cur);
            *head = NULL;
            return 1;
        }
        return 0;
    }

    if (pos == 0) {
        Node *tail = *head;
        while (tail->next != *head) tail = tail->next;

        Node *old = *head;
        *head = (*head)->next;
        tail->next = *head;

        free(old);
        return 1;
    }

    Node *prev = NULL;
    int i = 0;
    do {
        prev = cur;
        cur = cur->next;
        i++;
    } while (cur != *head && i < pos);

    if (i != pos) return 0;

    prev->next = cur->next;
    free(cur);
    return 1;
}

static void free_list(Node **head) {
    if (!head || !*head) return;

    Node *cur = (*head)->next;
    while (cur != *head) {
        Node *nxt = cur->next;
        free(cur);
        cur = nxt;
    }
    free(*head);
    *head = NULL;
}

static void menu(void) {
    printf("\n--- Circular Linked List Menu ---\n");
    printf("1) Insert at end\n");
    printf("2) Traverse\n");
    printf("3) Search value\n");
    printf("4) Delete by value\n");
    printf("5) Delete at position (0-based)\n");
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
                printf("List: ");
                traverse(head);
                break;

            case 3:
                printf("Search value: ");
                if (scanf("%d", &x) != 1) { printf("Input error.\n"); break; }
                found = search(head, x);
                if (found) printf("Found: %d\n", found->data);
                else printf("Not found.\n");
                break;

            case 4:
                printf("Delete value: ");
                if (scanf("%d", &x) != 1) { printf("Input error.\n"); break; }
                if (delete_by_value(&head, x)) printf("Deleted.\n");
                else printf("Value not found.\n");
                break;

            case 5:
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