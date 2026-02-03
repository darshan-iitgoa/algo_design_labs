#include <bits/stdc++.h>
using namespace std;

vector<int> bit_reversal(int n) {
    vector<int> rev(n);
    rev[0] = 0;

    for (int i = 1; i < n; i++) {
        int bit = n >> 1;
        rev[i] = rev[i - 1];

        while (rev[i] & bit) {
            rev[i] ^= bit;
            bit >>= 1;
        }
        rev[i] |= bit;
    }
    return rev;
}

int main() {
    int n = 8;
    auto rev = bit_reversal(n);
    for (int x : rev) cout << x << " ";
}
