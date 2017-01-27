#define _CRT_SECURE_NO_WARNINGS
#define MAXN 10000

#include <cstdio>
#include <ctime>

char a[MAXN][MAXN];
char t[MAXN][MAXN];

bool equal(char x, char y)
{
	return (x == y) || (x == '*' && y == '0') || (x == '2' && y == '1');
}

void change(char &c)
{
	if (c == '0')
		c = '*';

	if (c == '1')
		c = '2';
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int tn, tm, an, am, x;

	scanf("%d%d", &tn, &tm);
	for (int i = 0; i < tn; i++)
		for (int j = 0; j < tm; j++)
		{
			scanf("%d", &x);
			t[i][j] = x + '0';
		}

	scanf("%d%d", &an, &am);
	for (int i = 0; i < an; i++)
		for (int j = 0; j < am; j++)
		{
			scanf("%d", &x);
			a[i][j] = x + '0';
		}


	if (tn <= an && tm <= am)
	{
		for (int u = 0; u <= an - tn; u++)
			for (int v = 0; v <= am - tm; v++)
			{
				for (int i = 0; i < tn; i++)
					for (int j = 0; j < tm; j++)
						if (!equal(a[u + i][v + j], t[i][j]))
							goto END;
	
				for (int i = 0; i < tn; i++)
					for (int j = 0; j < tm; j++)
						change(a[u + i][v + j]);
				
				END:;
			}
	}

	for (int i = 0; i < an; i++)
	{
		for (int j = 0; j < am; j++)
			printf("%c ", a[i][j]);
		printf("\n");
	}
}