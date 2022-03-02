#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#define NMAX 1000005

using namespace std;

vector <int> MS, QS, RS, STLS , SS, BS ;

void Test (int n){
    for (int i = 1 ; i <= n ; ++i) {
        MS.push_back(rand()% INT_MAX ) ;
        QS.push_back(rand()% INT_MAX ) ;
        RS.push_back(rand()% INT_MAX ) ;
        STLS.push_back(rand()% INT_MAX ) ;
        SS.push_back(rand()% INT_MAX ) ;
        BS.push_back(rand()% INT_MAX ) ;
    }
}

void Merge (vector <int>& a, int left, int mid, int right){
    vector <int> b;
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

void MergeSort(vector <int>& a, int left, int right) {
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

void Radix_p_count(int a[], int n, int index) {
    const int max = 10;
    int output[n];
    int p_count[max];

    for (int i = 0 ; i < max ; ++i )
        p_count[i] = 0 ;

    for (int i = 0 ; i < n ; ++i )
        p_count[(a[i] / index) % 10]++ ;

    for (int i = 1 ; i < max ; ++i )
        p_count[i] += p_count[i - 1];

    for (int i = n - 1; i >= 0 ; --i ) {
        output[p_count[(a[i] / index) % 10] - 1] = a[i];
        p_count[(a[i] / index) % 10] -- ;
    }

    for ( int i = 0 ; i < n ; ++i )
        a[i] = output[i];
}

void RadixSort(int a[], int n) {
    int maxv = get_Max(a,n);
    for ( int index = 1 ; maxv / index > 0 ; index *= 10)
        Radix_p_count(a,n,index);
}

int Partition(vector <int>& a, int left, int right) {
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

void QuickSort(vector <int>& a, int left, int right) {
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

void ShellSort(vector <int>& a,int n){
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

void BubbleSort(vector <int>& a, int n){
    bool Ok = true;
    while (Ok == true) {
        Ok = false;
        for (int i = 0 ; i < n - 1 ; ++i)
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                Ok = true ;
            }
    }
}

int main(){

    const int N = 6;
    srand(time(NULL));
    int p_count;
    int start,stop,length[]= {50,100,1000,10000,100000,1000000};
    for (int i = 1 ; i <= 5 ; ++i ){
        cout << "Testul" << " " << i << " : " << "( " << length[i - 1] << " elemente )" << endl ;
        p_count = length[i - 1];
        Test(p_count);
        /*
        start = clock();
        MergeSort(MS,1,p_count);
        stop = clock();
        cout << "MergeSort:" << fixed << double(stop-start)/CLOCKS_PER_SEC << endl ;
        */
        start = clock();
        QuickSort(QS,1,p_count);
        stop = clock();
        cout << "QuickSort:" << fixed << double(stop-start)/CLOCKS_PER_SEC << endl ;
        /*
        start = clock();
        RadixSort(RS,p_count);
        stop = clock();
        cout << "RadixSort:" << fixed << double(stop-start)/CLOCKS_PER_SEC << endl ;
        */
        start = clock();
        ShellSort(SS,p_count);
        stop = clock();
        cout << "ShellSort:" << fixed << double(stop-start)/CLOCKS_PER_SEC << endl ;
        start = clock();
        BubbleSort(BS,p_count);
        stop = clock();
        cout << "BubbleSort:" << fixed << double(stop-start)/CLOCKS_PER_SEC << endl ;
        start = clock();
        sort(STLS.begin(),STLS.end());
        stop = clock();
        cout << "STLSort:" << fixed << double(stop-start)/CLOCKS_PER_SEC << endl << endl << endl ;
    }
}
