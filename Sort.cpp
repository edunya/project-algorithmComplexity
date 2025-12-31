#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

static inline void SWAP(int& a, int& b) { int t = a; a = b; b = t; }

// Selection
void selectionSort(int A[], int N) {
    for (int i = 0; i < N - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < N; j++)
            if (A[j] < A[minIdx]) minIdx = j;
        if (minIdx != i) SWAP(A[i], A[minIdx]);
    }
}

// Bubble
void bubbleSort(int A[], int N) {
    for (int i = 0; i < N - 1; i++) {
        bool degisti = false;
        for (int j = 0; j < N - 1 - i; j++) {
            if (A[j] > A[j + 1]) {
                SWAP(A[j], A[j + 1]);
                degisti = true;
            }
        }
        if (!degisti) break;
    }
}

// Insertion
void insertionSort(int A[], int N) {
    for (int p = 1; p < N; p++) {
        int tmp = A[p];
        int j = p;
        while (j > 0 && A[j - 1] > tmp) {
            A[j] = A[j - 1];
            j--;
        }
        A[j] = tmp;
    }
}

// Merge Sort
void mergeParts(int A[], int left, int mid, int right, int temp[]) {
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (A[i] <= A[j]) temp[k++] = A[i++];
        else temp[k++] = A[j++];
    }
    while (i <= mid) temp[k++] = A[i++];
    while (j <= right) temp[k++] = A[j++];
    for (int x = left; x <= right; x++) A[x] = temp[x];
}
void mergeSortRec(int A[], int left, int right, int temp[]) {
    if (left >= right) return;
    int mid = (left + right) / 2;
    mergeSortRec(A, left, mid, temp);
    mergeSortRec(A, mid + 1, right, temp);
    mergeParts(A, left, mid, right, temp);
}
void mergeSort(int A[], int N) {
    int* temp = new int[N];
    mergeSortRec(A, 0, N - 1, temp);
    delete[] temp;
}

// Quick Sort (Lomuto partition)
int partitionLomuto(int A[], int low, int high) {
    int pivot = A[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (A[j] <= pivot) {
            i++;
            SWAP(A[i], A[j]);
        }
    }
    SWAP(A[i + 1], A[high]);
    return i + 1;
}
void quickSortRec(int A[], int low, int high) {
    if (low >= high) return;
    int p = partitionLomuto(A, low, high);
    quickSortRec(A, low, p - 1);
    quickSortRec(A, p + 1, high);
}
void quickSort(int A[], int N) { quickSortRec(A, 0, N - 1); }

// Heap Sort (max heap)
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
void heapSort(int A[], int N) {
    for (int i = N / 2 - 1; i >= 0; i--) heapifyMax(A, N, i);
    for (int i = N - 1; i > 0; i--) {
        SWAP(A[0], A[i]);
        heapifyMax(A, i, 0);
    }
}

// Counting Sort (Satellite Data)
struct SatItem {
    int key;
    char tag;
};
void countingSortSatellite(vector<SatItem>& items, int maxKey) {
    vector<int> count(maxKey + 1, 0);
    vector<SatItem> out(items.size());

    for (auto& it : items) count[it.key]++;

    for (int i = 1; i <= maxKey; i++) count[i] += count[i - 1];

    // stable olması için sondan ilerliyoruz
    for (int i = (int)items.size() - 1; i >= 0; i--) {
        out[count[items[i].key] - 1] = items[i];
        count[items[i].key]--;
    }

    items = out;
}

// Radix Sort (LSD)
void countingByDigit(int A[], int N, int exp) {
    int count[10] = {0};
    int* out = new int[N];

    for (int i = 0; i < N; i++) count[(A[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++) count[i] += count[i - 1];

    for (int i = N - 1; i >= 0; i--) {
        int d = (A[i] / exp) % 10;
        out[count[d] - 1] = A[i];
        count[d]--;
    }

    for (int i = 0; i < N; i++) A[i] = out[i];
    delete[] out;
}
void radixSort(int A[], int N) {
    int mx = 0;
    for (int i = 0; i < N; i++) mx = max(mx, A[i]);
    for (int exp = 1; mx / exp > 0; exp *= 10)
        countingByDigit(A, N, exp);
}

// External Sorting
void externalSortSim(int A[], int N, int K) {
    if (K <= 1) { quickSort(A, N); return; }

    int parca = N / K;
    if (parca == 0) { quickSort(A, N); return; }

    // K run oluştur
    for (int p = 0; p < K; p++) {
        int start = p * parca;
        int size = (p == K - 1) ? (N - start) : parca;
        quickSort(A + start, size);
    }

    // K-way merge
    vector<int> idx(K, 0);
    vector<int> out(N);

    for (int t = 0; t < N; t++) {
        int bestVal = INT_MAX;
        int bestPart = -1;

        for (int p = 0; p < K; p++) {
            int start = p * parca;
            int size = (p == K - 1) ? (N - start) : parca;

            if (idx[p] < size) {
                int v = A[start + idx[p]];
                if (v < bestVal) {
                    bestVal = v;
                    bestPart = p;
                }
            }
        }

        out[t] = bestVal;
        idx[bestPart]++;
    }

    for (int i = 0; i < N; i++) A[i] = out[i];
}

static void kopyala(int* dst, const int* src, int N) {
    for (int i = 0; i < N; i++) dst[i] = src[i];
}

int main() {
    cout << "SIRALAMA ALGORITMALARI (chrono ile sure)\n";
    cout << "---------------------------------------\n";

    srand((unsigned)time(nullptr));
    int N = 10000;

    int* original = new int[N];
    int* test = new int[N];

    for (int i = 0; i < N; i++) original[i] = rand() % 50000;

    auto runAndPrint = [&](const char* name, void(*fn)(int*, int)) {
        kopyala(test, original, N);
        auto t1 = chrono::high_resolution_clock::now();
        fn(test, N);
        auto t2 = chrono::high_resolution_clock::now();
        cout << name << ": "
             << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count()
             << " ms\n";
    };

    runAndPrint("Selection Sort", selectionSort);
    runAndPrint("Bubble Sort   ", bubbleSort);
    runAndPrint("Insertion Sort", insertionSort);
    runAndPrint("Merge Sort    ", mergeSort);
    runAndPrint("Quick Sort    ", quickSort);
    runAndPrint("Heap Sort     ", heapSort);

    // Counting Sort (Satellite Data)
    {
        vector<SatItem> items = {
            {3,'A'},{1,'B'},{3,'C'},{2,'D'},{1,'E'},{0,'F'},{2,'G'},{3,'H'}
        };
        auto t1 = chrono::high_resolution_clock::now();
        countingSortSatellite(items, 3);
        auto t2 = chrono::high_resolution_clock::now();

        cout << "Counting Sort (Satellite) : "
             << chrono::duration_cast<chrono::microseconds>(t2 - t1).count()
             << " us | sonuc=";

        for (auto& it : items) cout << "(" << it.key << "," << it.tag << ") ";
        cout << "\n";
    }

    // Radix Sort
    {
        kopyala(test, original, N);
        auto t1 = chrono::high_resolution_clock::now();
        radixSort(test, N);
        auto t2 = chrono::high_resolution_clock::now();
        cout << "Radix Sort    : "
             << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count()
             << " ms\n";
    }

    // External Sorting Sim
    {
        kopyala(test, original, N);
        auto t1 = chrono::high_resolution_clock::now();
        externalSortSim(test, N, 4);
        auto t2 = chrono::high_resolution_clock::now();
        cout << "External Sort : "
             << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count()
             << " ms\n";
    }

    delete[] original;
    delete[] test;
    return 0;
}
