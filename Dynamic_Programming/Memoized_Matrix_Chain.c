#include <stdio.h>

int p[7] = {30, 35, 15, 5, 10, 20, 25};
int n = 6;
int m[7][7] = {0};
int s[7][7] = {0};

int LookupChain(int i, int j)
{
    if(m[i][j] > 0)
        return m[i][j];
    if(i == j)
        return 0;

    int u = LookupChain(i,i) + LookupChain(i+1, j) + p[i-1]*p[i]*p[j];
    s[i][j] = i;

    for(int k = i+1; k < j; k++){
        int t = LookupChain(i, k) + LookupChain(k+1, j) + p[i-1]*p[k]*p[j];
        if(t < u){
            u = t;
            s[i][j] = k;
        }
    }
    m[i][j] = u;

    return u;
}

int Memorized_Matrix_Chain(int n, int (*m)[7], int (*s)[7])
{
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            m[i][j] = 0;

    return LookupChain(1, n);
}

void TrackBack(int i, int j, int (*s)[7])
{
    if(i == j)
        return;
    TrackBack(i, s[i][j], s);      //第一次断开位置的前半部分
    TrackBack(s[i][j]+1, j, s);    //第一次断开位置的后半部分
    printf("A%d", i);
    printf(" and A%d", j);
    printf("\n");
}

int main(int argc, char const* argv[])
{

    Memorized_Matrix_Chain(n, m, s);
    TrackBack(1, n, s);

    printf("\n矩阵乘法最少次数为: %d\n", m[1][6]);

    return 0;
}
