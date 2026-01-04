//* Infix is our own way of doing operations with equations, postfix and prefix is however how machines do operations and solve equations *//
//* I used a stack to do postfix and i found that queues can be used for prefix but still used stack for the assignment, easier implementation*// 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 1024

//* classic stack implementation (array implementation) *//

typedef struct 
{
    char data[MAX];
    int top;
}stack;

//* classic stack functions: peek, push, pop etc. *//

void st_init(stack *s) { s->top = -1; }
int  st_empty(const stack *s) { return s->top < 0; }
int  st_full(const stack *s) { return s->top >= MAX - 1; }

int st_push(stack *s, char x) {
    if (st_full(s)) return 0;
    s->data[++s->top] = x;
    return 1;
}

int st_pop(stack *s, char *out) {
    if (st_empty(s)) return 0;
    *out = s->data[s->top--];
    return 1;
}

int st_peek(const stack *s, char *out) {
    if (st_empty(s)) return 0;
    *out = s->data[s->top];
    return 1;
}

int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

int precedence(char op) {
    switch (op) {
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        default:  return 0;
    }
}

int is_right_assoc(char op) {
    return op == '^';
}

int infix_to_postfix(const char *infix, char *postfix, int postfix_size) {
    stack ops;
    st_init(&ops);

    int out_len = 0;

    for (int i = 0; infix[i] != '\0'; ) {
        char c = infix[i];

        if (isspace((unsigned char)c)) {
            i++;
            continue;
        }

        if (isdigit((unsigned char)c)) {
            while (isdigit((unsigned char)infix[i])) {
                if (out_len + 1 >= postfix_size) return 0;
                postfix[out_len++] = infix[i++];
            }

            if (out_len + 1 >= postfix_size) return 0;
            postfix[out_len++] = ' ';
            continue;
        }

        if (isalpha((unsigned char)c)) {
            if (out_len + 2 >= postfix_size) return 0;
            postfix[out_len++] = c;
            postfix[out_len++] = ' ';
            i++;
            continue;
        }

        if (c == '(') {
            if (!st_push(&ops, c)) return 0;
            i++;
            continue;
        }

        if (c == ')') {
            char top;
            while (st_peek(&ops, &top) && top != '(') {
                st_pop(&ops, &top);
                if (out_len + 2 >= postfix_size) return 0;
                postfix[out_len++] = top;
                postfix[out_len++] = ' ';
            }

            if (!st_pop(&ops, &top) || top != '(') {
                return 0;
            }
            i++;
            continue;
        }

        if (is_operator(c)) {
            char top;
            while (st_peek(&ops, &top) && is_operator(top)) {
                int p1 = precedence(c);
                int p2 = precedence(top);

                int should_pop = is_right_associative(c) ? (p2 > p1) : (p2 >= p1);

                if (!should_pop) break;

                st_pop(&ops, &top);
                if (out_len + 2 >= postfix_size) return 0;
                postfix[out_len++] = top;
                postfix[out_len++] = ' ';
            }
            if (!st_push(&ops, c)) return 0;
            i++;
            continue;
        }

        return 0;
    }

    char top;
    while (st_pop(&ops, &top)) {
        if (top == '(' || top == ')') return 0;
        if (out_len + 2 >= postfix_size) return 0;
        postfix[out_len++] = top;
        postfix[out_len++] = ' ';
    }

    if (out_len > 0 && postfix[out_len - 1] == ' ') out_len--;

    if (out_len >= postfix_size) return 0;
    postfix[out_len] = '\0';
    return 1;
}

int main(void) {
    char infix[MAX];
    char postfix[MAX];

    printf("Enter infix expression:\n");
    if (!fgets(infix, sizeof(infix), stdin)) {
        printf("Input error.\n");
        return 1;
    }

    size_t len = strlen(infix);
    if (len > 0 && infix[len - 1] == '\n') infix[len - 1] = '\0';

    if (!infix_to_postfix(infix, postfix, (int)sizeof(postfix))) {
        printf("Conversion error (check parentheses / invalid characters / too long).\n");
        return 1;
    }

    printf("\nPostfix expression:\n%s\n", postfix);
    return 0;
}