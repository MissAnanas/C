#include <stdio.h>
#include <stdlib.h>

// Dynamic Array

typedef struct IntArray {
	int* pContent;

	int iSize;
	int ICapacity;

} IntArray;

void Init(IntArray* pIntArray) {
	pIntArray->pContent = (int*)malloc(sizeof(int));

	if (pIntArray->pContent == NULL) exit(1);
}

void Insert(IntArray* pIntArray, int iValue, int iIndex) {
	if (pIntArray->iSize > pIntArray->ICapacity) {
		pIntArray->ICapacity = pIntArray->iSize * 2;

		int* tab = (int*)realloc(pIntArray->pContent, pIntArray->ICapacity * sizeof(int));
		if (tab == NULL) {
			free(pIntArray->pContent);
			exit(1);
		}
		pIntArray->pContent = tab;
	}

	for (int i = pIntArray->iSize; i > iIndex; i--) {
		*(pIntArray->pContent + i + 1) = *(pIntArray->pContent + i);
	}

	*(pIntArray->pContent + iIndex) = iValue;
}

void Add(IntArray* pIntArray, int iValue) {
	Insert(pIntArray, iValue, pIntArray->iSize);
}

void Print(IntArray* pIntArray) {
	for (int i = 0; i < pIntArray->iSize; i++) {
		printf("%d", *pIntArray->pContent);
	}
}



int main() {
	IntArray pIntArray;

	Init(&pIntArray);

	Add(&pIntArray, 3);


	Print(&pIntArray);

	return 0;
}