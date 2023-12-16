// Binary Indexed Tree

const int MAXN = 100000;
int C[MAXN];


int sum(int i)
{
    return i ? C[i] + sum(i - lowbit(i)) : 0;
}

void add(int i, int v)
{
    if (i <= MAXN)
    {
        C[i] += v;
        add(i + lowbit(i), v);
    }
}