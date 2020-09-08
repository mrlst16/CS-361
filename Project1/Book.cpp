#include "Book.h"
#include "Author.h"
#include "Publisher.h"
#include <ostream>

using namespace std;

//Book::Book()
//:
//    _title(),
//    _publisher(nullptr),
//    _numAuthors(0)
//{
//}

Book::Book(
        const string& title,
        const string& isbn,
        const Publisher& publisher,
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
        const Publisher& publisher,
        const Author& author
) :
    _title(title),
    _isbn(isbn),
    _publisher(publisher)
{


}

void Book::addAuthor(const Author& author){

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
