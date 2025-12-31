#include <iostream>
#include <algorithm>
#include <climits>
#include <iomanip>

using namespace std;

// 1) Bottom-Up DP (Fibonacci)
int fibBottomUp(int n) {
    int size = max(2, n + 1);
    int* dp = new int[size];

    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) dp[i] = dp[i - 1] + dp[i - 2];

    cout << "Fibo DP Tablosu (i:dp[i]): ";
    for (int i = 0; i <= n; i++) cout << i << ":" << dp[i] << " ";
    cout << "\n";

    int ans = dp[n];
    delete[] dp;
    return ans;
}

// 2) Minimum Maliyet Yol (Top-Down memo)
static const int N = 3;
int M[N][N] = {
    {1,5,0},
    {2,4,2},
    {1,3,0}
};
int memoCost[N][N];

void initMemo() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            memoCost[i][j] = INT_MIN;
}

int minCost(int i, int j) {
    if (i >= N || j >= N) return INT_MAX / 4;
    if (i == N - 1 && j == N - 1) return M[i][j];

    if (memoCost[i][j] != INT_MIN) return memoCost[i][j];

    int down = minCost(i + 1, j);
    int right = minCost(i, j + 1);
    memoCost[i][j] = M[i][j] + min(down, right);
    return memoCost[i][j];
}

void fillAllMemo() {
    for (int i = N - 1; i >= 0; i--) {
        for (int j = N - 1; j >= 0; j--) {
            if (i == N - 1 && j == N - 1) memoCost[i][j] = M[i][j];
            else minCost(i, j);
        }
    }
}

void printMemo() {
    cout << "Min Maliyet Memo Tablosu:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << setw(4) << memoCost[i][j] << " ";
        cout << "\n";
    }
}

// 3) Sırt Çantası (0/1 Knapsack) - DP tablo
static const int ITEM = 5;
int val[ITEM] = {30, 20, 100, 90, 160};
int wt[ITEM]  = {5,  10, 20,  30,  40};

int knapSack(int W) {
    int dp[ITEM + 1][61];

    for (int i = 0; i <= ITEM; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) dp[i][w] = 0;
            else if (wt[i - 1] > w) dp[i][w] = dp[i - 1][w];
            else dp[i][w] = max(dp[i - 1][w], val[i - 1] + dp[i - 1][w - wt[i - 1]]);
        }
    }

    // DP tablosunu yazdır
    cout << "Knapsack DP Tablosu (satir=esyaSayisi, sutun=kapasite)\n";
    cout << setw(5) << " ";
    for (int w = 0; w <= W; w++) cout << setw(4) << w;
    cout << "\n";

    for (int i = 0; i <= ITEM; i++) {
        cout << setw(5) << i;
        for (int w = 0; w <= W; w++) cout << setw(4) << dp[i][w];
        cout << "\n";
    }

    return dp[ITEM][W];
}

int main() {
    cout << "DINAMIK PROGRAMLAMA\n";
    cout << "-------------------\n";

    int n = 8;
    cout << "[1] Fibonacci(" << n << ") = " << fibBottomUp(n) << "\n\n";

    cout << "[2] Min Maliyet Yol (Top-Down)\n";
    initMemo();
    int ans = minCost(0, 0);
    fillAllMemo();
    cout << "Min maliyet (0,0 -> " << N - 1 << "," << N - 1 << ") = " << ans << "\n";
    printMemo();
    cout << "\n";

    cout << "[3] Sirt Cantasi (0/1 Knapsack)\n";
    int cap = 60;
    int best = knapSack(cap);
    cout << "Max deger = " << best << "\n";

    return 0;
}
