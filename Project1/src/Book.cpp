#include "Book.h"

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
