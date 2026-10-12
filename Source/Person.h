// Person.h - BASE class. Customer and Courier inherit from it (inheritance).
#ifndef PERSON_H
#define PERSON_H
#include <string>
using namespace std;

class Person {
protected:               // protected: derived classes can use these, outside code cannot (encapsulation)
    int id;
    string name;
    string phone;
public:
    Person();                                          // default constructor
    Person(int id, string name, string phone);         // parameterized constructor
    virtual ~Person();                                 // virtual destructor

    int getId() const;
    string getName() const;
    string getPhone() const;
    void setName(string name);                         // setters check the data (validation)
    void setPhone(string phone);

    virtual void display() const;                      // "virtual" lets derived classes replace this function
    string toLine() const;                             // text used when saving to file: id|name|phone
};

#endif
