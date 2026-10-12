#ifndef COURIER_H
#define COURIER_H
#include "Person.h"

class Courier : public Person {       // Courier IS-A Person
public:
    Courier();
    Courier(int id, string name, string phone);
    ~Courier();
    virtual void display() const;     // overrides Person::display()
};

#endif
