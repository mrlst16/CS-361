#ifndef ADDRESS_H
#define ADDRESS_H

#include<string>

using namespace std;

class Address
{
    public:

        Address();
        Address(
           string street,
           string city,
           string state,
           string zip
           );

        string getStreet() const;
        void setStreet (std::string theStreet);

        string getCity() const;
        void setCity (std::string theCity);

        string getState() const;
        void setState (std::string theState);

        string getZip() const;
        void setZip (std::string theZip);

        bool operator==(const Address& addr) const;
    protected:

    private:
        string _street;
        string _city;
        string _state;
        string _zip;
};

//The output stream operator is decalred OUTSIDE the class
//The reason being is that the stream is on the LEFT side.
//Normally, a function is called by the oobject on the right
//E.G addr.SetZip("15106") vs cout << addr
std::ostream& operator<<(std::ostream& stream, const Address& addr);
#endif // ADDRESS_H
