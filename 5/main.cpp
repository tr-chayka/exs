#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

int a[1000];

bool check(int n)
{
	for (int i = 0; i < n;)
		if (a[i] == i)
			i++;
		else
		{
			for (int j = a[i], k = i; j >= i; j--, k++)
				if (a[j] != k)
					return false;

			i = a[i] + 1;
		}

	return true;
}

int main()
{
	/*
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	*/

	for (;;)
	{
		int n;
		scanf("%d", &n);

		if (n == 0)
			break;

		for (;;)
		{
			scanf("%d", a);
			
			if (a[0] == 0)
				break;

			a[0]--;
			for (int i = 1; i < n; i++)
			{
				scanf("%d", a + i);
				a[i]--;
			}

			printf("%s\n", check(n) ? "YES" : "NO");
		}

		printf("\n");
	}
}
