#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element[100];
typedef struct DListNode {
    element data;
    struct DListNode* llink;
    struct DListNode* rlink;
} DListNode;

void init(DListNode* phead)
{
    phead->llink = phead;
    phead->rlink = phead;
}

void print_dlist(DListNode* phead, DListNode* current)
{
    DListNode* p;
    for (p = phead->rlink; p != phead; p = p->rlink) {
        printf("%s", p->data);
        if (p == current)
            printf(" [O]");
        printf("\n");
    }
    printf("\n");
}

void dinsert(DListNode* before, element data)
{
    DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
    strncpy(newnode->data, data, sizeof(element) - 1);
    newnode->data[sizeof(element) - 1] = '\0';
    newnode->llink = before;
    newnode->rlink = before->rlink;
    before->rlink->llink = newnode;
    before->rlink = newnode;
}

void ddelete(DListNode* head, DListNode* removed)
{
    if (removed == head) return;
    removed->llink->rlink = removed->rlink;
    removed->rlink->llink = removed->llink;
    free(removed);
}

int main(void)
{
    DListNode* head = (DListNode*)malloc(sizeof(DListNode));
    init(head);
    DListNode* current = head;
    char select;
    element fruit;

    while (1) {
        printf("==== Menu ====\n");
        printf("n) next fruit\n");
        printf("p) previous fruit\n");
        printf("d) delete the current fruit\n");
        printf("i) insert fruit after current fruit\n");
        printf("o) output the fruit list(output [O] at the end of the currently selected fruit)\n");
        printf("e) exit the program\n");
        printf("===============\n");
        printf("Select a menu: ");
        scanf(" %c", &select);

        switch (select) {
        case 'n':
            if (current->rlink != head) {
                current = current->rlink;
            }
            printf("\n");
            break;
        case 'p':
            if (current->llink != head) {
                current = current->llink;
            }
            printf("\n");
            break;
        case 'd':
            if (current != head) {
                DListNode* temp = current;
                current = current->llink;
                ddelete(head, temp);
                current = current->rlink;
            }
            printf("\n");
            break;
        case 'i':
            printf("Enter the name of he fruit to add: ");
            scanf("%s", fruit);
            dinsert(current, fruit);
            if (current->rlink == current->llink) {
                current = current->rlink;
            }
            printf("\n");
            break;
        case 'o':
            print_dlist(head, current);
            printf("\n");
            break;
        case 'e':
            printf("Exit the program.\n\n");
            free(head);
            exit(1);
        default:
            printf("Invalid menu.\n\n");
            break;
        }
    }

    return 0;
}
