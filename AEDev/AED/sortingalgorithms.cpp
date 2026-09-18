#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <string>

using namespace std;
using namespace std::chrono;

void bubS(vector<int>& a, const int n) {
    bool swapp;
    do{
        swapp=false;
        for (int i= 0; i<n-1; i++) {
            if (a[i] > a[i+1]) {
                swap(a[i], a[i+1]);
                swapp=true;
            }
        }
    } while(swapp);
}

void instS(vector<int>& a, const int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j>=0 && a[j] > key) {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = key;
    }
}

void selS(vector<int>& a, const int n) {
    for (int i=0; i<n-1; i++) {
        int min=i;
        for (int j =i+1; j<n; j++) {
            if (a[j] < a[min]) {
                min=j;
            }
        }
        swap(a[i], a[min]);
    }
}

void mrg(vector<int>& og, int l, int m, int r) {
    int n1=m-l + 1;
    int n2=r-m;

    vector<int> L(n1), R(n2);

    for (int i=0; i < n1; i++) L[i] = og[l+i];
    for (int j=0; j < n2; j++) R[j] = og[m+1+j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            og[k] = L[i];
            i++;
        } else {
            og[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        og[k]=L[i];
        i++;
        k++;
    }

    while (j < n2) {
        og[k]=R[j];
        j++;
        k++;
    }
}

void mrgS(vector<int>& a, int l, int r) {
    if (l < r) {
        int m=l+ (r-l)/2;
        mrgS(a,l, m);
        mrgS(a,m+1, r);
        mrg(a, l, m, r);
    }
}

void compareandcontrast(int n) {
    cout << "\nArray de " << n << " de entrada\n";
    vector<int> values(n);

    auto f = [] { return rand() % 10000; };
    ranges::generate(values, f);

    vector<int> expected = values;
    ranges::sort(expected);

    vector<int> unordered1 =values;
    vector<int> unordered2 =values;
    vector<int> unordered3 =values;
    vector<int> unordered4 =values;

    auto start1 = high_resolution_clock::now();
    bubS(unordered1, unordered1.size());
    auto stop1 = high_resolution_clock::now();
    duration<double> durationBs=stop1-start1;
    bool verdadBs = (expected==unordered1);

    auto start2 = high_resolution_clock::now();
    instS(unordered2, unordered2.size());
    auto stop2 = high_resolution_clock::now();
    duration<double> durationIs=stop2-start2;
    bool verdadIs = (expected==unordered2);

    auto start3 = high_resolution_clock::now();
    selS(unordered3, unordered3.size());
    auto stop3 = high_resolution_clock::now();
    duration<double> durationSs=stop3-start3;
    bool verdadSs = (expected==unordered3);

    auto start4 = high_resolution_clock::now();
    mrgS(unordered4, 0, unordered4.size()-1);
    auto stop4 = high_resolution_clock::now();
    duration<double> durationMs=stop4-start4;
    bool verdadMs = (expected==unordered4);

    cout << "______________________________________________________\n"
         << "|    Algoritmo    |  Tiempo (s)  |     Validacion    |\n"
         << "______________________________________________________\n"
         << left
         << "| " << setw(15) << "BubbleSort" << " | " << setw(12) << fixed << setprecision(6) << durationBs.count() << " | " << setw(17) << (verdadBs ? "Correcto" : "Incorrecto") << " |\n"
         << "| " << setw(15) << "InsertionSort" << " | " << setw(12) << fixed << setprecision(6) << durationIs.count() << " | " << setw(17) << (verdadIs ? "Correcto" : "Incorrecto") << " |\n"
         << "| " << setw(15) << "SelectionSort" << " | " << setw(12) << fixed << setprecision(6) << durationSs.count() << " | " << setw(17) << (verdadSs ? "Correcto" : "Incorrecto") << " |\n"
         << "| " << setw(15) << "MergeSort" << " | " << setw(12) << fixed << setprecision(6) << durationMs.count() << " | " << setw(17) << (verdadMs ? "Correcto" : "Incorrecto") << " |\n"
         << "______________________________________________________\n";

    cout<< "Array orginal: \n";
    for (auto i:values) {
        cout << i <<" ";
    }
    cout << endl << endl;
    const vector vect={unordered1, unordered2, unordered3, unordered4};
    const vector names={"Bubble Sort", "Insertion Sort", "Selection Sort", "Merge Sort"};
    for (int i=0;i<4;i++) {
        cout<< "Ordenado con "<< names[i]<< ": \n";
        for (auto j : vect[i]) {
            cout << j << " ";
        }
        cout << endl << endl;
    }

}

/*int main() {
    srand(time(NULL));

    for (int i = 10; i <= 10000000; i *= 10) {
        compareandcontrast(i);
    }
    return 0;
}*/