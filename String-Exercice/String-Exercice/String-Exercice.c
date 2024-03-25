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
    int iSize = string.iLength + 1;

    string.pContent = (char*) malloc( iSize * sizeof(char) );
    if (string.pContent == NULL) exit(1);

    for (int i = 0; i < string.iLength + 1; i++) {
        string.pContent[i] = str[i];
    }

    return string;
}


void Print(const String* pStr) {
    printf("%s", pStr->pContent);
}


String Concatenate1(const String* pStr1, const String* pStr2) {
    String string;

    string.iLength = pStr1->iLength + pStr2->iLength + 1;
    string.pContent = (char*)malloc(sizeof(char) * string.iLength);
    if (string.pContent == NULL) exit(1);

    for (int i = 0; i < pStr1->iLength; i++) {
        string.pContent[i] = pStr1->pContent[i];
    }

    for (int i = 0; i <= pStr2->iLength; i++) {
        string.pContent[pStr1->iLength + i] = pStr2->pContent[i];
    }

    return string;
}


int main()
{
    String stringA = Create("JTM");
    String stringB = Create("Kiki");

    Print(&stringB);

    String LoveString = Concatenate1(&stringA, &stringB);

    Print(&LoveString);

    return 0;
}

