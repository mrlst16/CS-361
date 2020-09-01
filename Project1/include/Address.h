#ifndef ADDRESS_H
#define ADDRESS_H

#include<string>

using namespace std;

class Address
{
    public:

        Author(
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
    protected:

    private:
        string _street;
        string _city;
        string _state;
        string _zip;
};

#endif // ADDRESS_H
