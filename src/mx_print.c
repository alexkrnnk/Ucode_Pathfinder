#include "pathfinder.h"

void print_path(Pointers *path, Way *way)
{
    int i = way->route[way->length];
    int j = way->route[0];
    for (int p = 0; p < IslCount; p++)
    {
        if (p != way->route[way->length] && (path->unique[i][p] == path->matrix[i][j] - path->matrix[p][j]))
        {
            way->length += 1;
            way->route[way->length] = p;
            print_path(path, way);
            way->length -= 1;
        }
    }
    if (way->route[way->length] == way->route[0])
    {
        mx_printstr("========================================\n");
        mx_printstr("Path: ");
        mx_printstr(path->unique_isl[way->route[1]]);
        mx_printstr(" -> ");
        mx_printstr(path->unique_isl[way->route[0]]);
        mx_printstr("\n"); 
        mx_printstr("Route: ");
        for (int i = 1; i <= way->length; i++)
        {
            mx_printstr(path->unique_isl[way->route[i]]); 
            if (i < way->length) 
            {
                mx_printstr(" -> ");
            }
        }
        mx_printstr("\n");
        int sum = 0;
        mx_printstr("Distance: ");
        for (int i = 1; i < way->length; i++)
        {
            mx_printint(path->unique[way->route[i]][way->route[i + 1]]);
            sum += path->unique[way->route[i]][way->route[i + 1]];
            if (i < way->length - 1) 
            {
                mx_printstr(" + ");
            }
            else if (i > 1)
            {
                mx_printstr(" = ");
                mx_printint(sum);
            }
        }
        mx_printstr("\n");
        mx_printstr("========================================\n");
    }
}

