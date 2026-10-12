// Validation.h - small functions that check user input. They throw an exception if the input is bad.
#ifndef VALIDATION_H
#define VALIDATION_H
#include <string>
using namespace std;

void checkName(const string& name);    // 1-30 characters, no '|'
void checkPhone(const string& phone);  // exactly 10 digits
void checkWeight(double weight);       // more than 0 and at most 50 kg
void checkDate(const string& date);    // format DD-MM-YYYY
void checkId(int id);                  // must be positive

#endif
