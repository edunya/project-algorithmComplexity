# Algoritma Analizi Projesi (C++)

Bu proje, derste işlenen temel algoritma konularını (Rekürsif, Arama, Sıralama, Heap, Greedy, Dinamik Programlama, Maximum Subsequence) C++ ile uygulamak ve **chrono** kullanarak çalışma sürelerini karşılaştırmak amacıyla hazırlanmıştır.

## İçerik / Dosyalar

Projede her konu ayrı bir `.cpp` dosyası olarak tutulmuştur. Her dosyanın içinde `main()` vardır ve tek başına derlenip çalıştırılabilir.

- **MaxSubsequence.cpp**
  - Maximum Subsequence problemi için 4 farklı yaklaşım:
    - O(n³) Brute Force
    - O(n²) İyileştirilmiş Brute Force
    - O(n log n) Divide & Conquer
    - O(n) Kadane
  - Aynı veri üzerinde süre karşılaştırması yapılır (chrono).

- **Recursive.cpp**
  - 6 farklı rekürsif problem:
    1) 1+2+...+N  
    2) Dizi toplamı  
    3) a^n (Divide & Conquer)  
    4) Fibonacci  
    5) Tower of Hanoi  
    6) Recursive Digit Sum  
  - Her problemde **çağrı sayısı** (recursive call count) tutulur ve yazdırılır.

- **Search.cpp**
  - İleri yönlü lineer arama
  - Geri yönlü lineer arama
  - İkili arama (binary search)
  - Aynı aranan değer için tekrar sayısı üzerinden süre ölçümü yapılır (chrono).

- **Sort.cpp**
  - Sıralama algoritmaları ve süre ölçümleri (chrono):
    - Selection Sort
    - Bubble Sort
    - Insertion Sort
    - Merge Sort
    - Quick Sort
    - Heap Sort
    - Counting Sort (Satellite Data - stabil sıralama demo)
    - Radix Sort
    - External Sort (simülasyon: parçala + her parçayı sırala + merge)

- **heap.cpp**
  - Min-heap işlemleri:
    - findMin
    - deleteMin (heapify)
    - insert
    - buildMinHeap
    - decreaseKey / increaseKey
    - deleteKey
  - Ek olarak:
    - buildMaxHeap gösterimi
    - merge(H1, H2) (iki heap’i birleştirip yeniden heap oluşturma)

- **greedy.cpp**
  - Greedy algoritmalar:
    - İş Zamanlama (Job Sequencing with Deadlines: deadline + profit)
    - Aktivite Zamanlama (Activity Selection)
    - Huffman (Encode / Decode)
  - Süre ölçümleri chrono ile yapılır.

- **dinamik.cpp**
  - Dinamik programlama örnekleri:
    - Bottom-Up Fibonacci (DP tablosu gösterimi)
    - Minimum Maliyet Yol (Top-Down memoization, tablo gösterimi)
    - 0/1 Knapsack (DP tablosu gösterimi)

---

## Kurulum ve Derleme

### Gereksinimler
- C++ derleyicisi (g++ / clang / Visual Studio)
- C++11 veya üzeri önerilir

### Windows (MinGW / g++)
Örnek:
```bash
g++ -std=c++11 MaxSubsequence.cpp -o MaxSubsequence
./MaxSubsequence
