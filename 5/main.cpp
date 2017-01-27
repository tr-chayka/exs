#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <stack>

#define MAXN 1000

int a[MAXN];

bool check(int n)
{
	std::stack<int> b;
	std::stack<int> s;

	for (int i = n; i > 0; i--)
		b.push(i);

	for (int i = 0; i < n; i++)
	{
		int x = a[i];

		if (s.empty() || s.top() != x)
		{
			while (!b.empty() && b.top() <= x)
			{
				int y = b.top();
				b.pop();
				s.push(y);
			}

			if (s.empty() || s.top() != x)
				return false;
		}

		s.pop();
	}

	return true;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

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

			for (int i = 1; i < n; i++)
				scanf("%d", a + i);

			printf("%s\n", check(n) ? "Yes" : "No");
		}

		printf("\n");
	}
}
