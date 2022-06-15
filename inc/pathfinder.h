#pragma once
 
#include "libmx.h"
#include <unistd.h> 
#include <malloc/malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#define MAX_INT 2147483647

int IslCount;
int size;
typedef struct Pointers {
    char **islands;
    char **unique_isl;
    int **matrix;
    int **unique;
} Pointers;

typedef struct Way {
    int length;
    int *route;
} Way;

void mx_error(char *filename);
void mx_matrix(Pointers *path);
void mx_all_short_path_matrix(Pointers *path);
void print_path(Pointers *path, Way *way);

