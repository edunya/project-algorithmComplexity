#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <climits>

using namespace std;

static inline void SWAP(int& a, int& b) { int t = a; a = b; b = t; }

// -------- MIN HEAP --------
void heapifyMin(int A[], int N, int i) {
    int smallest = i;
    int l = 2 * i + 1, r = 2 * i + 2;

    if (l < N && A[l] < A[smallest]) smallest = l;
    if (r < N && A[r] < A[smallest]) smallest = r;

    if (smallest != i) {
        SWAP(A[i], A[smallest]);
        heapifyMin(A, N, smallest);
    }
}

void insertHeapMin(int A[], int& N, int key) {
    A[N] = key;
    int i = N;
    N++;

    while (i > 0 && A[(i - 1) / 2] > A[i]) {
        SWAP(A[i], A[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int findMin(const int A[], int N) {
    if (N <= 0) return INT_MAX;
    return A[0];
}

int deleteMin(int A[], int& N) {
    if (N <= 0) return INT_MAX;
    int root = A[0];
    A[0] = A[N - 1];
    N--;
    heapifyMin(A, N, 0);
    return root;
}

void buildMinHeap(int A[], int N) {
    for (int i = N / 2 - 1; i >= 0; i--) heapifyMin(A, N, i);
}

void decreaseKey(int A[], int i, int delta) {
    A[i] -= delta;
    while (i > 0 && A[(i - 1) / 2] > A[i]) {
        SWAP(A[i], A[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void increaseKey(int A[], int N, int i, int delta) {
    A[i] += delta;
    heapifyMin(A, N, i);
}

void deleteKey(int A[], int& N, int i) {
    if (i < 0 || i >= N) return;
    A[i] = A[N - 1];
    N--;
    heapifyMin(A, N, i);
}

// -------- MAX HEAP --------
void heapifyMax(int A[], int N, int i) {
    int largest = i;
    int l = 2 * i + 1, r = 2 * i + 2;

    if (l < N && A[l] > A[largest]) largest = l;
    if (r < N && A[r] > A[largest]) largest = r;

    if (largest != i) {
        SWAP(A[i], A[largest]);
        heapifyMax(A, N, largest);
    }
}

void buildMaxHeap(int A[], int N) {
    for (int i = N / 2 - 1; i >= 0; i--) heapifyMax(A, N, i);
}

// Merge(H1, H2): iki min-heap dizisini birleştirip tekrar min-heap yap
int* mergeHeaps(const int H1[], int N1, const int H2[], int N2, int& outN) {
    outN = N1 + N2;
    int* merged = (int*)malloc(sizeof(int) * outN);

    for (int i = 0; i < N1; i++) merged[i] = H1[i];
    for (int i = 0; i < N2; i++) merged[N1 + i] = H2[i];

    buildMinHeap(merged, outN);
    return merged;
}

int main() {
    cout << "HEAP YAPILARI\n";
    cout << "-------------\n";

    srand((unsigned)time(nullptr));

    const int CAP = 20000;
    int* H = (int*)malloc(sizeof(int) * CAP);
    int N = 0;

    // Insert
    auto t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < 5000; i++) insertHeapMin(H, N, rand() % 10000);
    auto t2 = chrono::high_resolution_clock::now();
    cout << "insertHeap: 5000 eleman, sure="
         << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count()
         << " ms\n";

    cout << "findMin: " << findMin(H, N) << "\n";

    // deleteMin
    t1 = chrono::high_resolution_clock::now();
    int silinen = deleteMin(H, N);
    t2 = chrono::high_resolution_clock::now();
    cout << "deleteMin: silinen=" << silinen
         << ", yeniMin=" << findMin(H, N)
         << ", sure=" << chrono::duration_cast<chrono::microseconds>(t2 - t1).count()
         << " us\n";

    // decrease / increase / deleteKey
    if (N > 20) {
        int eski = H[10];
        decreaseKey(H, 10, 3000);
        cout << "decreaseKey: H[10] " << eski << " -> " << H[10] << "\n";

        eski = H[0];
        increaseKey(H, N, 0, 4000);
        cout << "increaseKey: kok " << eski << " -> " << H[0] << " (heapify ile duzeldi)\n";

        cout << "deleteKey: indeks 5 silindi\n";
        deleteKey(H, N, 5);
    }

    // buildheap min/max gösterimi
    int raw1[] = {20, 6, 3, 10, 16, 2, 10, 14, 8, 7};
    int raw2[] = {20, 6, 3, 10, 16, 2, 10, 14, 8, 7};
    int rawN = (int)(sizeof(raw1) / sizeof(raw1[0]));

    buildMinHeap(raw1, rawN);
    buildMaxHeap(raw2, rawN);

    cout << "buildMinHeap ilk 5: ";
    for (int i = 0; i < 5; i++) cout << raw1[i] << " ";
    cout << "\n";

    cout << "buildMaxHeap ilk 5: ";
    for (int i = 0; i < 5; i++) cout << raw2[i] << " ";
    cout << "\n";

    // Merge(H1,H2)
    int N2 = 1000;
    int* H2 = (int*)malloc(sizeof(int) * N2);
    for (int i = 0; i < N2; i++) H2[i] = rand() % 10000;
    buildMinHeap(H2, N2);

    int mergedN = 0;
    t1 = chrono::high_resolution_clock::now();
    int* merged = mergeHeaps(H, N, H2, N2, mergedN);
    t2 = chrono::high_resolution_clock::now();

    cout << "merge(H1,H2): yeniBoyut=" << mergedN
         << ", min=" << merged[0]
         << ", sure=" << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count()
         << " ms\n";

    free(H);
    free(H2);
    free(merged);
    return 0;
}
