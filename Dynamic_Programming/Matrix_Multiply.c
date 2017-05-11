#include <stdio.h>

void MatrixChain(int *p, int n, int (*m)[7], int (*s)[7])
{
    int r = 0, i = 0, j = 0, k = 0;
    int tmp = 0;

    for(i = 1; i <= n; i++)
        m[i][i] = 0;    //只有一个矩阵时，即对角线元素全置为0

    for(r = 2; r <= n; r++)
        for(i = 1; i <= n-r+1; i++)
        {
            j = i + r - 1;
            m[i][j] = m[i][i] + m[i+1][j] + p[i-1]*p[i]*p[j];
            s[i][j] = i;

            for(k = i+1; k < j; k++){
                tmp = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if(tmp < m[i][j])
                {
                    m[i][j] = tmp;
                    s[i][j] = k;
                }
            }
        }
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


int main()
{
    int n = 6;
    int p[7] = {30, 35, 15, 5, 10, 20, 25};
    int s[7][7] = {0};
    int m[7][7] = {0};

    MatrixChain(p, n, m, s);
    TrackBack(1, n, s);

    printf("\n矩阵乘法最少次数为: %d\n", m[1][6]);

    return 0;
}
