#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int a[] = {6, 1, 4, 9, 5, 7, 2, 3, 8};

void Swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
int Random(int low, int hig)
{
    srand((unsigned)time(NULL));
    int ran = rand() % ((hig-low) + low);

    return ran;
}

int Partition(int a[], int low, int hig)
{
    int tmp = 0, i = 0, j = 0;

    if(low < hig){
        tmp = a[hig];
        i = low - 1;
    }
    for(j = low; j < hig; j++){
        if(a[j] < tmp){
            Swap(&a[i+1], &a[j]);
            i++;
        }
    }
    Swap(&a[hig], &a[i+1]);

    return i+1;
}

//确定一个基准元素，将子数组a[p, r]进行划分
int Random_partition(int a[], int p, int r)
{
    int i = Random(p, r);

    Swap(&a[i], &a[p]);

    return Partition(a, p, r);
}

void Random_select(int a[], int low, int hig, int aim)
{
    if(low == hig){
        printf("the num of smallest data what you want to find is: %d\n", a[low]);
        return ;
    }
    int i = Random_partition(a, low, hig);
    int j = i - low + 1;
    if(aim == j){
        printf("the num of smallest data what you want to find is: %d\n", a[i]);
        return ;
    }
    else if(aim < j)
        Random_select(a, low, i-1, aim);
    else
        Random_select(a, i+1, hig, aim-j);
}

int main()
{
    int i = 0, k = 0;

    printf("please input the num of smallest data what you want to find: ");
    scanf("%d", &k);
    printf("original array: \n");
    for(i = 0; i < 9; ++i)
        printf("%-4d", a[i]);
    printf("\n");

    Random_select(a, 0, 8, k);

    return 0;
}
