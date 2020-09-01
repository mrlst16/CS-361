#ifndef PUBLISHER_H
#define PUBLISHER_H

#include<string>

using namespace std;

class Publisher
{
    public:
        string getName() const;
        void setName(string name);
    protected:

    private:
        string _name;
};

#endif // PUBLISHER_H
