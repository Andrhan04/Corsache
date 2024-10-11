#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <fstream>
#include <math.h>
#include <random>

using namespace std;
#define all(v) (v).begin(),(v).end()

class Point {
private:
    double eps = 1e-4;
    mt19937 random_generator_;
    /*
    pair <double, double> Dif() {
        double Angle = Direction * acos(-1) / 180;
        double x = (cos(Angle) * Speed);
        double y = (sin(Angle) * Speed);
        return { x,y };
    }
    */

    int returnRandom(int min, int max) {
        if (max < min) swap(max, min);
        std::uniform_int_distribution<int> range(min, max);
        return range(random_generator_);
    }

    void CreateCoord() {
        //uniform_int_distribution die{ -10, 10 };
        X = returnRandom(0, 1000);
        X = -X;
        Y = returnRandom(0, 1000);
    }
    /*
    void CreateSpeed() {
        //uniform_int_distribution die{ 0, 100 };
        Speed = returnRandom(0,100) / 100.0;
    }

    void CreateDirection() {
        //uniform_int_distribution die{ 0, 359 };
        Direction = returnRandom(0,359);
    }
    */

public:
    double X, Y; // 0 - 1000 координата Х, координата Y,
    //double Speed; // 0.1 - 1 скорость,
    //int Direction; // 0 - 359 направление.

    bool Same(Point* other) {
        return ((abs(other->X - X) < eps) && (abs(other->Y - Y) < eps));
    }

    void Create() {
        CreateCoord();
        //CreateSpeed();
        //CreateDirection();
    }
    /*
    void iteration() {
        pair<double, double> p = Dif();
        X += p.first;
        Y += p.second;
        CreateSpeed();
        CreateDirection();
    }
    */
    Point() {
        random_device device;
        random_generator_.seed(device());
        Create();
    }
};

int main() {
    ofstream Start("C:\\Corsache\\Sowing\\startPoints.txt");
    if (!Start.is_open()) return 0;
    int n = 1000, r = 0;
    vector<Point*> v;
    Start << "JSON\nTest2DStochastic" << endl;
    for (int i = 0; i < n; i++) {
        Point* p = new Point();
        bool unic = true;
        bool repeat = true;
        while (repeat) {
            for (auto i : v) {
                if (p->Same(i)) {
                    unic = false;
                    break;
                }
            }
            if (!unic) {
                p->Create();
                unic = true;
                r++;
            }
            else {
                repeat = false;
            }
        }
        v.push_back(p);

        Start << setprecision(3) << fixed << setw(8) << p->X << setw(8) << p->Y << setw(8) << endl;
        cout << setprecision(3) << fixed << setw(8) << p->X << setw(8) << p->Y << setw(8) << endl;

    }
    cout << r;
    return 0;
}