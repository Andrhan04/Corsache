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

    void CreateSpeed() {
        Speed = returnRandom(10, 100) / 100.0;
    }

    void CreateDirection() {
        Direction = returnRandom(0, 359);
    }
    struct Punch{
        double X, Y;
        bool was = false;
    };

    int InWorkZone(double x, double y) {
        if (x < 0.0) {
            return 1;
        }
        if (x > 50000.0) {
            return 2;
        }
        if (y < 0.0) {
            return 3;
        }
        if (y > 1000.0) {
            return 4;
        }
        return 0;
    }

    int InWork(double x, double y) {
        /*
            В рабочем поле 0
            Левее зоны 1
            Правее зоны 2
            Ниже зоны 3
            Выше зоны 4
            Левее и ниже 5
            Правее и ниже 6
            Левее и выше 7
            Правее и выше 8
        */
        bool down = false, up = false, right = false, left = false;
        if (x < 0.0) {
            left = true;
        }
        if (x < 50000.0) {
            right = true;
        }
        if (y < 0.0) {
            down = true;
        }
        if (y > 1000.0) {
            up = true;
        }
        if (!down && !up && !right && left) {
            return 1;
        }
        if (!down && !up && right && !left) {
            return 2;
        }
        if (down && !up && !right && !left) {
            return 3;
        }
        if (!down && up && !right && !left) {
            return 4;
        }
        if (down && !up && !right && left) {
            return 5;
        }
        if (down && !up && right && !left) {
            return 6;
        }
        if (!down && up && !right && left) {
            return 7;
        }
        if (!down && up && right && !left) {
            return 8;
        }
        return 0;
    }

public:
    double X, Y; // координата Х, координата Y,
    double Speed; // 0.1 - 1 скорость,
    int Direction; // 0 - 359 направление.
    vector <Punch> v;
    bool Work = false;

    bool Same(Point* other) {
        return ((abs(other->X - X) < eps) && (abs(other->Y - Y) < eps));
    }

    void iteration() {
        CreateDirection();
        if (!Work && (Direction > 90 && Direction < 270)) {
            if (Direction > 180) {
                Direction += 90;
            }
            else {
                Direction -= 90;
            }
        }
        pair<double, double> p = Dif();
        auto [x, y] = p;
        x += X;
        y += Y;
        if (Work) {
            int flag = InWork(x, y);
            if (flag == 0) {
                X = x;
                Y = y;
            }
            else {
                double tg = tan(Direction * acos(-1) / 180);
                if (Direction == 45 || Direction == 135 || Direction == 225 || Direction == 315) {
                    return;
                }
                else {
                    if (flag < 5) {

                    }
                    else {

                    }
                }
            }
        }
        else {
            if (X < eps) {
                
            }
            

        }
    }

    void step() {
        CreateDirection();
        if (Direction > 90 && Direction < 270) {
            if (Direction > 180) {
                Direction += 90;
            }
            else {
                Direction -= 90;
            }
        }
        auto [dx, dy] = Dif();

        if (Work) { // Стенки
            double new_x = X + dx, new_y = Y + dy;
            int flag = InWorkZone(new_x, new_y);
            while (!flag) {
                Punch p;
                if (flag == 1) {
                    p.X = 0;
                    p.Y = Y - (((new_y - Y) * X) / (new_x - X));
                }
                else {
                    if (flag == 2) {
                        p.X = 50000.0;
                        p.Y = ((p.X - X) / (new_x - X)) * (new_y - Y) + Y;
                    }
                    else {
                        if (flag == 3) {
                            p.Y = 0;
                            p.X = X - (Y * (new_x - X) / (new_y - Y));
                        }
                        else {
                            p.Y = 1000.0;
                            p.X = X + ((p.Y-Y) * (new_x - X) / (new_y - Y));
                        }
                    }
                }
                v.push_back(p);
            }
        }
        else {

        }
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


class Trap
{
private:
    double eps = 1e-4;
    mt19937 random_generator_;

    int returnRandom(int min, int max) {
        if (max < min) swap(max, min);
        std::uniform_int_distribution<int> range(min, max);
        return range(random_generator_);
    }

public:
    double X, Y, Range;
    bool alive;
    Trap(double x, double y) {
        random_device device;
        random_generator_.seed(device());
        X = x;
        Y = y;
        Range = 0.5;
        alive = true;
    }

    bool Catch(Point * p) {
        return false;
    }


};


int main() {
    string line;
    ifstream in_Point("C:\\Corsache\\Sowing\\startPoints.txt");
    ifstream in_Traps("C:\\Corsache\\Sowing\\startTraps.txt");
    vector<Point*> myArr;
    if (in_Point.is_open() && in_Traps.is_open())
    {
        getline(in_Point, line);
        getline(in_Point, line);
        while (getline(in_Point, line))
        {
            string X = line.substr(0, 9);
            string Y = line.substr(9);
            Point* p = new Point(stod(X), stod(Y));
            myArr.push_back(p);
        }
        int t = 100;
        getline(in_Traps, line);
        getline(in_Traps, line);
        while (getline(in_Traps, line))
        {
            string X = line.substr(0, 10);
            string Y = line.substr(10);
            Point* p = new Point(stod(X), stod(Y));
            myArr.push_back(p);
        }
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
    in_Point.close();
    in_Traps.close();

}
