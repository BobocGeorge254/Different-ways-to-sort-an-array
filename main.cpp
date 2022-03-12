#include <iostream>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>

typedef unsigned long long ULL;

using namespace std;

vector <ULL> MS, QS, RS, STLS , SS, IS ;


//deoarece functia rand() returneaza valori pe 2 octeti, va trebui sa generam un numar pe 8 octeti prin a genera
//fiecare bit din configuratia sa.
ULL Random() {
    ULL x = 0 ;
    for (int i = 0 ; i < 64 ; ++i ) {
        bool bit = rand() % 2 ;
        x = x + bit * ( 1 << i ) ;
    }
    return x ;

}


//folosesc 6 vectori diferiti, cu nume sugestive, pentru a retine numerele de sortat.
void Test (int n){
    for (int i = 1 ; i <= n ; ++i) {
        ULL x = Random()%1000;
        MS.push_back(x) ;
        QS.push_back(x) ;
        RS.push_back(x) ;
        STLS.push_back(x) ;
        SS.push_back(x) ;
        IS.push_back(x) ;
    }
}

ULL max(ULL a , ULL b) {
    if ( a > b )
        return a;
    else return b;
}

void Merge (vector <ULL>& a, int left, int right, int mid){
    vector <ULL> b(right - left + 1);
    int x = left , y = mid + 1 , k = 0;
    while ( x <= mid && y <= right ) {
        if (a[x] <= a[y])
            b[k] = a[x++];
        else
            b[k] = a[y++];
        k++;
    }
    while (x <= mid)
        b[k++] = a[x++];
    while (y <= right)
        b[k++] = a[y++];
    for ( int i = left, k = 0 ; i <= right ; ++i , ++k )
        a[i] = b[k];
}

void MergeSort(vector <ULL>& a, int left, int right) {
    if ( left < right ) {
        int mid = (left + right) / 2 ;
        MergeSort(a,left,mid);
        MergeSort(a,mid + 1,right);
        Merge(a,left,right,mid);
    }
}

ULL get_max(vector<ULL> v){
    ULL mx = v.front();
    for (auto i: v)
        if (i > mx)
            mx = i;
    return mx;
}

void count_sort_by_exp(vector<ULL>& v, ULL exp, int base){
    vector<ULL> output(v.size()), cnt(base, 0);

    for(auto i: v)
        cnt[(i/exp) % base]++;

    for(int i = 1; i < base; i++)
        cnt[i] += cnt[i-1];

    for(int i = v.size()-1; i >= 0; i--)
        output[--cnt[(v[i]/exp) % base]] = v[i];

    v = output;
}

void count_sort_by_exp_65536(vector<ULL>& v, ULL exp, int base){
    vector<ULL> output(v.size()), cnt(base, 0);

    for(auto i: v)
        cnt[(i/exp) >> 16]++;

    for(int i = 1; i < base; i++)
        cnt[i] += cnt[i-1];

    for(int i = v.size()-1; i >= 0; i--)
        output[--cnt[(v[i]/exp) >> 16]] = v[i];

    v = output;
}

void RadixSort(vector<ULL>& v, int base){
    ULL mx = get_max(v);

    for (ULL exp = 1; mx/exp > 0; exp *= base)
        if (base == 65536) // 2^16
            count_sort_by_exp_65536(v, exp, base);
        else
            count_sort_by_exp(v, exp, base);
}


ULL Partition(vector <ULL>& a, int left, int right) {
    ULL pivot = a[right];
    int i = (left - 1) ;
    for ( int j = left ; j < right ; j ++ ) {
        if ( a[j] < pivot ) {
            i ++ ;
            swap (a[i], a[j]);
        }
    }
    swap(a[i + 1], a[right]);
    return (i + 1);
}

void QuickSort(vector <ULL>& a, int left, int right) {
    if (left < right) {
        ULL pi = Partition(a,left,right);
        QuickSort(a,left,pi - 1);
        QuickSort(a,pi + 1, right);
    }
}

void ShellSort(vector <ULL>& a,int n){
    for ( int gap = n / 2 ; gap > 0 ; gap /= 2) {
        for ( int i = gap ; i <= n ; i ++ ) {
            int temp = a[i] ;
            int j ;
            for ( j = i ; j >= gap && a[j - gap] > temp ; j -= gap )
                a[j] = a[j - gap];
            a[j] = temp;
        }
    }
}

void BubbleSort(vector <ULL>& a, int n){
    bool Ok = true;
    while (Ok == true) {
        Ok = false;
        for (int i = 0 ; i < n - 1  ; ++i)
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                Ok = true ;
            }
    }
}


void InsertionSort(vector <ULL>& a, int n) {
    int i, j;
    ULL temp ;
    for (int i = 1 ; i <= n ; ++i ) {
        temp = a[i] ;
        j = i - 1 ;
        while (j >= 0 && a[j] > temp) {
            a[j + 1] = a[j] ;
            j = j - 1 ;
        }
        a[j + 1] = temp ;
    }
}

void vprint(vector <ULL> a) {
    for (int i = 0 ; i < a.size(); ++i )
        cout << a[i] << " " ;
    cout << endl ;
}

int main(){

    srand(time(NULL));
    int test_length;
    int start,stop,length[]= {50,100,1000,10000,100000,1000000, 10000000};
    for (int i = 1 ; i <= 2 ; ++i ){
        cout << "Testul" << " " << i << " - " << " " << length[i - 1] << " elemente " << endl ;
        test_length = length[i - 1];
        Test(test_length);
        //vprint(IS);


        start = clock();
        MergeSort(MS,0,test_length - 1);
        stop = clock();
        cout << "MergeSort: " << fixed << double(stop-start)/CLOCKS_PER_SEC << " secunde" << endl ;
        //vprint(MS);

        start = clock();
        QuickSort(QS,0,test_length - 1);
        stop = clock();
        cout << "QuickSort: " << fixed << double(stop-start)/CLOCKS_PER_SEC << " secunde" << endl ;
        //vprint(QS);

        /*
        start = clock();
        RadixSort(RS,10);
        stop = clock();
        cout << "RadixSort: " << fixed << double(stop-start)/CLOCKS_PER_SEC << " secunde" << endl ;
        vprint(RS); */

        start = clock();
        vprint(SS);
        ShellSort(SS,test_length - 1);
        vprint(SS);
        stop = clock();
        cout << "ShellSort: " << fixed << double(stop-start)/CLOCKS_PER_SEC << " secunde" << endl ;
        //vprint(SS);


        start = clock();
        InsertionSort(IS,test_length - 1);
        stop = clock();
        cout << "InsertionSort: " << fixed << double(stop-start)/CLOCKS_PER_SEC << " secunde"<< endl ;
        //vprint(IS);

        start = clock();
        sort(STLS.begin(),STLS.end());
        stop = clock();
        cout << "STLSort: " << fixed << double(stop-start)/CLOCKS_PER_SEC << " secunde" << endl << endl << endl ;

    }
}
