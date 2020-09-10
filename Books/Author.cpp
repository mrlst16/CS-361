#include "Author.h"
#include<ostream>

using namespace std;

Author::Author(string name, const Address& address):_address(address){
    _name = name;
}

ostream& operator<<(ostream& out, const Author& author){
    out << author.getName();
    return out;
}

Author& Author::operator=(const Author& other){

    throw "Not yet implemented";
    return *this;
}
