#include "AuthorIterator.h"
#include "Author.h"

AuthorIterator::AuthorIterator()
{
}

AuthorIterator::reference AuthorIterator::operator*() const
{
    return *position;
}

AuthorIterator::pointer AuthorIterator::operator->() const{
    position;
}

AuthorIterator& AuthorIterator::operator++(){
    ++position;
    return *this;
}


AuthorIterator AuthorIterator::operator++(int){
    AuthorIterator saved = *this;
    position++;
    return saved;
}

bool AuthorIterator::operator==(const AuthorIterator& p) const{
    return position == p.position;
}

bool AuthorIterator::operator!=(const AuthorIterator& p) const{
    return position != p.position;
}

