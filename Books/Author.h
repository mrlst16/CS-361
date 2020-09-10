#ifndef AUTHOR_H
#define AUTHOR_H

#include<string>
#include "Address.h"
#include "Book.h"
#include <ostream>

using namespace std;

class Author
{
    public:
        Author();

        Author(std::string name, const Address& address);

        string getName() const{return _name;};
        void setName(string name);

        const Address& getAddress() const;
        void setAddress(const Address& addr);

        int numberOfBooks() const;
        const Book* getBook(int i) const;

        void addBook(const Book* b);
        void removeBook(const Book* book);

        Author& operator=(const Author& other);
    protected:

    private:
        string _name;
        const Address& _address;

        static const int MaxBooks = 10;
        int numBooks;
        Book* books[MaxBooks];
};

ostream& operator<<(ostream& out, const Author& author);

#endif // AUTHOR_H
