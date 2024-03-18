#include <stdio.h>
#include <stdlib.h>

void func(float* tf)
{
	for (int i = 0; i < 10; i++)
	{
		*(tf + i) = 5;
	}

}

int* mallocorrealloc(int* tab, int j)
{
	if (tab == NULL)
	{
		tab = (int*)malloc(sizeof(int) * j);

		if (tab == NULL)
		{
			exit(1);
		}
	}
	else
	{
		int* tab2 = (int*)realloc(tab, sizeof(int) * j);

		if (tab2 == NULL)
		{
			free(tab);
			exit(1);
		}

		tab = tab2;
	}

	return tab;
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
	
		free(pf2);
		free(pf1);
	}

	{
		float* tf = (float*) malloc(sizeof(float) * 10);

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

	}

	/*{
		int size;

		printf("\nDonnez une taille de tableau: ");
		scanf_s("%d", &size);

		int* tab = (int*)malloc(sizeof(int) * size);

		if (tab == NULL) 
		{
			exit(1);
		}

		for (int i = 0; i < size; i++)
		{
			printf("Rentrez une valeur:\n[%d] => ", i);
			scanf_s("%d", &tab[i]);
		}
		
		printf("\ntab: ");
		for (int i = 0; i < size; i++)
		{
			printf("%d, ", tab[i]);
		}
		
		free(tab);
	}*/

	{
		int j = 1;
		int val;
		int* tab = NULL;
		int NoValue = 0;

		for (int i = 0; i < j; i++)
		{
			printf("\nRentrez une valeur:\n[%d] => ", i);
			scanf_s("%d", &val);

			if (val != -1) 
			{
				tab = mallocorrealloc(tab, j);

				*(tab + i) = val;
				j++;

			}

			if (j == 1 && val == -1)
			{
				NoValue = 1;
			}

		}

		if (NoValue == 1) 
		{
			printf("Vous n'avez rentrer aucune valeur dans le tableau");
		}
		else 
		{
			printf("\ntab: ");
			for (int i = 0; i < j; i++)
			{
				printf("%d, ", tab[i]);
			}
		}

		free(tab);
	}
}
