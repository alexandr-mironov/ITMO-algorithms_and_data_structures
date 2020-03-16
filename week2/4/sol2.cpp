#include <fstream>


int split(int *a, int l, int r)
{
    int x = a[(l + r) / 2];
    int l_index = l, r_index = r, buff;

    while (l_index <= r_index) {
        while (a[l_index] < x)
            l_index++;
        while (a[r_index] > x)
            r_index--;

        if (l_index <= r_index) {
            buff = a[l_index];
            a[l_index] = a[r_index];
            a[r_index] = buff;
            l_index++;
            r_index--;
        }
    }

    return l_index;
}


void quicksort(int *a, int l, int r, int k1, int k2)
{
    if (l == r || l > k2 || r < k1)
        return;

    int m = split(a, l, r);

    quicksort(a, l, m - 1, k1, k2);
    quicksort(a, m, r, k1, k2);
}


int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    int n, k1, k2, i;
    fin >> n >> k1 >> k2;
    int *a = new int [n + 1];

    int A, B, C;
    fin >> A >> B >> C >> a[1] >> a[2];

    for (i = 3; i <= n; ++i)
        a[i] = A * a[i - 2] + B * a[i - 1] + C;

    quicksort(a, 1, n, k1, k2);

    for (i = k1; i <= k2; ++i)
        fout << a[i] << ' ';
    fout << '\n';

    delete [] a;

    return 0;
}