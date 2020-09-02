#include "Address.h"
#include <string>

using namespace std;

Address::Address(string street, string city, string state, string zip){
    _street = street;
    _city = city;
    _state = state;
    _zip = zip;
}
