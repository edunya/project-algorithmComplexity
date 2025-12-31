#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

// İleri yönlü lineer
int ileriLineerAra(const int A[], int N, int key) {
    for (int i = 0; i < N; i++)
        if (A[i] == key) return i;
    return -1;
}

// Geri yönlü lineer
int geriLineerAra(const int A[], int N, int key) {
    for (int i = N - 1; i >= 0; i--)
        if (A[i] == key) return i;
    return -1;
}

// İkili arama
int ikiliAra(const int A[], int left, int right, int key) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (A[mid] == key) return mid;
        if (key < A[mid]) right = mid - 1;
        else left = mid + 1;
    }
    return -1;
}

int main() {
    srand((unsigned)time(nullptr));

    int N = 10000;
    int tekrar = 10000;

    // Binary search için sıralı dizi şart
    vector<int> data(N);
    for (int i = 0; i < N; i++) data[i] = i * 2;

    int* arr = data.data();
    int randomIndex = rand() % N;
    int aranan = data[randomIndex];

    cout << "ARAMA ALGORITMALARI - PERFORMANS\n";
    cout << "Dizi boyutu=" << N << ", tekrar=" << tekrar << "\n";
    cout << "Aranan=" << aranan << " (index " << randomIndex << ")\n";
    cout << "----------------------------------\n";

    auto t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < tekrar; i++) ileriLineerAra(arr, N, aranan);
    auto t2 = chrono::high_resolution_clock::now();
    cout << "Ileri lineer  : "
         << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << " ms\n";

    t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < tekrar; i++) geriLineerAra(arr, N, aranan);
    t2 = chrono::high_resolution_clock::now();
    cout << "Geri lineer   : "
         << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << " ms\n";

    t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < tekrar; i++) ikiliAra(arr, 0, N - 1, aranan);
    t2 = chrono::high_resolution_clock::now();
    cout << "Binary search : "
         << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << " ms\n";

    return 0;
}
