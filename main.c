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

int sort(list li);

node *get(list li, int i);


int main() {
    int k;
    printf("enter size:\n");
    scanf_s("%d", &k);
    printf("enter data:\n");
    list li = generate(&k);
    sort(li)? printf("Sorted"): printf("Not sorted");
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

int sort(list li) {
    int count = li.size;
    for (int i = 0; i < count; i++)
        for (int j = i + 1; j < count; j++) {
            if (strcmp(get(li, i)->data, get(li, j)->data) < 0) {
                return 0;
            }
        }
    return 1;
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