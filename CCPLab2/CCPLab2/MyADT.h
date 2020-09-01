#pragma once
#include <string>

using namespace std;

class MyADT {
	int d1;
public:
	void f1();
	bool f2(string s) {

		return false;
	}
	bool f3(string s) const {
		
		return false;
	}
private:
	void f4();
	string* d2;
};
void f5(MyADT& w);
void f6(const MyADT& w);