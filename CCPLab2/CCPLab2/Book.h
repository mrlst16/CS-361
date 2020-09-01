#pragma once

#include<string>;

using namespace std;

//This just allows us to alias a type as another name
typedef string CityName;
using CityNameAlias = string;

class Book
{
public:
	string getTitle() const;
	void setTitle(string title);

	string getISBN() const;
	void setISBN(string isbn);
};

