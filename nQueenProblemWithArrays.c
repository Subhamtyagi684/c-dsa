#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct queenPosition
{
    int pos[2];
};

typedef struct queenPosition *posPtr;

struct intStack
{
    posPtr stackArray;
    int count;
    int maxItems;
    int top;
};

typedef struct intStack *stackPtr;

stackPtr createStackForNQueens(int num)
{
    stackPtr ptr = (stackPtr)malloc(sizeof(stackPtr));
    ptr->count = 0;
    ptr->top = -1;
    ptr->maxItems = num;
    ptr->stackArray = (posPtr)malloc(num * sizeof(posPtr));
    return ptr;
}

int checkPlacementInRow(stackPtr posPtr, int *curRow, int *curCol)
{
    if (*curRow > posPtr->maxItems)
    {
        return 0;
    }
    for (int i = 1; i <= posPtr->maxItems; i++)
    {
        if (i == posPtr->count + 1)
        {
            if (i == posPtr->maxItems)
            {
                return 0;
            }
            continue;
        };
        if ((posPtr->stackArray + i - 1)->pos[0] == *curRow)
        {
            return 1;
        }
    }
    return 0;
}

int checkPlacementInColumn(stackPtr posPtr, int *curRow, int *curCol)
{
    // (curRow=3,curCol=1
    if (*curCol > posPtr->maxItems)
    {
        return 0;
    }

    for (int i = 1; i <= posPtr->maxItems; i++)
    {
        if (i == posPtr->count + 1)
        {
            if (i == posPtr->maxItems)
            {
                return 0;
            }
            continue;
        }
        if ((posPtr->stackArray + i - 1)->pos[1] == *curCol)
        {
            return 1;
        }
    }
    return 0;
}

int checkPlacementInDiagonal(stackPtr posPtr, int *curRow, int *curCol)
{
    // (curRow=3,curCol=3)
    int nRow = *curRow;
    int nCol = *curCol;

    while (nRow != 0)
    {
        /* code */
        nRow-=1;
        nCol-=1;
        if (nRow < 1 || nCol < 1)
        {
            continue;
        }

        for (int i = 1; i <= posPtr->maxItems; i++)
        {
            if (i == posPtr->count + 1)
            {
                if (i == posPtr->maxItems)
                {
                    goto next1;
                }
                continue;
            }
            if ((posPtr->stackArray + i - 1)->pos[0] == nRow && (posPtr->stackArray + i - 1)->pos[1] == nCol)
            {
                return 1;
            };
        };
    }
    next1:
        nRow = *curRow;
        nCol = *curCol;
        while (nRow < posPtr->maxItems)
        {
            /* code */
            nRow += 1;
            nCol += 1;
            if (nRow > posPtr->maxItems || nCol > posPtr->maxItems)
            {
                continue;
            }
            for (int i = 1; i <= posPtr->maxItems; i++)
            {
                if (i == posPtr->count + 1)
                {
                    if (i == posPtr->maxItems)
                    {
                        goto next2;
                    }
                    continue;
                }
                
                if ((posPtr->stackArray + i - 1)->pos[0] == nRow && (posPtr->stackArray + i - 1)->pos[1] == nCol)
                {
                    return 1;
                };
            };
        }

    next2:
        nRow = *curRow;
        nCol = *curCol;
        nRow += 1;
        nCol -= 1;
        while ((nRow <= posPtr->maxItems) && (nCol > 0))
        {
            for (int i = 1; i <= posPtr->maxItems; i++)
            {
                if (i == posPtr->count + 1)
                {
                    if (i == posPtr->maxItems)
                    {
                        goto next3;
                    }
                    continue;
                }
                if ((posPtr->stackArray + i - 1)->pos[0] == nRow && (posPtr->stackArray + i - 1)->pos[1] == nCol)
                {
                    return 1;
                };
            };
            nRow+=1;
            nCol-=1;
        }

    next3:
        nRow = *curRow;
        nCol = *curCol;
        nRow-=1;
        nCol+=1;
        while (nCol <= posPtr->maxItems && nRow > 0)
        {
            /* code */

            for (int i = 1; i <= posPtr->maxItems; i++)
            {
                if (i == posPtr->count + 1)
                {
                    if (i == posPtr->maxItems)
                    {
                        goto next4;
                    }
                    continue;
                }
                if ((posPtr->stackArray + i - 1)->pos[0] == nRow && (posPtr->stackArray + i - 1)->pos[1] == nCol)
                {
                    return 1;
                };
            };
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
    ptr->stackArray->pos[0] = 1;
    ptr->stackArray->pos[1] = 1;
    while (ptr->count < ptr->maxItems)
    {
        if (ptr->count)
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
                    // (3,2)
                    (ptr->stackArray + (ptr->count))->pos[0] = 0;
                    (ptr->stackArray + (ptr->count))->pos[1] = 0;
                    ptr->count-=1;
                    *row-=1;
                    *column = (ptr->stackArray + (ptr->count))->pos[1] + 1;
                    if(*column>ptr->maxItems){
                        (ptr->stackArray + (ptr->count))->pos[0] = 0;
                        (ptr->stackArray + (ptr->count))->pos[1] = 0;
                        ptr->count-=1;
                        *row-=1;
                        *column = (ptr->stackArray + (ptr->count))->pos[1] + 1;
                    }
                    (ptr->stackArray + (ptr->count))->pos[1] = *column;
                    continue;
                }
            }
            else
            {
                
                if(*column==ptr->maxItems){
                    (ptr->stackArray + (ptr->count))->pos[0] = 0;
                    (ptr->stackArray + (ptr->count))->pos[1] = 0;
                    ptr->count-=1;
                    *row-=1;
                    *column = (ptr->stackArray + (ptr->count))->pos[1] + 1;
                    if(*column>ptr->maxItems){
                        (ptr->stackArray + (ptr->count))->pos[0] = 0;
                        (ptr->stackArray + (ptr->count))->pos[1] = 0;
                        ptr->count-=1;
                        *row-=1;
                        *column = (ptr->stackArray + (ptr->count))->pos[1] + 1;
                    }
                    (ptr->stackArray + (ptr->count))->pos[1] = *column;
                    
                }else{
                    *column += 1;
                    (ptr->stackArray + (ptr->count))->pos[1] = *column;
                }
                continue;
            }
        }else{
            *row += 1;
            (ptr->stackArray + (ptr->count))->pos[0] = *row;
            continue;
        };

        *row += 1;
        *column += 2;
        if(*column>ptr->maxItems){
            *column=1;
        }
        ptr->count += 1;
        (ptr->stackArray + (ptr->count))->pos[0] = *row;
        (ptr->stackArray + (ptr->count))->pos[1] = *column;
    }
}

int main()
{
    printf("Start!\n");
    stackPtr stack = createStackForNQueens(8);
    placeQueensInStack(stack);
    for (int i = 0; i < stack->maxItems; i++)
    {
        printf("[ %d, %d ]\n", (stack->stackArray + i)->pos[0], (stack->stackArray + i)->pos[1]);
    }
    printf("End!\n");
    return 0;
}
