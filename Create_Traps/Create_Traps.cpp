#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <fstream>
#include <math.h>
#include <random>
#include <string>

using namespace std;

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

	void CreateCoord() {
		X = returnRandom(0, 50000);
		Y = returnRandom(0, 1000);
		int p = returnRandom(0, 10) % 3;
		if (p == 0) {
			Y = 1000;
		}
		if (p == 1) {
			X = 50000;
		}
		if (p == 2) {
			Y = 0;
		}
	}

public:
	double X,Y, Range;

	void Create() {
		CreateCoord();
	}

	Trap() {
		random_device device;
		random_generator_.seed(device());
		Create();
		Range = 0.5;
	}

	bool Same(Trap * other) {
		return (abs(other->X - X) < Range * 2) && (abs(other->Y - Y) < Range * 2);
	}


};


int main()
{
	int n = 20000, r = 0;
	ofstream Start("C:\\Coursace\\Coursace\\Sowing\\Traps\\start_" + to_string(n) + ".txt");
	if (!Start.is_open()) return 0;
	vector<Trap*> v;
	Start << "JSON\nTest2DStochastic" << endl;
	Start << n << endl;
	for (int i = 0; i < n; i++) {
		Trap* t = new Trap();
		bool unic = true;
		bool repeat = true;
		while (repeat) {
			for (auto i : v) {
				if (t->Same(i)) {
					unic = false;
					break;
				}
			}
			if (!unic) {
				t->Create();
				unic = true;
				r++;
			}
			else {
				repeat = false;
			}
		}
		v.push_back(t);

		Start << setprecision(3) << fixed << setw(10) << t->X << setw(10) << t->Y << endl;
		//cout << setprecision(3) << fixed << setw(10) << t->X << setw(10) << t->Y << endl;
		if (i % (n/100) == 0) {
			cout << "Genered " << i / (n / 100) << " %" << endl;
		}
	}
	cout << "Complete" << endl;

	return 0;
}
