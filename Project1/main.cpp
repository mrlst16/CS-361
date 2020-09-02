#include <iostream>
#include "Author.h"
#include "Address.h"
#include "Publisher.h"
#include <string>

using namespace std;

int main()
{
    Author weiss (
        "Weiss, Mark",
        Address("21 Nowhere Dr.", "Podunk", "NY", "01010")
    );

    Author doe (
        "Doe, John",
        Address("212 Baker St.", "Peoria", "IL", "12345")
    );

    Author smith (
        "Smith, Jane",
        Address("47 Scenic Ct.", "Oahu", "HA", "54321")
    );

    Publisher prenticeHall = Publisher("prenticeHall");
    Publisher macmillan = Publisher("macmillan");

    Author textAuthors[] = {weiss};

    Book text361 (
                  "Data Structures and Algorithms in C++",
                    "013284737X",
                    macmillan,
                    weiss
                    );


    Author recipeAuthors[] = {doe, smith};
    Book recipes (
                    "Cooking with Gas",
                    "0-124-46821",
                    prenticeHall,
                    recipeAuthors,
                    2
                    );

    return 0;
}
