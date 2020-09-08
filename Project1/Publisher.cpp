#include "Publisher.h"
#include<ostream>
#include<string>

using namespace std;

Publisher::Publisher(string name):
    _name(name) {

}


ostream& operator<<(ostream& out, const Publisher& publisher){
    out << publisher.getName();
    return out;
}
