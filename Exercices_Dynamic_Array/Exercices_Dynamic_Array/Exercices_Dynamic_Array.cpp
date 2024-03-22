#include <stdio.h>
#include <stdlib.h>

// Dynamic Array

typedef struct IntArray {
    int* pContent;

    int iSize;
    int ICapacity;

} IntArray;

void Init(IntArray* pIntArray) {
    pIntArray->iSize = 0;
    pIntArray->ICapacity = 1;

    pIntArray->pContent = (int*)malloc(sizeof(int) * pIntArray->ICapacity);

    if (pIntArray->pContent == NULL) exit(1);
}

void Insert(IntArray* pIntArray, int iValue, int iIndex) {
    if (iIndex > pIntArray->iSize) {
        printf("L'index %d pour la valeur %d est en dehors du tableau\n", iIndex, iValue);
        return;
    }

    if (pIntArray->iSize >= pIntArray->ICapacity) {
        pIntArray->ICapacity *= 2;

        int* tab = (int*)realloc(pIntArray->pContent, pIntArray->ICapacity * sizeof(int));
        if (tab == NULL) {
            free(pIntArray->pContent);
            exit(1);
        }
        pIntArray->pContent = tab;
    }

    if (pIntArray->iSize > 0) 
    {
        for (int i = pIntArray->iSize - 1; i >= iIndex; i--) {
            pIntArray->pContent[i + 1] = pIntArray->pContent[i];
        }
    }
    
    pIntArray->pContent[iIndex] = iValue;
    pIntArray->iSize++;
}

void Add(IntArray* pIntArray, int iValue) {
    Insert(pIntArray, iValue, pIntArray->iSize);
}

void Remove(IntArray* pIntArray, int iIndex) {
    if (iIndex > pIntArray->iSize) {
        printf("L'index est en dehors du tableau\n");
        return;
    }

    for (int i = iIndex; i <= pIntArray->iSize; i++) {
        *(pIntArray->pContent + i) = *(pIntArray->pContent + (i + 1));
    }

    pIntArray->iSize--;

    if (pIntArray->iSize < pIntArray->ICapacity / 2) {
        pIntArray->ICapacity = pIntArray->ICapacity / 2;
        int* tab = (int*)realloc(pIntArray->pContent, pIntArray->ICapacity * sizeof(int));
        if (tab == NULL) {
            free(pIntArray->pContent);
            exit(1);
        }
        pIntArray->pContent = tab;
    }
}

void Get(IntArray* pIntArray, int iIndex) {
    if (iIndex > pIntArray->iSize) {
        printf("L'index est en dehors du tableau\n");
        return;
    }
}

void Print(IntArray* pIntArray) {
    for (int i = 0; i < pIntArray->iSize; i++) {
        printf("%d ; ", pIntArray->pContent[i]);
    }

    printf("\niSize : %d", pIntArray->iSize);
    printf("\nICapacity : %d\n", pIntArray->ICapacity);
}

void Destroy(IntArray* pIntArray) {
    free(pIntArray->pContent);
}

int main() {
    IntArray pIntArray;

    Init(&pIntArray);

    Insert(&pIntArray, 3, 0);
    Insert(&pIntArray, 1, 0);
    Insert(&pIntArray, 2, 1);
    Insert(&pIntArray, 50, 5);
    Insert(&pIntArray, 55, 2);

    Print(&pIntArray);

    Add(&pIntArray, 99);
    Add(&pIntArray, 100);
    Add(&pIntArray, 101);

    Insert(&pIntArray, 50, 5);
    Print(&pIntArray);

    Remove(&pIntArray, 6);

    Print(&pIntArray);

    Remove(&pIntArray, 1);
    Remove(&pIntArray, 1);
    Remove(&pIntArray, 1);
    Remove(&pIntArray, 1);

    Print(&pIntArray);

    Destroy(&pIntArray);

    return 0;
}