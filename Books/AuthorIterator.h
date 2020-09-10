#ifndef AUTHITERATOR_H
#define AUTHITERATOR_H

#include<iterator>

class Author;
class Book;
class AuthorIterator
{
    public:

        typedef std::forward_iterator_tag   iterator_category;
        typedef Author                      value_type;
        typedef ptrdiff_t                   difference_type;
        typedef value_type*                 pointer;
        typedef value_type&                 reference;

        AuthorIterator();

        //So, looks like this is the de-reference operator?
        //Get the data element at this position
        reference operator*() const;
        pointer operator->() const;

        //Move position forward one place
        AuthorIterator& operator++();
        AuthorIterator operator++(int);

        //COmparison operators
        bool operator==(const AuthorIterator&) const;
        bool operator!=(const AuthorIterator&) const;

    protected:

    private:
        Author* position;
        friend class Book;
};

//In this class, we make the value_type constant
class AuthorConstIterator
{
    public:

        typedef std::forward_iterator_tag   iterator_category;
        typedef Author                      value_type;
        typedef ptrdiff_t                   difference_type;
        typedef const value_type*           pointer;
        typedef const value_type&           reference;

        AuthorConstIterator();

        //So, looks like this is the de-reference operator?
        //Get the data element at this position
        reference operator*() const;
        pointer operator->() const;

        //Move position forward one place
        AuthorConstIterator& operator++();
        AuthorConstIterator operator++(int);

        //COmparison operators
        bool operator==(const AuthorConstIterator&) const;
        bool operator!=(const AuthorConstIterator&) const;

    protected:

    private:
        Author* position;
        friend class Book;
};

#endif // AUTHITERATOR_H
