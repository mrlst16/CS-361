// CCPLab2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>


using namespace std;
bool operator < (const string& one, const string& two) {
	cout << "This is a side effeect";
	return one.size() < two.size();
}

template<typename T>
bool operator < (const T& one, const T& two) {
	
	return one ;
}



int main()
{

	string f = "f";
	string ff = "FF";

	cout << "Hello World!\n";
	bool lessThan = f < ff;
	cout << lessThan;
	cin.get();
}