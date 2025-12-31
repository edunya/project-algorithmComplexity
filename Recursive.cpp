#include <iostream>

using namespace std;

// 1) 1+2+...+N
int toplama_1denN(int n, int& sayac) {
    sayac++;
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return toplama_1denN(n - 1, sayac) + n;
}

// 2) Dizi toplami
int diziToplami(const int A[], int N, int& sayac) {
    sayac++;
    if (N <= 0) return 0;
    if (N == 1) return A[0];
    return diziToplami(A, N - 1, sayac) + A[N - 1];
}

// 3) a^n (divide-conquer)
double usAl(double a, int n, int& sayac) {
    sayac++;
    if (n == 0) return 1.0;
    if (n == 1) return a;

    double yarim = usAl(a, n / 2, sayac);
    double sonuc = yarim * yarim;
    if (n % 2 == 1) sonuc *= a;
    return sonuc;
}

// 4) Fibonacci (rekürsif)
int fib(int n, int& sayac) {
    sayac++;
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return fib(n - 1, sayac) + fib(n - 2, sayac);
}

// 5) Tower of Hanoi
void hanoi(int n, int kaynak, int hedef, int yedek, int& sayac) {
    sayac++;
    if (n == 0) return;
    hanoi(n - 1, kaynak, yedek, hedef, sayac);
    cout << "Disk " << n << ": " << kaynak << " -> " << hedef << "\n";
    hanoi(n - 1, yedek, hedef, kaynak, sayac);
}

// 6) Recursive Digit Sum
int rakamToplaTekSefer(int x) {
    int s = 0;
    while (x > 0) {
        s += (x % 10);
        x /= 10;
    }
    return s;
}

int recursiveDigitSum(int n, int& sayac) {
    sayac++;
    if (n < 10) return n;
    return recursiveDigitSum(rakamToplaTekSefer(n), sayac);
}

int main() {
    cout << "REKURSIF ALGORITMALAR - CAGRI SAYISI\n";
    cout << "-----------------------------------\n";

    int sayac = 0;
    cout << "1) 1+2+...+10 = " << toplama_1denN(10, sayac) << " | cagri=" << sayac << "\n";

    sayac = 0;
    int A[] = {1,2,3,4,5,6,7,8,9,10};
    int N = (int)(sizeof(A) / sizeof(A[0]));
    cout << "2) diziToplami = " << diziToplami(A, N, sayac) << " | cagri=" << sayac << "\n";

    sayac = 0;
    cout << "3) 2^10 = " << usAl(2.0, 10, sayac) << " | cagri=" << sayac << "\n";

    sayac = 0;
    cout << "4) Fibonacci(10) = " << fib(10, sayac) << " | cagri=" << sayac << "\n";

    sayac = 0;
    cout << "5) Tower of Hanoi (n=3)\n";
    hanoi(3, 1, 3, 2, sayac);
    cout << "Hanoi cagri=" << sayac << "\n";

    sayac = 0;
    cout << "6) RecursiveDigitSum(9875) = " << recursiveDigitSum(9875, sayac)
         << " | cagri=" << sayac << "\n";

    return 0;
}
