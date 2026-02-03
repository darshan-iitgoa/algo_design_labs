#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class Complex {
public:
    double re, im;

    Complex(double r = 0, double i = 0) : re(r), im(i) {}

    Complex operator+(const Complex& other) const {
        return Complex(re + other.re, im + other.im);
    }

    Complex operator-(const Complex& other) const {
        return Complex(re - other.re, im - other.im);
    }

    Complex operator*(const Complex& other) const {
        return Complex(
            re * other.re - im * other.im,
            re * other.im + im * other.re
        );
    }

    void print(double eps = 1e-9) const {
        double r = (fabs(re) < eps) ? 0.0 : re;
        double i = (fabs(im) < eps) ? 0.0 : im;

        if (i == 0) cout << r;
        else if (r == 0) cout << i << "i";
        else cout << r << (i > 0 ? " + " : " - ") << fabs(i) << "i";
    }
};

// nth root of unity
Complex wn(int n) {
    double angle = 2 * M_PI / n;
    return Complex(cos(angle), sin(angle));
}


vector<Complex> FFT(vector<Complex> coeff) {
    int n = coeff.size();
    if (n == 1) return coeff;

    vector<Complex> Pe, Po;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) Pe.push_back(coeff[i]);
        else Po.push_back(coeff[i]);
    }

    vector<Complex> ye = FFT(Pe);
    vector<Complex> yo = FFT(Po);

    vector<Complex> y(n);
    Complex w = wn(n);
    Complex wj(1, 0);

    for (int j = 0; j < n / 2; j++) {
        y[j] = ye[j] + wj * yo[j];
        y[j + n / 2] = ye[j] - wj * yo[j];
        wj = wj * w;
    }

    return y;
}

vector<Complex> IFFT(vector<Complex> coeff, int orig_n) {
    int n = coeff.size();
    if (n == 1) return coeff;

    vector<Complex> Pe, Po;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) Pe.push_back(coeff[i]);
        else Po.push_back(coeff[i]);
    }

    vector<Complex> ye = IFFT(Pe, orig_n);
    vector<Complex> yo = IFFT(Po, orig_n);

    vector<Complex> y(n);
    Complex w = wn(-n);   // inverse root
    Complex wj(1, 0);

    for (int j = 0; j < n / 2; j++) {
        y[j] = ye[j] + wj * yo[j];
        y[j + n / 2] = ye[j] - wj * yo[j];
        wj = wj * w;
    }

    if (n == orig_n) {
        double inv_n = 1.0 / orig_n;
        for (int i = 0; i < n; i++)
            y[i] = y[i] * inv_n;
    }

    return y;
}


int main() {
    // P(x) = 1 + 2x + 3x^2 + 4x^3
    vector<Complex> coeff;
    coeff.push_back(Complex(1, 0));
    coeff.push_back(Complex(2, 0));
    coeff.push_back(Complex(3, 0));
    coeff.push_back(Complex(4, 0));

    cout << "Original coefficients:\n";
    for (auto &c : coeff) {
        c.print();
        cout << "\n";
    }

    cout << "\nFFT output:\n";
    vector<Complex> values = FFT(coeff);
    for (auto &v : values) {
        v.print();
        cout << "\n";
    }

    cout << "\nAfter IFFT:\n";
    vector<Complex> recovered = IFFT(values, values.size());
    for (auto &c : recovered) {
        c.print();
        cout << "\n";
    }

    return 0;
}
