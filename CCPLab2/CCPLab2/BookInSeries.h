#pragma once

#include <string>;
#include "Book.h";

using namespace std;

class BookInSeries: public Book
{
public:
	string getSeriesTitle() const;
	void setSeriesTitle(string title);

	int getVolume() const;
	void setVloume(int volume);

private:
	string seriesTitle;
	int volume;
};

