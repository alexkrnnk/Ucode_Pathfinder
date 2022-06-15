#include "pathfinder.h"

void mx_all_short_path_matrix(Pointers *path)
{
    for (int i = 0; i < IslCount; i++)
    {
        for (int j = i; j < IslCount; j++)
        {
            path->unique[i][j] = path->matrix[i][j];
            path->unique[j][i] = path->matrix[j][i];
        }
    }
    for (int k = 0; k < IslCount; k++)
    {
        for (int i = 0; i < IslCount; i++)
        {
            for (int j = i + 1; j < IslCount; j++)
            {
                int sum = path->matrix[i][k] + path->matrix[k][j];
                if(path->matrix[k][j] != MAX_INT && path->matrix[i][k] != MAX_INT && sum < path->matrix[i][j])
                {
                    path->matrix[i][j] = sum;
                    path->matrix[j][i] = sum;
                }
            }
        }
    }
}

