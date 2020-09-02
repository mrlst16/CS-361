#ifndef BOOK_H
#define BOOK_H

#include <string>

class Author;
class Publisher;

using namespace std;
class Book {

public:
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

    string getTitle() const;
    void setTitle(const string& newTitle);

    const Publisher& getPublisher() const;
    void setPublisher (const Publisher& publ);

    string getISBN() const;
    void setISBN(const string& newISBN);

protected:
private:
    string _title;
    const Publisher& _publisher;
    string _isbn;
};
#endif // BOOK_H
