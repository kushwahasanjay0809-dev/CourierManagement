#include "Person.h"
#include "Validation.h"
#include <iostream>

Person::Person() {
    id = 0;
    name = "None";
    phone = "0000000000";
}

Person::Person(int id, string name, string phone) {
    checkId(id);
    this->id = id;
    setName(name);
    setPhone(phone);
}

Person::~Person() {}

int Person::getId() const { return id; }
string Person::getName() const { return name; }
string Person::getPhone() const { return phone; }

void Person::setName(string name) {
    checkName(name);
    this->name = name;
}

void Person::setPhone(string phone) {
    checkPhone(phone);
    this->phone = phone;
}

void Person::display() const {
    cout << "  Person   | ID: " << id << " | Name: " << name << " | Phone: " << phone << endl;
}

string Person::toLine() const {
    return to_string(id) + "|" + name + "|" + phone;
}
