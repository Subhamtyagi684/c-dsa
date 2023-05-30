#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include "external.h"

int initStack(int num){
    return num;
    
}
struct listDetails{
    int count;
    struct data *curPtr;
    struct data *head;
};

typedef struct listDetails *stackList;

struct intStack {
    stackList stackArray;
    int count;
    int maxItems;
    int top;
};

struct data
{
    int num;
    struct data *link;
    struct data *prevLink;
};

typedef struct data *dataList;

typedef struct intStack *stackPtr;

stackPtr createStack(int num){
    
    stackPtr stackInst = (stackPtr) malloc(sizeof(stackPtr));
    stackList listInst = (stackList) malloc(sizeof(stackList));
    listInst->curPtr=NULL;
    listInst->count=0;
    listInst->head=NULL;
    stackInst->count=0;
    stackInst->maxItems=num;
    stackInst->stackArray = listInst;
    stackInst->top=-1;
    return stackInst;

}

void PUSH(int num, stackPtr stack){
    dataList daata = (dataList) malloc(sizeof(dataList));
    daata->num = num;
    daata->link=NULL;
    if(stack->count==0){
        daata->prevLink=NULL;
        stack->stackArray->head = daata;
        stack->stackArray->curPtr = daata;
    }else{
        daata->prevLink=stack->stackArray->curPtr;
        stack->stackArray->curPtr->link=daata;
        stack->stackArray->curPtr=daata;
    }
    stack->stackArray->count+=1;
    stack->count+=1;
}

void POP(stackPtr stack){
    dataList newAddr = stack->stackArray->curPtr;
    stack->stackArray->curPtr = stack->stackArray->curPtr->prevLink;
    stack->stackArray->count-=1;
    stack->count-=1;
    free(newAddr);
}

dataList getTop(stackPtr nPtr){
    return nPtr->stackArray->curPtr;
}

int main(){
    stackPtr ptr = createStack(5);
    PUSH(10,ptr);
    PUSH(20,ptr);
    PUSH(50,ptr);
    printf("Hello world!\n");
    dataList addr= ptr->stackArray->head;
    for(int i=0;i<ptr->stackArray->count;i++){
        printf("%d\n",addr->num);
        addr = addr->link;
    }
    printf("End!\n");
    POP(ptr);
    printf("Hello world!\n");
    addr= ptr->stackArray->head;
    for(int i=0;i<ptr->stackArray->count;i++){
        printf("%d\n",addr->num);
        addr = addr->link;
    }
    printf("End!\n");
    dataList curPtr = getTop(ptr);
    return 0;
}

//isEmpty function
//isFull function