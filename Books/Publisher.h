#ifndef PUBLISHER_H
#define PUBLISHER_H

#include<string>
#include<ostream>

using namespace std;

class Publisher
{
    public:
        Publisher();

        Publisher(string name);

        string getName() const{return _name;};
        void setName(string name);
    protected:

    private:
        string _name;
};

ostream& operator<<(ostream& out, const Publisher& publisher);

#endif // PUBLISHER_H
