#include<stdio.h>
#include<stdlib.h>

struct term {
    int co;
    int po;
    struct term* next;
};

struct term* createNode(int co, int po) {
    if (co == 0) return NULL; 
    struct term* newNode = (struct term*) malloc(sizeof(struct term));
    newNode->co = co;
    newNode->po = po;
    newNode->next = NULL;
    return newNode;
}

void append(struct term** head, struct term** tail, struct term* newNode) {
    if (!newNode) return;  
    if (*head == NULL) {
        *head = *tail = newNode;
    } else {
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

struct term* List() {
    struct term *head = NULL, *tail = NULL;
    int count, co, po;
    printf("Enter no.of terms : ");
    scanf("%d", &count);

    for (int i = 0; i < count; i++) {
        printf("Enter Coefficient and Exponent: ");
        scanf("%d%d", &co, &po);
        struct term* newNode = createNode(co, po);
        append(&head, &tail, newNode);
    }
    return head;
}

void display(struct term* list) {
    if (list == NULL) {
        printf("0\n");
        return;
    }
    struct term* temp = list;
    while (temp != NULL) {
        printf("%dx^%d", temp->co, temp->po);
        if (temp->next != NULL)
            printf(" %c ", (temp->next->co >= 0 ? '+' : ' '));
        temp = temp->next;
    }
    printf("\n");
}

struct term* addpoly(struct term* l1, struct term* l2) {
    struct term *result = NULL, *tail = NULL;

    while (l1 != NULL && l2 != NULL) {
        struct term* newNode = NULL;

        if (l1->po == l2->po) {
            int sum = l1->co + l2->co;
            newNode = createNode(sum, l1->po);
            l1 = l1->next;
            l2 = l2->next;
        }
        else if (l1->po > l2->po) {
            newNode = createNode(l1->co, l1->po);
            l1 = l1->next;
        }
        else {
            newNode = createNode(l2->co, l2->po);
            l2 = l2->next;
        }
        append(&result, &tail, newNode);
    }

    while (l1 != NULL) {
        append(&result, &tail, createNode(l1->co, l1->po));
        l1 = l1->next;
    }
    while (l2 != NULL) {
        append(&result, &tail, createNode(l2->co, l2->po));
        l2 = l2->next;
    }

    return result;
}

int main() {
    struct term *l1, *l2, *sum;

    printf("First polynomial values:\n");
    l1 = List();
    printf("First polynomial:\n");
    display(l1);

    printf("Second polynomial values:\n");
    l2 = List();
    printf("Second polynomial:\n");
    display(l2);

    sum = addpoly(l1, l2);
    printf("Sum of the two polynomials is:\n");
    display(sum);

    return 0;
}
