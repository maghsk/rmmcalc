#include <cstdlib> 
#include <iostream> 
#include <string>
#include <cstring>
#include <fstream>
#include <map>
#include <utility>

using namespace std;

ifstream din;
map<string, int> chart;
string s;
char tmpys[10];

int get_ram()
{
	din.open("RAM.data");
	if(!din.is_open())
	{
		cout << "Cannot find RAM.data! Please copy it! " << endl;
		return 0;
	}
	string tmp;
	int mass;
	double sj;
	while(!din.eof())
	{
		din >> tmp >> sj;
		mass = sj * 10;
		chart[tmp] = mass;
	}
	return 1;
}

int get_num(int *start)
{
	if(*start >= s.length()) return 1;
	int ret = 0;
	while(*start < s.length() && '0' <= s.at(*start) && s.at(*start) <= '9')
	{
		ret = ret * 10 + s.at(*start) - '0';
		*start = *start + 1;
	}
	if(!ret) return 1;
	return ret;
}

char *get_ys(int *start)
{
	int i = 1;
	memset(tmpys, 0, sizeof(tmpys));
	tmpys[0] = s.at(*start);
	*start = *start + 1; 
	while(*start < s.length() && 'a' <= s.at(*start) && s.at(*start) <= 'z')
	{
		tmpys[i] = s.at(*start);
		++ i;
		*start = *start + 1; 
	}
	return tmpys;
}

int m(string x)
{
	return chart[x];
}

int get_mass()
{
	int p = 0, tot, ret = 0, gs, tmp, tmptot;
	string ys;
	tot = get_num(&p);
	while(p < s.length())
	{
		if(s.at(p) == '(')
		{
			++ p;
			tmp = 0;
			while(s.at(p) != ')')
			{
				ys = get_ys(&p);
				gs = get_num(&p);
				tmp += m(ys) * gs;
			}
			++ p;
			tmptot = get_num(&p);
			ret += tmp * tmptot;
		}
		else
		{
			ys = get_ys(&p);
			gs = get_num(&p);
			ret += m(ys) * gs;
		}
	}
	return ret * tot;
}

int main()
{
	chart.clear();
	while(true)
	{
		s.clear();
		memset(tmpys, 0, sizeof(tmpys));
		if(!get_ram())
		{
			return 0;
		}
		cin >> s;
		if(s == "stop")return 0;
		int ms = get_mass();
		if(ms % 10)
		{
			cout << ms / 10 << "." << ms % 10;
		}
		else
		{
			cout << ms / 10;
		}
		cout << endl;
	}
	return 0;
}
