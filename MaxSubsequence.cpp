#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

long long alg1_n3(const std::vector<int>& a) {
    long long best = 0;
    int n = (int)a.size();

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            long long sum = 0;
            for (int k = i; k <= j; k++) sum += a[k];
            if (sum > best) best = sum;
        }
    }
    return best;
}

long long alg2_n2(const std::vector<int>& a) {
    long long best = 0;
    int n = (int)a.size();

    for (int i = 0; i < n; i++) {
        long long sum = 0;
        for (int j = i; j < n; j++) {
            sum += a[j];
            if (sum > best) best = sum;
        }
    }
    return best;
}

// divide & conquer yardımcıları
long long cross_sum(const std::vector<int>& a, int l, int m, int r) {
    long long bestL = 0, sum = 0;
    for (int i = m; i >= l; i--) {
        sum += a[i];
        if (sum > bestL) bestL = sum;
    }

    long long bestR = 0;
    sum = 0;
    for (int i = m + 1; i <= r; i++) {
        sum += a[i];
        if (sum > bestR) bestR = sum;
    }

    return bestL + bestR;
}

long long divconq_rec(const std::vector<int>& a, int l, int r) {
    if (l == r) return std::max(0, a[l]);

    int m = l + (r - l) / 2;
    long long left = divconq_rec(a, l, m);
    long long right = divconq_rec(a, m + 1, r);
    long long cross = cross_sum(a, l, m, r);

    return std::max(left, std::max(right, cross));
}

long long alg3_nlogn(const std::vector<int>& a) {
    if (a.empty()) return 0;
    return divconq_rec(a, 0, (int)a.size() - 1);
}

// Kadane O(n)
long long alg4_n(const std::vector<int>& a) {
    long long best = 0;
    long long cur = 0;
    for (int x : a) {
        cur = cur + x;
        if (cur < 0) cur = 0;
        if (cur > best) best = cur;
    }
    return best;
}

std::vector<int> rastgele_dizi(int n, int lo, int hi) {
    std::mt19937 rng((unsigned)std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(lo, hi);

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = dist(rng);
    return a;
}

long long zaman_olc_ve_sonuc(const std::vector<int>& a,
                            long long (*fn)(const std::vector<int>&),
                            long long& sonuc) {
    auto t0 = std::chrono::steady_clock::now();
    sonuc = fn(a);
    auto t1 = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
}

int main() {
    int N = 1500;
    int lo = -100, hi = 100;

    std::vector<int> A = rastgele_dizi(N, lo, hi);

    long long s1, s2, s3, s4;
    long long t1 = zaman_olc_ve_sonuc(A, alg1_n3, s1);
    long long t2 = zaman_olc_ve_sonuc(A, alg2_n2, s2);
    long long t3 = zaman_olc_ve_sonuc(A, alg3_nlogn, s3);
    long long t4 = zaman_olc_ve_sonuc(A, alg4_n, s4);

    std::cout << "N=" << N << "  aralik=[" << lo << "," << hi << "]\n";
    std::cout << "Alg1 O(n^3)     : " << t1 << " ms  Sonuc=" << s1 << "\n";
    std::cout << "Alg2 O(n^2)     : " << t2 << " ms  Sonuc=" << s2 << "\n";
    std::cout << "Alg3 O(n log n) : " << t3 << " ms  Sonuc=" << s3 << "\n";
    std::cout << "Alg4 O(n)       : " << t4 << " ms  Sonuc=" << s4 << "\n";

    // basit doğrulama
    if (!(s1 == s4 && s2 == s4 && s3 == s4)) {
        std::cout << "Uyari: algoritmalar ayni sonucu vermedi.\n";
    }

    return 0;
}
