#define NOMINMAX
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;

// O(n^3)
int maxSubSum1(const vector<int>& a) {
    int maxSum = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        for (int j = i; j < (int)a.size(); j++) {
            int thisSum = 0;
            for (int k = i; k <= j; k++) thisSum += a[k];
            maxSum = max(maxSum, thisSum);
        }
    }
    return maxSum;
}

// O(n^2)
int maxSubSum2(const vector<int>& a) {
    int maxSum = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        int thisSum = 0;
        for (int j = i; j < (int)a.size(); j++) {
            thisSum += a[j];
            maxSum = max(maxSum, thisSum);
        }
    }
    return maxSum;
}

static inline int max3(int x, int y, int z) {
    return max(x, max(y, z));
}

// O(n log n) Divide & Conquer
int maxSubSumRec(const vector<int>& a, int left, int right) {
    if (left == right) return (a[left] > 0) ? a[left] : 0;

    int mid = (left + right) / 2;
    int leftBest = maxSubSumRec(a, left, mid);
    int rightBest = maxSubSumRec(a, mid + 1, right);

    int leftBorderBest = 0, leftBorderSum = 0;
    for (int i = mid; i >= left; i--) {
        leftBorderSum += a[i];
        leftBorderBest = max(leftBorderBest, leftBorderSum);
    }

    int rightBorderBest = 0, rightBorderSum = 0;
    for (int i = mid + 1; i <= right; i++) {
        rightBorderSum += a[i];
        rightBorderBest = max(rightBorderBest, rightBorderSum);
    }

    return max3(leftBest, rightBest, leftBorderBest + rightBorderBest);
}

int maxSubSum3(const vector<int>& a) {
    return maxSubSumRec(a, 0, (int)a.size() - 1);
}

// O(n) Kadane
int maxSubSum4(const vector<int>& a) {
    int maxSum = 0, thisSum = 0;
    for (int x : a) {
        thisSum += x;
        if (thisSum > maxSum) maxSum = thisSum;
        else if (thisSum < 0) thisSum = 0;
    }
    return maxSum;
}

int main() {
    cout << "MAXIMUM SUBSEQUENCE PROBLEMI\n";
    cout << "----------------------------\n";

    // O(n^3) olduğu için N çok büyütülürse aşırı yavaşlar.
    // Burada tüm yaklaşımlar için aynı veri kullanılıyor.
    int N = 500;

    vector<int> A(N);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(-50, 50);
    for (int i = 0; i < N; i++) A[i] = dist(gen);

    auto t0 = chrono::high_resolution_clock::now();
    int s1 = maxSubSum1(A);
    auto t1 = chrono::high_resolution_clock::now();
    cout << "Alg1 O(n^3)   : " << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count()
         << " ms | sonuc=" << s1 << "\n";

    t0 = chrono::high_resolution_clock::now();
    int s2 = maxSubSum2(A);
    t1 = chrono::high_resolution_clock::now();
    cout << "Alg2 O(n^2)   : " << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count()
         << " ms | sonuc=" << s2 << "\n";

    t0 = chrono::high_resolution_clock::now();
    int s3 = maxSubSum3(A);
    t1 = chrono::high_resolution_clock::now();
    cout << "Alg3 O(nlogn) : " << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count()
         << " ms | sonuc=" << s3 << "\n";

    t0 = chrono::high_resolution_clock::now();
    int s4 = maxSubSum4(A);
    t1 = chrono::high_resolution_clock::now();
    cout << "Alg4 O(n)     : " << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count()
         << " ms | sonuc=" << s4 << "\n";

    return 0;
}
