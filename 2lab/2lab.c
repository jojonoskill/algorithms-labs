#include <stdio.h>
#include <stdlib.h>

int n;

struct list {
    double data;
    struct list *next;
    struct list *prev;
}*first, *last, *newFirst, *newLast;


void create(const double A[]) {
    struct list *temp; //*first
    printf("Enter the length: ");
    scanf("%d", &n);

    first = (struct list *)malloc(sizeof(struct list));
    first -> data = A[0];
    first -> next = NULL;
    first -> prev = NULL;
    last = first;

    for (int i = 1; i < n; i++) {
        temp = (struct list*)malloc(sizeof(struct list));
        temp->data = A[i];
        temp->next = NULL;
        temp->prev = last;
        last -> next = temp;
        last = temp;
    }
}

void display(struct list *p) {
    while (p!=NULL) {
        printf("source = %d,data = %f, next=%d, prev=%d \n  ", p , p->data, p->next, p->prev);
        p = p->next;
    }

    printf("\n\n\n");
}


void makeMagic(struct list *temp_first, struct list *temp_last) {
    struct list *temp, *temp2; //*first
    newFirst = (struct list*)malloc(sizeof(struct list));
    newFirst->data = temp_first->data;
    newFirst->prev = NULL;
    newFirst->next = NULL;
    newLast=newFirst;
    temp_first = temp_first->next;

    for (int i = 1; i <= n/2; i++) {
        temp = (struct list*)malloc(sizeof(struct list));
        temp->data = temp_last->data;
        temp->next = NULL;
        temp->prev = newLast;
        newLast -> next = temp;
        newLast = temp;
        temp_last=temp_last->prev;


        temp2 = (struct list*)malloc(sizeof(struct list));
        temp2->data = temp_first->data;
        if(i == n/2 &&  temp2->data == temp->data) break;
        temp2->next = NULL;
        temp2->prev = newLast;
        newLast -> next = temp2;
        newLast = temp2;
        temp_first=temp_first->next;

    }

}

struct list * delElement(struct list *p){
    struct list *node_p = p->next;
    if(!p) free(p);
    return node_p;
}

void delList(struct list *p){
    for(int i = 0;i < n;i++){
        p = delElement(p);
    }
}

int main() {
    double A[] = {16, 25, -65, 164, 19 , -4, 29, 30 , -45 , 13,150};  // array of values for a list
    create(A);  // linked list is created
    printf("Initial list\n");
    display(first);
    makeMagic(first,last);
    printf("Final list\n");
    display(newFirst);
    delList(first);
    delList(newFirst);
}
