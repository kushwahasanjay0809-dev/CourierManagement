#include "Validation.h"
#include <stdexcept>

void checkName(const string& name) {
    if (name.empty() || name.length() > 30)
        throw runtime_error("Name must be 1 to 30 characters.");
    if (name.find('|') != string::npos)
        throw runtime_error("Name cannot contain the | character.");
}

void checkPhone(const string& phone) {
    if (phone.length() != 10)
        throw runtime_error("Phone must be exactly 10 digits.");
    for (size_t i = 0; i < phone.length(); i++) {
        if (phone[i] < '0' || phone[i] > '9')
            throw runtime_error("Phone must contain digits only.");
    }
}

void checkWeight(double weight) {
    if (weight <= 0 || weight > 50)
        throw runtime_error("Weight must be more than 0 and at most 50 kg.");
}

void checkDate(const string& date) {
    if (date.length() != 10 || date[2] != '-' || date[5] != '-')
        throw runtime_error("Date must look like DD-MM-YYYY (example 25-12-2026).");
    for (size_t i = 0; i < date.length(); i++) {
        if (i == 2 || i == 5) continue;
        if (date[i] < '0' || date[i] > '9')
            throw runtime_error("Date must look like DD-MM-YYYY (example 25-12-2026).");
    }
}

void checkId(int id) {
    if (id <= 0)
        throw runtime_error("ID must be a positive number.");
}
