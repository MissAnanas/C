#include <stdio.h>
#include <stdlib.h>

void func(float* tf)
{
	for (int i = 0; i < 10; i++)
	{
		*(tf + i) = 5;
	}

}

int main() 
{
	{
		float f1 = 5;

		float* pf = &f1;
		*pf = 10;

		float f2;

		pf = &f2;
		*pf = 20;

		printf("f1: %f ; f2: %f", f1, f2);

	}

	{
		float* pf1 = (float*) malloc(sizeof(float));

		if (pf1 == NULL) 
		{
			exit(1);
		}

		*pf1 = 5;


		float* pf2 = (float*)malloc(sizeof(float));

		if (pf2 == NULL) 
		{
			exit(1);
		}

		float* temp = pf1;
		pf1 = pf2;
		pf2 = temp;

		printf("\npf1: %f ; pf2: %f", *pf1, *pf2);
	
		free(pf1);
		free(pf2);
	}

	{
		float* tf = (float*)malloc(sizeof(float) * 10);

		if (tf == NULL) 
		{
			exit(1);
		}

		for (int i = 0; i < 10; i++) 
		{
			*(tf + i) = 0;
		}
		
		printf("\ntf: ");
		for (int i = 0; i < 10; i++) 
		{
			printf("%f, ", *(tf + i));
		}

		func(tf);

		printf("\ntf: ");
		for (int i = 0; i < 10; i++)
		{
			printf("%f, ", *(tf + i));
		}


		free(tf);
	}

	{
		float tf[10];

		printf("\ntf: ");
		for (int i = 0; i < 10; i++) 
		{
			printf("%f", tf[i]);
		}

		for (int i = 0; i < 10; i++) 
		{
			tf[i] = 5;
		}

		printf("\ntf: ");
		for (int i = 0; i < 10; i++)
		{
			printf("%f, ", tf[i]);
		}

		free(tf);
	}
}

