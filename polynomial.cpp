#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

class Polynomial {
public:
    vector<double> coeff;   // coeff[i] = coefficient of x^i
    int degree;

    // Default constructor
    Polynomial() : degree(0), coeff({0.0}) {}

    // Constructor from coefficients
    Polynomial(const vector<double>& c) {
        coeff = c;
        degree = (int)coeff.size() - 1;
        normalize();
    }

    Polynomial(const vector<pair<double,double>>& points) {
        int n = points.size();

        Polynomial result(vector<double>(1, 0.0)); // zero polynomial

        for (int i = 0; i < n; i++) {
            double xi = points[i].first;
            double yi = points[i].second;

            Polynomial Li(vector<double>(1, 1.0)); // starting with 1
            double denom = 1.0;

            for (int j = 0; j < n; j++) {
                if (i == j) continue;

                double xj = points[j].first;
                Li = Li * Polynomial({-xj, 1}); // (x - xj)
                denom *= (xi - xj);
            }

            // Multiplying Li by yi / denom
            for (double& c : Li.coeff)
                c *= (yi / denom);

            result = result + Li;
        }

        coeff = result.coeff;
        degree = coeff.size() - 1;
        normalize();
    }

    // Remove trailing zeros
    void normalize() {
        while (coeff.size() > 1 && abs(coeff.back()) < 1e-9)
            coeff.pop_back();
        degree = coeff.size() - 1;
    }

    // Addition
    Polynomial operator+(const Polynomial& other) const {
        int max_deg = max(degree, other.degree);
        vector<double> res(max_deg + 1, 0.0);

        for (int i = 0; i <= degree; i++)
            res[i] += coeff[i];
        for (int i = 0; i <= other.degree; i++)
            res[i] += other.coeff[i];

        return Polynomial(res);
    }

    // Subtraction
    Polynomial operator-(const Polynomial& other) const {
        int max_deg = max(degree, other.degree);
        vector<double> res(max_deg + 1, 0.0);

        for (int i = 0; i <= degree; i++)
            res[i] += coeff[i];
        for (int i = 0; i <= other.degree; i++)
            res[i] -= other.coeff[i];

        return Polynomial(res);
    }

    // Multiplication (brute-force convolution)
    Polynomial operator*(const Polynomial& other) const {
        vector<double> res(degree + other.degree + 1, 0.0);

        for (int i = 0; i <= degree; i++)
            for (int j = 0; j <= other.degree; j++)
                res[i + j] += coeff[i] * other.coeff[j];

        return Polynomial(res);
    }

    // Evaluate polynomial at a point
    double evaluate(double x) const {
        double result = 0.0;
        double power = 1.0;
        for (int i = 0; i <= degree; i++) {
            result += coeff[i] * power;
            power *= x;
        }
        return result;
    }

    // Evaluate at multiple x values
    vector<pair<double,double>> evaluate(const vector<double>& xs) const {
        vector<pair<double,double>> res;
        for (double x : xs)
            res.push_back({x, evaluate(x)});
        return res;
    }

    // Print polynomial
    void print() const {
        for (int i = degree; i >= 0; i--) {
            cout << coeff[i];
            if (i > 0) cout << "x^" << i << " + ";
        }
        cout << endl;
    }
};

int main() {
    vector<pair<double,double>> points = {
        {1, 2},
        {2, 3},
        {4, 1}
    };

    Polynomial P(points);

    cout << "Interpolated Polynomial:\n";
    P.print();

    cout << "\nCheck values:\n";
    for (auto& p : points) {
        cout << "P(" << p.first << ") = "
             << P.evaluate(p.first) << endl;
    }

    return 0;
}
