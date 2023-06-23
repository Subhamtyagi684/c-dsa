#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct queenPosition
{
    int pos[2];
    struct queenPosition *lastAddr;
};

typedef struct queenPosition *posPtr;

struct intStack
{
    posPtr stackArray;
    int count;
    int maxItems;
    posPtr top;
};

typedef struct intStack *stackPtr;

stackPtr createStackForNQueens(int num)
{
    stackPtr ptr = (stackPtr)malloc(sizeof(stackPtr));
    ptr->count = 0;
    ptr->maxItems = num;
    ptr->stackArray = NULL;
    ptr->top = NULL;
    return ptr;
}

int checkPlacementInRow(stackPtr mainPtr, int *curRow, int *curCol)
{
    if (*curRow > mainPtr->maxItems)
    {
        return 0;
    }

    posPtr curVal = mainPtr->top->lastAddr;
    while (curVal!=NULL)
    {
        if(curVal->pos[0]==*curRow){
            return 1;
        }
        curVal = curVal->lastAddr;
    }
    
    return 0;
}

int checkPlacementInColumn(stackPtr mainPtr, int *curRow, int *curCol)
{
    if (*curCol > mainPtr->maxItems)
    {
        return 0;
    }

    posPtr curVal = mainPtr->top->lastAddr;
    while (curVal!=NULL)
    {
        if(curVal->pos[1]==*curCol){
            return 1;
        }
        curVal = curVal->lastAddr;
    }
    
    return 0;
}

int checkPlacementInDiagonal(stackPtr mainPtr, int *curRow, int *curCol)
{
    // (curRow=3,curCol=3)
    int nRow = *curRow;
    int nCol = *curCol;
    posPtr curVal = mainPtr->top->lastAddr;
    while (nRow != 0)
    {
        /* code */
        nRow-=1;
        nCol-=1;
        if (nRow < 1 || nCol < 1)
        {
            continue;
        }
        while (curVal!=NULL)
        {
           if (curVal->pos[0]==nRow  &&  curVal->pos[1]==nCol)
           {
                return 1;
           }
            curVal = curVal->lastAddr;
        }

    }
    next1:
        nRow = *curRow;
        nCol = *curCol;
        curVal = mainPtr->top->lastAddr;
        while (nRow < mainPtr->maxItems)
        {
            /* code */
            nRow += 1;
            nCol += 1;
            if (nRow > mainPtr->maxItems || nCol > mainPtr->maxItems)
            {
                continue;
            }
            while (curVal!=NULL)
            {
                if (curVal->pos[0]==nRow  &&  curVal->pos[1]==nCol)
                {
                        return 1;
                }
                curVal = curVal->lastAddr;
            }
        }

    next2:
        nRow = *curRow;
        nCol = *curCol;
        nRow += 1;
        nCol -= 1;
        curVal = mainPtr->top->lastAddr;
        while ((nRow <= mainPtr->maxItems) && (nCol > 0))
        {
            while (curVal!=NULL)
            {
                if (curVal->pos[0]==nRow  &&  curVal->pos[1]==nCol)
                {
                        return 1;
                }
                curVal = curVal->lastAddr;
            }
            nRow+=1;
            nCol-=1;
        }

    next3:
        nRow = *curRow;
        nCol = *curCol;
        nRow-=1;
        nCol+=1;
        curVal = mainPtr->top->lastAddr;
        while (nCol <= mainPtr->maxItems && nRow > 0)
        {
            while (curVal!=NULL)
            {
                if (curVal->pos[0]==nRow  &&  curVal->pos[1]==nCol)
                {
                        return 1;
                }
                curVal = curVal->lastAddr;
            }
            nRow-=1;
            nCol+=1;
        }

    next4:
        return 0;

    return 0;
}

int rowChecked = 0;
int colChecked = 0;

void placeQueensInStack(stackPtr ptr)
{

    int totalItems = ptr->maxItems;
    int count = ptr->count + 1;
    int *row = (int *)malloc(sizeof(int));
    int *column = (int *)malloc(sizeof(int));
    *row = 1;
    *column = 1;
    posPtr startAddr;
    startAddr = (posPtr)malloc(sizeof(posPtr));
    startAddr->lastAddr= NULL;
    ptr->stackArray = startAddr;
    ptr->top = startAddr;
    
    while (ptr->count < ptr->maxItems)
    {
        
        startAddr->pos[0]=*row;
        startAddr->pos[1] = *column;
        if (*column > ptr->maxItems)
        {
            *column = 1;
        }

        int columnFound = 0, diagonalFound = 0;

        int rowFound = checkPlacementInRow(ptr, row, column);
        if (!rowFound)
        {
            columnFound = checkPlacementInColumn(ptr, row, column);
            if (!columnFound)
            {
                diagonalFound = checkPlacementInDiagonal(ptr, row, column);
                if (diagonalFound)
                {
                    ptr->top = ptr->top->lastAddr;
                    ptr->count-=1;
                    *row-=1;
                    *column = ptr->top->pos[1] + 1;
                    if(*column>ptr->maxItems){
                        ptr->top = ptr->top->lastAddr;
                        ptr->count-=1;
                        *row-=1;
                        *column = ptr->top->pos[1] + 1;
                    }
                    ptr->top->pos[1] = *column;
                    continue;
                }

            }
            else
            {
                
                if(*column==ptr->maxItems){
                    ptr->top = ptr->top->lastAddr;
                    ptr->count-=1;
                    *row-=1;
                    *column = ptr->top->pos[1] + 1;
                    if(*column>ptr->maxItems){
                        ptr->top = ptr->top->lastAddr;
                        ptr->count-=1;
                        *row-=1;
                        *column = ptr->top->pos[1] + 1;
                    }
                    ptr->top->pos[1] = *column;
                    
                }else{
                    *column += 1;
                    ptr->top->pos[1]=*column;
                }
                continue;
            }
        }else{
            *row += 1;
            ptr->top->pos[0]=*row;
            continue;
        };
        
        *row += 1;
        *column += 2;
        if(*column>ptr->maxItems){
            *column=1;
        }
        ptr->count += 1;
        if (ptr->count<ptr->maxItems)
        {
            startAddr = (posPtr)malloc(sizeof(posPtr));
            startAddr->lastAddr = ptr->top;
            ptr->top = startAddr;
        }
        
        
    };
}

int main()
{
    printf("Start!\n");
    stackPtr stack = createStackForNQueens(50);
    placeQueensInStack(stack);
    posPtr nPtr = stack->top;
    while (nPtr!=NULL)
    {   
        printf("[ %d, %d ]\n", nPtr->pos[0],nPtr->pos[1]);
        nPtr = nPtr->lastAddr;
    }
    
    printf("End!\n");
    return 0;
}
