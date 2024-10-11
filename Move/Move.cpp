#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <fstream>
#include <math.h>
#include <random>
#include <string>

using namespace std;
#define all(v) (v).begin(),(v).end()

class Point {
private:
    double eps = 1e-4;
    mt19937 random_generator_;

    pair <double, double> Dif() {
        double Angle = Direction * acos(-1) / 180;
        double x = (cos(Angle) * Speed);
        double y = (sin(Angle) * Speed);
        return { x,y };
    }


    int returnRandom(int min, int max) {
        if (max < min) swap(max, min);
        std::uniform_int_distribution<int> range(min, max);
        return range(random_generator_);
    }

    void CreateCoord() {
        X = returnRandom(0, 1000);
        Y = returnRandom(0, 1000);
    }

    void CreateSpeed() {
        Speed = returnRandom(10, 100) / 100.0;
    }

    void CreateDirection() {
        Direction = returnRandom(0, 359);
    }

    bool InBufer() {
        return X < eps;
    }

public:
    double X, Y; // координата Х, координата Y,
    double Speed; // 0.1 - 1 скорость,
    int Direction; // 0 - 359 направление.

    bool Same(Point* other) {
        return ((abs(other->X - X) < eps) && (abs(other->Y - Y) < eps));
    }

    void Create() {
        CreateCoord();
    }

    void iteration() {
        CreateDirection();
        if (InBufer() && (Direction > 90 && Direction < 270)) {
            if (Direction > 180) {
                Direction += 90;
            }
            else {
                Direction -= 90;
            }
        }
        pair<double, double> p = Dif();
        X += p.first;
        Y += p.second;
    }


    Point() {
        random_device device;
        random_generator_.seed(device());
        Create();
    }

    Point(double x, double y) {
        X = x;
        Y = y;
        Direction = 0;
        random_device device;
        random_generator_.seed(device());
        CreateSpeed();
    }
};


int main() {
    string line;
    ifstream in("C:\\Corsache\\Sowing\\startPoints.txt");
    vector<Point*> myArr;
    if (in.is_open())
    {
        getline(in, line);
        getline(in, line);
        while (getline(in, line))
        {
            string X = line.substr(0, 9);
            string Y = line.substr(9);
            Point* p = new Point(stod(X), stod(Y));
            myArr.push_back(p);
        }
        int t = 100;
        while (t--) {
            for (auto i : myArr) {
                i->iteration();
                //cout << setprecision(3) << setw(9) << fixed << i->X << setw(9) << i->Y << setw(7) << i->Speed << endl;
            }
        }
        for (auto i : myArr) {
            i->iteration();
            cout << setprecision(3) << setw(9) << fixed << i->X << setw(9) << i->Y << setw(7) << i->Speed << endl;
        }
    }
    else {
        cout << "warning" << endl;
    }
    in.close();

}
