#ifndef BOOK_H
#define BOOK_H

#include <string>
#include "Author.h"
#include "Publisher.h"

using namespace std;
class Book {

public:

//    Book(
//     string& title,
//     const string& isbn,
//     const Publisher& publisher,
//     Author* authors = nullptr,
//     int numAuthors = 0
//     );

    string getTitle() const;
    void setTitle(const string& newTitle);

    const Publisher& getPublisher() const;
    void setPublisher (const Publisher& publ);

    string getISBN() const;
    void setISBN(const string& newISBN);

protected:
private:
    string _title;
    Publisher _publisher;
    string _isbn;
};

#endif // BOOK_H
