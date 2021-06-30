#include <iostream>
#include <string>
#include "vector.hpp"

struct TValue {
	int Day;
	int Month;
	int Year;
	std::string Data;

	TValue() : Day(1), Month(1), Year(1) {};
};

void Sort(TVector<struct TValue> &v) {
	
	TVector<int> c(10000);
	c.Nul();
	TVector<int> c2(32);
	c2.Nul();
	TVector<int> c3(32);
	c3.Nul();
	TVector<struct TValue> v2(v.Capacity);
	
	for(int i = 0; i < v.Capacity; ++i) {
		c3.Data[(v.Data[i]).Day] += 1;
	}

	for(int i = 1; i < c3.Capacity; ++i) {
		c3.Data[i] += c3.Data[i - 1];
	}

	for(int i = v.Capacity - 1; i >= 0; --i) {
		(v2.Data[c3.Data[(v.Data[i]).Day] - 1]) = v.Data[i];
		c3.Data[(v.Data[i]).Day] -= 1;
	}

	for(int i = 0; i < v.Capacity; ++i) {
		v.Data[i] = v2.Data[i];
	}

	for(int i = 0; i < v.Capacity; ++i) {
		c2.Data[(v.Data[i]).Month] += 1;
	}

	for(int i = 1; i < c2.Capacity; ++i) {
		c2.Data[i] += c2.Data[i - 1];
	}

	for(int i = v.Capacity - 1; i >= 0; --i) {
		(v2.Data[c2.Data[(v.Data[i]).Month]-1]) = v.Data[i];
		c2.Data[(v.Data[i]).Month] -= 1;
	}

	for(int i = 0; i < v.Capacity; ++i) {
		v.Data[i] = v2.Data[i];
	}

	for(int i = 0; i < v.Capacity; ++i) {
		c.Data[(v.Data[i]).Year] += 1;
	}

	for(int i = 1; i < c.Capacity; ++i) {
		c.Data[i] += c.Data[i - 1];
	}

	for(int i = v.Capacity - 1; i >= 0; --i) {
		(v2.Data[c.Data[(v.Data[i]).Year] - 1]) = v.Data[i];
		c.Data[(v.Data[i]).Year] -= 1;
	}

	for(int i = 0; i < v.Capacity; ++i) {
		v.Data[i] = v2.Data[i];
	}
}



void Add(TVector<struct TValue> &v, int day, int month, int year, std::string d) {
    v.Push();
    (v.Data[v.Capacity - 1]).Day = day;
    (v.Data[v.Capacity - 1]).Month = month;
    (v.Data[v.Capacity - 1]).Year = year;
    (v.Data[v.Capacity - 1]).Data = d;
}

int main() {
    TVector<struct TValue> v;
    int day = 0;
    int month = 0;
    int year = 0;
    std::string d,d2;
    int u = 0;
    std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
    while(std::cin >> d2 >> d) {  
    	for(int i = 0; i < d2.size(); ++i) {
    	
    		if(d2[i] == '.') {
    			u += 1;
    			continue;
    		}

	    	if(u == 0) {
	    		day = day * 10 + d2[i] - '0';
	    	}

	    	if(u == 1) {
	    		month = month * 10 + d2[i] - '0';
	    	}

	    	if(u == 2) {
	    		year = year * 10 + d2[i] - '0';
	    	}

    	}
	    d2 = d2 + " " + d;
	    Add(v,day,month,year,d2);
	    day = 0;
	    month = 0;
	    year = 0;
	    u = 0;
	}	

	Sort(v);
	for(int i = 0; i < v.Capacity; ++i) {
		std::cout << (v.Data[i]).Data << " " << std::endl;
    }

}
