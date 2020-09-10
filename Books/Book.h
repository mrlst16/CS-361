#ifndef BOOK_H
#define BOOK_H

#include <string>
#include "AuthorIterator.h"

class Author;
class Publisher;

using namespace std;

class Book {

public:

    typedef AuthorIterator iterator;
    typedef AuthorConstIterator const_iterator;

    Book();

    //Copy Constructor
    //If not defined, this is also created for us
    Book(const Book& book);

    Book(
        const string& title,
        const string& isbn,
        const Publisher& publisher,
        Author* authors = nullptr,
        int numauthors = 0
     );

     Book(
        const std::string& title,
        const std::string& isbn,
        const Publisher& publisher,
        const Author& author1
        );

    string getTitle() const{return _title;};
    void setTitle(const string& newTitle);

    const Publisher& getPublisher() const;
    void setPublisher (const Publisher& publ);

    string getISBN() const{return _isbn;};
    void setISBN(const string& newISBN);

    void addAuthor(const Author& author);
    void removeAuthor(const Author& author);
    Author getAuthor(int i) const;

    bool operator==(const Book& other) const;
    bool operator<(const Book& other) const;

    int numberOfAuthors() const {return _numAuthors;}

    //Iterator stuff
    iterator begin();
    const_iterator begin() const;
    iterator end();
    //???? How can this be called? Because the const looks to change the signature
    //But the same number of params remains...
    const_iterator end() const;

protected:
private:
    string _title;
    const Publisher& _publisher;
    string _isbn;
    Author* _authors;  // array of authors
    int _numAuthors;
};

ostream& operator<<(ostream& out, const Book& book);
#endif // BOOK_H
