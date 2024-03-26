#include <stdio.h>
#include <stdlib.h>

typedef struct String {
    char* pContent;
    int iLength;
} String;

int GetLength(const char* str)
{
    int count = 0;

    while (str[count] != '\0') {
        count++;
    }

    return count;
}

String Create(const char* str) {
    String string;

    string.iLength = GetLength(str);

    string.pContent = (char*) malloc( (string.iLength + 1) * sizeof(char) );
    if (string.pContent == NULL) exit(1);

    for (int i = 0; i < string.iLength + 1; i++) {
        string.pContent[i] = str[i];
    }

    return string;
}


void Print(const String* pStr) {
    for (int i = 0; i < pStr->iLength; i++) {
        printf("%c", pStr->pContent[i]);
    }
    printf("\n");
}


String Concatenate1(const String* pStr1, const String* pStr2) {
    String string;

    string.iLength = pStr1->iLength + pStr2->iLength;
    string.pContent = (char*)malloc(sizeof(char) * (string.iLength + 1));
    if (string.pContent == NULL) exit(1);

    for (int i = 0; i < pStr1->iLength; i++) {
        string.pContent[i] = pStr1->pContent[i];
    }

    for (int i = 0; i <= pStr2->iLength; i++) {
        string.pContent[pStr1->iLength + i] = pStr2->pContent[i];
    }

    return string;
}


String Concatenate2(const char* str1, const char* str2) {
    String string1;
    String string2;
    String newstring;

    string1.iLength = GetLength(str1);
    string2.iLength = GetLength(str2);
    newstring.iLength = string1.iLength + string2.iLength;

    newstring.pContent = (char*)malloc(sizeof(char) * (newstring.iLength + 1));
    if (newstring.pContent == NULL) exit(1);

    for (int i = 0; i < string1.iLength; i++) {
        newstring.pContent[i] = str1[i];
    }

    for (int i = 0; i <= string2.iLength; i++) {
        newstring.pContent[string1.iLength + i] = str2[i];
    }

    return newstring;
}


String Substring(const String* pStr1, int iStartIndex, int iLength) {
    String newstring;
    newstring.iLength = iLength;

    newstring.pContent = (char*)malloc(sizeof(char) * (iLength + 1));
    if (newstring.pContent == NULL) exit(1);

    for (int i = 0; i < iLength; i++) {
        newstring.pContent[i] = pStr1->pContent[iStartIndex + i];
    }
    newstring.pContent[iLength] = '\0';

    return newstring;
}


String Insert(const String* pStr1, const String* pStr2, int iIndex) {
    
    String newstring;
    int iLength = pStr1->iLength + pStr2->iLength;
    newstring.iLength = iLength;

    newstring.pContent = (char*)malloc(sizeof(char) * (iLength + 1));
    if (newstring.pContent == NULL) exit(1);

    for (int i = 0; i < iIndex; i++) {
        newstring.pContent[i] = pStr1->pContent[i];
    }

    for (int i = 0; i < pStr2->iLength; i++) {
        newstring.pContent[iIndex + i] = pStr2->pContent[i];
    }

    for (int i = 0; i < pStr1->iLength; i++) {
        int iCurrentIndex = iIndex + pStr2->iLength + i;
        newstring.pContent[iCurrentIndex] = pStr1->pContent[i];
    }

    return newstring;
}


int AreEquals(const String* pStr1, const String* pStr2) {
    if (pStr1->iLength != pStr2->iLength) return 0;

    for (int i = 0; i < pStr1->iLength; i++) {
        if (pStr1->pContent[i] != pStr2->pContent[i]) return 0;
    }

    return 1;
}

int IsDigit(const String* pStr, int iIndex) {

}

int TryCastToInt(const String* pStr1, int* presult) {
    char Checktab[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int intTab[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    for (int i = 0; i < pStr1->iLength; i++) {
        for (int j = 0; j < 10; j++) {
            if (pStr1->pContent[i] != Checktab[j]) {
                continue;
            }
            else {


                break;
            }
            
            
        }
    }
}


void Destroy(String* pStr) {
    free(pStr->pContent);
}


int main()
{
    String stringA = Create("AA");
    String stringB = Create("BB");
    Print(&stringA);
    Print(&stringB);

    String LoveString = Concatenate1(&stringA, &stringB);
    Print(&LoveString);

    String stringC = Concatenate2("Hello ", "World !");
    Print(&stringC);

    String stringD = Create("Willem Giron Saulnier de Praingy");
    String cutstring = Substring(&stringD, 7, 25);
    Print(&cutstring);
   
    String stringE = Insert(&stringA, &stringB, 1);
    Print(&stringE);

    String stringAP = Create("AA");
    String stringBP = Create("B");

    int isEqual = AreEquals(&stringA, &stringB);
    printf("%d", isEqual);

    isEqual = AreEquals(&stringA, &stringBP);
    printf("%d", isEqual);

    isEqual = AreEquals(&stringA, &stringAP);
    printf("%d", isEqual);


    Destroy(&stringA);
    Destroy(&stringAP);
    Destroy(&stringB);
    Destroy(&stringBP);
    Destroy(&LoveString);
    Destroy(&stringC);
    Destroy(&cutstring);

    return 0;
}

