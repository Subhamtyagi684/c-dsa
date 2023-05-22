#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct intList
{
    int count;
    struct node *head;
};


struct node
{
    int num;
    struct node *link;
};

typedef struct node *pNode;
typedef struct intList *iList;

struct node *insertNumberInLinkedList(iList ptr,int num,pNode lastPtr){
    struct node *first = (pNode) malloc(sizeof(struct node));
    if(lastPtr==NULL){
        ptr->head = first;
    }else{
        lastPtr->link=first;
    }
    first->num = num;
    first->link = NULL;

    ptr->count+=1;
    return first;
}

int main(){
    struct intList *mainList;
    mainList = (iList) malloc(sizeof(struct intList));
    mainList->count=0;
    mainList->head=NULL;
    pNode lastPointer = NULL;

    for(int i=1;i<=3;i++){
        lastPointer = insertNumberInLinkedList(mainList,i,lastPointer);
    }
    
    printf("Start\n");

    pNode addr= mainList->head;
    for(int i=0;i<mainList->count;i++){
        printf("%d\n",addr->num);
        addr = addr->link;
    }
    free(addr);
    printf("End\n");
    return 0;
}
