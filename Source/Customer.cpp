#include "Customer.h"
#include <iostream>

Customer::Customer() : Person() {}
Customer::Customer(int id, string name, string phone) : Person(id, name, phone) {}
Customer::~Customer() {}

void Customer::display() const {
    cout << "  Customer | ID: " << id << " | Name: " << name << " | Phone: " << phone << endl;
}
