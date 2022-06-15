#include "pathfinder.h"

int get_Name_id(Pointers *path, char *island)
{
    for (int i = 0; i < IslCount; i++)
    {
        if (mx_strcmp(island, path->unique_isl[i]) == 0)
        {
            return i;
        }
    }
    return 0;
}

void mx_matrix(Pointers *path)
{
    path->matrix = (int**)malloc(8 * IslCount);
    path->unique = (int**)malloc(8 * IslCount);
    for (int i = 0; i < IslCount; i++)
    {
        path->matrix[i] = malloc(8 * IslCount);
        path->unique[i] = malloc(8 * IslCount);
        for (int j = 0; j < IslCount; j++)
        {
            if(i != j)
            {
                path->matrix[i][j] = MAX_INT;
            }
            else
            {
                path->matrix[i][j] = 0;
            }
        }
    }
    for (int i = 1; i < size; i += 3)
    {
        path->matrix[get_Name_id(path, path->islands[i])][get_Name_id(path, path->islands[i + 1])] = mx_atoi(path->islands[i + 2]);
        path->matrix[get_Name_id(path, path->islands[i + 1])][get_Name_id(path, path->islands[i])] = mx_atoi(path->islands[i + 2]);
    }
}

