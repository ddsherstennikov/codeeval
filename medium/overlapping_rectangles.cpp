#include <iostream>
#include <fstream>
#include <vector>
#include <initializer_list>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;



struct Rect
{
		Rect(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}

		int x1, y1, x2, y2;

		int l_x() {return x2-x1;}
		int l_y() {return y1-y2;}
};

std::vector<std::string> split(const std::string& line)
{
	std::vector<std::string> result;

	std::stringstream lineStream(line);
	std::string cell;

	while(std::getline(lineStream,cell, ','))
	{
		result.push_back(cell);
	}
	return result;
}

int main(int argc, char* argv[])
{
	ifstream ifs(argv[1], ios::in);

	std::string line;
	while (std::getline(ifs, line))
	{
		auto vs = split(line);

		Rect a {stoi(vs[0]),stoi(vs[1]),stoi(vs[2]),stoi(vs[3])};
		Rect b {stoi(vs[4]),stoi(vs[5]),stoi(vs[6]),stoi(vs[7])};

		auto xs = {a.x1, a.x2, b.x1, b.x2};
		auto ys = {a.y1, a.y2, b.y1, b.y2};
		int minx = min<int>(xs);
		int maxx = max<int>(xs);
		int miny = min<int>(ys);
		int maxy = max<int>(ys);

		pair<int, int> coverage{maxx - minx, maxy - miny};

		bool intersect = (coverage.first <= a.l_x() + b.l_x()) && (coverage.second <= a.l_y() + b.l_y());

		cout << (intersect ? "True" : "False") << endl;
	}

	return 0;
}