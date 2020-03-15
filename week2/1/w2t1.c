/**
 * author Vladimir Ivanov
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include "errno.h"

char **in_lines, **out_lines;
int in_lines_cnt, out_lines_cnt, out_lines_i = 0;

bool read(FILE *f)
{
    size_t fsize, i, len;
    char *contents, *tmp;
    int a;

    if(!f) {
#ifdef DEBUG
        printf("Invalid input file, error %d", errno);
#endif
        return false;
    }

    fseek(f, 0, SEEK_END);
    fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    contents = malloc(sizeof(char) * fsize + 1);

    if(!contents) {
#ifdef DEBUG
        printf("Unable to allocate temporary memory for input file contents, error %d", errno);
#endif
        return false;
    }

    contents[fsize] = 0;

    if(fread(contents, 1, fsize, f) != fsize) {
#ifdef DEBUG
        printf("Unable to read input file into temporary memory, error %d", errno);
#endif
        return false;
    }

    in_lines_cnt = 0;

    for(i = 0; i < fsize; i++) {
        if(contents[i] == '\n') {
            in_lines_cnt++;
        }
    }

    in_lines = malloc(sizeof(char*) * in_lines_cnt);

    if(!in_lines) {
#ifdef DEBUG
        printf("Unable to allocate memory for input lines array, errno %d", errno);
#endif
        return false;
    }

    a = 0;
    tmp = strtok(
        contents,
#ifdef UNIX_NEW_LINE
        "\n"
#else
        "\r\n"
#endif
    );

    while(tmp) {
        if(a == in_lines_cnt) {
#ifdef DEBUG
            printf("Tokenized lines count is more than readed from file");
#endif
            return false;
        }

        in_lines[a] = tmp;
        tmp = strtok(
            NULL,
#ifdef UNIX_NEW_LINE
            "\n"
#else
            "\r\n"
#endif
        );
        a++;
    }

    return true;
}

void sort(int *arr, int first, int last)
{
    if(first == last) {
        return;
    }

    int mid = (first + last) / 2,
        range = last - first,
        *arr_tmp,
        i = 0,
        l = first,
        r = mid + 1,
        f = first;

    arr_tmp = malloc(sizeof(int) * (range + 1));

    if(!arr_tmp) {
#ifdef DEBUG
        printf("Unable to allocate memory for temporary array, error %d", errno);
#endif
        exit(EXIT_FAILURE);
    }

    sort(arr, first, mid);
    sort(arr, mid + 1, last);
    i = 0;

    while(i <= range) {
        if(l > mid) {
            arr_tmp[i] = arr[r];
            r++;
        } else if(r > last) {
            arr_tmp[i] = arr[l];
            l++;
        } else {
            if(arr[l] <= arr[r]) {
                arr_tmp[i] = arr[l];
                l++;
            } else if(arr[l] > arr[r]) {
                arr_tmp[i] = arr[r];
                r++;
            }
        }

        i++;
    }

    i = 0;
    while(f <= last) {
        arr[f] = arr_tmp[i];
        f++;
        i++;
    }

    out_lines[out_lines_i] = malloc(sizeof(char) * 50);

    if(!out_lines[out_lines_i]) {
#ifdef DEBUG
        printf("Unable to allocate memory for one of the output lines, error %d", errno);
#endif
        exit(EXIT_FAILURE);
    }

    int written = sprintf(out_lines[out_lines_i], "%d %d %d %d", (first + 1), (last + 1), arr[first], arr[last]);
    out_lines[out_lines_i][written] = 0;
    out_lines_i++;

    free(arr_tmp);
}

bool fill_out()
{
    int cnt = atoi(in_lines[0]), *tmp, i, written;
    char *ptr;

    tmp = malloc(sizeof(int) * cnt);

    if(!tmp) {
#ifdef DEBUG
        printf("Unable to allocate memory for the main array, error %d", errno);
#endif
        return false;
    }

    out_lines_cnt = cnt;
    out_lines = malloc(sizeof(char*) * out_lines_cnt);

    if(out_lines == NULL) {
#ifdef DEBUG
        printf("Unable to allocate memory for out_lines, error %d", errno);
#endif
        return false;
    }

    ptr = strtok(in_lines[1], " ");
    i = 0;

    while(ptr) {
        tmp[i] = atoi(ptr);
        ptr = strtok(NULL, " ");
        i++;
    }

    sort(tmp, 0, cnt - 1);
    out_lines[out_lines_i] = malloc(sizeof(char) * 12 * cnt);
    written = 0;

    if(!out_lines[out_lines_i]) {
#ifdef DEBUG
        printf("Unable to allocate memory for one of the output lines, error %d", errno);
#endif
        return false;
    }

    for(i = 0; i < cnt; i++) {
        written += sprintf(out_lines[out_lines_i] + written, "%d ", tmp[i]);
    }

    out_lines[out_lines_i][written - 1] = 0;

    return true;
}

bool write(FILE *f)
{
    int i;

    if(!f) {
#ifdef DEBUG
        printf("Invalid output file, error %d", errno);
#endif
        return false;
    }

    for(i = 0; i < out_lines_cnt; i++) {
        if(
            fputs(out_lines[i], f) == EOF
#ifndef UNIX_NEW_LINE
            || fputc('\r', f) == EOF
#endif
            || fputc('\n', f) == EOF
        ) {
#ifdef DEBUG
            printf("Unable to write output line to file, error %d", errno);
#endif
            return false;
        }
    }

    return true;
}

int main()
{
    FILE *f = fopen("input.txt", "rb");
    bool result = false;

    if(f) {
        result = read(f);
        fclose(f);
    }

    if(!f || !result)
        return EXIT_FAILURE;

    if(!fill_out()) {
        return EXIT_FAILURE;
    }

    f = fopen("output.txt", "w+b");

    if(f) {
        result = write(f);
        fclose(f);
    }

    if(!f || !result) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}