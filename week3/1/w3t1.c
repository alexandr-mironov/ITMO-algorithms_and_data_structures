#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include "time.h"
#include "errno.h"

const char *line_sep = "\r\n";
short m, n;
clock_t exec_time;
unsigned short *A, *B;
int **array;
int *tmp_array;
int *count, cnt, max = 0;
bool mode = false;

void countSort(int exp);
void radixsort(int n);
void measure_time();
void print_time();
int count_digits(int i);

int main()
{
    FILE *f = fopen("input.txt", "rb");
    char *input, *tmp, *tmp2;
    size_t i, input_len;
    int e, j;
    int k;
    unsigned long long res;
    if(!f) exit(EXIT_FAILURE);

    fseek(f, 0, SEEK_END);
    input_len = ftell(f);
    fseek(f, 0, SEEK_SET);

    if(!(input = malloc(sizeof(char) * (input_len + 1)))) exit(EXIT_FAILURE);

    if(fread(input, 1, input_len, f) != input_len) exit(EXIT_FAILURE);
    input[input_len] = 0;

    fclose(f);

    if(!(tmp = strtok(input, line_sep))) exit(EXIT_FAILURE);

    i = strlen(tmp);

    if(!(tmp2 = strtok(tmp, " "))) exit(EXIT_FAILURE);

    n = atoi(tmp2);

    if(!(tmp2 = strtok(NULL, " "))) exit(EXIT_FAILURE);

    m = atoi(tmp2);
    cnt = n * m;

    if(!(A = malloc(sizeof(unsigned short) * n))) exit(EXIT_FAILURE);
    if(!(B = malloc(sizeof(unsigned short) * m))) exit(EXIT_FAILURE);
    if(!(array = malloc(sizeof(int*) * 2))) exit(EXIT_FAILURE);
    if(!(array[0] = malloc(sizeof(int) * cnt))) exit(EXIT_FAILURE);
    if(!(array[1] = malloc(sizeof(int) * cnt))) exit(EXIT_FAILURE);
    if(!(tmp_array = malloc(sizeof(int) * cnt))) exit(EXIT_FAILURE);

    if(!(tmp = strtok(tmp + i + 1, line_sep))) exit(EXIT_FAILURE);

    i = strlen(tmp);

    if(!(tmp2 = strtok(tmp, " "))) exit(EXIT_FAILURE);

    for(e = 0; e < n; e++) {
        A[e] = (unsigned short) atoi(tmp2);
        tmp2 = strtok(NULL, " ");
    }

    if(!(tmp = strtok(tmp + i + 1, line_sep))) exit(EXIT_FAILURE);
    if(!(tmp2 = strtok(tmp, " "))) exit(EXIT_FAILURE);

    for(e = 0; e < m; e++) {
        B[e] = (unsigned short) atoi(tmp2);
        tmp2 = strtok(NULL, " ");
    }

    for(e = 0, k = 0; e < m; e++) {
        for(j = 0; j < n; j++, k++) {
            array[0][k] = B[e] * A[j];

            if(array[0][k] > max)
                max = array[0][k];
        }
    }

    if(!(count = malloc(sizeof(int) * 10))) exit(EXIT_FAILURE);

    measure_time();

    radixsort(cnt);

    /*for(j = 0; j < cnt; j++) {
        printf("%d\n", array[mode][j]);
    }*/

    res = 0;

    for(j = 0; j < cnt; j++) {
        if(j % 10 == 0) {
            res += array[mode][j];
        }
    }

    f = fopen("output.txt", "w+b");

    if(!f) exit(EXIT_FAILURE);

    fprintf(f, "%llu%s", res, line_sep);

    fclose(f);

    print_time();
    exit(EXIT_SUCCESS);
}

void countSort(int exp)
{
    int i, count[40] = {0};
    int n = cnt, a;
    bool mode_rev = !mode;

    for (i = n; i--;) {
        tmp_array[i] = (array[mode][i] / exp) % 40;
        count[ tmp_array[i] ]++;
    }

    for (i = 1; i < 40; i++)
        count[i] += count[i - 1];

    for (i = n; i--;) {
        array[mode_rev][count[ tmp_array[i] ] - 1] = array[mode][i];
        count[ tmp_array[i] ]--;
    }

    mode = mode_rev;
}

// The main function to that sorts arr[] of size n using
// Radix Sort
void radixsort(int n)
{
    // Find the maximum number to know number of digits
    int m = max;

    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m/exp > 0; exp *= 40)
        countSort(exp);
}
void measure_time()
{
    exec_time = clock();
}

void print_time()
{
    clock_t end = clock();
    double time_spent = (double) (end - exec_time) / CLOCKS_PER_SEC;

    printf("%f\n", time_spent);
}

int count_digits(int n)
{
    int count = 0;

    while (n != 0) {
        n = n / 10;
        ++count;
    }

    return count;
}