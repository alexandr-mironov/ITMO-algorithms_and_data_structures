#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int n;
vector<int> arr;
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	cin>>n;
    arr.resize(n);
//    for (int i=0;i<n;i++){
//        arr[i] = i+1;
//    }
//	for (int i=2;i<n;i++){
//        swap(arr[i],arr[i/2]);
//    }
	for (int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    return 0;
}