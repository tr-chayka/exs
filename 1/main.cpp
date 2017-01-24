#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <queue>
#include <list>

using namespace std;

struct point
{
	double x, y;
};

struct segment
{
	point a, b;
};

istream &operator >> (istream &stream, point &p)
{
	return stream >> p.x >> p.y;
}

istream &operator >> (istream &stream, segment &s)
{
	return stream >> s.a >> s.b;
}

point operator -(const point &a, const point &b)
{
	return { a.x - b.x, a.y - b.y };
}

point operator +(const point &a, const point &b)
{
	return { a.x + b.x, a.y + b.y };
}

point operator *(const point &p, double a)
{
	return { p.x * a, p.y * a };
}

point operator -(const point &a)
{
	return { -a.x, -a.y };
}

bool operator == (const point &a, const point &b)
{
	return a.x == b.x && a.y == b.y;
}

bool operator != (const point &a, const point &b)
{
	return !(a == b);
}

double cross(const point &a, const point &b)
{
	return a.x * b.y - a.y * b.x;
}

bool operator == (const segment &p, const segment &q)
{
	return p.a == q.a && p.b == q.b;
}

bool operator != (const segment &p, const segment &q)
{
	return !(p == q);
}

segment swap(const segment &s)
{
	return { s.b, s.a };
}

point center(const segment &s)
{
	return (s.a + s.b) * 0.5;
}

void sort(segment &s1, segment &s2)
{
	if (s1.a.x > s1.b.x || (s1.a.x == s1.b.x && s1.a.y > s1.b.y))
		s1 = swap(s1);

	if (s2.a.x > s2.b.x || (s2.a.x == s2.b.x && s2.a.y > s2.b.y))
		s2 = swap(s2);

	if (s1.a.x > s2.a.x || (s1.a.x == s2.a.x && s1.a.y > s2.a.y))
		swap(s1, s2);
}

bool intersect(const segment &s1, const segment &s2, point &ip)
{
	// x1 = m1 + p1 * n
	// x2 = m2 + p2 * m
	point m1 = s1.a;
	point m2 = s2.a;
	point p1 = s1.b - s1.a;
	point p2 = s2.b - s2.a;

	// {p1, - p2} * [n, m] = [m2 - m1]
	double detA = cross(p1, -p2);
	double detN = cross(m2 - m1, -p2);
	double detM = cross(p1, m2 - m1);

	if (detA == 0) // paralleled
	{
		// not lie on one line
		if (cross(s1.b - s1.a, s2.a - s1.a) != 0)
			return false;

		segment q1 = s1;
		segment q2 = s2;

		sort(q1, q2);

		if (q1.b == q2.a)
		{
			ip = q1.b;
			return true;
		}

		if (q1.b.x < q2.a.x || (q1.b.x == q2.a.x && q1.b.y < q2.a.y))
			return false;
		
		// overlapped 
		ip.x = ip.y = NAN;
		return true;
	}

	double n = detN / detA;
	double m = detM / detA;

	if (n < 0 || n > 1 || m < 0 || m > 1)
		return false;

	ip = m1 + p1 * n;
	return true;
}

int main()
{
	/*
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	*/

	int n;
	cin >> n;

	list<segment> segment_list;

	segment_list.push_back({ {0,0}, {100,0} });
	segment_list.push_back({ {0,0}, {0,100} });
	segment_list.push_back({ {100,0}, {100,100} });
	segment_list.push_back({ {0,100}, {100,100} });

	for (int i = 0; i < n; i++)
	{
		segment s;
		cin >> s;

		list<segment> new_s;
		list<segment> changed_s;
		new_s.push_back(s);

		for (auto i = segment_list.begin(); i != segment_list.end();)
		{
			bool removed = false;

			for (auto j = new_s.begin(); j != new_s.end(); ++j)
			{
				point ip;
				if (intersect(*i, *j, ip))
				{
					segment x = *i;
					segment y = *j;

					i = segment_list.erase(i);
					j = new_s.erase(j);

					if (x.a != ip)
						changed_s.push_back({ x.a, ip });
					if (x.b != ip)
						changed_s.push_back({ x.b, ip });

					if (y.a != ip)
						new_s.push_back({ y.a, ip });
					if(y.b != ip) 
						new_s.push_back({ y.b, ip });

					removed = true;
					break;
				}
			}

			if (!removed)
				++i;
		}

		for (segment j : new_s)
			segment_list.push_back(j);

		for (segment j : changed_s)
			segment_list.push_back(j);
	}

	int scount = segment_list.size();
	
	vector<int> p(scount, 0);	
	vector<segment> s;
	queue<int> q;

	s.reserve(scount);
	for (auto sg : segment_list)
		s.push_back(sg);

	segment_list.clear();

	/*
	cout << scount << "\n";
	for (int i = 0; i < scount; i++)
		cout << s[i].a.x << " " << s[i].a.y << " " << s[i].b.x << " " << s[i].b.y << "\n";
	*/

	auto p_reachable = [&s](const point &p, const segment &t)
	{
		point ip;
		segment c = { p, center(t) };

		for (auto i : s)
			if (t != i && intersect(i, c, ip))
				return false;

		return true;
	};

	auto s_reachable = [&s](const segment &t, const segment &u)
	{
		point ip;
		segment c = { center(t), center(u) };

		for (auto i : s)
			if (t != i && u != i && intersect(i, c, ip))
				return false;

		return true;
	};

	auto end_point = [](point p)
	{
		return p.x == 0 || p.y == 0 || p.x == 100 || p.y == 100;
	};

	point start;
	cin >> start;
	
	/*
	cout << start.x << " " << start.y << "\n";
	*/

	for (int i = 0; i < scount; i++)
		if (p_reachable(start, s[i]))
		{
			p[i] = 1;
			q.push(i);
		}

	// BFS
	while (!q.empty())
	{
		int i = q.front();
		q.pop();

		if (end_point(center(s[i])))
		{
			cout << "Number of doors = " << p[i] << "\n";
			return 0;
		}

		for(int j = 0; j < scount; j++)
			if (p[j] == 0 && s_reachable(s[i], s[j]))
			{
				p[j] = p[i] + 1;
				q.push(j);
			}
	}
}
