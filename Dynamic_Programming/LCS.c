#include <stdio.h>
#include <string.h>

char a[500], b[500];
char num[501][501];     //记录中间结果的数组
char flag[501][501];    //标记数组，用于标识下标的走向，构造出公共子序列
                        //1:斜向下标记 2:向右标记 3:向下标记

void LCS();             //动态规划求解
void getLCS();          //采用逆推的方式求最长公共子序列

int main(int argc, char const* argv[])
{
    int i;
    strcpy(a, "ABCBDAB");
    strcpy(b, "BDCABA");
    memset(num, 0, sizeof(num));
    memset(flag, 0, sizeof(flag));

    LCS();
    printf("子串a:%s\n", a);
    printf("子串b:%s\n", b);
    printf("最长公共子序列为: ");
    getLCS();
    printf("\n最长公共子序列的长度为:%d\n", num[strlen(a)][strlen(b)]);

    return 0;
}

void LCS()
{
     int i, j;
     for(i = 1; i <= strlen(a); i++)
     {
         for(j = 1; j <= strlen(b); j++)
         {
             if(a[i-1] == b[j-1])
             {
                  num[i][j] = num[i-1][j-1] + 1;
                  flag[i][j] = 1;   //斜向下标记
             }
             else if(num[i][j-1] > num[i-1][j])
             {
                  num[i][j] = num[i][j-1];
                  flag[i][j] = 2;   //向右标记
             }
             else
             {
                 num[i][j] = num[i-1][j];
                 flag[i][j] = 3;    //向下标记
             }
         }
     }
}

void getLCS()
{
     char res[500];
     int i = strlen(a);
     int j = strlen(b);
     int k = 0;     //用于保存结果的数组标志位

     while(i > 0 && j > 0)
     {
          if(flag[i][j] == 1)   //如果是斜向下标记
          {
              res[k] = a[i-1];
              k++;
              i--;
              j--;
          }
          else if(flag[i][j] == 2)  //如果是向右标记
              j--;
          else if(flag[i][j] == 3)  //如果是向下标记
              i--;
     }

     for(i = k-1; i >= 0; i--)
         printf("%c", res[i]);
}
