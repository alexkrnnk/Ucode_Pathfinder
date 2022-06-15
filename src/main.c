#include "pathfinder.h"

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        Pointers *path = malloc(sizeof(Pointers));
        mx_error(argv[1]);
        char *str = mx_file_to_str(argv[1]);
        char *buffer = mx_strdup(str);
        IslCount = mx_atoi(buffer);
        for (int i = 0; buffer[i] != '\0'; i++)
        {
            if(buffer[i] == ',' || buffer[i] == '\n')
            {
                buffer[i] = '-';
            }
        }
        size = mx_count_words(buffer, '-');
        path->islands = mx_strsplit(buffer, '-');
        path->unique_isl = (char **)malloc(8 * size);
        path->unique_isl[0] = mx_strdup(path->islands[1]);
        for (int i = 1, counter = 1; i < size; i++)
        {
            if (mx_isdigit(path->islands[i][0]) == false)
            {
                for (int j = 0; j < counter; j++)
                {
                    if (mx_strcmp(path->unique_isl[j], path->islands[i]) == 0)
                    {
                        break;
                    }
                    if (j == counter - 1)
                    {
                        path->unique_isl[counter++] = mx_strdup(path->islands[i]);
                    }
                }
            }
        }
        mx_matrix(path);
        mx_all_short_path_matrix(path);
        Way *way = malloc(sizeof(Way));
        way->route = malloc(4 * (IslCount + 1));
        for (int i = 0; i < IslCount; i++)
        {
            for (int j = i + 1; j < IslCount; j++)
            {
                way->length = 1;
                way->route[0] = j;
                way->route[1] = i;
                print_path(path, way);
            }
        }
        return 0;
    }
    else
    {
        mx_printerr("usage: ./pathfinder [filename]\n");
        exit(-1);
    }
}

