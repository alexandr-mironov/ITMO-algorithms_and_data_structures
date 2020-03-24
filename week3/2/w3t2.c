#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include "time.h"

const char *line_sep = "\r\n";
char **lines;
char *line_tmp;
int m, n;
int *lines_nums;
int *lines_nums_tmp;
bool mode = false;
int *count;
clock_t begin;

void print_time()
{
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f\n", time_spent);
}

void swap(char *a, char *b)
{
    char c;

    c = *a;
    *a = *b;
    *b = c;
}

void sort(int rad)
{
    int i, cnt;

    for(i = 0; i < n; i++) {
        line_tmp[i] = lines[rad][lines_nums[i]];
        //printf("%d %c %c\n", lines_nums[i], lines[rad][lines_nums[i]], lines[rad][i]);
    }

    for(i = 123; i--;) {
        count[i] = 0;
    }

    for(i = n; i--;) {
        count[line_tmp[i]]++;
    }

    for(i = 98; i < 123; i++) {
        count[i] += count[i - 1];
    }

    for(i = n; i--;) {
        cnt = count[line_tmp[i]] - 1;

        lines_nums_tmp[cnt] = lines_nums[i];
        count[line_tmp[i]]--;
    }

    for(i = 0; i < n; i++) {
        lines_nums[i] = lines_nums_tmp[i];
        //printf("%d\n", lines_nums[i]);
    }
}

int main()
{
    FILE *f = fopen("input.txt", "rb");
    char *input, *tmp;
    size_t i, input_len;
    int k, j, e;

    begin = clock();

    if(!f) exit(EXIT_FAILURE);

    fseek(f, 0, SEEK_END);
    input_len = ftell(f);
    fseek(f, 0, SEEK_SET);

    if(!(input = malloc(sizeof(char) * (input_len + 1)))) exit(EXIT_FAILURE);

    if(fread(input, 1, input_len, f) != input_len) exit(EXIT_FAILURE);
    input[input_len] = 0;

    fclose(f);
    input[input_len] = 0;

    if((tmp = strtok(input, " ")) == NULL) exit(EXIT_FAILURE);

    n = atoi(tmp);
    input_len -= strlen(tmp) + 1;

    if((tmp = strtok(NULL, " ")) == NULL) exit(EXIT_FAILURE);

    m = atoi(tmp);
    input_len -= strlen(tmp) + 1;

    if((tmp = strtok(NULL, " ")) == NULL) exit(EXIT_FAILURE);

    k = atoi(tmp);
    input_len -= strlen(tmp) + 1;

    if(!(lines = malloc(sizeof(char*) * m))) exit(EXIT_FAILURE);
    if(!(line_tmp = malloc(sizeof(char) * n))) exit(EXIT_FAILURE);

    for(i = 0; i < input_len; i++) {
        if((tmp + i)[0] == '\n') {
            break;
        }
    }

    tmp = strtok(tmp + i + 1, line_sep);
    i = 0;

    while(tmp) {
        lines[i] = tmp;
        tmp = strtok(NULL, line_sep);
        i++;
    }

    if(!(lines_nums = malloc(sizeof(int) * n))) exit(EXIT_FAILURE);
    if(!(lines_nums_tmp = malloc(sizeof(int) * n))) exit(EXIT_FAILURE);

    for(e = 0; e < n; e++) {
        lines_nums[e] = e;
    }

    if(!(count = malloc(sizeof(int) * 123))) exit(EXIT_FAILURE);

    for(j = m - 1, e = m - k; j >= e; j--) {
        sort(j);
    }

    if(!(tmp = malloc(sizeof(char) * n * 13))) exit(EXIT_FAILURE);
    j = 0;

    for(e = 0; e < n; e++) {
        j += sprintf(tmp + j, "%d ", lines_nums[e] + 1);
    }

    tmp[j - 1] = 0;
    f = fopen("output.txt", "w+b");

    if(!f) exit(EXIT_FAILURE);

    fprintf(f, "%s%s", tmp, line_sep);

    fclose(f);
    print_time();
    exit(EXIT_SUCCESS);
}