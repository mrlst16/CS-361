#ifndef AUTHOR_H
#define AUTHOR_H

#include<string>
#include "Address.h"
#include "Book.h"

using namespace std;

class Author
{
    public:
        Author();

        Author(std::string name, const Address& address);

        string getName() const;
        void setName(string name);

        const Address& getAddress() const;
        void setAddress(const Address& addr);

        int numberOfBooks() const;
        Book& getBook(int i);

        void addBook(Book& b);
        void removeBook(Book& book);
    protected:

    private:
        string _name;
        const Address& _address;
};

#endif // AUTHOR_H
