#include "libmx.h"

// static void mx_write(char **lineptr, char *buf) {
//     *lineptr = mx_realloc(*lineptr,
//                           mx_s_strlen(*lineptr) + mx_s_strlen(buf));
//     *lineptr = mx_strcat(*lineptr, buf);
// }

// static int mx_remembered_part(char **lineptr, char *readed,
//                               r_line *l) {
//     char *buf = mx_strdup(readed);
//     int len = mx_strlen(buf);
//     int r;
//     int i = 0;

//     for (int j = 0; buf[j] != '\0' ; j++, i++)
//         if (buf[j] == l->delim) {
//             buf[j++] = '\0';
//             mx_write(lineptr, buf);
//             for(r = 0; r < (len - i); readed[r++] = buf[j++]);
//             l->flag = 1;
//             mx_strdel(&buf);
//             l->sum += i;
//             return i;
//         }
//     mx_write(lineptr, buf);
//     mx_strdel(&buf);
//     mx_strdel(&readed);
//     l->sum += i;
//     return i;
// }

// static char *mx_read(char **lineptr, char *readed,
//                      size_t buf_size, r_line *l) {
//     for ( ; (l->chars = read(l->fd, l->buf, buf_size)) > 0; ) {
//         l->buf[l->chars] = '\0';
//         l->sum += l->chars;
//         readed = mx_strdup(l->buf);
//         for (size_t j = 0;
//              j < buf_size || l->buf[j] != '\0'; j++, l->index++)
//             if (l->buf[j] == l->delim) {
//                 l->buf[j++] = '\0';
//                 for (l->k = 0; l->k < buf_size - l->index % buf_size; )
//                     readed[l->k++] = l->buf[j++];
//                 l->flag = 1;
//                 break;
//             }
//         mx_write(lineptr, l->buf);
//         if (l->flag == 1)
//             break;
//         mx_strdel(&readed);
//     }
//     (int) l->chars == 0 && l->index == 0 ? l->index-- : l->index;
//     return readed;
// }

// static r_line *struct_creator(size_t buf_size, char delim, const int fd) {
//     r_line *l = (r_line *)malloc(sizeof(r_line));

//     l->buf = mx_strnew(buf_size);
//     l->flag = 0;
//     l->index = 0;
//     l->chars = 0;
//     l->sum = 0;
//     l->fd = fd;
//     l->delim = delim;
//     return l;
// }

// int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
//     r_line *l = struct_creator(buf_size, delim, fd);
//     static char *readed;
//     int result;

//     if (readed != NULL && mx_s_strlen(readed) == 0)
//         mx_strdel(&readed);
//     l->fd < 0 ? (l->index = -2, l->flag = 1) : l->index;
//     if (readed != NULL && mx_strlen(readed) > 0)
//         l->index = mx_remembered_part(lineptr, readed, l);
//     if (l->flag == 0)
//         readed = mx_read(lineptr, NULL, buf_size, l);
//     result = l->index > l->sum ? l->sum : l->index;
//     if (result == -1)
//         mx_strdel(&readed);
//     free(l->buf);
//     free(l);
//     return result;
// }

// static void *mx_realloc2(void *ptr, size_t size) { // LEAKS
//     if (!ptr && size)
//         return malloc(size);
//     if (size == 0 && ptr) {
//         free(ptr);
//         return NULL;
//     }
//     void *res;
//     size_t len = mx_strlen(ptr);

//     res = malloc(len > size ? len : size);
//     if (!res)
//         return NULL;
//     return mx_memmove(res, ptr, size);
// }

/*
 * WORKS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */
static void *mx_realloc2(void *ptr, size_t size) {
    char *new = mx_strnew(size);
    char *p = (char *)ptr;

    if (new == NULL)
        return NULL;
    if (ptr == NULL)
        return new;
    for (unsigned int i = 0; i < size; i++)
        new[i] = p[i];
    free(ptr);
    return new;
}

