#include "Courier.h"
#include <iostream>

Courier::Courier() : Person() {}
Courier::Courier(int id, string name, string phone) : Person(id, name, phone) {}
Courier::~Courier() {}

void Courier::display() const {
    cout << "  Courier  | ID: " << id << " | Name: " << name << " | Phone: " << phone << endl;
}
