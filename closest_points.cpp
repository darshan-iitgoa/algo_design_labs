#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

const double INF = 1e18;

struct Point {
    double x;
    double y;
    Point(double X, double Y) {
        this->x = X;
        this->y = Y;
    }
};

/*
 * HELPER FUNCTIONS
 */

// Function to display a vector of points on the console
void displayPoints(vector<Point *> pts) {
    for (int i = 0; i < pts.size(); i++) {
        cout << "(" << pts[i]->x << "," << pts[i]->y << ") ";
    }
    cout << endl;
}

// Function to find the distance between two points p and q, that is ||p-q||
double norm(Point* p, Point* q) {
    double x_diff = p->x - q->x;
    double y_diff = p->y - q->y;
    return sqrt(x_diff*x_diff + y_diff*y_diff);
}


// Function to find the minimum distance between 2 points from a given set using brute force
double min_dist_brute(vector<Point *> pts) {
    double min_dist = INF;
    for (int i = 0; i < pts.size(); i++) {
        for (int j = i+1; j < pts.size(); j++) {
            double dist = norm(pts[i], pts[j]);
            min_dist = min(min_dist,dist);
        }
    }
    return min_dist;
}

// comparator function for x coordinate
bool comparator_x(Point * p, Point * q) {
    return p->x < q->x;
}

// comparator function for y coordinate
bool comparator_y(Point * p, Point * q) {
    return p->y < q->y;
}

/*
 * Functions part of the main algorithm
 */

 double CPRec(vector<Point *> Px, vector<Point *> Py, int start, int end) {
     if (end-start+1<= 3) {
         return min_dist_brute(Px);
     }

     int mid = start + (end-start)/2;
     double x_ = Px[mid]->x;
     vector<Point *> Pyl, Pyr;
     for (auto p: Py) {
         if (p->x <= x_) {
             Pyl.push_back(p);
         } else {
             Pyr.push_back(p);
         }
     }

     double dl = CPRec(Px, Pyl, start, mid);
     double dr = CPRec(Px, Pyr, mid+1, end);
     double d = min(dl, dr);

     vector<Point *> strip;
     for (int i = 0; i < Py.size(); i++) {
         if (abs(Py[i]->x - x_) <= d) {
             strip.push_back(Py[i]);
         }
     }

     double min_dist = INF;
     for (int i = 0; i < strip.size(); i++) {
         for (int j = i+1; j<=min(i+15,(int)strip.size()-1); j++) {
             double dist = norm(strip[i], strip[j]);
             min_dist = min(dist, min_dist);
         }
     }

     return min_dist;

 }


 double solve(vector<Point *> pts) {
     vector<Point *> Px = pts;
     vector<Point *> Py = pts;
     sort(Px.begin(), Px.end(), comparator_x);
     sort(Py.begin(), Py.end(), comparator_y);
     return CPRec(Px,Py,0,pts.size()-1);
 }

 /*
  * MAIN FUNCTION
  */
int main() {
    vector<Point*> points = {
        new Point(1.5,  3.2),
        new Point(-2.1, 4.8),
        new Point(0.0, -1.7),
        new Point(3.9, -0.4),
        new Point(-4.6, 2.3),
        new Point(2.2, -3.8),
        new Point(-1.9, -4.1),
        new Point(4.4,  1.1)
    };
    double ans = min_dist_brute(points);
    cout << ans << endl;
    return 0;
}