static void mx_free(char **lineptr, char *buf, int *count, int chars) {
    chars == 0 && (*count) == 0 ? (*count)-- : (*count);
    mx_strdel(&buf);
    if (*lineptr == NULL && (*count) < 1) {
        *lineptr = malloc(1);
        *lineptr[0] = '\0';
    }
}

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
    char *buf = mx_strnew(1);
    int count = 0;
    int chars;

    fd < 0 ? (count = -2) : count;
    for ( ; (chars = read(fd, buf, (buf_size / buf_size))) > 0; ) {
        if (*buf == delim)
            break;
        *lineptr = mx_realloc2(*lineptr,
                            mx_s_strlen(*lineptr) + mx_s_strlen(buf));
        *lineptr = mx_strcat(*lineptr, buf);
        count++;
    }
    mx_free(&(*lineptr), buf, &count, chars);
    return count;
}

// static void *mx_realloc2(void *ptr, size_t size) {
//     char *new = mx_strnew(size);
//     char *p = (char *)ptr;

//     if (new == NULL)
//         return NULL;
//     if (ptr == NULL)
//         return new;
//     for (unsigned int i = 0; i < size; i++)
//         new[i] = p[i];
//     free(ptr);
//     return new;
// }

// static void mx_free(char **lineptr, char *buf, int *count, int chars) {
//     chars == 0 && (*count) == 0 ? (*count)-- : (*count);
//     mx_strdel(&buf);
//     if (*lineptr == NULL && (*count) < 1) {
//         *lineptr = malloc(1);
//         *lineptr[0] = '\0';
//     }
// }

// int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
//     static char *mem = NULL;
//     char *buf = mx_strnew(1);
//     int count = 0;
//     int chars = 0;
//     int i;

//     fd < 0 ? (count = -2) : count;
//     // printf("mem1 = |%s|\n\n", mem);

//     if (mem != NULL) {
//         for (i = 0; i < mx_s_strlen(mem); i++) {
//             if (mem[i] == delim)
//                 break;
//             buf[0] = mem[i];
//             *lineptr = mx_realloc2(*lineptr,
//                                 mx_s_strlen(*lineptr) + mx_s_strlen(buf));
//             *lineptr = mx_strcat(*lineptr, buf);
//             count++;
//         }
//         if (count < mx_s_strlen(mem)) {
//             for (i = 0; (count + i) % buf_size + 1 != buf_size; i++) {
//                 char *buf2 = strdup(mem + count);
//                 mx_strdel(&mem);
//                 mem = mx_realloc2(buf2, mx_s_strlen(buf2));
//                 mem = mx_strcat(mem, buf2);
//             }
//         }
//         else
//             mx_strdel(&mem);
//     }
//     // printf("mem2 = |%s|\t\t counter = %d\n\n", mem, count);
//     if (mem == NULL) {
//         for ( ; (chars = read(fd, buf, (buf_size / buf_size))) > 0; ) {
//             if (*buf == delim)
//                 break;
//             *lineptr = mx_realloc2(*lineptr,
//                                 mx_s_strlen(*lineptr) + mx_s_strlen(buf));
//             *lineptr = mx_strcat(*lineptr, buf);
//             count++;
//         }
//     }
//     if (chars != 0 && (count % buf_size + 1 != 0)) {
//         for (i = 0; (count + i) % buf_size + 1 != buf_size; i++) {
//             read(fd, buf, (buf_size / buf_size));
//             mem = mx_realloc2(mem, mx_s_strlen(mem) + mx_s_strlen(buf));
//             mem = mx_strcat(mem, buf);
//             // printf("mem = %s\n\n", mem);
//             // sleep(1);
//         }
//     }
//     // printf("mem = %s\n\n", mem);
//     mx_free(&(*lineptr), buf, &count, chars);
//     return count;
// }


// // ter a fire lic



