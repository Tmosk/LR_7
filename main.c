#include "malloc.h"
#include <stdio.h>
#include <string.h>

typedef struct node {
    char data[100];
    struct node *next;
    struct node *prev;
} node;
typedef struct list {
    int size;
    struct node *head;
    struct node *tail;
} list;

list generate(int *k);

void print(list li);

list sort(list li);

node *get(list li, int i);

list swap(node *a, node *b, list li);

int main() {
    int k;
    printf("enter size:\n");
    scanf_s("%d", &k);
    printf("enter data:\n");
    list li = generate(&k);
    li = sort(li);
    print(li);
    return 0;
}

list generate(int *k) {
    list li = *(list *) malloc(sizeof(list));
    li.size = *k;
    li.head = li.tail = NULL;
    for (int i = 0; i < li.size; ++i) {
        node *tmp = (node *) malloc(sizeof(node));
        scanf_s("%s", &tmp->data);
        if (li.head == NULL) {
            tmp->next = tmp->prev = NULL;
            li.head = li.tail = tmp;
        } else {
            tmp->prev = NULL;
            tmp->next = li.head;
            li.head->prev = tmp;
            li.head = tmp;
        }
    }
    return li;
}

void print(list li) {
    node *tmp = li.tail;
    while (tmp->prev != NULL) {
        printf("%s\n", tmp->data);
        tmp = tmp->prev;
    }
    printf("%s\n", tmp->data);
}

list sort(list li) {
    int count = li.size;
    for (int i = 0; i < count; i++)
        for (int j = i + 1; j < count; j++) {
            if (strcmp(get(li, i)->data, get(li, j)->data) < 0) {
                li = swap(get(li, i), get(li, j), li);
            }
        }
    return li;
}

list swap(node *a, node *b, list li) {
    if ((a == NULL) || (b == NULL)) {
        return li;
    }
    node *tmp;
    if (li.head == a)li.head = b;
    else if (li.head == b)li.head = a;
    if (li.tail == a)li.tail = b;
    else if (li.tail == b)li.tail = a;

    if (a->next == b) {
        a->next = b->next;
        if (b->next != NULL) {
            b->next->prev = a;
        }
        b->next = a;
        b->prev = a->prev;
        if (a->prev != NULL) {
            a->prev->next = b;
        }
        a->prev = b;
    } else if (b->next == a) {
        b->next = a->next;
        if (a->next != NULL) {
            a->next->prev = b;
        }
        a->next = b;
        a->prev = b->prev;
        if (b->prev != NULL) {
            b->prev->next = a;
        }
        b->prev = a;
    } else if (a->prev == b) {
        a->prev = b->prev;
        if (b->prev != NULL) {
            b->prev->next = a;
        }
        b->prev = a;
        b->next = a->prev;
        if (a->next != NULL) {
            a->next->prev = b;
        }
        a->next = b;
    } else if (b->prev == a) {
        b->prev = a->prev;
        if (a->prev != NULL) {
            a->prev->next = b;
        }
        a->prev = b;
        a->next = b->prev;
        if (b->next != NULL) {
            b->next->prev = a;
        }
        b->next = a;
    } else {
        if (a->prev != NULL) {
            a->prev->next = b;
        }
        if (a->next != NULL) {
            a->next->prev = b;
        }
        if (b->prev != NULL) {
            b->prev->next = a;
        }
        if (b->next != NULL) {
            b->next->prev = a;
        }
        tmp = a->next;
        a->next = b->next;
        b->next = tmp;
        tmp = a->prev;
        a->prev = b->prev;
        b->prev = tmp;
    }

    return li;
}

node *get(list li, int i) {
    node *tmp = li.head;
    int j = 0;
    while (j < i) {
        if (tmp->next == NULL) {
            return NULL;
        } else {
            tmp = tmp->next;
            j++;
        }
    }
    return tmp;
}