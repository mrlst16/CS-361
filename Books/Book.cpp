#include "Book.h"
#include "Author.h"
#include "Publisher.h"
#include <ostream>
#include <iostream>
#include<vector>
#include "AuthorIterator.h"

using namespace std;



Book::Book(
        const string& title,
        const string& isbn,
        Publisher& publisher,
        Author* authors,
        int numauthors
) :
    _title(title),
    _isbn(isbn),
    _publisher(publisher)
{

    for(int i = 0; i < numauthors; i++){
        addAuthor(authors[i]);
    }
}

Book::Book(
        const string& title,
        const string& isbn,
        Publisher& publisher,
        const Author& author
) :
    _title(title),
    _isbn(isbn),
    _publisher(publisher)
{


}

Book& Book::operator=(const Book& book){
    _authors = book._authors;
    _numAuthors = book._numAuthors;
    _isbn = book._isbn;
    _publisher = book._publisher;
    _title = book._title;
    return *this;
}

void Book::addAuthor(const Author& author){
    _authors[_numAuthors] = author;
    _numAuthors++;
}

void Book::removeAuthor(const Author& author){
}

Author Book::getAuthor(int i) const{return _authors[i];}

const Publisher& Book::getPublisher() const{return _publisher;}

ostream& operator<< (ostream& out, const Book& book){
    out << book.getTitle() << ", by ";
	for (int i = 0; i < book.numberOfAuthors(); ++i)
	{
		if (i > 0)
			out << ", ";
		out << book.getAuthor(i);
	}
	out << "; " << book.getPublisher() << ", " << book.getISBN();
	return out;
}

Book::Book(
    const std::string& title,
    const std::string& isbn,
    Publisher& publisher,
    const initializer_list<Author> authors
 )
:   _title(title),
    _isbn(isbn),
    _publisher(publisher)
{
    for(auto it = authors.begin(); it != authors.end(); ++it)
        this->addAuthor(*it);
}

double Sum(std::vector<double>& v){
    double result = 0;
    for(std::vector<double>::iterator it = v.begin(); it != v.end(); ++it){
        result += *it;
    }

    return result;
}

double Sum2(std::vector<double>& v){
    double result = 0;
    std::vector<double>::iterator it = v.begin();
    while(it != v.end()){
        result += *it;
        ++it;
    }
    return result;
}

Book::iterator Book::begin(){
    AuthorIterator b;
    b.position = _authors;
    return b;
}

Book::iterator Book::end(){
    AuthorIterator b;
    //????Why and how are we adding an integer to this "dynamic array"
    //Looks like in pointer addition, you point to so many bytes or
    //"positions" ahead by adding an int to a pointer
    //This is a "logical" and not a numerical addition
    b.position = _authors+_numAuthors;
    return b;
}

template <typename Iterator>
Book::Book (std::string theTitle, const Publisher* publ,
            Iterator startAuthors, Iterator stopAuthors,
            std::string theISBN)
 : _title(theTitle), _publisher(publ),
   _numAuthors(0), _authors(new Author*[10]),
   _isbn(theISBN)
{
    for(auto it = startAuthors; it != stopAuthors; ++it)
        addAuthor(*it);
};

int main(){


    std::cout << "main" << std::endl;
}
