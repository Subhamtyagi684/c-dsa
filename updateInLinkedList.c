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

void *updateNumberInLinkedList(int index,int num,pNode lastPtr,iList ptr){

    struct node *first = (pNode) malloc(sizeof(struct node));
    first->num = num;
    if(index==0){
        first->link = lastPtr;
        ptr->head = first;
    }else if(index==ptr->count){
        first->link = NULL;
        lastPtr->link=first;
    }else{
        first->link = lastPtr->link;
        lastPtr->link=first;
    }

    
}

void addValueAtPosition(int pos,int num, iList ptr){
    if(pos>ptr->count){
        printf("Error: Index out of range\n");
        exit(EXIT_FAILURE);
    }
    pNode prevPtr;
    for(int i=0;i<=pos;i++){
        if(i==0 || i==1){
            prevPtr = ptr->head;
        }else{
            prevPtr = prevPtr->link;
        }
    }
    updateNumberInLinkedList(pos,num,prevPtr,ptr);
    ptr->count+=1;
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
    if(mainList->count){
        for(int i=0;i<mainList->count;i++){
            printf("%d\n",addr->num);
            addr = addr->link;
        }
    }
    free(addr);
    printf("End of insert\n");
    printf("Start update\n");
    addValueAtPosition(0,12,mainList);
    addr= mainList->head;
    for(int i=0;i<mainList->count;i++){
        printf("%d\n",addr->num);
        addr = addr->link;
    }
    free(addr);
    printf("End update\n");
    return 0;
}
