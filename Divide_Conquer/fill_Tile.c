#include <stdio.h>
#define TILE_SIZE 8

int tile[TILE_SIZE][TILE_SIZE]; //地砖的大小

//s_x, s_y; 地砖开始的坐标
//d_x, d_y; 脏块的坐标
//size = 2^k;
void fill_Tile(int s_x, int s_y, int d_x, int d_y, int size)
{
    if(1 == size)
        return ;
    int half_size;
    static int dirty_num = 1;
    int d = dirty_num++;
    half_size = size/2;

    if(d_x < s_x + half_size && d_y < s_y + half_size) //脏块在左上角的地砖上
        fill_Tile(s_x, s_y, d_x, d_y, half_size);
    else    //脏块不在左上角的地砖上，则填脏块在该地砖的右下角
    {
        tile[s_x + half_size - 1][s_y + half_size - 1] = d;
        fill_Tile(s_x, s_y, s_x + half_size - 1, s_y + half_size - 1, half_size);
    }

    if(d_x < s_x + half_size && d_y >= s_y + half_size) //脏块在右上角的地砖上
        fill_Tile(s_x, s_y + half_size, d_x, d_y, half_size);
    else    //脏块不在右上角的地砖上，则填脏块在该地砖的左下角
    {
        tile[s_x + half_size - 1][s_y + half_size] = d;
        fill_Tile(s_x, s_y + half_size, s_x + half_size - 1, s_y + half_size, half_size);
    }

    if(d_x >= s_x + half_size && d_y < s_y + half_size) //脏块在左下角的地砖上
        fill_Tile(s_x + half_size, s_y, d_x, d_y, half_size);
    else    //脏块不在左下角的地砖上，则填脏块在该地砖的右上角
    {
        tile[s_x + half_size][s_y + half_size - 1] = d;
        fill_Tile(s_x + half_size, s_y, s_x + half_size, s_y + half_size - 1, half_size);
    }

    if(d_x >= s_x + half_size && d_y >= s_y + half_size) //脏块在右下角的地砖上
        fill_Tile(s_x + half_size, s_y + half_size, d_x, d_y, half_size);
    else    //脏块不在右下角的地砖上，则填脏块在该地砖的左上角
    {
        tile[s_x + half_size][s_y + half_size] = d;
        fill_Tile(s_x + half_size, s_y + half_size, s_x + half_size, s_y + half_size, half_size);
    }
}

int main()
{
    int i, j;

    tile[2][2] = 0;//脏块的位置
    fill_Tile(0, 0, 2, 2, TILE_SIZE);

    printf("'0'表示脏块所在的位置:\n");
    for(i=0; i<TILE_SIZE; i++)
    {
        for(j=0; j<TILE_SIZE; j++)
            printf("%-4d", tile[i][j]);
        printf("\n");
    }

    return 0;
}
