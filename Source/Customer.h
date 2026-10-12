#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "Person.h"

class Customer : public Person {      // Customer IS-A Person
public:
    Customer();
    Customer(int id, string name, string phone);
    ~Customer();
    virtual void display() const;     // overrides Person::display()
};

#endif
