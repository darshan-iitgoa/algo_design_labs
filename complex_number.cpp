#include <iostream>
#include <cmath>
using namespace std;

class Complex {
public:
    double re, im;

    Complex(double r = 0, double i = 0) : re(r), im(i) {}

    // Addition
    Complex operator+(const Complex& other) const {
        return Complex(re + other.re, im + other.im);
    }

    // Subtraction
    Complex operator-(const Complex& other) const {
        return Complex(re - other.re, im - other.im);
    }

    // Multiplication
    Complex operator*(const Complex& other) const {
        return Complex(
            re * other.re - im * other.im,
            re * other.im + im * other.re
        );
    }

    // Scalar multiplication
    Complex operator*(double k) const {
        return Complex(re * k, im * k);
    }

    // Power (integer exponent)
    Complex pow(int n) const {
        Complex result(1, 0);
        Complex base = *this;
        while (n > 0) {
            if (n & 1) result = result * base;
            base = base * base;
            n >>= 1;
        }
        return result;
    }

    // Magnitude
    double abs() const {
        return sqrt(re * re + im * im);
    }


    void print(double eps = 1e-9) const {
        double r = (fabs(re) < eps) ? 0.0 : re;
        double i = (fabs(im) < eps) ? 0.0 : im;

        if (i == 0) {
            cout << r;
        } else if (r == 0) {
            cout << i << "i";
        } else {
            cout << r << (i > 0 ? " + " : " - ") << fabs(i) << "i";
        }
    }

};

// Function to get nth root of unity

Complex wn(int n, int k = 1) {
    double angle = 2 * M_PI * k / n;
    return Complex(cos(angle), sin(angle));
}


int main() {
    int n = 8;      // n must be EVEN for properties 2 & 3
    int k = 3;

    cout << "n = " << n << ", k = " << k << "\n\n";

    // Property 1: (e^(2πik/n))^n = 1
    Complex w = wn(n, k);
    Complex lhs1 = w.pow(n);
    Complex one(1, 0);

    cout << "Property 1:\n";
    lhs1.print();
    cout << " = 1 " << endl << endl;

    // Property 2: (w_n^k)^2 = (w_(n/2))^k
    Complex lhs2 = wn(n, k).pow(2);
    Complex rhs2 = wn(n / 2, k);

    cout << "Property 2:\n";
    lhs2.print();
    cout << " = ";
    rhs2.print();
    cout << endl << endl;

    // Property 3: w_n^(k+n/2) = -w_n^k
    Complex lhs3 = wn(n, k + n / 2);
    Complex rhs3 = wn(n, k) * (-1);

    cout << "Property 3:\n";
    lhs3.print();
    cout << " = ";
    rhs3.print();
    cout << endl << endl;

    return 0;
}
