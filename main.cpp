#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#define NMAX 1000005

using namespace std;


int MS[NMAX], QS[NMAX], SS[NMAX], RS[NMAX], BS[NMAX], STLS[NMAX];
void Test (int n){
    for (int i = 1 ; i <= n ; ++i)
        MS[i] = QS[i] = SS[i] = RS[i] = BS[i] = STLS[i] = rand()% INT32_MAX;
}

void Merge(int a[], int left, int mid, int right){
    int b[NMAX];
    int x = left , k = 1 , y = mid + 1 ;
    while ( x <= mid && y <= right )
        if (a[x] < a[y])
            b[k++] = a[x++];
        else 
            b[k++] = a[y++];
    while (x <= mid)
        b[k++] = a[x++];
    while (y <= right)
        b[k++] = a[y++];
    int t = left;
    for (k = 1 ; k <= (right-left) + 1 ; k ++ )
        a[t++] = b[k];

}

void MergeSort(int a[], int left, int right) {
    if ( left < right ) {
        int mid = (left + right) / 2 ;
        MergeSort(a,left,mid);
        MergeSort(a,mid + 1,right);
        Merge(a,left,mid,right);
    }
}

int get_Max(int a[], int n){
    int cand = a[1];
    for (int i = 2 ; i <= n ; ++i)
        if (a[i] > cand)
            cand = a[i];
    return cand;
}

void Radix_Count(int a[], int n, int index) {
    const int max = 10;
    int output[n];
    int count[max];

    for (int i = 0 ; i < max ; ++i )
        count[i] = 0 ;
    
    for (int i = 0 ; i < n ; ++i )
        count[(a[i] / index) % 10]++ ;
    
    for (int i = 1 ; i < max ; ++i )
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0 ; --i ) {
        output[count[(a[i] / index) % 10] - 1] = a[i];
        count[(a[i] / index) % 10] -- ;
    }

    for ( int i = 0 ; i < n ; ++i )
        a[i] = output[i];
}

void RadixSort(int a[], int n) {
    int maxv = get_Max(a,n);
    for ( int index = 1 ; maxv / index > 0 ; index *= 10)
        Radix_Count(a,n,index);
}

void swap(int a, int b){
    int t = a;
    a = b;
    b = t;
}

int Partition(int a[], int left, int right) {
    int pivot = a[right];
    int i = (left - 1) ;
    for ( int j = left ; j < right ; j ++ ) {
        if ( a[j] <= pivot ) {
            i ++ ;
            swap (a[i], a[j]);
        }
    }
    swap(a[i + 1], a[right]);
    return (i + 1);
}

void QuickSort(int a[], int left, int right) {
    if (left < right) {
        int pi = Partition(a,left,right);
            if (pi - left < right - pi) {
                QuickSort(a,left,pi - 1);
                left = pi + 1;
            }
            else {
                QuickSort(a,pi + 1,right);
                right = pi - 1;
            }
    }
}

void ShellSort(int a[],int n){
    for ( int gap = n / 2 ; gap > 0 ; gap /= 2) {
        for ( int i = gap ; i < n ; i ++ ) {
            int temp = a[i] ;
            int j ;
            for ( j = i ; j >= gap && a[j - gap] > temp ; j -= gap )
                a[j] = a[j] - gap;
            a[j] = gap;
        }
    }
}

void BubbleSort(int a[], int n){
    bool Ok = true;
    while (Ok == true) {
        Ok = false;
        for (int i = 1 ; i < n ; ++i)
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                Ok = true ;
            }
    }
}

int main(){

    const int N = 6;
    int length[] = {50,100,1000,10000,100000,1000000};
    int count;
    for (int i = 1 ; i <= 6 ; ++i ){
        cout << "Testul" << " " << i << " : " << "( " << length[i - 1] << " elemente )" << endl ;
        count = length[i - 1];
        Test(count);
        int start, stop, startM, stopM;
        start = clock();
        MergeSort(MS,1,count);
        stop = clock();
        cout << "MergeSort:" << fixed << double(stop-start)/CLOCKS_PER_SEC << endl ;
        start = clock();
        QuickSort(QS,1,count);
        stop = clock();
        cout << "QuickSort:" << fixed << double(stop-start)/CLOCKS_PER_SEC << endl ;
        start = clock();
        RadixSort(RS,count);
        stop = clock();
        cout << "RadixSort:" << fixed << double(stop-start)/CLOCKS_PER_SEC << endl ;
        start = clock();
        ShellSort(SS,count);
        stop = clock();
        cout << "ShellSort:" << fixed << double(stop-start)/CLOCKS_PER_SEC << endl ;
        start = clock();
        ShellSort(BS,count);
        stop = clock();
        cout << "BubbleSort:" << fixed << double(stop-start)/CLOCKS_PER_SEC << endl ;
        start = clock();
        sort(STLS + 1, STLS + count + 1);
        stop = clock();
        cout << "STLSort:" << fixed << double(stop-start)/CLOCKS_PER_SEC << endl << endl << endl ;
    }


}
