#include <cstdio>
#include <queue>

using std::queue;

const int dx[] = { 0, 0, 1, -1 };
const int dy[] = { -1, 1, 0, 0 };

const int n = 10;
const int m = 15;

char a[n][m];
bool u[n][m];

struct point
{
    int x;
    int y;
};

bool operator < (const point &a, const point &b)
{
    return a.y < b.y || (a.y == b.y && a.x > b.x);
}

bool valid(int x, int y)
{
    return x >= 0 && x < n && y >= 0 && y < m && a[x][y] && !u[x][y];
}

void play(int game_number)
{
    printf("Game %d:\n\n", game_number);

    int move = 0;
    int count = n * m;
    int score = 0;

    while(count > 0)
    {
        int sum = 0;
        point position;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                u[i][j] = false;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (a[i][j] && !u[i][j])
                {
                    int s = 1;
                    u[i][j] = true;
                    point p = {i, j};

                    queue<point> q;
                    q.push(p);

                    while (!q.empty())
                    {
                        point t = q.front();
                        q.pop();

                        for(int k = 0; k < 4; k++)
                        {
                            int x = t.x + dx[k];
                            int y = t.y + dy[k];

                            if (valid(x, y) && a[x][y] == a[t.x][t.y])
                            {
                                point nt = {x, y};

                                q.push(nt);
                                s++;

                                if (nt < p)
                                    p = nt;

                                u[x][y] = true;
                            }
                        }
                    }

                    if(s > sum || (s == sum && p < position))
                    {
                        sum = s;
                        position = p;
                    }
            }

        if (sum <= 1)
            break;

        char color = a[position.x][position.y];

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                u[i][j] = false;

        queue<point> q;

        u[position.x][position.y] = true;
        q.push(position);

        while (!q.empty())
        {
            point t = q.front();
            q.pop();

            for (int i = 0; i < 4; i++)
            {
                int x = t.x + dx[i];
                int y = t.y + dy[i];

                if (valid(x, y) && a[x][y] == a[t.x][t.y])
                {
                    u[x][y] = true;
                    q.push({x, y});
                }
            }
        }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (u[i][j])
                    a[i][j] = 0;

        for (int j = 0; j < m; j++)
            for (int i = n - 1; i > 0; i--)
                if (a[i][j] == 0)
                {
                    int k = i - 1;
                    while(k >= 0 && a[k][j] == 0)
                        k--;

                    if(k < 0)
                        break;

                    a[i][j] = a[k][j];
                    a[k][j] = 0;
                }

        for (int j = 0; j < m; j++)
            if (a[n - 1][j] == 0)
            {
               int k = j + 1;
               while (k < m && a[n - 1][k] == 0)
                   k++;

               if(k == m)
                   break;

               for (int i = 0; i < n; i++)
               {
                   a[i][j] = a[i][k];
                   a[i][k] = 0;
               }
            }

        count = count - sum;
        score = score + (sum - 2) * (sum - 2);

        printf("Move %d at (%d,%d): removed %d balls of color %c, got %d points.\n", ++move, n - position.x, position.y + 1, sum, color, (sum - 2) * (sum - 2));

    }

    if (count == 0)
        score = score + 1000;

    printf("Final score: %d, with %d balls remaining.", score, count);
}


int main()
{
    /*
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    */

    int game_count;
    scanf("%d\n\n", &game_count);

    for (int gn = 1; gn <= game_count; gn++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
                scanf("%c", &a[i][j]);
            scanf("\n");
        }

        scanf("\n");
        play(gn);

        printf("\n");
        if( gn < game_count)
            printf("\n");
    }
}
