/**
 * author Vladimir Ivanov
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include "errno.h"

char **in_lines, **out_lines;
int in_lines_cnt, out_lines_cnt, *intervs, *arr_a;

bool read(FILE *f)
{
    size_t fsize, i, len;
    char *contents, *tmp;
    int a;

    if(!f) {
        return false;
    }

    fseek(f, 0, SEEK_END);
    fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    contents = malloc(sizeof(char) * fsize + 1);

    if(!contents) {
        return false;
    }

    contents[fsize] = 0;

    if(fread(contents, 1, fsize, f) != fsize) {
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

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

//int partition(int *arr, int low, int high)
//{
//    int i = (low - 1);
//
//    for(int j = low; j <= high - 1; j++) {
//        if(arr[j] < arr[high]) {
//            i++;
//            swap(&arr[i], &arr[j]);
//        }
//    }
//
//    swap(&arr[i + 1], &arr[high]);
//
//    return i + 1;
//}

int partition(int *mas, int l, int r) {
    if (l!=r)
        swap(&mas[l + rand() % (r - l)], &mas[r]);
    int x = mas[r];
    int i = l-1;
    for (int j = l; j <= r-1; j++) {
        if (mas[j] <= x)
            swap(&mas[++i],&mas[j]);
    }
    return i;
}

int nth(int mas, int n) {
    int l = 0, r = mas.size() - 1;
    for(;;) {
        int pos = partition(mas,l,r);
        if (pos < n)
            l = pos + 1;
        else if (pos > n)
            r = pos - 1;
        else return mas[n];
    }
}

//void quick_sort(int *arr, int low, int high)
//{
//    if(low < high) {
//        int mid = partition(arr, low, high);
//
//        if(intervs[1] - 1 <= mid - 1)
//            quick_sort(arr, low, mid - 1);
//
//        if(intervs[2] - 1 >= mid + 1)
//            quick_sort(arr, mid + 1, high);
//    }
//}

bool fill_out()
{
    int *tmp, written, a;
    char *ptr;

    intervs = malloc(sizeof(int) * 3);

    if(!intervs) {
        return false;
    }

    ptr = strtok(in_lines[0], " ");
    a = 0;

    while(ptr) {
        intervs[a] = atoi(ptr);
        ptr = strtok(NULL, " ");
        a++;
    }

    tmp = malloc(sizeof(int) * 5);

    if(!tmp) {
        return false;
    }

    ptr = strtok(in_lines[1], " ");
    a = 0;

    while(ptr) {
        tmp[a] = atoi(ptr);
        ptr = strtok(NULL, " ");
        a++;
    }

    arr_a = malloc(sizeof(int) * intervs[0]);

    if(!arr_a) {
        return false;
    }

    arr_a[0] = tmp[3];
    arr_a[1] = tmp[4];

    for(a = 2; a < intervs[0]; a++) {
        arr_a[a] = tmp[0] * arr_a[a - 2] + tmp[1] * arr_a[a - 1] + tmp[2];
    }


    //quick_sort(arr_a, 0, intervs[0] - 1);

    for(a = 0; a < intervs[0]; a++) {
        printf("%d\n", nth(arr_a, a));
    }

    out_lines_cnt = 1;
    out_lines = malloc(sizeof(char*));

    if(out_lines == NULL) {
        return false;
    }

    out_lines[0] = malloc(sizeof(char) * 24);

    if(!out_lines[0]) {
        return false;
    }

    return true;
}

bool write(FILE *f)
{
    int i, size = intervs[2] - intervs[1] + 1, written = 0;

    if(!f) {
        return false;
    }

    char *tmp = malloc(sizeof(char) * size * 13);

    intervs[1]--;

    while(intervs[1] < intervs[2]) {
        written += sprintf(tmp + written, "%d ", arr_a[intervs[1]]);
        intervs[1]++;
    }

    fprintf(f, "%s", tmp);

    if(
#ifdef UNIX_NEW_LINE
        || fputc('\n', f) == EOF
#else
        fputc('\r', f) == EOF
        || fputc('\n', f) == EOF
#endif
    ) {
        return false;
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