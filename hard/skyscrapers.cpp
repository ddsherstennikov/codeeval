#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <queue>

using namespace std;



struct Rect
{
	int l;
	int h;
	int r;
};

template<class Rect>
struct myless
{
	bool operator()(const Rect &lhs, const Rect &rhs) const
	{
		return lhs.h < rhs.h;
	}
};

std::vector<std::string> split(const std::string& line, char del)
{
	std::vector<std::string> result;

	std::stringstream lineStream(line);
	std::string cell;

	while (std::getline(lineStream, cell, del))
	{
		result.push_back(cell);
	}
	return result;
}



vector<int> skyline(vector<Rect>& vr)
{
	vector<int> res;

	// critical points: 
	//		int point coord on 1-dimensional axis
	//		q of Rects "above" this point in maxheap sorted by h (height)
	vector<pair<int, Rect>> critp;

	// gather critical points (l and r of each rect)
	for (auto R : vr)
	{
		critp.push_back(make_pair(R.l, R));
		critp.push_back(make_pair(R.r, R));
	}

	// sort them by value on 1-dimensional axis
	sort(critp.begin(), critp.end(), [](const pair<int, Rect>& pp1, const pair<int, Rect>& pp2) { return pp1.first < pp2.first; });

	// q of rects in maxheap on r (rect's right edge)
	priority_queue<Rect, vector<Rect>, myless<Rect>> active;
	active.push(Rect({ critp[0].first, 0, critp.back().first + 1 }));

	// leave unique points (on absciss) with greatest height
	pair<int, int> last_xy = { 0, 0 };
	for (auto it = critp.begin(); it != critp.end(); it++)
	{
		if (last_xy.first == it->first && it->first == it->second.r && last_xy.second >= it->second.h)
			it = critp.erase(it);
		else if (last_xy.first == it->first && it->first == it->second.l)
			it = critp.erase(it - 1) + 1;

		last_xy = { it->first, it->second.h };
	}
	
	for (size_t i=0; i<critp.size(); i++)
	{
		active.push(critp[i].second);

		while (!active.empty() && active.top().r <= critp[i].first)
			active.pop();

		if (res.empty() || active.top().h != res.back())
		{
			res.push_back(critp[i].first);
			res.push_back(active.top().h);
		}
	}
	
	return res;
}




int main(int argc, char* argv[])
{
	ifstream ifs(argv[1], ios::in);

	std::string line;
	while (std::getline(ifs, line))
	{
		vector<Rect> v;

		auto vs = split(line, ';');

		for (auto& s : vs)
		{
			auto vss = split(s, ',');
			
			Rect rct;
				
			rct.l = stoi(vss[0].substr(1));
			rct.h = stoi(vss[1]);
			rct.r = stoi(vss[2].substr(0, vss[2].size() - 1));

			v.push_back(rct);
		}

		auto sky_v = skyline(v);

		for (int c : sky_v)
			cout << c << " ";

		cout << endl;
	}

}

