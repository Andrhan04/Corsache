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
    struct Punch {
        double X, Y;
        bool was = false;
    };

    int InWorkZone(double x, double y) {
        if (x < eps) {
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

    int InBuferZone(double x, double y) {
        if (x > 0.0) {
            Work = true;
            return 1;
        }
        if (x < -1000.0) {
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


public:
    double X, Y; // координата Х, координата Y,
    double Speed; // 0.1 - 1 скорость,
    int Direction; // 0 - 359 направление.
    vector <Punch> v;
    bool Work = false;
    bool Alive = true;

    bool Same(Point* other) {
        return ((abs(other->X - X) < eps) && (abs(other->Y - Y) < eps));
    }

    void step() {
        CreateDirection();
        if (!Work && Direction > 90 && Direction < 270) {
            if (Direction > 180) {
                Direction += 90;
            }
            else {
                Direction -= 90;
            }
        }
        auto [dx, dy] = Dif();

        if (Work) { // Стенки, расстояние сохраняется
            double new_x = X + dx, new_y = Y + dy;
            int flag = InWorkZone(new_x, new_y);
            while (flag != 0) {
                Punch p;
                if (flag == 1) {
                    p.X = 0;
                    p.Y = Y - (((new_y - Y) * X) / (new_x - X));
                    new_x = abs(new_x);
                }
                else {
                    if (flag == 2) {
                        p.X = 50000.0;
                        p.Y = ((p.X - X) / (new_x - X)) * (new_y - Y) + Y;
                        new_x = 50000.0 - (new_x - 50000.0);
                    }
                    else {
                        if (flag == 3) {
                            p.Y = 0;
                            p.X = X - (Y * (new_x - X) / (new_y - Y));
                            new_y = abs(new_y);
                        }
                        else {
                            p.Y = 1000.0;
                            p.X = X + ((p.Y - Y) * (new_x - X) / (new_y - Y));
                            new_y = 1000.0 - (new_y - 1000.0);
                        }
                    }
                }
                v.push_back(p);
                X = p.X; Y = p.Y;
                flag = InWorkZone(new_x, new_y);
            }
            X = new_x; Y = new_y;
        }
        else {
            double new_x = X + dx, new_y = Y + dy;
            int flag = InBuferZone(new_x, new_y);
            while (flag) {
                Punch p;
                if (flag == 1) {
                    Work = true;
                    flag = InWorkZone(new_x + 1, new_y);
                    if (flag) {
                        Punch p;
                        if (flag == 1) {
                            p.X = 0;
                            p.Y = Y - (((new_y - Y) * X) / (new_x - X));
                            new_x = abs(new_x);
                        }
                        else {
                            if (flag == 2) {
                                p.X = 50000.0;
                                p.Y = ((p.X - X) / (new_x - X)) * (new_y - Y) + Y;
                                new_x = 50000.0 - (new_x - 50000.0);
                            }
                            else {
                                if (flag == 3) {
                                    p.Y = 0;
                                    p.X = X - (Y * (new_x - X) / (new_y - Y));
                                    new_y = abs(new_y);
                                }
                                else {
                                    p.Y = 1000.0;
                                    p.X = X + ((p.Y - Y) * (new_x - X) / (new_y - Y));
                                    new_y = 1000.0 - (new_y - 1000.0);
                                }
                            }
                        }
                        v.push_back(p);
                        X = p.X; Y = p.Y;
                    }
                }
                else {
                    if (flag == 2) {
                        new_x = -1000.0 - (new_x + 1000.0);
                    }
                    else {
                        if (flag == 3) {
                            new_y = abs(new_y);
                        }
                        else {
                            new_y = 1000.0 - (new_y - 1000.0);
                        }
                    }
                }
                v.push_back(p);
                X = p.X; Y = p.Y;
                if (Work) {
                    flag = InWorkZone(new_x, new_y);
                }
                else{
                    flag = InBuferZone(new_x, new_y);
                }
            }
            X = new_x; Y = new_y;
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
    bool Alive;
    Trap(double x, double y) {
        random_device device;
        random_generator_.seed(device());
        X = x;
        Y = y;
        Range = 0.5;
        Alive = true;
    }

    bool Catch(Point p) {
        if ((p.X - X) * (p.X - X) + (p.Y - Y) * (p.Y - Y) < Range * Range) {
            p.Alive = false;
            Alive = false;
            cout << "No alive " << p.Alive << ' '  << X << ' ' << Y << endl;
            return true;
        }
        return false;
    }


};


int main() {
    string line;
    ifstream in_Point("C:\\Users\\student\\Desktop\\01321\\c++\\Sowing\\startPoints.txt");
    ifstream in_Traps("C:\\Users\\student\\Desktop\\01321\\c++\\Sowing\\startTraps.txt");
    ofstream Dead("MyFile.txt");
    vector<Point> myArr;
    vector<Trap> myTrap;
    if (in_Point.is_open() && in_Traps.is_open())
    {
        getline(in_Point, line);
        getline(in_Point, line);
        while (getline(in_Point, line))
        {
            string X = line.substr(0, 9);
            string Y = line.substr(9);
            Point p = Point(stod(X), stod(Y));
            myArr.push_back(p);
        }
        cerr << 1 << endl;
        int t = 1000, cp_t;
        cp_t = t;
        getline(in_Traps, line);
        getline(in_Traps, line);
        getline(in_Traps, line);
        while (getline(in_Traps, line))
        {
            string X = line.substr(0, 10);
            string Y = line.substr(10);
            Trap tr =  Trap(stod(X), stod(Y));
            myTrap.push_back(tr);
        }
        cerr << 2 << endl;
        int cnt = 0;
        while (t--) {
            for (auto i : myArr) {
                if (i.Alive) {
                    i.step();
                    if (i.Work) {
                        bool flag = false;
                        for (auto tr : myTrap) {
                            if (tr.Alive == 1) {                                
                                if (tr.Catch(i)) {
                                    Dead << setprecision(3) << fixed << setw(8) << cp_t - t << setw(8) << tr.X << setw(8) << tr.Y;
                                    Dead << setprecision(3) << fixed << setw(8) << i.X <<  setw(8) << i.Y << ' ' << tr.Alive << endl;
                                    cnt++;
                                    flag = true;                                    
                                }
                            }
                            if (flag) {
                                cout << tr.Alive << endl;
                                break;
                            }
                        }
                    }
                }
            }
            //cout << t << endl;
        }
        cerr << 3 << endl;
        Dead << cnt << endl;
    }
    else {
        cout << "warning" << endl;
    }
    in_Point.close();
    in_Traps.close();

}
